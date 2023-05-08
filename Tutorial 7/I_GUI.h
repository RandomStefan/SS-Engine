#pragma once
#include "imgui.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"

#include <iostream>
#include <SDL.h>
#include "Sprite.h"

//class Bitmap;

class I_GUI
{
private:


	SDL_Window* currentWindow;
	ImGuiIO io;

public:
	I_GUI(SDL_Renderer* game, SDL_Window* win);
	~I_GUI();


	SDL_Window* getWindow();
	void displayDemo();
	void displayInfo(Sprite* m_sprite);
	//virtual void DrawGUI() = 0;
	void startFrame();
	void endFrame();
};

