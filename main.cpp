#include "Base.h"
#include"CommonFunc.h"
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


base_oj g_bg;

bool initdata() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) { return false; }

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	// Bắt đầu tạo cửa sổ window
	
	
	g_window = SDL_CreateWindow("background game ", 
								SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								chieu_rong, chieu_cao, SDL_WINDOW_SHOWN);
	if (g_window == NULL) { success = false; }
	else 
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) 
		{
			success = false; 
		}
		else
			{
				SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
				int ImgFlags = IMG_INIT_JPG;
				if (!(IMG_Init(ImgFlags) && ImgFlags)) { success = false; }
			}
	
	}
	return success;
}


bool loadbg() {
	bool ret = g_bg.loadimage("bg.JPG", g_screen);
	if (ret == false) {
		return false;

	}
	return true;


}

void close() {
	g_bg.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();

		
}


int main(int argc, char* argv[])
{
	if (initdata() == false) {
		return -1;
	}
	if (loadbg() == false) { return -1; }
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&g_event) != 0) {
			if ( (g_event.type) == SDL_QUIT) {
				quit = false;
			}
		}
		SDL_SetRenderDrawColor(g_screen, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color);
		SDL_RenderClear(g_screen);
		g_bg.Render(g_screen, NULL);
		SDL_RenderPresent(g_screen);

	}
	close();
	return 0;

}