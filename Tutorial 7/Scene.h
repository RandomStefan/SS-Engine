#pragma once

#include <stdio.h>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Debug.h"

#include "I_GUI.h"
#include <filesystem>




using namespace std;

class Scene
{
private:

	Input* input;
	int windowWidth;
	int windowHeight;

public:

	

	//------------------Constructor and destructor------------------

	/// <summary>
	/// Constructor. Creates a new Scene that takes in an Input variable to handle user input, a Renderer variable that will get passed data to render
	/// and the current window's width and height.
	/// </summary>
	/// <param name="m_input"> - Takes in input from user and passes it around objects that require it</param>
	/// <param name="s_Renderer"> - Renderer that will handle rendering of scene data</param>
	///  <param name="s_Window"> - Window where the scene is displayed</param>
	/// <param name="window_w"> - Current window's width</param>
	/// <param name="window_h"> - Current window's height</param>
	Scene(Input* m_input, SDL_Renderer* s_Renderer, SDL_Window* s_Window, int window_w, int window_h);

	/// <summary>
	/// Destructor. Unloads and destroys scene objects to free memory and allow a clean exit from the scene.
	/// </summary>
	~Scene();

	
	//------------------Variables------------------
	

	// Renderer
	SDL_Renderer* m_Renderer;

	// Window
	SDL_Window* m_Window;

	// Debugging
	int OldTime;
	Frametime frameTimes;

	// Variables used for moving the enemy
	bool AIdirection;
	int offset;
	int initialPos;

	// Scene objects
	std::vector<GameObject*> sceneObjects;
	GameObject* sceneText;
	GameObject* background;
	GameObject* m_monster;
	GameObject* m_monsterTrans;
	GameObject* m_monsterTransKeyed;
	GameObject* m_movingMonster;
	string myString = " ";

	// Engine Interface
	I_GUI* interface;
	string objectName;
	int nrofObj;
	GameObject* AssetToDrag;
	vector<GameObject*> content;


	//------------------Methods------------------

	/// <summary>
	/// Destroys every element of sceneObjects vector and cleans the memory.
	/// </summary>
	void destroyScene();

	/// <summary>
	/// Save the scene elements inside a given vector.
	/// </summary>
	/// <param name="savedSceneObjects"> - Vector that will store the current scene's objects</param>
	void saveScene(vector<GameObject*> savedSceneObjects);

	/// <summary>
	/// Update handles rendering of every frame.
	/// Anything put in here will run every frame.
	/// </summary>
	void Update();
};

