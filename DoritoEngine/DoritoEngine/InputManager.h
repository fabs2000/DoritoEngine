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

typedef std::function<void()> DoritoAction;
typedef std::function<void(const sf::Vector2f& axis)> DoritoAxis;

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

struct GamePadActionEvent
{
	GamePadActionEvent()
		: ActionDesc("No Action")
		, GamepadButtonCode(0)
		, ControllerID(PlayerControllers::Player1)
		, State()
		, EventActionFunc()
	{}

	GamePadActionEvent(const std::string& actionDesc, WORD gamepadButtonCode, PlayerControllers controllerID, DoritoAction func, InputTriggerState state = InputTriggerState::Down)
		: ActionDesc(actionDesc)
		, GamepadButtonCode(gamepadButtonCode)
		, ControllerID(controllerID)
		, EventActionFunc(func)
		, State(state)
	{}

	std::string ActionDesc;
	WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
	PlayerControllers ControllerID;
	InputTriggerState State;

	DoritoAction EventActionFunc;
};

struct GamePadAxisEvent
{
	GamePadAxisEvent()
		: AxisDesc("No Axis")
		, GamepadAxisCode()
		, ControllerID()
		, EventAxisFunc()
	{}

	GamePadAxisEvent(const std::string& desc, WORD gamepadAxisCode, PlayerControllers controllerID, DoritoAxis func)
		: AxisDesc(desc)
		, GamepadAxisCode(gamepadAxisCode)
		, ControllerID(controllerID)
		, EventAxisFunc(func)
	{}

	std::string AxisDesc;
	WORD GamepadAxisCode; //XINPUT_GAMEPAD_...
	PlayerControllers ControllerID;

	DoritoAxis EventAxisFunc;
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

	KeyBoardEvent(const std::string& actionDesc, KeyboardButton button, DoritoAction func, InputTriggerState state = InputTriggerState::Down)
		: ActionDesc(actionDesc)
		, KeyboardButton(button)
		, State(state)
		, ControllerID(PlayerControllers::Player1)
		, EventFunction(func)
	{}

	std::string ActionDesc;
	KeyboardButton KeyboardButton;
	InputTriggerState State;
	PlayerControllers ControllerID;

	DoritoAction EventFunction;
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
	DOWN_D = XINPUT_GAMEPAD_DPAD_DOWN,
	 
	START = XINPUT_GAMEPAD_START
};

enum GamepadAxis : WORD
{
	L_STICK = XINPUT_GAMEPAD_LEFT_THUMB,
	R_STICK = XINPUT_GAMEPAD_RIGHT_THUMB
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
	void AddGamePadActionEvent(const GamePadActionEvent& padEvent);
	void AddGamePadAxisEvent(const GamePadAxisEvent& padEvent);
	void AddKeyboardEvent(const KeyBoardEvent& keyEvent);


	void BindGamepadAction(const std::string& actionName, DoritoAction func);
	void BindGamepadAxisAction(const std::string& actionName, DoritoAxis func);
	void BindKeyboardAction(const std::string& actionName, DoritoAction func);


private:
	InputManager() = default;

	void CheckControllerConnections();
	void UpdateControllers();
	void RegisterGamepadInput();
	
	void RegisterKetboardInput(const sf::Event& e);

	bool IsLStick_InDeadZone(PlayerControllers playerID);
	bool IsRStick_InDeadZone(PlayerControllers playerID);

	sf::Vector2f RightStickPos(PlayerControllers playerID);
	sf::Vector2f LeftStickPos(PlayerControllers playerID);


	bool m_IsKeyDown = false;

	//Gamepad Variables
	std::array<XINPUT_STATE, XUSER_MAX_COUNT> m_CurrentGamepadStates = 
		std::array<XINPUT_STATE, XUSER_MAX_COUNT>();
	std::array<XINPUT_STATE, XUSER_MAX_COUNT> m_OldGamepadStates =
		std::array<XINPUT_STATE, XUSER_MAX_COUNT>();

	std::array<bool, XUSER_MAX_COUNT> m_ConnectedGamepads = 
		std::array<bool, XUSER_MAX_COUNT>();

	std::multimap<std::string, GamePadActionEvent> m_GamepadActionEvents =
		std::multimap<std::string, GamePadActionEvent>();

	std::multimap<std::string, GamePadAxisEvent> m_GamepadAxisEvents =
		std::multimap<std::string, GamePadAxisEvent>();

	sf::Vector2f m_JoyStickPos;

	//Keyboard
	std::map<std::string, KeyBoardEvent> m_KeyboardEvents =
		std::map<std::string, KeyBoardEvent>();
};
