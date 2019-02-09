#include "Entity.h"

using glm::vec2;

class Sprite : public Entity {


public:
	Sprite(const GLchar *  texturePath, const  GLchar * shaderPath, glm::mat4 & bas, float x, float y , float size) {
		float arr[8];
		makeArr(arr, x, y, size);
		vb = VBO(arr, sizeof(arr));
		va = VAO();
		VAO::Layout la;
		unsigned int ind[] = {
		0 , 1, 2 , 0 , 2 ,3
		};
		ib = IBO(ind, 6);
		la.add<float>(2);
		va.addLayout(la, vb);

		txt = Texture(texturePath);

		uvCords.push_back(vec2(0, 1));
		uvCords.push_back(vec2(1, 1));
		uvCords.push_back(vec2(1, 0));
		uvCords.push_back(vec2(0 ,0 ));

		vbCord = VBO(&uvCords[0], sizeof(vec2) * 4);
		
		va.addLayout(la , vbCord);

		shad = Shader(shaderPath);
		txt = Texture(texturePath);

		model = glm::mat4(1);
		view = glm::mat4(1);
		setBasis(bas);
		
		MVP = projection * view * model;
		shad.setUniform4m("MVP", MVP);

	

	}
};