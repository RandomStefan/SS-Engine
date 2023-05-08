#pragma once
#include "Scene.h"



struct SDL_Window;
struct SDL_Renderer;
using namespace std;

class SceneManager
{

private:

	//------------------Variables------------------
	Input* input = new Input();
	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;
	int window_w, window_h;
	// Scene objects vector
	vector<GameObject*> sceneObjects;
	vector<GameObject*> savedSceneObjects;
	// Running status of scene
	bool m_Running = 0;


public:

	//------------------Constructor and destructor------------------

	/// <summary>
	/// Constructor. Initializes SDL and creates a window.
	/// </summary>
	/// <param name="m_input"> - Input variable that is going to be passed to scenes and objects when required</param>
	/// <param name="w"> - Window width</param>
	/// <param name="h"> - Window height</param>
	SceneManager(Input* m_input,int w, int h);

	/// <summary>
	/// Destroys created window.
	/// </summary>
	~SceneManager();


	//------------------Variables------------------

	Scene* currentScene;

	//------------------Methods------------------

	/// <summary>
	/// Creates a renderer and ties it to a window then creates the scene "Scene".
	/// </summary>
	void LoadScene();

	/// <summary>
	/// Saves current scene's objects inside savedSceneObjects then destroys the scene.
	/// </summary>
	void UnloadScene();

	

};

