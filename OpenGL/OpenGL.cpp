#include "Renderer.h"
#include <glfw3.h>
#include "Texture.h"

#define printOpenGLError() printOglError(__FILE__, __LINE__)

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	static float trn = 0.0f;
	

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		trn += 0.01;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		trn -= 0.01;
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

int main() {
	GLFWwindow * window = init(640, 480, (char*)"testWindow");
	float triangle[] = {
		0.0f , 0.5f, 0.5f , 1.0f,
		0.5f, 0.0f, 1.0f , 0.0f,
		-0.5f, 0.0f , 0.0f , 0.0f
	};
	float vertices[] = {
		// Позиции          // Цвета             // Текстурные координаты
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Верхний правый
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Нижний правый
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Верхний левый
	};	
	float square1[] = {
		-0.5f , 0.5f, 1.0f , 1.0f, //left top
		0.5f , 0.5f ,0.5f , 0.5f, // right top
		-0.5f , -0.5f,0.5f ,0.5f , // left bot
		0.5f , -0.5f, 0.5f , 0.5f  // right bot
	};
	float square[] = {
		50.0f, 350.0f, //left top
		350.0f , 350.0f , // right top
		50.0f , 50.0f, // left bot
		350.0f , 50.0f // right bot
	};
	unsigned int indices[] = {
		0 , 1 , 3 , 1 , 2 , 3
	};
	VBO vb(vertices, sizeof(vertices));
	IBO ib(indices, 6);
	ib.bind();
	VAO va;
	VAO::Layout la;
	la.add<float>(3);
	la.add<float>(3);
	la.add<float>(2);
	va.addLayout(la, vb);

	Renderer rer;
	Shader shad("Res/Shaders/Basic.shader");

	glm::mat4 proj = presp(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 view2 = glm::lookAt(
		glm::vec3(1, 1, 1), // Камера находится в мировых координатах (4,3,3);
		glm::vec3(0, 0, 0), // И направлена в начало координа�);
		glm::vec3(0, 1, 0)  // "Голова" находится сверх�);
	);
	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 MVP = proj * model;
	Texture txt("Res/Textures/container.jpg");

	while (!glfwWindowShouldClose(window)){
		txt.bind();
		rer.clear();
		rer.display(vb, va, ib, shad);
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
