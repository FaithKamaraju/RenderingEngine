#pragma once

enum class GraphicsAPI {
	OPENGL = 0,
	D3D11 = 1,
	VULKAN = 2,
	D3D12 = 3,
	METAL = 4,
};

// Boolean Enums
typedef bool FEbool;

constexpr FEbool FE_FAILED =								0x00000000;
constexpr FEbool FE_FALSE =									0x00000000;
constexpr FEbool FE_SUCCESS =								0x00000001;
constexpr FEbool FE_TRUE =									0x00000001;

// Log Level Enums
typedef unsigned int FELogLevel;

constexpr FELogLevel FE_ERROR =								0x00000001;
constexpr FELogLevel FE_WARNING =							0x00000002;
constexpr FELogLevel FE_INFO =								0x00000004;

// Window Mode enums
typedef unsigned int FEWindowMode;

constexpr FEWindowMode FE_WINDOW_VISIBLE =					0x00000001;
constexpr FEWindowMode FE_WINDOW_HIDDEN =					0x00000002;
constexpr FEWindowMode FE_WINDOW_WINDOWED =					0x00000004;
constexpr FEWindowMode FE_WINDOW_BORDERLESS_WINDOWED =		0x00000008;
constexpr FEWindowMode FE_WINDOW_FULLSCREEN =				0x00000010;
constexpr FEWindowMode FE_WINDOW_MINIMIZED =				0x00000020;
constexpr FEWindowMode FE_WINDOW_MAXIMIZED =				0x00000040;

// Cursor Mode enums
typedef unsigned int FECursorMode;

constexpr FECursorMode FE_CURSOR_VISIBLE =					0x00000001;
constexpr FECursorMode FE_CURSOR_HIDDEN =					0x00000002;
constexpr FECursorMode FE_CURSOR_RELATIVE =					0x00000003;
constexpr FECursorMode FE_CURSOR_GRABBED =					0x00000004;
constexpr FECursorMode FE_CURSOR_CAPTURED =					0x00000005;


typedef unsigned int FEInputEventType;

constexpr FEInputEventType FE_EVENT_EMPTY =						0x00000000;
constexpr FEInputEventType FE_EVENT_QUIT =						0x00000001;
constexpr FEInputEventType FE_EVENT_MOUSE_MOTION =				0x00000002;
constexpr FEInputEventType FE_EVENT_MOUSE_BUTTON_UP =			0x00000003;
constexpr FEInputEventType FE_EVENT_MOUSE_BUTTON_DOWN =			0x00000004;
constexpr FEInputEventType FE_EVENT_MOUSE_WHEEL =				0x00000005;

constexpr FEInputEventType FE_EVENT_KEY_UP =					0x00000006;
constexpr FEInputEventType FE_EVENT_KEY_DOWN =					0x00000007;
