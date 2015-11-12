#pragma once

#include "Singleton.h"
#include <vector>
#include <GLFW/glfw3.h>

class InputListener
{
public:
	virtual bool HandleKeyPress();
	virtual bool HandleMouseClick();
	virtual bool HandleMouseMove();
};


class InputManager : public Singleton < InputManager >
{
public:
	InputManager();

	void AddListener(InputListener* listener);
	void RemoveListener(InputListener* listener);
	void HandleKeyPress(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
	void HandleMouseMove(GLFWwindow* pWindow, double x, double y);
	void HandleMouseClick(GLFWwindow* pWindow, int Button, int Action, int Mode);


private:
	std::vector<InputListener*> Listeners;
};
