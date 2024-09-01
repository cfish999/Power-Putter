#pragma once

#include <memory>
#include <stack>
#include "state.h"

namespace Fish
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() { } // constructor
		~StateMachine() { } // destructor

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		void ProcessStateChanges();

		StateRef& GetActiveState();

	private:

		std::stack<StateRef> _states; // a stack of the states
		StateRef _newState; // the new state to be added

		bool _isRemoving; // variable for whether we are removing a state 
		bool _isAdding, _isReplacing; // variable for whether we are adding or replacing a state 
	};
}