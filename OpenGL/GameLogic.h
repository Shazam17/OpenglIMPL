#include "Renderer.h"
#include "Point.h"
#include <thread> 
#include <vector>
class Player {

	VAO va;
	VBO vb;
	IBO ib;
	Shader shad;
	std::thread th;
	float x;
	float y;
	float size;
	float speed;
	short snakeSize;
	int dir;
	std::vector<Point> cords;
public:
	Player(float size, float x, float y) {
		this->size = size;
		this->x = 0;
		this->y = 0;
		dir = 0;
		speed = 200;
		float arr[8];
		makeArr(arr, 320, 240, size);
		unsigned int ind[] = {
			0 , 1, 2 , 0 , 2 ,3
		};
		cords.push_back({ x , y });
		shad = Shader("Res/Shaders/newBasic.shader");
		vb = VBO(arr, sizeof(arr));
		va = VAO();
		VAO::Layout la;
		la.add<float>(2);
		va.addLayout(la, vb);
		va.bind();
		ib = IBO(ind, 6);

		snakeSize = 1;

	}
	void render(Renderer rer) {
		va.bind();
		vb.bind();
		ib.bind();
		shad.bind();
		glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);


	}
	void setBasis(glm::mat4 & bas) {
		shad.setUniform4m("View", bas);
	}
	void moveX() {
		shad.setUniform1f("xMove", x);
	}
	void moveY() {
		shad.setUniform1f("yMove", y);
	}

	void keyCheck(GLFWwindow * window, float deltaTime) {
		int state = glfwGetKey(window, GLFW_KEY_W);
		if (state == GLFW_PRESS) {
			dir = 0;
			//y -= speed * deltaTime;
		}
		state = glfwGetKey(window, GLFW_KEY_S);
		if (state == GLFW_PRESS) {
			dir = 2;
			//y += speed * deltaTime;
		}
		state = glfwGetKey(window, GLFW_KEY_A);

		if (state == GLFW_PRESS) {
			dir = 1;
			//x -= speed * deltaTime;
		}
		state = glfwGetKey(window, GLFW_KEY_D);
		if (state == GLFW_PRESS) {
			dir = 3;
			//x += speed * deltaTime;
		}
	}
	void move(float deltaTime) {
		float localSpeed = 100;
		switch (dir) {
		case 0:	 y -= localSpeed * deltaTime;
			break;
		case 1:	x -= localSpeed * deltaTime;
			break;
		case 2:	y += localSpeed * deltaTime;
			break;
		case 3:	x += localSpeed * deltaTime;
			break;
		}
	}
	float getX() const {
		return 320 + x;
	}
	float getY() const {
		return 240 + y;
	}
	float getSize() const {
		return size;
	}
	void timer(float wait, GLFWwindow * window, float deltaTime) {
		float time = glfwGetTime();
		while (glfwGetTime() - time < wait) {

		}
	}
	void update(GLFWwindow * window, float deltaTime, Renderer rer) {

		timer(0.3, window, deltaTime);
		keyCheck(window, deltaTime);
		move(deltaTime);
		moveY();
		moveX();
		render(rer);
	}
};

class Obstacle {

	VAO va;
	VBO vb;
	IBO ib;
	Shader shad;
	float size;
	float x;
	float y;
public:
	Obstacle(float size, float x, float y, glm::mat4 & bas) {

		shad = Shader("Res/Shaders/Obstacle.shader");

		this->x = x;
		this->y = y;
		this->size = size;
		float arr[8];
		arr[0] = x + -size;
		arr[1] = y + size;

		arr[2] = x + size;
		arr[3] = y + size;

		arr[4] = x + size;
		arr[5] = y + -size;

		arr[6] = x + -size;
		arr[7] = y + -size;
		vb = VBO(arr, sizeof(arr));
		unsigned int ind[] = {
		0 , 1, 2 , 0 , 2 ,3
		};
		VAO::Layout la;
		la.add<float>(2);
		va.addLayout(la, vb);

		va.bind();
		ib = IBO(ind, 6);

		shad.setUniform4m("View", bas);

	}
	float getX() const {
		return x;
	}
	float getY() const {
		return y;
	}
	float getSize() const {
		return size;
	}
	void setX(float x) {
		shad.setUniform1f("x", x);
	}
	void setY(float y) {
		shad.setUniform1f("y", y);
	}
	void color(glm::vec3 color) {
		shad.setUniformVec3("NewColor", color);
	}
	void render(Renderer rer) {
		va.bind();
		vb.bind();
		ib.bind();
		shad.bind();
		glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void setBasis(glm::mat4 & bas) {
		shad.setUniform4m("View", bas);
	}
};
bool collisionDetection(Player & plr, Obstacle & ost) {
	bool collisionX = plr.getX() + 3 * plr.getSize() >= ost.getX() && ost.getX() + 1.4 * ost.getSize() >= plr.getX();
	// Collision y-axis?
	bool collisionY = plr.getY() + 3 * plr.getSize() >= ost.getY() && ost.getY() + 1.4 * ost.getSize() >= plr.getY();

	return collisionX && collisionY;
}
float deltaTimeCalc(float * lastFrame) {
	float currentFrame = glfwGetTime();
	float ret = currentFrame - *lastFrame;
	*lastFrame = currentFrame;
	return ret;

}
