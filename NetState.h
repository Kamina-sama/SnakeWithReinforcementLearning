#pragma once
#include"snake_game.h" //for the space, coordinate and direction enums
#include "tiny_dnn/tiny_dnn.h"
using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;

using GridState= snake_game::space (&)[grid_width][grid_height];
inline void copy_grid_state(const GridState from, GridState to) {
	for(int i=0;i<grid_width;++i) for(int j=0;j<grid_height;++j) to[i][j]=from[i][j];
}
//NetState encapsulates the job of transforming the snake game's state 
//into something the neural network library can understand (in the case of tiny_dnn, vector of floats)
struct NetState {
	NetState()=default;
	/*NetState(const GridState grid_state, const coordinate& snake_head, const direction head_pointing):snake_head(snake_head),head_pointing(head_pointing) {
		copy_grid_state(grid_state, grid);
	}*/
	NetState(snake_game& game) /*:snake_head(game.snake[0]),head_pointing(game.head_facing)*/ {
		//game.update_grid(); //the grid is only updated to render the game to screen. this ensures that, no matter the order of the calls, 
		//the NetState will never get an outdated version. While flexibe, this approach might be more inneficient since the grid is updated twice... Too bad!
		//copy_grid_state(game.grid, grid);
		convert_game_to_state(game);
	} 
	NetState(const NetState& state) /*: NetState((GridState)state.grid, state.snake_head, state.head_pointing) {}*/ =default;
	operator vec_t() const {
		vec_t v(length);
		/*for(int i=0 ; i<grid_width ; ++i) {
			for(int j=0 ; j<grid_height ; ++j) {
				v[grid_width*j+i]=(float)grid[i][j];
			}
		}
		//M axb (a rows by b columns). in row y= y0, y1, y2 ... y(b-1) (b total elements) matrix index=b*j+i
		v[length-3]=((float)snake_head.x);
		v[length-2]=((float)snake_head.y);
		v[length-1]=((float)head_pointing);*/
		v[0]=(float)apple_above;
		v[1]=(float)apple_below;
		v[2]=(float)apple_left;
		v[3]=(float)apple_right;
		
		v[4]=(float)snake_up;
		v[5]=(float)snake_down;
		v[6]=(float)snake_left;
		v[7]=(float)snake_right;
		
		v[8]=(float)obstacle_above;
		v[9]=(float)obstacle_below;
		v[10]=(float)obstacle_left;
		v[11]=(float)obstacle_right;
		
		v[12]=(float)obstacle_above2;
		v[13]=(float)obstacle_below2;
		v[14]=(float)obstacle_left2;
		v[15]=(float)obstacle_right2;
		
		v[16]=(float)obstacle_above3;
		v[17]=(float)obstacle_below3;
		v[18]=(float)obstacle_left3;
		v[19]=(float)obstacle_right3;
		
		/*v[20]=(float)obstacle_above_left;
		v[21]=(float)obstacle_above_right;
		v[22]=(float)obstacle_below_left;
		v[23]=(float)obstacle_below_right;
		v[24]=(float)obstacle_above_left2;
		v[25]=(float)obstacle_above_right2;
		v[26]=(float)obstacle_below_left2;
		v[27]=(float)obstacle_below_right2;
		v[28]=(float)obstacle_above_left3;
		v[29]=(float)obstacle_above_right3;
		v[30]=(float)obstacle_below_left3;
		v[31]=(float)obstacle_below_right3;*/
		return v;
	}
	const static size_t length=20; //total length of the vector, needed for neural net initialization (how many inputs will it take)
	/*coordinate snake_head;
	direction head_pointing;*/
	
