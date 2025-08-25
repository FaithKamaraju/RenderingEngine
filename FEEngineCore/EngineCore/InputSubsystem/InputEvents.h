#pragma once

#include "EngineMacros.h"

#include "Symbols.h"
#include "Keycodes.h"
#include "ScanCodes.h"

namespace FE {

	struct FE_API MouseMotionEvent {
		float x, y;			// For mouse movement or position
		float xRel, yRel;
	};

	struct FE_API MouseButtonEvent {
		uint8_t button;
		uint8_t clicks;
		bool down;
		float x, y;
	};

	struct FE_API MouseWheelEvent {
		float wheelX, wheelY;
		int wheelTickX, wheelTickY;
	};

	struct FE_API KeyboardEvent {

		FE_Scancode scancode;  /**< SDL physical key code */
		FE_Keycode keycode;        /**< SDL virtual key code */
		FE_Keymod mod;
		bool down;              /**< true if the key is pressed */
		bool repeat;            /**< true if this is a key repeat */
	};

	struct FE_API InputEvent {
		FEInputEventType type;
		Uint64 timestamp;
		MouseMotionEvent mouseMotion;
		MouseButtonEvent mouseBtn;
		MouseWheelEvent mouseWheel;
		KeyboardEvent key;
		
	};
}
