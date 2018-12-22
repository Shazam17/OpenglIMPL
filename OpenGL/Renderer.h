#pragma once
#include <glew.h>
#include <vector>
#include "VBO.h"
#include "IBO.h"
#include "Shader.h"
#include "VAO.h"
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


class Renderer {
public:
	Renderer() {

	}
	void clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void display(VBO vb, VAO va, IBO ib, Shader shad) {
		va.bind();
		vb.bind();
		ib.bind();
		shad.bind();
		glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}
};