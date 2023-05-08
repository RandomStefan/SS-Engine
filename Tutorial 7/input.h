#pragma once
#include "SDL.h"

//Global vars for keys the engine will understand

enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE, KEY_R, KEY_G, KEY_B, KEY_W, KEY_A, KEY_S, KEY_D, SIZE_OF_KEYS_PRESSED_ENUM
};


class Input
{
public:

	//------------------Constructor and destructor------------------
	
	/// <summary>
	/// Constructor. Goes through each key in KEYS_PRESSED_LIST and sets their 'pressed' status to false.
	/// </summary>
	Input();

	/// <summary>
	/// Destructor. Currently empty.
	/// </summary>
	~Input();


	//------------------Methods------------------

	/// <summary>
	/// Checks for a key press event among every key from KEYS_PRESSED_LIST and updates their 'pressed' status.
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	/// <summary>
	/// Debugging function currently out of use
	/// </summary>
	void HandleKeys();

	/// <summary>
	/// Returns if a given key from the KEYS_PRESSED_LIST is currently being pressed.
	/// Returns true if is being pressed and false otherwise.
	/// </summary>
	/// <param name="key"> - Key from the keys list</param>
	/// <returns> - Returns if the key given is currently pressed</returns>
	bool KeyIsPressed(KEYS_PRESSED_LIST key);



private:

	SDL_Event m_event;
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];
};
