#include "SceneManager.h"

SceneManager::SceneManager(Input* m_input, int w, int h)
{
	// Setting the variables
	input = m_input; // input passed to the scene
	m_Window = nullptr; // window variable
	m_Renderer = nullptr; // renderer variable
	window_w = w; // window width
	window_h = h; // window height
	currentScene = nullptr; // current scene variable

	// SDL Initialization
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GLContext gl_context = SDL_GL_CreateContext(m_Window);
	SDL_GL_MakeCurrent(m_Window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	// Window Initialization
	m_Window = SDL_CreateWindow(
		"Game Engine", //title
		250,			   //initial x position
		50,				   //initial y position
		window_w,			   //width, in pixels
		window_h,			   //height, in pixels
		0				   //window behaviour flags (ignore for now)
	);

	// Error handling
	if (!m_Window)
	{
		printf("WINDOW initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar();
		return;
	}


}

SceneManager::~SceneManager()
{
	if (m_Window)
	{
		SDL_DestroyWindow(m_Window);

	}
}

void SceneManager::LoadScene()
{
	// First checks if there is already a scene running and returns if true
	if (m_Running)
	{
		printf("A scene is already running, please unload it before loading a new one.\n");
		printf("Press any key to continue\n");
		getchar();
		return;
	}
	else
	{
		m_Running = true;
		SDL_Renderer* m_Renderer;
		m_Renderer = SDL_CreateRenderer(m_Window, -1, 0); // We create a renderer and tie it to the current window
		// Error if something fails
		if (!m_Renderer)
		{
			printf("RENDERER initialisation failed: %s\n", SDL_GetError());
			printf("Press any key to continue\n");
			getchar();

			return;
		}
		currentScene = new Scene(input, m_Renderer, m_Window, window_w, window_h); // We create the game scene
		
	
	}
}

void SceneManager::UnloadScene()
{
	// Error handling
	if (!m_Running)
	{
		printf("No scene is running currently. Load a scene first.\n");
		printf("Press any key to continue\n");
		getchar();
		return;
	}
	else
	{
		m_Running = false;
		if (m_Renderer)
		{
			currentScene->saveScene(savedSceneObjects);
			currentScene->destroyScene();
			SDL_Delay(33);
			SDL_DestroyRenderer(m_Renderer);


		}
	}

}
