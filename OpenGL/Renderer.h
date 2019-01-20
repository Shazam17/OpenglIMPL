#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include "VBO.h"
#include "IBO.h"
#include "VAO.h"
#include "Shader.h"

#ifndef Log(x)
#define Log(x) std::cout << x << std::endl
#endif

bool LogCall() {
	while (GLenum err = glGetError()) {
		std::cout << "GL ERROR " << err << std::endl;
		return false;
	}
	return true;
}
void glClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}
#define Assert(x) if (!(x)) __debugbreak()
#define glCall(x) glClearErrors();\
	x;\
	Assert(LogCall())

class Entity;

void makeArr(float arr[], float X, float Y, float size) {
	float x = 320;
	float y = 240;
	arr[0] = X + -size;
	arr[1] = Y + size;

	arr[2] = X + size;
	arr[3] = Y + size;

	arr[4] = X + size;
	arr[5] = Y + -size;

	arr[6] = X + -size;
	arr[7] = Y + -size;
}
class Renderer {
public:
	Renderer() {

	}
	void clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void pollEvents() {
		glfwPollEvents();
	}
	void swapBuffers(GLFWwindow * window) {
		glfwSwapBuffers(window);
	}
	
	void displayElem(Entity * ent);
	void display(VAO va , IBO ib , VBO vb , Shader shad) {
		va.bind();
		ib.bind();
		vb.bind();
		shad.bind();
		glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}
};
