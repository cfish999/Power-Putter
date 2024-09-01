#include "StateMachine.h"

namespace Fish
{
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		// prepares variables for processStateChanges to add a state
		this->_isAdding = true;
		this->_isReplacing = isReplacing;

		this->_newState = std::move(newState);
	}

	void StateMachine::RemoveState()
	{
		// prepares variables for processStateChanges to remove a state
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		// if removing is true and the stack of states is not empty
		if (this->_isRemoving && !this->_states.empty())
		{
			// remove the top state
			this->_states.pop();

			// if the new highest state is present and the stack is not empty run the new top of the stack state
			if (!this->_states.empty())
			{
				this->_states.top()->Resume();
			}

			// set removing to false as state has now been removed
			this->_isRemoving = false;
		}

		// if state should be added (_isAdding is true)
		if (this->_isAdding)
		{
			// if the stack isn't empty
			if (!this->_states.empty())
			{
				// if replacing is trye
				if (this->_isReplacing)
				{
					// remove the top most state
					this->_states.pop();
				}
				else
				{
					// pause the action of the top most state
					this->_states.top()->Pause();
				}
			}

			// pushes the new state onto the top of the stack
			this->_states.push(std::move(this->_newState));
			// initialises the new state 
			this->_states.top()->Init();
			// sets adding to false as operation is now complete
			this->_isAdding = false;
		}
	}

	StateRef& StateMachine::GetActiveState()
	{
		// returns the state that is currently running
		return this->_states.top();
	}
}