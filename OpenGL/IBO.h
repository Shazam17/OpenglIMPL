#pragma once
#include "Renderer.h"
class IBO {
	unsigned int id;
	unsigned int count;
public:
	IBO() {

	}

	IBO(const unsigned int * data, const unsigned int cnt) {
		glGenBuffers(1, &id);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cnt * sizeof(unsigned int), data, GL_STATIC_DRAW);
		this->count = cnt;
		unBind();
	}
	unsigned int getCount() {
		return count;
	}
	void bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	void unBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


};