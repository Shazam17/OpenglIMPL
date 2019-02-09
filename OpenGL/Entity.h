#include "Renderer.h"
#include "Texture.h"
class Entity {
public:
	unsigned int id;
	VAO va;
	VBO vb;
	IBO ib;
	Texture txt;
	Shader shad;
	VBO vbCord;
	std::vector<glm::vec2> uvCords;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 MVP;

	void bind() {
		va.bind();
		vb.bind();
		ib.bind();
		txt.bind();
		shad.bind();
	}
	unsigned int getCount() {
		return ib.getCount();
	}
	void move(glm::vec3 trans) {
		view = glm::translate(view, trans);
		MVP = MVP * view;
		shad.setUniform4m("MVP", MVP);
	}
	void transform() {

	}
	void rotate() {

	}
	void setBasis(glm::mat4 & bas) {
		projection = bas;
		shad.setUniform4m("view", projection);
	}
	void matriceToShader() {
		shad.setUniform4m("model", model);
		shad.setUniform4m("view", view);
		shad.setUniform4m("projection", projection);
	}

};

