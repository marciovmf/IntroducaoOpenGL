#include <iostream>
#include "Window.h"

int main(int argc, char** argv)
{

	Window w(800, 600, "Introducao OpenGL - Design Code Play Repeat!");


	while (!w.shouldClose())
	{
		w.update();
	}

	return 0;
}