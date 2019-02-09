#include "Renderer.h"

using glm::vec3;
using glm::mat4;

class Camera {
	vec3 pos;

	float yAngle;
	float xAngle;
	float mouseSpeed;
	float speed;
public:
	Camera(vec3 pos, float mouseSpeed, float speed) {
		yAngle = 0;
		xAngle = 0;
		this->pos = pos;
		this->mouseSpeed = mouseSpeed;
		this->speed = speed;
	}

	void translate(vec3 v) {
		pos += v;

	}

	mat4 move(GLFWwindow * window, int width, int height, float dT) {
		double mX;
		double mY;
		glfwGetCursorPos(window, &mX, &mY);
		glfwSetCursorPos(window, width / 2, height / 2);

		xAngle += mouseSpeed * dT * float(width / 2 - mX);
		yAngle += mouseSpeed * dT * float(height / 2 - mY);


		glm::vec3 direction(
			cos(yAngle) * sin(xAngle),
			sin(yAngle),
			cos(yAngle) * cos(xAngle));

		vec3 right = cross(direction, vec3(0, 1, 0));
		vec3 up = cross(right, direction);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			pos += direction * dT * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			pos -= direction * dT * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			pos -= right * dT * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			pos += right * dT * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			pos += up * dT * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			pos -= up * dT * speed;
		}
		return glm::lookAt(pos, pos + direction, up);

	}
};