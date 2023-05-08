#include <iostream>

#include "input.h"
#include "SceneManager.h"

int main(int argc, char* argv[])
{
	Input* input = new Input(); 
	SceneManager* game = new SceneManager(input, 1270, 720); // We create a window of 1270x720 resolution
	game->LoadScene(); // We load our game scene

	while (game && input)
	{
			while (!input->KeyIsPressed(KEY_ESCAPE))
			{
				// We update the game every 33 frames
				game->currentScene->Update(); 
				input->Update();
				SDL_Delay(33);
			}

			// We cleanup
			game->UnloadScene();
			delete game;
			game = nullptr;

			delete input;
			input = nullptr;
			SDL_Quit();
	}

	// Exit
	return 0; 
}