	void convert_game_to_state(snake_game& game) {
		game.update_grid();
		const coordinate snake_head=game.snake[0];
		const coordinate apple=game.apple;
		apple_above=snake_head.y-apple.y>0;
		apple_below=snake_head.y-apple.y<0;
		apple_left=snake_head.x-apple.x>0;
		apple_right=snake_head.x-apple.x<0;
		switch(game.head_facing) {
			case direction::UP:
			snake_up=true;
			snake_down=snake_left=snake_right=false;
			break;
			case direction::DOWN:
			snake_down=true;
			snake_up=snake_left=snake_right=false;
			break;
			case direction::LEFT:
			snake_left=true;
			snake_down=snake_up=snake_right=false;
			break;
			case direction::RIGHT:
			snake_right=true;
			snake_down=snake_left=snake_up=false;
			break;
		}
		obstacle_above= ((snake_head.y==0) or (game.grid[snake_head.x][snake_head.y-1]==snake_game::space::SNAKE));
		obstacle_below= ((snake_head.y==grid_height-1) or (game.grid[snake_head.x][snake_head.y+1]==snake_game::space::SNAKE));
		obstacle_left= ((snake_head.x==0) or (game.grid[snake_head.x-1][snake_head.y]==snake_game::space::SNAKE));
		obstacle_right= ((snake_head.x==grid_width-1) or (game.grid[snake_head.x+1][snake_head.y]==snake_game::space::SNAKE));
		
		obstacle_above2= (obstacle_above or (snake_head.y==1) or (game.grid[snake_head.x][snake_head.y-2]==snake_game::space::SNAKE));
		obstacle_below2= (obstacle_below or (snake_head.y==grid_height-2) or (game.grid[snake_head.x][snake_head.y+2]==snake_game::space::SNAKE));
		obstacle_left2= (obstacle_left or (snake_head.x==1) or (game.grid[snake_head.x-2][snake_head.y]==snake_game::space::SNAKE));
		obstacle_right2= (obstacle_right or (snake_head.x==grid_width-2) or (game.grid[snake_head.x+2][snake_head.y]==snake_game::space::SNAKE));
		
		obstacle_above3= (obstacle_above2 or (snake_head.y==2) or (game.grid[snake_head.x][snake_head.y-3]==snake_game::space::SNAKE));
		obstacle_below3= (obstacle_below2 or (snake_head.y==grid_height-3) or (game.grid[snake_head.x][snake_head.y+3]==snake_game::space::SNAKE));
		obstacle_left3= (obstacle_left2 or (snake_head.x==2) or (game.grid[snake_head.x-3][snake_head.y]==snake_game::space::SNAKE));
		obstacle_right3= (obstacle_right2 or (snake_head.x==grid_width-3) or (game.grid[snake_head.x+3][snake_head.y]==snake_game::space::SNAKE));
		
		/*bool obstacle_above_left=((snake_head.x==0) or (snake_head.y==0) or (game.grid[snake_head.x-1][snake_head.y-1]==snake_game::space::SNAKE));
		bool obstacle_above_right=((snake_head.x==grid_width-1) or (snake_head.y==0) or (game.grid[snake_head.x+1][snake_head.y-1]==snake_game::space::SNAKE));
		bool obstacle_below_left=((snake_head.x==0) or (snake_head.y==grid_height-1) or (game.grid[snake_head.x-1][snake_head.y+1]==snake_game::space::SNAKE));
		bool obstacle_below_right=((snake_head.x==grid_width-1) or (snake_head.y==grid_height-1) or (game.grid[snake_head.x+1][snake_head.y+1]==snake_game::space::SNAKE));
		
		bool obstacle_above_left2=(obstacle_above_left or (snake_head.x==1) or (snake_head.y==1) or (game.grid[snake_head.x-2][snake_head.y-2]==snake_game::space::SNAKE));
		bool obstacle_above_right2=(obstacle_above_right or (snake_head.x==grid_width-2) or (snake_head.y==1) or (game.grid[snake_head.x+2][snake_head.y-2]==snake_game::space::SNAKE));
		bool obstacle_below_left2=(obstacle_below_left or (snake_head.x==1) or (snake_head.y==grid_height-2) or (game.grid[snake_head.x-2][snake_head.y+2]==snake_game::space::SNAKE));
		bool obstacle_below_right2=(obstacle_below_right or (snake_head.x==grid_width-2) or (snake_head.y==grid_height-2) or (game.grid[snake_head.x+2][snake_head.y+2]==snake_game::space::SNAKE));
		
		bool obstacle_above_left3=(obstacle_above_left2 or (snake_head.x==2) or (snake_head.y==2) or (game.grid[snake_head.x-3][snake_head.y-3]==snake_game::space::SNAKE));
		bool obstacle_above_right3=(obstacle_above_right2 or (snake_head.x==grid_width-3) or (snake_head.y==2) or (game.grid[snake_head.x+3][snake_head.y-3]==snake_game::space::SNAKE));
		bool obstacle_below_left3=(obstacle_below_left2 or (snake_head.x==2) or (snake_head.y==grid_height-3) or (game.grid[snake_head.x-3][snake_head.y+3]==snake_game::space::SNAKE));
		bool obstacle_below_right3=(obstacle_below_right2 or (snake_head.x==grid_width-3) or (snake_head.y==grid_height-3) or (game.grid[snake_head.x+3][snake_head.y+3]==snake_game::space::SNAKE));*/
	}
	bool apple_above;
	bool apple_below;
	bool apple_left;
	bool apple_right;
	bool snake_up;
	bool snake_down;
	bool snake_left;
	bool snake_right;
	
	bool obstacle_above;
	bool obstacle_below;
	bool obstacle_left;
	bool obstacle_right;
	
	bool obstacle_above2;
	bool obstacle_below2;
	bool obstacle_left2;
	bool obstacle_right2;
	
	bool obstacle_above3;
	bool obstacle_below3;
	bool obstacle_left3;
	bool obstacle_right3;
	
	/*bool obstacle_above_left;
	bool obstacle_below_left;
	bool obstacle_above_right;
	bool obstacle_below_right;
	
	bool obstacle_above_left2;
	bool obstacle_below_left2;
	bool obstacle_above_right2;
	bool obstacle_below_right2;
	
	bool obstacle_above_left3;
	bool obstacle_below_left3;
	bool obstacle_above_right3;
	bool obstacle_below_right3;*/
	/*snake_game::space grid[grid_width][grid_height];*/
};