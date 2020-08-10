#include "DoritoPCH.h"
#include "InputManager.h"
#include <map>

void InputManager::Initialize()
{
	//Check for controllers connected
	CheckControllerConnections();
}

void InputManager::ProcessInput(sf::RenderWindow& window)
{
	//Check if any controllers updated
	UpdateControllers();

	sf::Event e = {};
	while (window.pollEvent(e))
	{
		//Check for window closed
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}

		window.setKeyRepeatEnabled(m_IsKeyDown);
		RegisterKetboardInput(e);
	}

	//Gamepad Input
	RegisterGamepadInput();
}

void InputManager::AddGamePadActionEvent(const GamePadActionEvent& padEvent)
{
	m_GamepadActionEvents.emplace(padEvent.ActionDesc, padEvent);
}

void InputManager::AddGamePadAxisEvent(const GamePadAxisEvent& padEvent)
{
	m_GamepadAxisEvents.emplace(padEvent.AxisDesc, padEvent);
}

void InputManager::AddKeyboardEvent(const KeyBoardEvent& keyEvent)
{
	m_KeyboardEvents.emplace(keyEvent.ActionDesc, keyEvent);
}

void InputManager::BindGamepadAction(const std::string& actionName, DoritoAction func)
{
	auto gameEvent = (*m_GamepadActionEvents.find(actionName)).second;

	gameEvent.EventActionFunc = func;
}

void InputManager::BindGamepadAxisAction(const std::string& actionName, DoritoAxis func)
{
	auto gameEvent = (*m_GamepadAxisEvents.find(actionName)).second;

	gameEvent.EventAxisFunc = func;
}

void InputManager::BindKeyboardAction(const std::string& actionName, DoritoAction func)
{
	auto gameEvent = (*m_KeyboardEvents.find(actionName)).second;

	gameEvent.EventFunction = func;
}

void InputManager::CheckControllerConnections()
{
	DWORD dwResult;

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &state);
		m_ConnectedGamepads.at(i) = (dwResult == ERROR_SUCCESS);

		if(m_ConnectedGamepads.at(i))
			m_CurrentGamepadStates.at(i) = state;
	}
}

void InputManager::UpdateControllers()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_ConnectedGamepads[i])
			return;

		m_OldGamepadStates[i] = m_CurrentGamepadStates[i];

		const DWORD dwResult = XInputGetState(i, &m_CurrentGamepadStates[i]);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

void InputManager::RegisterGamepadInput()
{
	for (auto it = m_GamepadActionEvents.begin(); it != m_GamepadActionEvents.end(); ++it)
	{
		auto currEvent = it->second;

		if (currEvent.GamepadButtonCode != 0)
		{
			switch (currEvent.State)
			{
				//Pressed
			case InputTriggerState::Pressed:
				if (!IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID, true) &&
					IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID))
				{
					currEvent.EventActionFunc();
				}
				break;

				//Released
			case InputTriggerState::Released:
				if (IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID, true) && 
					!IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID))
				{
					currEvent.EventActionFunc();
				}
				break;

				//Down
			case InputTriggerState::Down:
				if (IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID, true))
				{
					currEvent.EventActionFunc();
				}
				break;
			}
		}
	}

	for (auto it = m_GamepadAxisEvents.begin(); it != m_GamepadAxisEvents.end(); ++it)
	{
		auto currEvent = it->second;

		if (currEvent.GamepadAxisCode == L_STICK && !IsLStick_InDeadZone(currEvent.ControllerID))
		{
			currEvent.EventAxisFunc(LeftStickPos(currEvent.ControllerID));
		}
		if (currEvent.GamepadAxisCode == R_STICK && !IsRStick_InDeadZone(currEvent.ControllerID))
		{
			currEvent.EventAxisFunc(RightStickPos(currEvent.ControllerID));
		}
	}
}

void InputManager::RegisterKetboardInput(const sf::Event& e)
{
	for (auto it = m_KeyboardEvents.begin(); it != m_KeyboardEvents.end(); ++it)
	{
		auto& currEvent = it->second;

		if (currEvent.KeyboardButton != sf::Keyboard::Unknown)
		{
			switch (currEvent.State)
			{
			case InputTriggerState::Pressed:

				if ((e.type == sf::Event::KeyPressed) 
					&& (e.key.code == currEvent.KeyboardButton))
				{
					currEvent.EventFunction();

					m_IsKeyDown = false;
				}
				break;

			case InputTriggerState::Released:

				if ((e.type == sf::Event::KeyReleased)
					&& (e.key.code == currEvent.KeyboardButton))
				{
					currEvent.EventFunction();

					m_IsKeyDown = false;
				}
				break;

			case InputTriggerState::Down:
				if ((e.type == sf::Event::KeyPressed)
					&& (e.key.code == currEvent.KeyboardButton))
				{
					currEvent.EventFunction();

					m_IsKeyDown = true;
				}
				break;
			}
		}
	}
}

bool InputManager::IsLStick_InDeadZone(PlayerControllers playerID)
{
	UINT pi = static_cast<UINT>(playerID);

	if (!m_ConnectedGamepads[pi])
		return false;

	short lX = m_CurrentGamepadStates[pi].Gamepad.sThumbLX;
	short lY = m_CurrentGamepadStates[pi].Gamepad.sThumbLY;

	if (lX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || lX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	if (lY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || lY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	return true;
}

bool InputManager::IsRStick_InDeadZone(PlayerControllers playerID)
{
	UINT pi = static_cast<UINT>(playerID);

	if (!m_ConnectedGamepads[pi])
		return false;

	short rX = m_CurrentGamepadStates[pi].Gamepad.sThumbRX;
	short rY = m_CurrentGamepadStates[pi].Gamepad.sThumbRY;

	if (rX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || rX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	if (rY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || rY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	return true;
}

sf::Vector2f InputManager::RightStickPos(PlayerControllers playerID)
{
	UINT pi = static_cast<UINT>(playerID);

	short rX = m_CurrentGamepadStates[pi].Gamepad.sThumbRX;
	short rY = m_CurrentGamepadStates[pi].Gamepad.sThumbRY;

	return sf::Vector2f(static_cast<float>(rX)/32768.f,
		static_cast<float>(rY)/32768.f);
}

sf::Vector2f InputManager::LeftStickPos(PlayerControllers playerID)
{
	UINT pi = static_cast<UINT>(playerID);

	short lX = m_CurrentGamepadStates[pi].Gamepad.sThumbLX;
	short lY = m_CurrentGamepadStates[pi].Gamepad.sThumbLY;

	return sf::Vector2f(static_cast<float>(lX) / 32768.f, 
		static_cast<float>(lY) / 32768.f);
}

bool InputManager::IsGamePadButtonDown(WORD button, PlayerControllers playerID, bool isPrevFrame)
{
	UINT pi = static_cast<UINT>(playerID);

	if (!m_ConnectedGamepads[pi])
		return false;

	if (isPrevFrame)
		return (m_OldGamepadStates[pi].Gamepad.wButtons & button) != 0;

	return (m_CurrentGamepadStates[pi].Gamepad.wButtons & button) != 0;
}