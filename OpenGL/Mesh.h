#include "GameLogic.h"
#include "Texture.h"

using glm::mat4;


class Mesh {

	mat4 MVP;
	VAO va;
	VBO vb;
	Texture txt;
	Shader shad;
	IBO ib;
	unsigned int count;
	glm::mat4 proj;
public:
	Mesh(std::string meshPath, std::string txtPath, std::string shaderPath) {
		std::vector<glm::vec3> verts;
		std::vector<glm::vec2> uvCords;
		std::vector<float> end;

		loadOBJ(meshPath.c_str(), verts, uvCords);
		count = verts.size();
		for (int i = 0; i < verts.size(); i++) {
			end.push_back(verts[i].x);
			end.push_back(verts[i].y);
			end.push_back(verts[i].z);
			end.push_back(uvCords[i].x);
			end.push_back(uvCords[i].y);
		}

		vb = VBO(&end[0], sizeof(float) * end.size());
		VAO::Layout la;
		la.add<float>(3);
		la.add<float>(2);

		va = VAO();
		va.addLayout(la, vb);
		txt = Texture(txtPath.c_str());
		shad = Shader("Res/Shaders/cube.shader");
	}
	void draw() {
		va.bind();
		shad.bind();
		txt.bind();
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void setUniform(const GLchar * name, mat4 mvp) {
		shad.setUniform4m(name, mvp);
	}
	void setUniform(mat4 mvp) {

		shad.setUniform4m("proj", mvp);
	}
};