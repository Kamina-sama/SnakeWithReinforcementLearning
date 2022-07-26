#include<vector>
#include<deque>
#include<type_traits>
#include<ccomplex>
template<typename State, typename Action> class QLearningPolicy {
public:
	struct Record {
		State beforeAction;
		Action actionTook;
		int reward;
		State afterAction;
	};
};
template<typename State, typename Action> class SarsaPolicy {
public:
	struct Record {
		State beforeAction;
		Action actionTook;
		int reward;
		State afterAction;
		Action actionTookInNewState;
	};
};
temp
template<typename State=std::vector<double>, typename Action=int, template<typename ST, typename A> class AlgorithmPolicy=QLearningPolicy>
class DeepRLAgent: public AlgorithmPolicy, private ActionTrait<Action> {
	using RecordType=typename AlgorithmPolicy<State, Action>::Record;
	std::deque<RecordType> memory_replay;
	RecordType current_memory;
public:
	double epsilon=1;
	double epsilon_decay=0.9999;
	double epsilon_threshold=0.01;
	double discount_factor=0.95;
	double learning_rate=0.00025;
	Action Step(const State& state) {
		epsilon=std::max(epsilon*epsilon_decay,epsilon_threshold);
		if(epsilon>randMToN(0,1)) {
			Action a=random_action();
			current_memory.action_took=a;
			return a;
		}
	}
	void TrainNetworks() {
		
	}
private:
	double randMToN(double M, double N) const {
		return M + (rand() / ( RAND_MAX / (N-M) ));  
	}
};


/*
 * RLAgent 
 * 
 * 
 * 
 * 
 * 
 * 
 * */