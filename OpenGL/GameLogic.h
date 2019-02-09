#include "Renderer.h"
#include "Point.h"
#include <thread> 
#include <vector>

void loadOBJ(const char * path, std::vector<glm::vec3> & cords , std::vector<glm::vec2> & uvCords) {
	float ** fileArr;
	std::ifstream file(path);
	std::vector<glm::vec3> tempVertex;
	std::vector<glm::vec2> tempTextCord;

	
	std::vector<glm::vec3> tempNorm;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	int mode = -1;
	std::string str;
	while (getline(file, str)) {
		if (str[0] == 'v' && str[1] == ' ') {
			std::istringstream ss(str);
			std::string fWord;
			ss >> fWord;
			float x, y, z;
			ss >> x >> y >> z;
			tempVertex.push_back({ x , y , z });

		}
		else if (str[0] == 'v' && str[1] == 't') {
			std::istringstream ss(str);
			std::string fWord;
			float x, y;
			ss >> fWord;
			ss >> x >> y;
			tempTextCord.push_back({ x , y });
		}
		else if (str[0] == 'v' && str[1] == 'n') {
			std::istringstream ss(str);
			std::string fWord;
			ss >> fWord;
			float x, y, z;
			ss >> x >> y >> z;
			tempNorm.push_back({ x , y , z });
		}
		else if (str[0] == 'f') {
			std::istringstream ss(str);
			std::string fWord;
			ss >> fWord;
			char buff;
			unsigned int n1;
			unsigned int n2;
			unsigned int n3;
			//-ss >>  vIndex[0] >> buff >> uvIndex[1] >> nIndex[2] 
			//>> buff >> vIndex[0] >> uvIndex[1] >> uvIndex[2] >> buff >> vIndex[0] >> uvIndex[1] >> nIndex[2];
			while (ss >> n1 >> buff >> n2 >> buff >> n3) {
				vertexIndices.push_back(n1);
				uvIndices.push_back(n2);
			}
		}
	}
	for (int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		cords.push_back(tempVertex[vertexIndex - 1]);
	}
	for (int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		uvCords.push_back(tempTextCord[uvIndex - 1]);
	}
}

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
	bool canGo;
	float iTime;
	std::vector<Point> cords;
public:
	Player(float size, float x, float y) {
		this->size = size;
		this->x = 0;
		this->y = 0;
		dir = 0;
		speed = 20;
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
		canGo = true;
		iTime = 0;
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
	void move(float deltaTime = 1) {
		switch (dir) {
		case 0:	 y -= speed * deltaTime;
			break;
		case 1:	x -= speed * deltaTime;
			break;
		case 2:	y += speed * deltaTime;
			break;
		case 3:	x += speed * deltaTime;
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
	void update(GLFWwindow * window, float deltaTime, Renderer rer, float time) {

		keyCheck(window, deltaTime);
		if (canGo) {
			iTime = time;
			moveY();
			moveX();
			move();

			canGo = false;
		}
		if (glfwGetTime() - iTime > 0.4f) {
			canGo = true;
		}

		render(rer);
	}
};

void makeArra(float arr[], float X, float Y, float size) {
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
