//#pragma once
#ifndef base_object_h_
#define base_object_h_

#include "CommonFunc.h"
class base_oj
{
public:
	base_oj();
	~base_oj();
	void setrect(const int& x, const int& y) { rect.x = x, rect.y = y; }
	SDL_Rect GetRect() const { return rect; } // lấy ra rect
	SDL_Texture* Getoj() const { return p_oj_; } // lấy ra oj

	bool loadimage(std::string path, SDL_Renderer* screen); // đường dẫn chứa tấm ảnh && màn hình 
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* p_oj_; //lưu trữ hình ảnh
	SDL_Rect rect; // lưu trữ kích thước ảnh
};


#endif 