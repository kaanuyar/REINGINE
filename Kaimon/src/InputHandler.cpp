#include "InputHandler.h"

InputHandler::InputHandler(Window& window, std::vector<IUpdatable*>& updatableList)
	: m_window(window), m_updatableList(updatableList)
{
	glfwSetWindowUserPointer(window.getWindow(), this);
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		m_window.windowShouldClose();

	Event::State state;
	if		(key == GLFW_KEY_W)
		state = Event::KEY_W;
	else if (key == GLFW_KEY_S)
		state = Event::KEY_S;
	else if (key == GLFW_KEY_A)
		state = Event::KEY_A;
	else if (key == GLFW_KEY_D)
		state = Event::KEY_D;
	/*else if (key == GLFW_KEY_R)
		state = Event::KEY_R;*/
	else
		return;

	for (IUpdatable* updatable : m_updatableList)
	{
		if (action == GLFW_PRESS)
			updatable->getEventHandler().addEventToList(Event(state, true));
		else if (action == GLFW_RELEASE)
			updatable->getEventHandler().removeEventFromList(Event(state, true));
	}

}

void InputHandler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(m_window.getWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		double xoffset = xpos - m_prevXposition;
		double yoffset = m_prevYposition - ypos; // reversed since y-coordinates go from bottom to top
		m_prevXposition = xpos;
		m_prevYposition = ypos;

		for (IUpdatable* updatable : m_updatableList)
			updatable->getEventHandler().addEventToList(Event(Event::MOUSE_BUTTON_MIDDLE_DRAGGED, false, float(xoffset), float(yoffset)));
	}
	else
	{
		m_prevXposition = xpos;
		m_prevYposition = ypos;
	}
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	for (IUpdatable* updatable : m_updatableList)
		updatable->getEventHandler().addEventToList(Event(Event::MOUSE_SCROLL, false, float(xoffset), float(yoffset)));
}

void InputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		for (IUpdatable* updatable : m_updatableList)
		{
			updatable->getEventHandler().removeEventFromList(Event(Event::MOUSE_BUTTON_RIGHT_PRESSED, true, float(xpos), float(ypos)));
			updatable->getEventHandler().addEventToList(Event(Event::MOUSE_BUTTON_RIGHT_PRESSED, true, float(xpos), float(ypos)));
		}

	}
}

void InputHandler::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	for (IUpdatable* updatable : m_updatableList)
		updatable->getEventHandler().addEventToList(Event(Event::WINDOW_RESIZE, false, float(width), float(height)));
}
