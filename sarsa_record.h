#pragma once
#include"record.h"
#include"snake_game.h"  //for action enum
//every time the reinforcement learning agent takes an action, it must record how that MDP (Markov decision process)
//transition went so the algorithm can work. the necessary things to remember are those described in this class: 
struct sarsa_record: public record {
	action action_took_after;
	sarsa_record(): record(), action_took_after((action)0) {
		
	}
	sarsa_record(const sarsa_record& sr): record(sr), action_took_after(sr.action_took_after) {}
};
