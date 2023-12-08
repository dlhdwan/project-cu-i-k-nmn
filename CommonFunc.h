#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_


#include<windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Surface* g_object = NULL;   // sử dụng để quản lý nhân vật


// màn hình
const int chieu_rong = 1200;
const int chieu_cao = 586;
const int pixel = 32;
// màu sắc
const int color_key_r = 167;
const int color_key_g = 175;
const int color_key_b = 180;
 
const int Render_Draw_Color = 0Xff;
#endif