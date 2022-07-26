#include"input.h"
#include"snake_game.h"
namespace snake {
	action input::get_current_action(direction d) {
		while(SDL_PollEvent(&e)!=0) {
			should_quit=(e.type==SDL_QUIT);
			if( e.type == SDL_KEYDOWN ) {
				action where_to_turn;
				//Select surfaces based on key press
				switch( e.key.keysym.sym )
				{
					case SDLK_w:
					where_to_turn=(d==direction::RIGHT)?action::TURN_LEFT:((d==direction::LEFT)?action::TURN_RIGHT:action::DO_NOTHING);
						break;
					case SDLK_a:
					where_to_turn=(d==direction::UP)?action::TURN_LEFT:((d==direction::DOWN)?action::TURN_RIGHT:action::DO_NOTHING);
						break;
					case SDLK_s:
					where_to_turn=(d==direction::LEFT)?action::TURN_LEFT:((d==direction::RIGHT)?action::TURN_RIGHT:action::DO_NOTHING);
						break;
					case SDLK_d:
					where_to_turn=(d==direction::DOWN)?action::TURN_LEFT:((d==direction::UP)?action::TURN_RIGHT:action::DO_NOTHING);
						break;
					default:
					return action::DO_NOTHING;
						break;
				}
				return where_to_turn;
			}
		}
		return action::DO_NOTHING;
	}
}