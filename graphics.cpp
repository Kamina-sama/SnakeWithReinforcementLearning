#include"graphics.h"
#include"SDL.h"
#include<stdio.h>

graphics::graphics(std::string window_name, const int width, const int height):screen_width(width), screen_height(height) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else {
		//Create window
		window = SDL_CreateWindow( window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else {
			screenSurface=SDL_GetWindowSurface(window);
		}
	}
}
graphics::graphics(graphics&& g):window(g.window), screenSurface(g.screenSurface), screen_width(g.screen_width), screen_height(g.screen_height) {
	g.window=nullptr;
	g.screenSurface=nullptr;
}
graphics::~graphics() {
	//Destroy window
	SDL_DestroyWindow( window );
	//Quit SDL subsystems
	SDL_Quit();
}
void graphics::draw_box(int x, int y, int width, int height, draw_color color /*=draw_color::WHITE*/) {
	SDL_Rect rect={x,y,width,height};
	SDL_FillRect(screenSurface, &rect, translate_color(color));
}
graphics::color_translated graphics::translate_color(draw_color color) const {
	int r=0,g=0,b=0;
	switch(color) {
		case RED:
		r=0xFF;
			break;
		case GREEN:
		g=0xFF;
			break;
		case BLUE:
		b=0xFF;
			break;
		case WHITE:
		r=0xFF;
		g=0xFF;
		b=0xFF;
			break;
		case PURPLE:
		r=0xFF;
		b=0xFF;
			break;
		default:
		case BLACK:
			break;
	}
	return SDL_MapRGB( screenSurface->format, r,g,b);
}
void graphics::render() {
	SDL_UpdateWindowSurface(window);
}
void graphics::clear_screen(draw_color color /*=draw_color::BLACK*/) {
	draw_box(0,0, screen_width, screen_height, color);
}
void graphics::convert_grid_to_screen_coordinates(int i, int j, int& x, int& y, const int grid_x_size, const int grid_y_size) const {
	const double box_x_size=(double)screen_width/grid_x_size;
	const double box_y_size=(double)screen_height/grid_y_size;
	const double i_scaling_factor=(screen_width-box_x_size)/(grid_x_size-1);
	const double j_scaling_factor=(screen_height-box_y_size)/(grid_y_size-1);
	x=i*i_scaling_factor;
	y=j*j_scaling_factor;
}
