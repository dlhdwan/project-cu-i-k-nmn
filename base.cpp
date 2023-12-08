#include "Base.h"
base_oj::base_oj(){
	p_oj_ = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}
base_oj::~base_oj() {
	Free();
}
bool base_oj::loadimage(std::string path, SDL_Renderer* screen) {
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	// xóa background ảnh 
	if (load_surface != NULL) {
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, color_key_b, color_key_g, color_key_r));
		// key b, key g, key r = màu của background
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL) {
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_oj_ = new_texture;
	
	return p_oj_ != NULL;
}

void base_oj::Render(SDL_Renderer* des, const SDL_Rect* clip /*= NULL*/) {
	SDL_Rect renderquad = { rect.x ,rect.y, rect.w, rect.h }; // vị trí ảnh && kích thước ảnh
	
	SDL_RenderCopy(des, p_oj_, clip, &renderquad); // đẩy toàn bộ thông số của p_oj lên des với kích thước vị trí trong renderquad 

}
void base_oj::Free() {
	if (p_oj_ != NULL) {
		SDL_DestroyTexture(p_oj_);
		p_oj_ = NULL;
		rect.w = 0;
		rect.h = 0;

	}
}