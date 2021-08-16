// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "glfw3.h"
#include "..//glm/glm.hpp"
#include "GLWrapper.h"


//Test:
#include "Ray.h"
#include "hitable.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "ElipticCylinder.h"
#include "..\\glm\gtx\string_cast.hpp"


//GEN TEXTURE IMAGE  TEST

#define checkImageWidth 128
#define checkImageHeight 128
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;

void makeCheckImage(void)
{
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++)
	{
		for (j = 0; j < checkImageWidth; j++)
		{
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)255;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)255;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}
}






 GLint WIDTH = 800, HEIGHT = 600;

int main()
{	
	GLWrapper glWrapper(WIDTH, HEIGHT);
	glWrapper.InitWindow();
	glfwSwapInterval(1);

	WIDTH = glWrapper.GetWidth();
	HEIGHT = glWrapper.GetHeight();

	// fix ray direction
	if (WIDTH % 2 == 1) WIDTH++;
	if (HEIGHT % 2 == 1) HEIGHT++;

	Shader simpleSH("Simple.vs", "Simple.fs");
	glWrapper.InitShader(&simpleSH);

	Cuboid box(glm::vec3(1.0f, 2.3f, 10.0f), glm::vec3(2.3f, 11.9f, 14.0f));

	makeCheckImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
		checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		checkImage);


	//TODO Scene Manager time
	//TODO Create Scene

	//TODO replace defines;


	//Setting Skybox
	//std::vector<std::string> faces =
	//{
	//	"Textures/CubeMap/GalaxyTex_PositiveX.jpg",
	//	"Textures/CubeMap/GalaxyTex_NegativeX.jpg",
	//	"Textures/CubeMap/GalaxyTex_PositiveY.jpg",
	//	"Textures/CubeMap/GalaxyTex_NegativeY.jpg",
	//	"Textures/CubeMap/GalaxyTex_PositiveZ.jpg",
	//	"Textures/CubeMap/GalaxyTex_NegativeZ.jpg"
	//};

	//glWrapper.SetSkybox(GLWrapper::LoadCubemap(faces, false));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // revert wireframe mode

	//Loop pana la inchiderea ferestrei



	while (!glfwWindowShouldClose(glWrapper.WindowScreen))
	{
		//Get + Handle User Input
		glfwPollEvents();

		//Curata Fereastra
		//glClearColor(50.f,255,255,0.0f);
		//glWrapper.InitShader(&simpleSH);

		glWrapper.Draw();


		glfwSwapBuffers(glWrapper.WindowScreen);

	}




	//TEST INTERSECTION RAY->SPHERE
	glm::vec3 rayO = glm::vec3(1.f, -2.f, -1.f);
	glm::vec3 rayD = glm::vec3(1.f, 2.f, 4.f);
	Ray raza(rayO, rayD);
	hit_record record;
	Sphere ball(glm::vec3(3.f, 0.f, 5.f), 3);
	if (ball.hit(raza, record))
	{
		std::cout << "Punctul de intersectie: " << glm::to_string(record.intersectPoint) << std::endl;
		std::cout << "Valoarea lui t : " << record.t << std::endl;
		std::cout << "Valoarea Normalei : " << glm::to_string(record.intersectNormal) << std::endl;
	}
	else
		std::cout << "Nu intersecteaza .\n";

	//TEST INTERSECTION RAY->CUBOID

	rayO = glm::vec3(0.f,4.f,2.f);
	rayD = glm::vec3(0.218f,-0.436f,0.873f);
	glm::vec3 smallCorner = glm::vec3(-1.f, 2.f, 1.f);
	glm::vec3 bigCorner = glm::vec3(3.f, 3.f, 3.f);
	Cuboid testCube(smallCorner, bigCorner);
	HitInfo hit_info;
	std::cout<<"\n Ray intersects cube: "<<std::boolalpha<<testCube.TestIntersection(rayO, rayD, hit_info);


	//TEST INTERSECTION RAY->CYLINDER

	ElipticCylinder c1(2,1,2);
	//rayO = glm::vec3(1.f, 0.f, -5.f);
	//rayD = glm::vec3(0.f, 0.f, 1.f);
	//c1.TestIntersection(rayO, rayD, hit_info);
	rayO = glm::vec3(0.5f, 0.0f, -5.0f);
	rayD = glm::vec3(0.1f, 1.0f, 1.0f);
	
	c1.TestIntersection(rayO, glm::normalize(rayD), hit_info);
	



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
