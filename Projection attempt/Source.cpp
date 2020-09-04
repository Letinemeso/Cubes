#include <glew.h>
#include <glfw3.h>

#include <mat4x4.hpp>
#include <gtx\transform.hpp>

#include <thread>
#include <chrono>

#include "ShaderParser.h"

int main() {
	glfwInit();

	GLFWwindow* wind = glfwCreateWindow(500, 500, "airstream", 0, 0);
	glfwMakeContextCurrent(wind);

	glewInit();

	glEnable(GL_CULL_FACE);

	Shader shader("C:\\Users\\User\\Desktop\\Snare\\Программы\\Repository\\Projection attempt\\v.shader",
		"C:\\Users\\User\\Desktop\\Snare\\Программы\\Repository\\Projection attempt\\f.shader");

	//MOVE MATRIX
	glm::mat4x4 move = glm::mat4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, -250.0f, 1.0f
	);

	//ANOTHER MATRICES
	glm::mat4x4 ortho = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, 0.0f, 500.0f);
	
	float angle = 0.0f;
	glm::vec3 axis(0.0f, 1.0f, 0.0f);
	glm::mat4x4 rotate = glm::rotate(angle, axis);

	glm::mat4x4 size = glm::mat4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4x4 modelTransf = glm::translate(glm::mat4x4(), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4x4 perspProjection = glm::perspective(60.0f, 1.0f, 0.1f, 10.0f);




	shader.initMatrix(ortho, "projection");
	shader.initMatrix(move, "move");
	shader.initMatrix(rotate, "rotate");
	//shader.initMatrix(size, "size");

	shader.initMatrix(modelTransf, "modelTransf");
	shader.initMatrix(perspProjection, "perspProjection");




	//COORDINATES SETUP
	float cX = 0.0f, cY = 0.0f, cZ = 0.0f;
	float cvc[8][3] = {
		{cX - 100.0f, cY - 100.0f, cZ + 100.0f}, //0
		{cX + 100.0f, cY - 100.0f, cZ + 100.0f}, //1
		{cX + 100.0f, cY + 100.0f, cZ + 100.0f}, //2
		{cX - 100.0f, cY + 100.0f, cZ + 100.0f}, //3

		{cX - 100.0f, cY - 100.0f, cZ - 100.0f}, //4
		{cX + 100.0f, cY - 100.0f, cZ - 100.0f}, //5
		{cX + 100.0f, cY + 100.0f, cZ - 100.0f}, //6
		{cX - 100.0f, cY + 100.0f, cZ - 100.0f}  //7
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

	//INITIALIZING VERTICES
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

	while (!glfwWindowShouldClose(wind)) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(wind, GLFW_KEY_UP)) {
			if (move[3][2] < 500.0f) {
				move[3][2] += 5.0f;
			}
			std::cout << move[3][2] << "\n";
		}
		if (glfwGetKey(wind, GLFW_KEY_DOWN)) {
			if (move[3][2] > 0.0f) {
				move[3][2] -= 5.0f;
			}
			std::cout << move[3][2] << "\n";
		}

		if (glfwGetKey(wind, GLFW_KEY_LEFT)) {
			angle -= 0.02f;
			rotate = glm::rotate(angle, axis);
			shader.initMatrix(rotate, "rotate");
		}
		if (glfwGetKey(wind, GLFW_KEY_RIGHT)) {
			angle += 0.02f;
			rotate = glm::rotate(angle, axis);
			shader.initMatrix(rotate, "rotate");
		}


		glDrawArrays(GL_QUADS, 0, 24);


		

		glfwPollEvents();
		glfwSwapBuffers(wind);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
	}







	return 0;
}