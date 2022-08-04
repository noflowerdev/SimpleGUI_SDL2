#include "Includes/Button.hpp"
#include <iostream>
using namespace std;
#undef main
int main()
{
	SDL_Window* window = SDL_CreateWindow("GUI", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("res/fnt.ttf", 15);
	SDL_Event e;
	auto button1 = SimpleGUI::Button("Red", { 100, 100 }, &e, render, font);
	auto button2 = SimpleGUI::Button("Green", { 150, 100 }, &e, render, font);
	auto button3 = SimpleGUI::Button("Blue", { 220, 100 }, &e, render, font);
	auto button4 = SimpleGUI::Button("Exit", { 280, 100 }, &e, render, font);
	bool run = true;
	SDL_Color quad_color = {255, 0, 0, 255};
	SDL_Texture* quad = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, 100, 100);
	SDL_Rect quad_rect = {200, 240, 100, 100};
	while (run)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) run = false;
			button1.OnEvent();
			button2.OnEvent();
			button3.OnEvent();
			button4.OnEvent();
			if (button1.getMouseState() == "enable") quad_color = { 255, 0, 0, 255 };
			if (button2.getMouseState() == "enable") quad_color = { 0, 255, 0, 255 };
			if (button3.getMouseState() == "enable") quad_color = { 0, 0, 255, 255 };
			if (button4.getMouseState() == "enable") run = false;
		}
		SDL_RenderClear(render); 
		button1.OnDraw();
		button2.OnDraw();
		button3.OnDraw();
		button4.OnDraw();
		SDL_SetRenderDrawColor(render, quad_color.r, quad_color.g, quad_color.b, quad_color.a);
		SDL_RenderFillRect(render, &quad_rect);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderPresent(render);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	TTF_CloseFont(font);
	TTF_Quit();
	return 0;
}