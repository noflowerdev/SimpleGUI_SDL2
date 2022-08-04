#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "miniMath.hpp"
#include <string>
using std::string;
namespace SimpleGUI {
	class Button
	{
		string title;
		vec2 pos, form;
		SDL_Event* evt = 0;
		SDL_Renderer* render = 0;
		TTF_Font* fnt = 0;
		string mouseMode = "disable";
	public:
		Button(string title, vec2 pos, SDL_Event* e, SDL_Renderer* renderer, TTF_Font* font) :
			title(title), pos(pos), evt(e), render(renderer), fnt(font) {
			int w = 0, h = 0;
			TTF_SizeText(fnt, title.c_str(), &w, &h);
			form.x = 1.5 * w;
			form.y = h;
		}
		~Button(void) {
		}
		string getMouseState(void)
		{
			return mouseMode;
		}
		string& getTitle(void)
		{
			return title;
		}
		void OnEvent(void)
		{
			SDL_Rect m_rect = {
				evt->motion.x, evt->motion.y,
				1, 1
			};
			SDL_Rect b_rect = {
				static_cast<int>(pos.x), static_cast<int>(pos.y),
				static_cast<int>(form.x), static_cast<int>(form.y)
			};
			if (SDL_HasIntersection(&m_rect, &b_rect) && (evt->button.type != SDL_MOUSEBUTTONDOWN)) mouseMode = "hower";
			else if (SDL_HasIntersection(&m_rect, &b_rect) && (evt->button.type == SDL_MOUSEBUTTONDOWN) && (evt->button.button == SDL_BUTTON_LEFT)) mouseMode = "enable";
			else mouseMode = "disable";
		}
		void OnDraw(void)
		{
			SDL_FRect f = {pos.x, pos.y, form.x, form.y};
			uint8_t r, g, b, a;
			SDL_GetRenderDrawColor(render, &r, &g, &b, &a);
			SDL_SetRenderDrawColor(render, 90, 136, 242, 255);
			SDL_RenderDrawRectF(render, &f);
			if (mouseMode == "hower")
			{
				f.x += 1; f.y += 1;
				f.w -= 2; f.h -= 2;
				SDL_SetRenderDrawColor(render, 124*(100/255.0), 141*(100/255.0), 253*(100/255.0), 255);
				SDL_RenderFillRectF(render, &f);
			}
			else if (mouseMode == "enable")
			{
				f.x += 1; f.y += 1;
				f.w -= 2; f.h -= 2;
				SDL_SetRenderDrawColor(render, 90, 136, 242, 150);
				SDL_RenderFillRectF(render, &f);
			}
			SDL_Surface* text_sf = TTF_RenderText_Blended(fnt, title.c_str(), SDL_Color{ 124, 214, 253, 255 });
			SDL_Texture* text_tx = SDL_CreateTextureFromSurface(render, text_sf);
			SDL_FRect text_rect = {
				pos.x + form.x / 8,
				pos.y + form.y / 8,
				text_sf->w, text_sf->h
			};
			SDL_RenderCopyF(render, text_tx, 0, &text_rect);
			SDL_FreeSurface(text_sf);
			SDL_DestroyTexture(text_tx);
			SDL_SetRenderDrawColor(render, r, g, b, a);
		}
	};
}