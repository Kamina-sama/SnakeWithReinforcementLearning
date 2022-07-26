#pragma once
#include"SDL.h"
enum class action;
enum class direction;
namespace snake {
	class input {
		SDL_Event e;
	public:
		action get_current_action(direction d);
		bool should_quit=false;
	};
}
