#include <glew.h>
#include <glfw3.h>

#include <mat4x4.hpp>
#include <gtx\transform.hpp>

#include <thread>
#include <chrono>
#include <math.h>

#include "ShaderParser.h"

int main() {
	glfwInit();

	GLFWwindow* wind = glfwCreateWindow(500, 500, "airstream", 0, 0);
	glfwMakeContextCurrent(wind);

	glewInit();

	glEnable(GL_CULL_FACE);

	Shader shader("C:\\Users\\User\\Desktop\\Snare\\Программы\\Repository\\Projection attempt\\v.shader",
		"C:\\Users\\User\\Desktop\\Snare\\Программы\\Repository\\Projection attempt\\f.shader");

	//CAMERA
	glm::vec3 cameraLocation = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 pointOfView = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 pointOfViewTop = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4x4 modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation , pointOfViewTop);

	glm::mat4x4 perspProjection = glm::perspective(glm::radians(90.0f), 500.0f/500.0f, 0.1f, 20.0f);

	//MATRICES SETUP
	shader.initMatrix(modelTransf, "modelTransf");
	shader.initMatrix(perspProjection, "perspProjection");


	//FIRST CUBE
	float cX = 0.5f, cY = 0.0f, cZ = 0.0f;
	float halfSide = 0.3f;
	float cvc[8][3] = {
		{cX - halfSide, cY - halfSide, cZ + halfSide}, //0
		{cX + halfSide, cY - halfSide, cZ + halfSide}, //1
		{cX + halfSide, cY + halfSide, cZ + halfSide}, //2
		{cX - halfSide, cY + halfSide, cZ + halfSide}, //3

		{cX - halfSide, cY - halfSide, cZ - halfSide}, //4
		{cX + halfSide, cY - halfSide, cZ - halfSide}, //5
		{cX + halfSide, cY + halfSide, cZ - halfSide}, //6
		{cX - halfSide, cY + halfSide, cZ - halfSide}  //7
	};
	float cubeCoords[72] = {
		cvc[0][0], cvc[0][1], cvc[0][2],	//FORWARD (UGLY-PINK)
		cvc[1][0], cvc[1][1], cvc[1][2],
		cvc[2][0], cvc[2][1], cvc[2][2],
		cvc[3][0], cvc[3][1], cvc[3][2],

		cvc[7][0], cvc[7][1], cvc[7][2],	//BACKWARD (red)
		cvc[6][0], cvc[6][1], cvc[6][2],
		cvc[5][0], cvc[5][1], cvc[5][2],
		cvc[4][0], cvc[4][1], cvc[4][2],

		cvc[3][0], cvc[3][1], cvc[3][2],	//TOP (green)
		cvc[2][0], cvc[2][1], cvc[2][2],
		cvc[6][0], cvc[6][1], cvc[6][2],
		cvc[7][0], cvc[7][1], cvc[7][2],

		cvc[4][0], cvc[4][1], cvc[4][2],	//BOTTOM (blue)
		cvc[5][0], cvc[5][1], cvc[5][2],
		cvc[1][0], cvc[1][1], cvc[1][2],
		cvc[0][0], cvc[0][1], cvc[0][2],

		cvc[4][0], cvc[4][1], cvc[4][2],	//LEFT (yellow)
		cvc[0][0], cvc[0][1], cvc[0][2],
		cvc[3][0], cvc[3][1], cvc[3][2],
		cvc[7][0], cvc[7][1], cvc[7][2],

		cvc[6][0], cvc[6][1], cvc[6][2],	//RIGHT (purple)
		cvc[2][0], cvc[2][1], cvc[2][2],
		cvc[1][0], cvc[1][1], cvc[1][2],
		cvc[5][0], cvc[5][1], cvc[5][2],

	};
	
	//SECOND CUBE
	float cX2 = -0.5f, cY2 = 0.0f, cZ2 = 0.0f;
	float cvc2[8][3] = {
		{cX2 - halfSide, cY2 - halfSide, cZ2 + halfSide}, //0
		{cX2 + halfSide, cY2 - halfSide, cZ2 + halfSide}, //1
		{cX2 + halfSide, cY2 + halfSide, cZ2 + halfSide}, //2
		{cX2 - halfSide, cY2 + halfSide, cZ2 + halfSide}, //3

		{cX2 - halfSide, cY2 - halfSide, cZ2 - halfSide}, //4
		{cX2 + halfSide, cY2 - halfSide, cZ2 - halfSide}, //5
		{cX2 + halfSide, cY2 + halfSide, cZ2 - halfSide}, //6
		{cX2 - halfSide, cY2 + halfSide, cZ2 - halfSide}  //7
	};
	float cubeCoords2[72] = {

		cvc2[4][0], cvc2[4][1], cvc2[4][2],	//LEFT (yellow)
		cvc2[0][0], cvc2[0][1], cvc2[0][2],
		cvc2[3][0], cvc2[3][1], cvc2[3][2],
		cvc2[7][0], cvc2[7][1], cvc2[7][2],

		cvc2[0][0], cvc2[0][1], cvc2[0][2],	//FORWARD (UGLY-PINK)
		cvc2[1][0], cvc2[1][1], cvc2[1][2],
		cvc2[2][0], cvc2[2][1], cvc2[2][2],
		cvc2[3][0], cvc2[3][1], cvc2[3][2],

		cvc2[6][0], cvc2[6][1], cvc2[6][2],	//RIGHT (purple)
		cvc2[2][0], cvc2[2][1], cvc2[2][2],
		cvc2[1][0], cvc2[1][1], cvc2[1][2],
		cvc2[5][0], cvc2[5][1], cvc2[5][2],

		cvc2[7][0], cvc2[7][1], cvc2[7][2],	//BACKWARD (red)
		cvc2[6][0], cvc2[6][1], cvc2[6][2],
		cvc2[5][0], cvc2[5][1], cvc2[5][2],
		cvc2[4][0], cvc2[4][1], cvc2[4][2],

		cvc2[3][0], cvc2[3][1], cvc2[3][2],	//TOP (green)
		cvc2[2][0], cvc2[2][1], cvc2[2][2],
		cvc2[6][0], cvc2[6][1], cvc2[6][2],
		cvc2[7][0], cvc2[7][1], cvc2[7][2],

		cvc2[4][0], cvc2[4][1], cvc2[4][2],	//BOTTOM (blue)
		cvc2[5][0], cvc2[5][1], cvc2[5][2],
		cvc2[1][0], cvc2[1][1], cvc2[1][2],
		cvc2[0][0], cvc2[0][1], cvc2[0][2],

	};

	//COLORS SETUP
	float cubeColors[72]{
		1.0f, 0.4f, 0.4f,	//UGLY-PINK
		1.0f, 0.4f, 0.4f,
		1.0f, 0.4f, 0.4f,
		1.0f, 0.4f, 0.4f,

		1.0f, 0.0f, 0.0f,	//RED
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,	//GREEN
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 1.0f,	//BLUE DA BU DE DA BU DAE
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f,	//YELLOW
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 1.0f,	//PURPLE
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f
	};

	//INITIALIZING VERTICES FOR CUBES
	unsigned int vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	unsigned int buffer[2];
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72 + 1, cubeCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72 + 1, cubeColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	unsigned int vertexArray2;
	glGenVertexArrays(1, &vertexArray2);
	glBindVertexArray(vertexArray2);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	unsigned int buffer2[2];
	glGenBuffers(2, buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72 + 1, cubeCoords2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72 + 1, cubeColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	

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



	while (!glfwWindowShouldClose(wind)) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(wind, GLFW_KEY_W)) {
			cameraLocation = glm::vec3(cameraLocation[0] - (0.01 * -pointOfView[0]), cameraLocation[1], cameraLocation[2] - (0.01f * -pointOfView[2]));
			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}
		if (glfwGetKey(wind, GLFW_KEY_S)) {
			cameraLocation = glm::vec3(cameraLocation[0] + (0.01 * -pointOfView[0]), cameraLocation[1], cameraLocation[2] + (0.01 * -pointOfView[2]));
			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}
		if (glfwGetKey(wind, GLFW_KEY_LEFT)) {
			cameraLocation = glm::vec3(cameraLocation[0] - (0.01 * -pointOfView[2]), cameraLocation[1], cameraLocation[2] + (0.01 * -pointOfView[0]));
			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");

		}
		if (glfwGetKey(wind, GLFW_KEY_RIGHT)) {
			cameraLocation = glm::vec3(cameraLocation[0] + (0.01 * -pointOfView[2]), cameraLocation[1], cameraLocation[2] - (0.01 * -pointOfView[0]));
			modelTransf = glm::lookAt(cameraLocation, pointOfView + cameraLocation, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");

		}
		if (glfwGetKey(wind, GLFW_KEY_A)) {
			if (((pointOfView[0] > -1.0f) && (pointOfView[0] <= 0.0f))&& (pointOfView[2] < 0.0f)) {
				pointOfView = glm::vec3(pointOfView[0] - 0.025f, pointOfView[1], pointOfView[2] + 0.025f);

				if ((pointOfView[0] < -1.0f) && (pointOfView[2] > 0.0f)) {
					pointOfView[0] = -1.0f;
					pointOfView[2] = 0.0f;
				}
			}
			else if ((pointOfView[0] <= 0.0f) && (pointOfView[2] < 1.0f)) {
				pointOfView = glm::vec3(pointOfView[0] + 0.025f, pointOfView[1], pointOfView[2] + 0.025f);

				if ((pointOfView[0] > 0.0f) && (pointOfView[2] > 1.0f)) {
					pointOfView[0] = 0.0f;
					pointOfView[2] = 1.0f;
				}
			}
			else if ((pointOfView[0] <= 1.0f) && (pointOfView[2] > 0.0f)) {
				pointOfView = glm::vec3(pointOfView[0] + 0.025f, pointOfView[1], pointOfView[2] - 0.025f);

				if ((pointOfView[0] > 1.0f) && (pointOfView[2] < 0.0f)) {
					pointOfView[0] = 1.0f;
					pointOfView[2] = 0.0f;
				}
			}
			else if ((pointOfView[0] > 0.0f) && (pointOfView[2] > -1.0f)) {
				pointOfView = glm::vec3(pointOfView[0] - 0.025f, pointOfView[1], pointOfView[2] - 0.025f);

				if ((pointOfView[0] < 0.0f) && (pointOfView[2] < -1.0f)) {
					pointOfView[0] = 0.0f;
					pointOfView[2] = -1.0f;
				}

				if (pointOfView[0] < 0.025f) {
					pointOfView[0] = 0.0f;
					pointOfView[2] = -1.0f;
				}
			}
			modelTransf = glm::lookAt(cameraLocation, cameraLocation + pointOfView, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}
		if (glfwGetKey(wind, GLFW_KEY_D)) {
			if (((pointOfView[0] < 1.0f) && (pointOfView[0] >= 0.0f)) && (pointOfView[2] < 0.0f)) {
				pointOfView = glm::vec3(pointOfView[0] + 0.025f, pointOfView[1], pointOfView[2] + 0.025f);

				if ((pointOfView[0] > 1.0f) && (pointOfView[2] > 0.0f)) {
					pointOfView[0] = 1.0f;
					pointOfView[2] = 0.0f;
				}
			}
			else if ((pointOfView[0] >= 0.0f) && (pointOfView[2] < 1.0f)) {
				pointOfView = glm::vec3(pointOfView[0] - 0.025f, pointOfView[1], pointOfView[2] + 0.025f);

				if ((pointOfView[0] < 0.0f) && (pointOfView[2] > 1.0f)) {
					pointOfView[0] = 0.0f;
					pointOfView[2] = 1.0f;
				}
			}
			else if ((pointOfView[0] >= -1.0f) && (pointOfView[2] > 0.0f)) {
				pointOfView = glm::vec3(pointOfView[0] - 0.025f, pointOfView[1], pointOfView[2] - 0.025f);

				if ((pointOfView[0] <-1.0f) && (pointOfView[2] < 0.0f)) {
					pointOfView[0] = -1.0f;
					pointOfView[2] = 0.0f;
				}
			}
			else if ((pointOfView[0] <= 0.0f) && (pointOfView[2] > -1.0f)) {
				pointOfView = glm::vec3(pointOfView[0] + 0.025f, pointOfView[1], pointOfView[2] - 0.025f);

				if ((pointOfView[0] > 0.0f) && (pointOfView[2] < -1.0f)) {
					pointOfView[0] = 0.0f;
					pointOfView[2] = -1.0f;
				}

				if (pointOfView[0] > -0.025f) {
					pointOfView[0] = 0.0f;
					pointOfView[2] = -1.0f;
				}
			}
			modelTransf = glm::lookAt(cameraLocation, cameraLocation + pointOfView, pointOfViewTop);
			shader.initMatrix(modelTransf, "modelTransf");
		}

		if (glfwGetKey(wind, GLFW_KEY_ESCAPE)) {
			return 0;
		}

		float distance = sqrt((cameraLocation[0] - cX) * (cameraLocation[0] - cX) + (cameraLocation[2] - cZ) * (cameraLocation[2] - cZ));
		float distance2 = sqrt((cameraLocation[0] - cX2) * (cameraLocation[0] - cX2) + (cameraLocation[2] - cZ2) * (cameraLocation[2] - cZ2));

		glBindVertexArray(floorArray);
		glDrawArrays(GL_QUADS, 0, 4);

		if (distance > distance2) {
			glBindVertexArray(vertexArray);
			glDrawArrays(GL_QUADS, 0, 24);
			glBindVertexArray(vertexArray2);
			glDrawArrays(GL_QUADS, 0, 24);
		}
		else {
			glBindVertexArray(vertexArray2);
			glDrawArrays(GL_QUADS, 0, 24);
			glBindVertexArray(vertexArray);
			glDrawArrays(GL_QUADS, 0, 24);
		}
		
		glfwPollEvents();
		glfwSwapBuffers(wind);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
	}







	return 0;
}