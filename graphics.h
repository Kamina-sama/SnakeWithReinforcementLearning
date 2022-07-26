#pragma once
#include"SDL.h"
#include<string>

enum draw_color {RED, GREEN, BLUE, YELLOW, PURPLE, WHITE, BLACK};

class graphics {
	//The window we'll be rendering to
    SDL_Window* window = nullptr;
    //The surface contained by the window
    SDL_Surface* screenSurface = nullptr;
	//TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
public:
	const int screen_width;
	const int screen_height;
	
	using color_translated=decltype(SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));
	
	graphics(std::string window_name, int width, int height);
	graphics(graphics&& g);
	~graphics();
	void draw_box(int x, int y, int width, int height, draw_color color=draw_color::WHITE);
	void render();
	void clear_screen(draw_color color=draw_color::BLACK);
	void convert_grid_to_screen_coordinates(int i, int j, int& x, int& y, const int grid_x_size, const int grid_y_size) const;
private:
	color_translated translate_color(draw_color color) const;
};