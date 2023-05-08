#pragma once
#include <iostream>

#include "vector"
#include "string"

#include "Sprite.h"
#include "SDL_ttf.h"

using namespace std;

// Structure to store object's coords
struct coords
{
	int x;
	int y;
};

// Enum to store type of objects
enum Type
{
	SPRITE,
	TRIGGER,
	TEXT,
	NUM_ELEMENTS
};

class GameObject
{
private:

	//------------------Variables------------------

	
	Input* input; // Input
	SDL_Renderer* game; // Renderer

	// Font
	TTF_Font* defaultFont;
	const char* fontPath;
	int fontSize;


public:

	//------------------Constructor------------------


	/// <summary>
	/// Constructor.
	/// Creates a GameObject object that takes in an SDL Renderer, a type and a name
	/// </summary>
	/// <param name="m_game"> - Renderer that will render the object </param>
	/// <param name="objType"> - Type that can be either Sprite, Trigger or Text</param>
	/// <param name="objName"> - Name of the created object for reference</param>
	GameObject(SDL_Renderer* m_game, Type objType, string objName);


	//------------------Variables------------------

	string name; // Name of the object
	Sprite* m_Sprite; // Sprite of the object if applicable
	Type type; // Determines type of the object (SPRITE, TRIGGER, TEXT)
	coords objCoords; // Srores object's coords
	int layer; // Determines the layer where the object is situated


	//------------------Methods------------------

	/// <summary>
	/// Adds the game object into the vector of game objects
	/// </summary>
	/// <param name="Objects"> - Vector of game objects to take in the new object</param>
	void addObject(std::vector<GameObject*>& Objects);

	/// <summary>
	/// Removes the game object from a vector of game objects
	/// </summary>
	/// <param name="Objects"> - Vector of game objects to remove the object from</param>
	/// <param name="name"></param>
	void removeObject(std::vector<GameObject*>& Objects);



	/// <summary>
	/// Initializez a sprite object.
	/// </summary>
	/// <param name="path"> - Path to the image for the sprite</param>
	/// <param name="x"> - Location on the x Axis of the scene</param>
	/// <param name="y"> - Location on the y Axis of the scene</param>
	/// <param name="transparent"> - Use transparency on the image ?</param>
	/// <param name="layer"> - Layer to be drawn to</param>
	void initSprite(string path, int x, int y, bool transparent, int layer);

	/// <summary>
	/// Initializez a trigger object.
	/// </summary>
	/// <param name="x"> - Location on the x Axis of the scene</param>
	/// <param name="y"> - Location on the y Axis of the scene</param>
	void initTrigger(int x, int y);

	/// <summary>
	/// Initializez the text with a given font.
	/// </summary>
	/// <param name=""> - Path to the font used for the text</param>
	void initText(const char*);
	



	/// <summary>
	/// Sets the value of x and y of the game object.
	/// </summary>
	/// <param name="x"> - Sets the value of x Axis to "x"</param>
	/// <param name="y"> - Sets the value of y Axis to "y"</param>
	void setCoords(int x, int y);

	/// <summary>
	/// Offset the position by an ammount
	/// </summary>
	/// <param name="x"> - x ammount of offset on the x Axis</param>
	/// <param name="y"> - y ammount of offset on the y Axis</param>
	void offsetPosition(int x, int y);

	/// <summary>
	/// Automatically moves an object on the Y Axis on one direction until "dir" tells it to go the other direction.
	/// </summary>
	/// <param name="dir"> - Dictates the direction the object will head: up or down</param>
	void autoMoveYAxis(bool dir);

	/// <summary>
	/// Checks collision between object that called the function and another object.
	/// Works for SPRITE and TRIGGER type objects.
	/// TRIGGER objects don't have a sprite so their sprite values will be set to 0.
	/// </summary>
	/// <param name="object"> - Object that collides with object that called checkCollision</param>
	/// <returns></returns>
	bool checkCollision(GameObject* object);

	
	

	/// <summary>
	/// Updates text on screen.
	/// </summary>
	/// <param name="msg"> - Text to be shown</param>
	/// <param name="x"> - Location on the x axis of the text</param>
	/// <param name="y"> - Location on the y axis of the text</param>
	/// <param name="fontSize"> - Font size</param>
	/// <param name="colour"> - Color of the text</param>
	void UpdateText(string msg, int x, int y, int fontSize, SDL_Color colour);

	/// <summary>
	/// Calls according function based on the object's type.
	/// For SPRITE type objects calls draw()
	/// For TRIGGER type objects prints created location.
	/// For TEXT type objects doesn't do anything. Call UpdateText() instead.
	/// </summary>
	void render();

	/// <summary>
	/// Function that acts like a destructor.
	/// Checks the type of GameObject it is called from and calls their corresponding functions that destroys them
	/// </summary>
	void destroy();



	/// <summary>
	/// Used to dictate how much the player's position will offset when pressing a specified key.
	/// </summary>
	/// <param name="m_input"> - Takes in an input variable to use to handle key press events</param>
	void handleInput(Input* m_input);

	/// <summary>
	/// Not used. For debugging.
	/// </summary>
	void updateInput();

	/// <summary>
	/// Checks the number of times the name of the object is found inside a game object vector.
	/// </summary>
	/// <param name="objects"> - Vector to search in</param>
	/// <returns> - Returns number of times the name is found in the vector</returns>
	int checkName(vector<GameObject*> objects);

	/// <summary>
	/// Returns path to the image used for the sprite.
	/// </summary>
	/// <returns> - Returns string that holds the path to the image used for the sprite</returns>
	string getPathToTexture();


	
};

