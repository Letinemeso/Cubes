#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <fstream>

class Shader {
	std::ifstream sh;
	int length = 0;

	char* vSourceCode;
	char* fSourceCode;

	unsigned int vShader, fShader;

	bool vCompileSuccessful;
	bool fCompileSuccessful;
	bool linkSuccessful;

	unsigned int program;

	void createShaderProgram() {
		vShader = glCreateShader(GL_VERTEX_SHADER);
		fShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vShader, 1, &vSourceCode, 0);
		glCompileShader(vShader);

		glShaderSource(fShader, 1, &fSourceCode, 0);
		glCompileShader(fShader);

		int vResult, fResult;
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &vResult);
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &fResult);

		(vResult == 0 ? vCompileSuccessful = false : vCompileSuccessful = true);
		(fResult == 0 ? fCompileSuccessful = false : fCompileSuccessful = true);

		program = glCreateProgram();
		glAttachShader(program, vShader);
		glAttachShader(program, fShader);

		glLinkProgram(program);
		int linkResult;
		glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

		(linkResult == 0 ? linkSuccessful = false : linkSuccessful = true);

		if (linkResult != 0) {
			glUseProgram(program);
		}
		else {
			std::cout << "Some errors occured. shaderDebug() recomended.\n\n";
		}
	}
public:
	Shader(const char* vPath, const char* fPath) {
		sh.open(vPath);
		while (!sh.eof()) {
			sh.ignore(1, -1);
			length += 1;
		}
		sh.seekg(0);

		vSourceCode = new char[length + 1];

		for (int i = 0; i < length; ++i) {
			int ch = sh.get();
			vSourceCode[i] = (char)ch;
		}
		vSourceCode[length] = 0;
		sh.close();

		sh.open(fPath);
		while (!sh.eof()) {
			sh.ignore(1, -1);
			length += 1;
		}
		sh.seekg(0);

		fSourceCode = new char[length + 1];

		for (int i = 0; i < length; ++i) {
			int ch = sh.get();
			fSourceCode[i] = (char)ch;
		}
		fSourceCode[length] = 0;
		sh.close();

		createShaderProgram();
	}

	~Shader() {
		delete[] vSourceCode;
		delete[] fSourceCode;
	}

	bool debug() {
		bool everythingOk = true;
		if (vCompileSuccessful) {
			std::cout << "Vertex shader has been compiled successfully.\n\n";
		}
		else {
			int localLength;
			glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &localLength);
			char* infoLog = new char[localLength];

			glGetShaderInfoLog(vShader, localLength, &localLength, infoLog);
			std::cout << infoLog << "\n";
			delete[] infoLog;
			everythingOk = false;
		}
		if (fCompileSuccessful) {
			std::cout << "Fragment shader has been compiled successfully.\n\n";
		}
		else { 
			int localLength;
			glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &localLength);
			char* infoLog = new char[localLength];

			glGetShaderInfoLog(fShader, localLength, &localLength, infoLog);
			std::cout << infoLog << "\n";
			delete[] infoLog;
			everythingOk = false;
		}
		if (linkSuccessful) {
			std::cout << "Program linked successfully.\n\n";
		}
		else {
			int localLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &localLength);
			char* infoLog = new char[localLength];

			glGetProgramInfoLog(program, localLength, &localLength, infoLog);
			std::cout << infoLog << "\n";
			delete[] infoLog;
			everythingOk = false;
		}
		return everythingOk;
	}

	void initMatrix(glm::mat4x4 matrix, const char* name) {
		unsigned int location = glGetUniformLocation(program, name);
		/*if (location != 0) {
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
		}
		else {
			std::cout << "some errors occured with matrix \"" << name << "\".\n";
		}*/
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);

	}

	unsigned int getProgram() {
		return program;
	}
};