#include <glew.h>
#include <glfw3.h>

#include <mat4x4.hpp>
#include <gtx\transform.hpp>

#include <thread>
#include <chrono>
#include <cmath>

#include "ShaderParser.h"
#include "Cube.cpp"

int cubeCollCheckX(float currPosX, float nextPosX, float currPosZ, float currPosY, int count, Cube cube[]) {
	for (int i = 0; i < count; ++i) {
		if (!cube[i].collisionCheckX(currPosX, nextPosX, currPosZ, currPosY)) {
			return false;
		}
	}
	return true;
}
int cubeCollCheckZ(float currPosZ, float nextPosZ, float currPosX, float currPosY, int count, Cube cube[]) {
	for (int i = 0; i < count; ++i) {
		if (!cube[i].collisionCheckZ(currPosZ, nextPosZ, currPosX, currPosY)) {
			return false;
		}
	}
	return true;
}
bool cubeCollCheckY(float currPosX, float currPosZ, float nextPosY, int count, Cube cube[]) {
	for (int i = 0; i < count; ++i) {
		if (!cube[i].collisionCheckY(currPosX, currPosZ, nextPosY)) {
			return false;
		}
	}
	return true;
}

int main() {
	glfwInit();

	GLFWwindow* wind = glfwCreateWindow(1000, 800, "airstream", 0, 0);
	glfwMakeContextCurrent(wind);

	glfwSetWindowSizeLimits(wind, 1000, 800, 1000, 800);

	glfwSetWindowPos(wind, 70, 50);

	glewInit();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Shader shader("v.shader", "f.shader");

	//CAMERA
	glm::vec3 cameraLocation = glm::vec3(1.7f, 0.0f, 1.7f);
	float angle = 3.925f;
	glm::vec3 pointOfView = glm::vec3(cos(angle), 0.0f, sin(angle));
	glm::vec3 pointOfViewTop = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4x4 modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation , pointOfViewTop);
	glm::mat4x4 perspProjection = glm::perspective(glm::radians(90.0f), 1000.0f/ 800.0f, 0.1f, 10.0f);

	//MATRICES SETUP
	shader.initMatrix(modelTransf, "modelTransf");
	shader.initMatrix(perspProjection, "perspProjection");

	//CUBES INITIALIZATION
	Cube cube[3] = {
		Cube(
			0.9f, 0.1f, -0.9f, 0.4f,
			0.3f, 0.0f, 0.0f,
			0.3f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.3f,
			0.0f, 0.0f, 0.3f,
			0.0f, 0.3f, 0.0f,
			0.0f, 0.3f, 0.0f
		),

		Cube(
			-0.9f, -0.1f, 1.2f, 0.2f,
			0.0f, 0.0f, 0.7f,
			0.0f, 0.0f, 0.7f,
			0.7f, 0.0f, 0.0f,
			0.7f, 0.0f, 0.0f,
			0.0f, 0.7f, 0.0f,
			0.0f, 0.7f, 0.0f
		),

		Cube(
			-0.9f, 0.0f, -0.7f, 0.3f,
			0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.0f, 0.0f, 0.5f,
			0.0f, 0.0f, 0.5f
		)
	};

	//UGLY BROWN FLOOR 
	float floorSquareCoords[] = {
		-2.0f, -0.3f, -2.0f,
		-2.0f, -0.3f, 2.0f,
		2.0f, -0.3f, 2.0f,
		2.0f, -0.3f, -2.0f

	};
	float floorColors[] = {
		0.2f, 0.2f, 0.0f,
		0.2f, 0.2f, 0.0f,
		0.2f, 0.2f, 0.0f,
		0.2f, 0.2f, 0.0f
	};

	unsigned int floorArray;
	glGenVertexArrays(1, &floorArray);
	glBindVertexArray(floorArray);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	unsigned int floorBuffer[2];
	glGenBuffers(2, floorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, floorBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, floorSquareCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glBindBuffer(GL_ARRAY_BUFFER, floorBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, floorColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	int cubeCount = 3;
	while (!glfwWindowShouldClose(wind)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetKey(wind, GLFW_KEY_W)) {
			cameraLocation = glm::vec3(
				(cubeCollCheckX(cameraLocation[0], cameraLocation[0] - (0.01f * -pointOfView[0]), cameraLocation[2], cameraLocation[1], cubeCount, cube) ? cameraLocation[0] - (0.01f * -pointOfView[0])  :  cameraLocation[0]),
				cameraLocation[1],
				(cubeCollCheckZ(cameraLocation[2], cameraLocation[2] - (0.01f * -pointOfView[2]), cameraLocation[0], cameraLocation[1], cubeCount, cube) ? cameraLocation[2] - (0.01f * -pointOfView[2]) : cameraLocation[2]));

			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}
		if (glfwGetKey(wind, GLFW_KEY_S)) {
			cameraLocation = glm::vec3(
				(cubeCollCheckX(cameraLocation[0], cameraLocation[0] + (0.01 * -pointOfView[0]), cameraLocation[2], cameraLocation[1], cubeCount, cube) ? cameraLocation[0] + (0.01 * -pointOfView[0]) : cameraLocation[0]),
				cameraLocation[1],
				(cubeCollCheckZ(cameraLocation[2], cameraLocation[2] + (0.01f * -pointOfView[2]), cameraLocation[0], cameraLocation[1], cubeCount, cube) ? cameraLocation[2] + (0.01f * -pointOfView[2]) : cameraLocation[2])
			);

			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}
		if (glfwGetKey(wind, GLFW_KEY_A)) {
			cameraLocation = glm::vec3(
				(cubeCollCheckX(cameraLocation[0], cameraLocation[0] - (0.01 * -pointOfView[2]), cameraLocation[2], cameraLocation[1], cubeCount, cube) ? cameraLocation[0] - (0.01 * -pointOfView[2]) : cameraLocation[0]),
				cameraLocation[1],
				(cubeCollCheckZ(cameraLocation[2], cameraLocation[2] + (0.01 * -pointOfView[0]), cameraLocation[0], cameraLocation[1], cubeCount, cube) ? cameraLocation[2] + (0.01 * -pointOfView[0]) : cameraLocation[2])
			);

			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");

		}
		if (glfwGetKey(wind, GLFW_KEY_D)) {
			cameraLocation = glm::vec3(
				(cubeCollCheckX(cameraLocation[0], cameraLocation[0] + (0.01 * -pointOfView[2]), cameraLocation[2], cameraLocation[1], cubeCount, cube) ? cameraLocation[0] + (0.01 * -pointOfView[2]) : cameraLocation[0]),
				cameraLocation[1],
				(cubeCollCheckZ(cameraLocation[2], cameraLocation[2] - (0.01 * -pointOfView[0]), cameraLocation[0], cameraLocation[1], cubeCount, cube) ? cameraLocation[2] - (0.01 * -pointOfView[0]) : cameraLocation[2])
			);
			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");

		}

		if (glfwGetKey(wind, GLFW_KEY_RIGHT)) {
			angle += 0.04f;
			if (angle > 6.28f) {
				angle = 0.0f;
			}
			pointOfView = glm::vec3(cos(angle), pointOfView[1], sin(angle));

			modelTransf = glm::lookAt(cameraLocation, cameraLocation + pointOfView, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}
		if (glfwGetKey(wind, GLFW_KEY_LEFT)) {
			angle -= 0.04f;
			if (angle < 0.0f) {
				angle = 6.28f;
			}
			pointOfView = glm::vec3(cos(angle), pointOfView[1], sin(angle));

			modelTransf = glm::lookAt(cameraLocation, cameraLocation + pointOfView, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}
		if (glfwGetKey(wind, GLFW_KEY_DOWN)) {
			if (cameraLocation[1] < 2.0f) {
				pointOfView = glm::vec3(pointOfView[0], pointOfView[1] - 0.01f, pointOfView[2]);
				cameraLocation = glm::vec3(cameraLocation[0], cameraLocation[1] + 0.01f, cameraLocation[2]);

				if (cameraLocation[1] > 2.0f) {
					cameraLocation[1] = 2.0f;
					pointOfView[1] = -2.0f;
				}

				modelTransf = glm::lookAt(cameraLocation, cameraLocation + pointOfView, pointOfViewTop);
				shader.initMatrix(modelTransf, "modelTransf");
			}
		}
		if (glfwGetKey(wind, GLFW_KEY_UP)) {
			if (cubeCollCheckY(cameraLocation[0], cameraLocation[2], cameraLocation[1] - 0.3f - 0.01f, cubeCount, cube)) {
				if (cameraLocation[1] > 0.0f) {
					pointOfView = glm::vec3(pointOfView[0], pointOfView[1] + 0.01f, pointOfView[2]);
					cameraLocation = glm::vec3(cameraLocation[0], cameraLocation[1] - 0.01f, cameraLocation[2]);

					if (cameraLocation[1] < 0.0f) {
						cameraLocation[1] = 0.0f;
						pointOfView[1] = 0.0f;
					}

					modelTransf = glm::lookAt(cameraLocation, cameraLocation + pointOfView, pointOfViewTop);
					shader.initMatrix(modelTransf, "modelTransf");
				}
			}
		}

		if (glfwGetKey(wind, GLFW_KEY_ESCAPE)) {
			return 0;
		}

		glBindVertexArray(floorArray);
		glDrawArrays(GL_QUADS, 0, 4);

		for (int i = 0; i < cubeCount; ++i) {
			cube[i].drawIt();
		}

		glfwPollEvents();
		glfwSwapBuffers(wind);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
	}

	return 0;
}