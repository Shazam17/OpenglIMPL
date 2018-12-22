#pragma once
#include "Renderer.h"
class VBO {
	unsigned int id;

public:
	VBO(const void * data, unsigned int size) {
		glGenBuffers(1, &id);
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		unBind();
	}
	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void unBind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};