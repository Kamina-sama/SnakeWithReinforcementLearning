#pragma once
#include"graphics.h"
#include"input.h"
#include<chrono>
#include<deque>

class NetState;

enum class action {DO_NOTHING, TURN_LEFT, TURN_RIGHT};
enum class direction {UP,LEFT,DOWN,RIGHT};

struct coordinate {
		int x;
		int y;
		coordinate(int x=0, int y=0):x(x),y(y) {}
		bool operator==(const coordinate& c) const {
			return (x==c.x && y==c.y);
		}
		bool operator!=(const coordinate& c) const {
			return !(*this==c);
		}
		coordinate(const coordinate&)=default;
};

inline constexpr int grid_width=10;
inline constexpr int grid_height=10;

inline constexpr int reward_apple=100;
inline constexpr int reward_closer_to_apple=1;
inline constexpr int reward_further_from_apple=-1;
inline constexpr int reward_game_over=-10000;

class snake_game {
	graphics gfx;
	snake::input input_handler;
	const std::chrono::milliseconds frame_time;
	friend class NetState;
public:
	enum space { EMPTY, SNAKE, APPLE } grid[grid_width][grid_height];

	snake_game(graphics&& g, snake::input input_handler, int milliseconds_per_frame);
	void game_loop();
	int game_step(action a);
	void draw_graphics();
private:
	bool snake_in_coordinate(int x, int y) const;
	void reset();
	int process_game_state(action a);
	void update_apple_position();
	void update_grid();
	int distance_to_apple() const;
	coordinate apple;
	std::deque<coordinate> snake;
	direction head_facing;
	const int box_size_x;
	const int box_size_y;
	int previous_distance_from_apple;
};