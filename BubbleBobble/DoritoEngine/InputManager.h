#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Joystick.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

#include <Xinput.h>
#include <array>
#include <map>
#include <functional>


typedef sf::Keyboard::Key KeyboardButton;

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
		, State()
		, EventFunction()
	{}

	GamePadEvent(const std::string& actionDesc, WORD gamepadButtonCode, PlayerControllers controllerID, std::function<void()> function, InputTriggerState state = InputTriggerState::Down)
		: ActionDesc(actionDesc)
		, GamepadButtonCode(gamepadButtonCode)
		, ControllerID(controllerID)
		, EventFunction(function)
		, State(state)
	{}

	std::string ActionDesc;
	WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
	PlayerControllers ControllerID;
	InputTriggerState State;

	std::function<void()> EventFunction;
};


struct KeyBoardEvent
{
	KeyBoardEvent()
		: ActionDesc("No Action")
		, KeyboardButton(KeyboardButton::Unknown)
		, State()
		, ControllerID(PlayerControllers::Player1)
		, EventFunction()
	{}

	KeyBoardEvent(const std::string& actionDesc, KeyboardButton button, std::function<void()> function, InputTriggerState state = InputTriggerState::Down)
		: ActionDesc(actionDesc)
		, KeyboardButton(button)
		, State(state)
		, ControllerID(PlayerControllers::Player1)
		, EventFunction(function)
	{}

	std::string ActionDesc;
	KeyboardButton KeyboardButton;
	InputTriggerState State;
	PlayerControllers ControllerID;

	std::function<void()> EventFunction;
};

enum GamepadButtons : WORD
{
	A = XINPUT_GAMEPAD_A,
	B = XINPUT_GAMEPAD_B,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,

	RSB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	LSB = XINPUT_GAMEPAD_LEFT_SHOULDER,

	LEFT_D = XINPUT_GAMEPAD_DPAD_LEFT,
	RIGHT_D = XINPUT_GAMEPAD_DPAD_RIGHT,
	UP_D = XINPUT_GAMEPAD_DPAD_UP,
	DOWN_D = XINPUT_GAMEPAD_DPAD_DOWN
};

class InputManager 
{
public:
	static InputManager* GetInstance()
	{
		static InputManager instance{};
		return &instance;
	}
	~InputManager() = default;

	void Initialize();

	//Processes user input
	void ProcessInput(sf::RenderWindow& window);

	//Manually checks for input
	bool IsGamePadButtonDown(WORD button, PlayerControllers playerID, bool isPrevFrame = false);
	
	//Adding Events
	void AddGamePadEvent(const GamePadEvent& padEvent);
	void AddKeyboardEvent(const KeyBoardEvent& keyEvent);

private:
	InputManager() = default;

	void CheckControllerConnections();
	void UpdateControllers();
	void RegisterGamepadInput();
	
	void RegisterKetboardInput(const sf::Event& e);

	bool m_IsKeyDown = false;

	//Gamepad Variables
	std::array<XINPUT_STATE, XUSER_MAX_COUNT> m_CurrentGamepadStates = 
		std::array<XINPUT_STATE, XUSER_MAX_COUNT>();
	std::array<XINPUT_STATE, XUSER_MAX_COUNT> m_OldGamepadStates =
		std::array<XINPUT_STATE, XUSER_MAX_COUNT>();

	std::array<bool, XUSER_MAX_COUNT> m_ConnectedGamepads = 
		std::array<bool, XUSER_MAX_COUNT>();

	std::multimap<std::string, GamePadEvent> m_GamepadEvents =
		std::multimap<std::string, GamePadEvent>();

	//Keyboard
	std::map<std::string, KeyBoardEvent> m_KeyboardEvents =
		std::map<std::string, KeyBoardEvent>();
};
