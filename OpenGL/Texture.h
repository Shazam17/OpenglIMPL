#pragma once
#include "stb_image.h"
#include "Renderer.h"
#include <iostream>

class Texture {
	unsigned int id;
	const void * data;
	int width;
	int height;
	int bpp;
public:
	Texture(const char * filepath) {
		unsigned char * bytes = stbi_load(filepath, &width, &height, &bpp, 4);
		if (!bytes) {
			Log("ERROR WITH DOWNOLOAD OF IMAGE");
		}
		glGenTextures(1, &id);
		glCall(glBindTexture(GL_TEXTURE_2D, id));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes));

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void bind(int slot = 0) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void unBind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};
