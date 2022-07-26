#include"DeepQAgent.h"
DeepQAgent::DeepQAgent() {
	initialize_net(net1);
	initialize_net(net2);
	optim.alpha=learning_rate;
}
void DeepQAgent::store_current_memory(const int reward, snake_game& game) {
	if(experience_replay.size()>=experience_replay_size) experience_replay.pop_back(); //arbitrary max capacity
	current_memory.reward=reward;
	NetState after_action_state(game);
	current_memory.after_action=after_action_state;
	experience_replay.push_front(current_memory);
}
action DeepQAgent::play_game_step(snake_game& game) {
	using tiny_dnn::mse;
	epsilon=std::max(epsilon*epsilon_decay,epsilon_threshold);
	NetState net_state(game);
	current_memory.before_action=net_state;
	if(epsilon>randMToN(0,1)) {
		action a=(action)(rand()%3);
		current_memory.action_took=a;
		return a;
	}
	int a=net1.predict_label((vec_t)net_state);
	current_memory.action_took=(action)a;
	return (action)a;
}
void DeepQAgent::train_networks() {
	static int how_many_times_trained=0;
	const static int how_long_until_update_net2=20;
	const static int batch_size=20;
	
	if(experience_replay.size()<batch_size*20) return;
	std::set<unsigned int> indices;
	while (indices.size() < batch_size) indices.insert(rand()%experience_replay.size());
	
	std::vector<vec_t> y_values;
	std::vector<vec_t> x_values;
	for(auto i:indices) {
		record experience=experience_replay[i];
		auto net_answers=net1.predict((vec_t)experience.before_action);
		
		net_answers[(size_t)experience.action_took]=experience.reward;
		if(experience.reward!=reward_game_over) {
			net_answers[(size_t)experience.action_took]+=discount_factor*max_Q_value(experience.after_action, net2);
		}
		x_values.push_back(std::move((vec_t)experience.before_action));
		y_values.push_back(std::move(net_answers));
	}
	const int epoch=1;
	net1.fit<mse>(optim, x_values, y_values, batch_size, epoch);
	how_many_times_trained=(how_many_times_trained+1)%how_long_until_update_net2;
	if(how_many_times_trained==0) {
		net1.save("net1");
		net2.load("net1");
	}
}
float DeepQAgent::max_Q_value(const NetState& current, network<sequential>& net) const {
	return net.predict_max_value((vec_t)current);
}
void DeepQAgent::initialize_net(network<sequential>& net) {
	using activation::relu;
	net << fc(NetState::length, 20) << relu()  // 
	//<< fc(20, 20) << relu()
	<< fc(20, 20) << relu()
	<< fc(20, 20) << relu()
	<< fc(20, 3);
	assert(net.out_data_size() == 3);
	assert(net.in_data_size() == NetState::length);
}
double DeepQAgent::randMToN(double M, double N) const {
	return M + (rand() / ( RAND_MAX / (N-M) ));  
}