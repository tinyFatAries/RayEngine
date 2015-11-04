/**
* This engine is a "wheel" made by myself , the reason why i did this
* is just for study game engine & render architecture.
*
* Author: RaymondTao
* Date: 2015-10-30
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <stdio.h>

#include "Engine/Tools/RayUtils.h"
#include "Engine/Engine/OpenGLRender.h"

#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	RenderSystem* render = new OpenGLRenderSystem(1024, 768, "Ray Engine", false);

	cout << RenderSystem::getInstancePtr()->getSysname() << endl;
	RenderSystem::getInstancePtr()->StartRendering();

	return 0;
}