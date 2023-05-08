#include <SDL.h>
#include <stdio.h>
#include "input.h"



Input::Input()
{
	int i;
	for(i=0;i< SIZE_OF_KEYS_PRESSED_ENUM;i++)
		m_keysPressed[i] = false;

}

Input::~Input()
{

	

}

void Input::Update(void)
{
	//Loop through all the events
	while (SDL_PollEvent(&m_event) != NULL)
	{
		// If an event is found we process it.
		// We check for a key down event:
		if (m_event.type == SDL_KEYDOWN)
		{
			// Cache the code of key we pressed for easier debugging.
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			// Update the keys.
			switch (keyPressed)
			{
				case SDLK_ESCAPE:
					m_keysPressed[KEY_ESCAPE] = true;
					break;

				case SDLK_r:
					m_keysPressed[KEY_R] = true;
					break;

				case SDLK_g:
					m_keysPressed[KEY_G] = true;
					break;

				case SDLK_b:
					m_keysPressed[KEY_B] = true;
					break;

				case SDLK_w:
					m_keysPressed[KEY_W] = true;
					break;

				case SDLK_a:
					m_keysPressed[KEY_A] = true;
					break;

				case SDLK_s:
					m_keysPressed[KEY_S] = true;
					break;

				case SDLK_d:
					m_keysPressed[KEY_D] = true;
					break;



			}
		}

		// Check for key up.
		else if (m_event.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = m_event.key.keysym.sym;


			// Update keys.
			switch (keyPressed)
			{
			case SDLK_r:
				m_keysPressed[KEY_R] = false;
				break;

			case SDLK_g:
				m_keysPressed[KEY_G] = false;
				break;

			case SDLK_b:
				m_keysPressed[KEY_B] = false;
				break;

			case SDLK_w:
				m_keysPressed[KEY_W] = false;
				break;

			case SDLK_a:
				m_keysPressed[KEY_A] = false;
				break;

			case SDLK_s:
				m_keysPressed[KEY_S] = false;
				break;

			case SDLK_d:
				m_keysPressed[KEY_D] = false;
				break;

			}
		}
	}
}

void Input::HandleKeys()
{
	if (KeyIsPressed(KEY_R))
	{
		//cout << "r" << endl;
	}

	if (KeyIsPressed(KEY_G))
	{
		//cout << "g" << endl;
	}

	if (KeyIsPressed(KEY_B))
	{
		//cout << "b" << endl;
	}

	if (KeyIsPressed(KEY_W))
	{

		//cout << "w" << endl;
	}

	if (KeyIsPressed(KEY_A))
	{

		//cout << "a" << endl;
	}

	if (KeyIsPressed(KEY_S))
	{

		//cout << "s" << endl;
	}

	if (KeyIsPressed(KEY_D))
	{

		//cout << "d" << endl;
	}
}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];

}


