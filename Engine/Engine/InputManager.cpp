#include "InputManager.h"
#include "RenderSystem.h"
#include "../Tools/RayUtils.h"


/**
 * Global functions to catch inputs
 */

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


/**
 * Input Manager Members definition: 
 */

template<> InputManager* Singleton<InputManager>::m_pSingleton = nullptr;

InputManager::InputManager()
{
	GLFWwindow* window = (GLFWwindow*)RenderSystem::getInstancePtr()->getWindowHandle();
	glfwSetKeyCallback(window, GLFWKeyPress);
	glfwSetCursorPosCallback(window, GLFWMouseMove);
	glfwSetMouseButtonCallback(window, GLFWMouseClick);
}

void InputManager::AddListener(InputListener* listener)
{
	Listeners.insert(listener);
}

void InputManager::RemoveListener(InputListener* listener)
{
	auto itr = Listeners.find(listener);
	if ( itr != Listeners.end())
	{
		Listeners.erase(itr);
	}
}

void InputManager::HandleKeyPress(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	for (auto& listener : Listeners)
	{
		listener->HandleKeyPress(key, scancode, action, mods);
	}
}

void InputManager::HandleMouseClick(GLFWwindow* pWindow, int button, int action, int mode)
{
	for (auto& listener : Listeners)
	{
		listener->HandleMouseClick(button, action, mode);
	}
}

void InputManager::HandleMouseMove(GLFWwindow* pWindow, double x, double y)
{
	for (auto& listener : Listeners)
	{
		listener->HandleMouseMove(x, y);
	}
}


