#pragma once
#include <iostream>
#include <glew.h>
#include <sstream>
#include <fstream>
#include <glm.hpp>
//#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define Log(x) std::cout << x << std::endl


class Shader {
	unsigned int id;

public:
	Shader(const std::string filepath) {
		std::ifstream file(filepath);

		if (!file) {
			Log("File isnt opened");
		}
		int mode = -1;
		std::string line;
		std::stringstream ss[2];
		while (!file.eof()) {
			getline(file, line);
			if (line.find("shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					mode = 0;
				}
				if (line.find("fragment") != std::string::npos) {
					mode = 1;
				}
			}
			else {
				ss[mode] << line << '\n';
			}
			Log(line);
		}
		std::string strCode[2];
		strCode[0] = ss[0].str();
		strCode[1] = ss[1].str();
		const GLchar * shaderCode[2];
		shaderCode[0] = strCode[0].c_str();
		shaderCode[1] = strCode[1].c_str();;
		Log(ss[1].str());
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertexShader, 1, &shaderCode[0], NULL);
		glCompileShader(vertexShader);
		glShaderSource(fragmentShader, 1, &shaderCode[1], NULL);
		glCompileShader(fragmentShader);
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		id = glCreateProgram();
		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);
		glLinkProgram(id);
		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void setUniform4m(const GLchar * name, glm::mat4 &mat) {
		bind();
		unsigned int loc = glGetUniformLocation(id, name);
		if (loc == -1) {
			Log("uniform didnt find");
		}
		glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
		unBind();
	}

	void setUniform1f(const GLchar * name, GLfloat var) {
		bind();
		unsigned int loc = glGetUniformLocation(id, name);
				if (loc == -1) {
			Log("uniform didnt find");
		}
		glUniform1f(loc, var);
		unBind();
	}
	void setUniform1i(const GLchar * name, GLint var) {
		bind();
		unsigned int loc = glGetUniformLocation(id, name);
		if (loc == -1) {
			Log("uniform didnt find");
		}
		glUniform1f(loc, var);
		unBind();
	}
	void bind() {
		glUseProgram(id);
	}
	void unBind() {
		glUseProgram(0);
	}
};