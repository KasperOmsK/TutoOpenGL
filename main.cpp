#include <iostream>
#include "src/graphics/OpenGLScene.h"
#include <string>
#include "src\graphics\Shader.h"
 
#include "src/graphics/CubeMeshRenderer.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "src\graphics\Texture.h"
#include "src/render/Camera.h"
#include "src\math\math.h"
#include "src/game/Block.h"
#include "src\game\Chunk.h"

#include "src/game/TextureManager.h"

#define FRAMERATE 60

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const double ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;



int main(int argc, char **argv) 
{	
	using namespace glm;
	//creating scene
	math::initRand();

	OpenGLScene scene = OpenGLScene("openGL", WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.initWindow();
	scene.initGL();

	//Load resources AFTER creating the GL context in scene.
	if (!TextureManager::Init()) {
		std::cout << "could not load resources" << std::endl;
		return EXIT_FAILURE;
	}
	
	scene.inputs().SetCursorRelative(true);

	float elapsedTime = 0.0;
	int frameStartTime = 0; 
	float targetDT = 1000.0f / (1000 * FRAMERATE);
	float camSpeed = 10;
	float deltaTime = 0;

	int frameRate = 0;
	int frameCount = 0;
	float lastFrameRateUpdateTime = 0;

	Camera cam = Camera(math::toRad(90.0), (double)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 100);
	
	mat4 modelView = mat4(1.0);
	CubeMeshRenderer::Build(1, "src/shaders/texture.vert", "src/shaders/texture.frag");

	Chunk c(0, 0);
	c.build();

	cam.setPosition(Vector3(0,0,-2));
	//cam.setForward(Vector3(0,0,1));

	Vector3 forward;
	Vector3 target_forward;
	Vector3 dv;
	Vector3 target_dv;
	float pitch = 0;
	float yaw = 0;
	float camSensitivity = 5;

	while (scene.closed() == false) 
	{
		frameStartTime = SDL_GetTicks();
		scene.updateInputs();

#pragma region userInput
		
		if (scene.inputs().IsKeyDown(SDL_SCANCODE_ESCAPE)) {
			scene.close();
		}

		Vector3 mouseDelta = scene.inputs().GetMousePositionRelative();
		yaw -= math::toRad(mouseDelta.x * deltaTime * camSensitivity);
		pitch -= math::toRad(mouseDelta.y * deltaTime * camSensitivity);

		math::clamp(pitch, (float)math::toRad(-89), (float)math::toRad(89));

		target_forward.x = cos(pitch)*sin(yaw);
		target_forward.y = sin(pitch);
		target_forward.z = cos(pitch)*cos(yaw);
		
		math::lerp(forward, target_forward, 20*deltaTime);
		cam.setForward(forward);

		if (scene.inputs().IsKeyHeld(SDL_SCANCODE_W)) {
			target_dv.z = 1;
		}
		else if (scene.inputs().IsKeyHeld(SDL_SCANCODE_S)) {
			target_dv.z = -1;
		}
		else {
			target_dv.z = 0;
		}
		if (scene.inputs().IsKeyHeld(SDL_SCANCODE_A)) {
			target_dv.x = 1;
		}
		else if (scene.inputs().IsKeyHeld(SDL_SCANCODE_D)) {
			target_dv.x = -1;
		}
		else {
			target_dv.x = 0;
		}

		target_dv.normalize();
		math::lerp(dv, target_dv, 20 * deltaTime);
		cam.move( (cam.GetForward()*dv.z - cam.GetRight()*dv.x) * deltaTime * camSpeed);
#pragma endregion

		modelView = cam.getModelViewMatrix();
		//clear screen & reset model view matrixs
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (scene.inputs().IsKeyDown(SDL_SCANCODE_T)) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					for (int y = 0; y < CHUNK_HEIGHT; y++) {
						Block* b = c.GetBlockAt(x, y, z);
						if (b != NULL) {
							b->SetType((math::NextInt(0,100) < 50) ? BlockType::Stone : BlockType::Dirt);
						}
					}
				}
			}
		}
		
		c.render(cam);

		scene.swapBuffers();

#pragma region timeProcessing
		deltaTime = SDL_GetTicks() / 1000.0 - frameStartTime / 1000.0; //in seconds
		/*if (deltaTime < targetDT) {
			SDL_Delay(targetDT * 1000 - deltaTime * 1000);
			deltaTime = targetDT;
		}*/
		elapsedTime += deltaTime;

		frameCount++;
		if (frameCount > 60) {
			frameRate = frameCount / (elapsedTime - lastFrameRateUpdateTime);
			frameCount = 0;
			lastFrameRateUpdateTime = elapsedTime;

			scene.SetTitle(std::string("openGL | ") + std::to_string(frameRate) + " fps");
		}

#pragma endregion

	}

	TextureManager::Free();
	return EXIT_SUCCESS;

}
