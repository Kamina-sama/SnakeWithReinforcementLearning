#pragma once
#include"NetState.h" //for netstate struct
#include"snake_game.h"  //for action enum
//every time the reinforcement learning agent takes an action, it must record how that MDP (Markov decision process)
//transition went so the algorithm can work. the necessary things to remember are those described in this class: 
struct record {
	NetState before_action;
	action action_took;
	int reward;
	NetState after_action;
	record():before_action(), action_took((action)0), reward(0), after_action() {
		
	}
	record(const record&)=default;
	virtual ~record()=default;
};
