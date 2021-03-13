#include "Input.h"
#include "Mouse.h"
#include "CameraController.h"


namespace Input
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}


	void processInput(GLFWwindow* window, float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			CameraController::instance().GetCamera().ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			CameraController::instance().GetCamera().ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			CameraController::instance().GetCamera().ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			CameraController::instance().GetCamera().ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	}


	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (Mouse::instance().firstMouse)
		{
			Mouse::instance().lastX = xpos;
			Mouse::instance().lastY = ypos;
			Mouse::instance().firstMouse = false;
		}

		float xoffset = xpos - Mouse::instance().lastX;
		float yoffset = Mouse::instance().lastY - ypos; // reversed since y-coordinates go from bottom to top

		Mouse::instance().lastX = xpos;
		Mouse::instance().lastY = ypos;

		CameraController::instance().GetCamera().ProcessMouseMovement(xoffset, yoffset);
	}


	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		CameraController::instance().GetCamera().ProcessMouseScroll(yoffset);
	}
}
