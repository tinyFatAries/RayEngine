#include "InputManager.h"
#include "RenderSystem.h"
#include "../Tools/RayUtils.h"

template<> InputManager* Singleton<InputManager>::m_pSingleton = nullptr;

void GLFWKeyPress(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	InputManager::getInstancePtr()->HandleKeyPress(pWindow, key, scancode, action, mods);
}

void GLFWMouseClick(GLFWwindow* pWindow, int Button, int Action, int Mode)
{
	InputManager::getInstancePtr()->HandleMouseClick(pWindow, Button, Action, Mode);
}

void GLFWMouseMove(GLFWwindow* pWindow, double x, double y)
{
	InputManager::getInstancePtr()->HandleMouseMove(pWindow, x, y);
}

InputManager::InputManager()
{
	GLFWwindow* window = (GLFWwindow*)RenderSystem::getInstancePtr()->getWindowHandle();
	glfwSetKeyCallback(window, GLFWKeyPress);
	glfwSetCursorPosCallback(window, GLFWMouseMove);
	glfwSetMouseButtonCallback(window, GLFWMouseClick);
}

void InputManager::AddListener(InputListener* listener)
{
	Listeners.push_back(listener);
}

void InputManager::RemoveListener(InputListener* listener)
{
	for (auto itr = Listeners.begin(); itr != Listeners.end(); ++itr)
	{
		if (*itr == listener)
		{
			Listeners.erase(itr);
		}
	}
}

void InputManager::HandleKeyPress(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
//	DEBUG_MESSAGE(RAY_MESSAGE, "key pressed key:%d scancode:%d action:%d mods:%d", key, scancode, action, mods);
	for (size_t i = 0; i < Listeners.size(); ++i)
	{
		Listeners[i]->HandleKeyPress();
	}
}

void InputManager::HandleMouseClick(GLFWwindow* pWindow, int button, int action, int mode)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "mouse clicked button:%d action:%d mods:%d", button, action, mode);
	for (size_t i = 0; i < Listeners.size(); ++i)
	{
		Listeners[i]->HandleMouseClick();
	}
}

void InputManager::HandleMouseMove(GLFWwindow* pWindow, double x, double y)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "mouse move x:%f y:%f ", x, y);
	for (size_t i = 0; i < Listeners.size(); ++i)
	{
		Listeners[i]->HandleMouseClick();
	}
}


