#include "Renderer.h"
#include <glfw3.h>

#include "Sprite.h"
#include "GameLogic.h"	
#include <vector>

#define printOpenGLError() printOglError(__FILE__, __LINE__)

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
	
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {

	}
}
GLFWwindow * init(int x , int y , char * name ) {
	GLFWwindow* window;
	if (!glfwInit()){
		glfwTerminate();
		Log("Failed to load glfw");
	}
	window = glfwCreateWindow(640, 480, name, NULL, NULL);
	if (!window) {
		glfwTerminate();
		
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, (GLFWkeyfun)key_callback);
	if (GLEW_OK != glewInit()){
		Log("Failed to load glew");
	}
	glewExperimental = GL_TRUE;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	return window;
}

glm::mat4 ortho(float l, float r, float b, float t, float zn, float zf){
	return glm::ortho(l, r, b,t, zn, zf);
}
glm::mat4 presp(float fov , float cond , float near, float far){
	return glm::perspective(glm::radians(fov) , cond , near, far);
}

void makeArra(float arr[], float X , float Y , float size) {
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

void Renderer::displayElem(Entity * itm) {
	itm->bind();
	glDrawElements(GL_TRIANGLES, itm->getCount(), GL_UNSIGNED_INT, nullptr);
}
int main() {
	GLFWwindow * window = init(640, 480, (char*)"testWindow");
	Renderer rer;
	
	int width = 640;
	int height = 480;

	glm::mat4 view = ortho(0, width, height, 0, 0, -1);

	Player plr(20, 320, 240);
	plr.setBasis(view);

	Obstacle ost(50, 200, 250, view);
	Sprite * spr = new Sprite("Res/Textures/container.jpg", "Res/Shaders/Sprite.shader", view, 200 , 400);


	float lastFrame = 0;

	while (!glfwWindowShouldClose(window)) {
		rer.clear();

		float deltaTime = deltaTimeCalc(&lastFrame);

		
		bool col = collisionDetection(plr, ost);
		if (col) {
			ost.color(glm::vec3(1, 0, 0));
		}
		else {
			ost.color(glm::vec3(1, 1, 1));
		}
		rer.displayElem(spr);
		ost.render(rer);
		plr.update(window, deltaTime, rer);

		rer.swapBuffers(window);
		rer.pollEvents();
	}
	glfwTerminate();
	return 0;
}
