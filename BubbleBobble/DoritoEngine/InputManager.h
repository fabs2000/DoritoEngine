#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Joystick.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

#include <Xinput.h>
#include <array>
#include <map>

enum class PlayerControllers : DWORD 
{
	Player1 = 0,
	Player2 = 1,
	Player3 = 2,
	Player4 = 3
};

enum class InputTriggerState
{
	Pressed,
	Released,
	Down
};

struct GamePadEvent
{
	GamePadEvent()
		: ActionDesc("No Action")
		, GamepadButtonCode(0)
		, ControllerID(PlayerControllers::Player1)
		, IsTriggered(false)
	{}

	GamePadEvent(const std::string& actionDesc, WORD gamepadButtonCode, PlayerControllers controllerID)
		: ActionDesc(actionDesc)
		, GamepadButtonCode(gamepadButtonCode)
		, ControllerID(controllerID)
		, IsTriggered(false)
	{}

	std::string ActionDesc;
	WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
	PlayerControllers ControllerID;
	bool IsTriggered;
};

//struct ControllerLayout
//{
//	enum Buttons : int
//	{
//		//Face buttons
//		A_BUTTON = static_cast<int>(sf::Joystick::X),
//		B_BUTTON = static_cast<int>(sf::Joystick::Y),
//		X_BUTTON = static_cast<int>(sf::Joystick::Z),
//		Y_BUTTON = static_cast<int>(sf::Joystick::R),
//
//		//D-Pad
//		DPAD_LEFT = static_cast<int>(sf::Joystick::PovX),
//		//DPAD_RIGHT = sf::Joystick::PovX,
//		DPAD_UP = static_cast<int>(sf::Joystick::PovY),
//		//DPAD_DOWN = sf::Joystick::PovY,
//
//		//Bumpers
//		LB = sf::Joystick::U,
//		RB = sf::Joystick::V
//	};
//
//	enum AnalogInput : int
//	{
//		//Triggers
//		LT = sf::Joystick::Axis::Z,
//		RT = -sf::Joystick::Axis::Z,
//
//		//Joysticks
//		LEFT_AXIS_X = sf::Joystick::Axis::X,
//		LEFT_AXIS_Y = sf::Joystick::Axis::Y,
//		RIGHT_AXIS_X = sf::Joystick::Axis::U,
//		RIGHT_AXIS_Y = sf::Joystick::Axis::R
//	};
//};

class InputManager 
{
public:
	static InputManager* GetInstance()
	{
		static InputManager instance{};
		return &instance;
	}
	~InputManager() = default;

	void ProcessInput(sf::RenderWindow& pWindow);

	void AddGamePadEvent(GamePadEvent event);
	bool IsGamepadEventTriggered(const std::string& event, PlayerControllers playerID);

private:
	InputManager() = default;

	void RefreshControllers();
	bool IsGamePadButtonDown(WORD button, PlayerControllers playerID);
	void RegisterGamepadInput();


	std::array<XINPUT_STATE, XUSER_MAX_COUNT> m_GamepadStates = 
		std::array<XINPUT_STATE, XUSER_MAX_COUNT>();

	std::array<bool, XUSER_MAX_COUNT> m_ConnectedGamepads = 
		std::array<bool, XUSER_MAX_COUNT>();

	std::multimap<std::string, GamePadEvent> m_GamepadEvents =
		std::multimap<std::string, GamePadEvent>();
};
