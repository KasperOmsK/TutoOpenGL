#include <iostream>
#include "src/graphics/OpenGLScene.h"
#include <string>
#include "src\Shader.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "src/graphics/Cube.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

#define PI 3.14159265359
#define FRAMERATE 60

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const double ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;

double toRad(double angleInDegree) {
	return angleInDegree * PI / 180.0;
}

int main(int argc, char **argv) 
{	
	using namespace glm;
	//creating scene
	
	OpenGLScene scene = OpenGLScene("openGL", WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.initWindow();
	scene.initGL();
	float elapsedTime = 0.0;
	float frameStartTime = 0.0;
	float targetDT = 1000.0 / FRAMERATE;
	float x =0, y = 0;
	float deltaTime;

	Cube c(2, "src/shaders/couleur3D.vert", "src/shaders/couleur3D.frag");
	

	c.position = vec3(0, 0, 0);

	//====================matrices=====================
	mat4 projection = perspective(toRad(70), ratio, 1.0, 100.0);
	//mat4 projection = ortho(-4.0, 4.0, -3.0, 3.0, 0.5, 10.0);
	mat4 modelView = mat4(1.0);

	while (scene.closed() == false) 
	{
		frameStartTime = SDL_GetTicks();
		scene.events();
		
		if (scene.inputs().IsKeyDown(SDL_SCANCODE_ESCAPE)) {
			scene.close();
		}
		if (scene.inputs().IsKeyDown(SDL_SCANCODE_LEFT)) {
			y -= 0.05f;
		}
		if (scene.inputs().IsKeyDown(SDL_SCANCODE_RIGHT)) {
			y += 0.05f;
		}
		if (scene.inputs().IsKeyDown(SDL_SCANCODE_UP)) {
			x -= 0.05f;
		}
		if (scene.inputs().IsKeyDown(SDL_SCANCODE_DOWN)) {
			x += 0.05f;
		}

		//clear screen & reset model view matrixs
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelView = lookAt(vec3(0,0,5), vec3(0, 0, 0), vec3(0, 1, 0));	
		c.eulerAngles = vec3(x, y, 0);
		c.render(projection, modelView);

		scene.swapBuffers();

		float dt = SDL_GetTicks() - frameStartTime;
		if (dt < targetDT) {
			SDL_Delay(targetDT - dt);
		}

		elapsedTime += dt;
	}

	return EXIT_SUCCESS;

}
	
