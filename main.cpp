#include"snake_game.h"
#include<utility>
#include<iostream>
#include<deque>
#include<thread>
#include"DeepQAgent.h"
#include "tiny_dnn/tiny_dnn.h"

int main(int argc, char **argv)
{
	using namespace std::chrono_literals;
	auto g=graphics("Snake",600,600); //600x600 pixels
	snake::input input_handler;
	auto game=snake_game(std::move(g),input_handler,100); //100ms per frame
	
	DeepQAgent agent;
	int episodes=0;
	int episodic_threshold=1400;
	while(true) {
		int reward=0;
		int apples=0;
		action agent_action=agent.play_game_step(game);
		while(reward!=reward_game_over) {
			reward=game.game_step(agent_action);
			if(reward==reward_apple) ++apples;
			agent.store_current_memory(reward, game);
			agent_action=agent.play_game_step(game);
			if(episodes>episodic_threshold) {
				game.draw_graphics();
				std::this_thread::sleep_for(200ms);
			}
			agent.train_networks();
		}
		++episodes;
		std::cout<<"Episode nº"<<episodes<<" finished."<< std::endl;
		std::cout<<"Episode score (apples eaten): "<<apples<<std::endl;
		std::cout<<"Current epsilon value:"<<agent.epsilon<<std::endl;
		//agent.train_networks();
	}
	
	return 0;
}
	/*
	
	auto g=graphics("Snake",600,600); //600x600 pixels
	snake::input input_handler;
	auto game=snake_game(std::move(g),input_handler,100); //100ms per frame

	
	DeepQAgent agent;
	while(true) {
		int reward=0;
		action agent_action=agent.play_game_step(game.grid);
		while(reward!=reward_game_over) { //magic constant, fix this (-1000 is the game over reward)
			reward=game.game_step(agent_action);
			agent.store_experience(agent_action,reward,game.grid);
			agent_action=agent.play_game_step(game.grid);
		}
		agent.train_networks();
		agent.reset();
	}
	
	*/
