#include "Entity.h"

class Sprite : public Entity {


public:
	Sprite(const GLchar *  texturePath, const  GLchar * shaderPath, glm::mat4 & bas, float x, float y) {
		float arr[8];
		makeArr(arr, x, y, 20);
		vb = VBO(arr, sizeof(arr));
		va = VAO();
		VAO::Layout la;
		unsigned int ind[] = {
		0 , 1, 2 , 0 , 2 ,3
		};
		ib = IBO(ind, 6);
		la.add<float>(2);
		va.addLayout(la, vb);



		model = glm::mat4(1);
		view = glm::mat4(1);
		setBasis(bas);
		shad = Shader(shaderPath);
		txt = Texture(texturePath);
		MVP = projection * model * view;
		shad.setUniform4m("MVP", MVP);

		move(glm::vec3(-100, -200, 0));

	}
};