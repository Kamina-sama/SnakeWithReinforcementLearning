#include"snake_game.h"
#include<utility>
#include<thread>
#include<algorithm>
#include<vector>
#include<iostream>
snake_game::snake_game(graphics&& g, snake::input input_handler, int milliseconds_per_frame): 
	gfx(std::move(g)), 
	input_handler(input_handler), 
	frame_time(milliseconds_per_frame), 
	box_size_x(gfx.screen_width/grid_width), 
	box_size_y(gfx.screen_height/grid_height) {
	reset();
	update_grid();
	previous_distance_from_apple=distance_to_apple();
}
bool snake_game::snake_in_coordinate(int x, int y) const {
	coordinate c(x,y);
	auto it=std::find(snake.begin()+1, snake.end(), c);
	return it!=snake.end();
}
void snake_game::reset() {
	head_facing=direction::RIGHT;
	snake.clear();
	snake.emplace_front(3,3);
	snake.emplace_back(2,3);
	snake.emplace_back(1,3);
	update_apple_position();
}
void snake_game::game_loop() {
	while(!input_handler.should_quit) {
		auto this_frame_begin=std::chrono::system_clock::now();
		game_step(input_handler.get_current_action(head_facing));
		auto this_frame_end=std::chrono::system_clock::now();
		auto difference=this_frame_end - this_frame_begin;
		auto how_long_to_sleep=frame_time - difference;
		std::this_thread::sleep_for(how_long_to_sleep);
	}
}
int snake_game::game_step(action a) {
	int reward=process_game_state(a);
	return reward;
}
int snake_game::process_game_state(action a) {
	coordinate snake_head=snake.front();
	switch(a) {
		case action::DO_NOTHING:
		default:
			break;
		case action::TURN_LEFT:
			switch(head_facing) {
				case direction::UP:
					head_facing=direction::LEFT;
					break;
				case direction::LEFT:
					head_facing=direction::DOWN;
					break;
				case direction::RIGHT:
					head_facing=direction::UP;
					break;
				case direction::DOWN:
					head_facing=direction::RIGHT;
					break;
			}
			break;
		case action::TURN_RIGHT:
			switch(head_facing) {
				case direction::UP:
					head_facing=direction::RIGHT;
					break;
				case direction::LEFT:
					head_facing=direction::UP;
					break;
				case direction::RIGHT:
					head_facing=direction::DOWN;
					break;
				case direction::DOWN:
					head_facing=direction::LEFT;
					break;
			}
			break;
	}
	switch(head_facing) {
		case direction::UP:
			if(snake_head.y-1<0) {
				reset();
				return reward_game_over;
			}
			snake.emplace_front(snake_head.x, snake_head.y-1);
		break;
		case direction::LEFT:
			if(snake_head.x-1<0) {
				reset();
				return reward_game_over;
			}
			snake.emplace_front(snake_head.x-1, snake_head.y);
		break;
		case direction::RIGHT:
			if(snake_head.x+1>=grid_width) {
				reset();
				return reward_game_over;
			}
			snake.emplace_front(snake_head.x+1, snake_head.y);
		break;
		case direction::DOWN:
			if(snake_head.y+1>=grid_width) {
				reset();
				return reward_game_over;;
			}
			snake.emplace_front(snake_head.x, snake_head.y+1);
		break;
	}
	snake_head=snake.front();
	const int distance_apple=distance_to_apple();
	int reward= (distance_apple<previous_distance_from_apple)? reward_closer_to_apple: reward_further_from_apple; //calculate distance to apple, return
	previous_distance_from_apple=distance_apple;
	if(apple!=snake_head) snake.pop_back();
	else {
		reward=reward_apple;
		update_apple_position();
	}
	auto collision=std::find(snake.begin()+1, snake.end(), snake_head);
	if(collision!=snake.end()) {
		reward=reward_game_over;
		reset();
	}
	return reward;
}
void snake_game::update_grid() {
	for(auto& r:grid) for(auto& elem:r) elem=space::EMPTY;
	grid[apple.x][apple.y]=APPLE;
	for(const auto& snake_part:snake) grid[snake_part.x][snake_part.y]=SNAKE;
}
void snake_game::draw_graphics() {
	gfx.clear_screen();
	update_grid();
	draw_color whatToDraw;
	for(int i=0;i<grid_width;++i) {
		for(int j=0;j<grid_height;++j) {
			switch(grid[i][j]) {
				case SNAKE:
				whatToDraw=WHITE;
					break;
				case APPLE:
				whatToDraw=RED;
					break;
				case EMPTY:
				default:
				whatToDraw=BLACK;
					break;
			}
			int x,y;
			gfx.convert_grid_to_screen_coordinates(i,j,x,y,grid_width,grid_height);
			gfx.draw_box(x,y,box_size_x,box_size_y,whatToDraw);
		}
	}
	gfx.render();
}
void snake_game::update_apple_position() {
	apple.x=rand()%grid_width;
	apple.y=rand()%grid_height;
}
int snake_game::distance_to_apple() const {
	return std::abs(snake[0].x-apple.x)+std::abs(snake[0].y-apple.y);
}
/*
 * i*S=x     when i=0, x=0, when i=width, x=screen_width-boxSizeX  S=(screen_width-boxSizeX)/width   boxSizeX=screen_width/width
 * j*S2=y    when j=height, y=screen_height-boxSizeY, S2=(screen_height-boxSizeY)/height boxSizeY=screen_height/height
 * 
 * */