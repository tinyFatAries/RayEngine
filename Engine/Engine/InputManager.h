#pragma once

#include "Singleton.h"
#include <set>
#include <GLFW/glfw3.h>

class InputListener
{
public:
	InputListener() {}
	virtual ~InputListener() {}

	virtual void HandleKeyPress(int key, int scancode, int action, int mods) {}
	virtual void HandleMouseClick(int button, int action, int mode) {}
	virtual void HandleMouseMove(double x, double y) {}
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
	std::set<InputListener*> Listeners;
};
