#pragma once


#include "EngineMacros.h"

#include <mutex>
#include <functional>
#include <vector>

#include "EngineCore/Engine.h"
#include "InputEvents.h"
#include "EngineCore/GameplayFramework/Object.h"


namespace FE {

	using Listener = std::function<void(const InputEvent&, float deltaTime)>;

	class FE_API InputHandler
	{

	public:
		InputHandler();

		InputHandler(InputHandler& other) = delete;
		void operator=(const InputHandler&) = delete;

		
		void PollEvents(float deltaTime);
		//void DispatchEvents(float deltaTime);
		void RegisterListener(Listener listener);

		/*void setCursorPos(const MouseCursorPos& cursorPos);
		void setScrollOffset(const MouseScrollOffset& scrollOffset);*/

	protected:

		std::vector<Listener> listeners;

	private:

		

		friend class Engine;
	};

	
}



