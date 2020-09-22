// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "glew.h"
#include "glfw3.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main()
{	
	//Initializare GLFW
	if (!glfwInit())
	{
		std::cout << "Initializare esuata pentru GLFW.";
		glfwTerminate();
		return 1;
	}

    //Seteaza Propietatea Fereasta
	// Versiunea OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile = nu e compatibil cu versiunile vechi
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);

	if (!mainWindow)
	{
		std::cout << "Crearea Ferestrei a esuat. \n";
		glfwTerminate();
		return 1;
	}

	//Gaseste dimensiunea bufferului de fereastra

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);


	//Seteaza contextul pentru GLEW -> Unde se deseneaza ceva; -> Daca ai mai multe ferestre poti sa schimbi intre ele
	glfwMakeContextCurrent(mainWindow);

	//Permite extensii moderne
	glewExperimental = GL_TRUE;

	if (glewInit()!= GLEW_OK)
	{
		std::cout << "Initializare GLEW esuata. \n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//Seteaza Viewportul (unde sa deseneze)?
	glViewport(0, 0, bufferWidth, bufferHeight);

	//Loop pana la inchiderea ferestrei

	while (!glfwWindowShouldClose(mainWindow))
	{
		//Get + Handle User Input
		glfwPollEvents();

		//Curata Fereastra
		glClearColor(0.0f,1.0f,0.0f,1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);

	}



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
