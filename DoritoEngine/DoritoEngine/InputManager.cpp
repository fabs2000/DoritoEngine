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

void InputManager::AddGamePadEvent(const GamePadEvent& padEvent)
{
	m_GamepadEvents.emplace(padEvent.ActionDesc, padEvent);
}

void InputManager::AddKeyboardEvent(const KeyBoardEvent& keyEvent)
{
	m_KeyboardEvents.emplace(keyEvent.ActionDesc, keyEvent);
}

void InputManager::CheckControllerConnections()
{
	DWORD dwResult;

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
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
	for (auto it = m_GamepadEvents.begin(); it != m_GamepadEvents.end(); ++it)
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
					currEvent.EventFunction();
				}
				break;

				//Released
			case InputTriggerState::Released:
				if (IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID, true) && 
					!IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID))
				{
					currEvent.EventFunction();
				}
				break;

				//Down
			case InputTriggerState::Down:
				if (IsGamePadButtonDown(currEvent.GamepadButtonCode, currEvent.ControllerID, true))
				{
					currEvent.EventFunction();
				}
				break;
			}
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

bool InputManager::IsGamePadButtonDown(WORD button, PlayerControllers playerID, bool isPrevFrame)
{
	UINT pi = static_cast<UINT>(playerID);

	if (!m_ConnectedGamepads[pi])
		return false;

	if (isPrevFrame)
		return (m_OldGamepadStates[pi].Gamepad.wButtons & button) != 0;

	return (m_CurrentGamepadStates[pi].Gamepad.wButtons & button) != 0;
}