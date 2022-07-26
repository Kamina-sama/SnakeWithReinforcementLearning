#pragma once
#include"NetState.h"
#include"sarsa_record.h"
#include<deque>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;

class snake_game;

class SarsaAgent {
private:
	network<sequential> net1;
	network<sequential> net2;
	adam optim;
	//these are the algorithm hyper-parameters, to be tuned in ad-hoc fashion to the task being solved (in this case, snek)
public:
	double epsilon=1;
private:
	double epsilon_decay=0.9999;
	double epsilon_threshold=0.01;
	double discount_factor=0.95;
	double learning_rate=0.00025;
	//---------------------------------------------------------------------------------------------------------------------
	std::deque<sarsa_record> experience_replay;
	const int experience_replay_size=2500;
	sarsa_record current_memory;
public:
	SarsaAgent();
	//Warning: this function can only be meaningfully used AFTER "play_game_step" is called. 
	//This is because that function updates partially the current memory record (leaving the rest of the update and storage to this function).
	//calling this function without that one before is a MISTAKE.
	void store_current_memory(const int reward, action action_after, snake_game& game);
	action play_game_step(snake_game& game);
	void train_networks();
private:
	//float max_Q_value(const NetState& current, network<sequential>& net) const; //needed for "training the nets" step part of the algorithm
	void initialize_net(network<sequential>& net);
	double randMToN(double M, double N) const; //auxiliary function made to compare with epsilon in "play_game_step" (epsilon-greedy policy)
};