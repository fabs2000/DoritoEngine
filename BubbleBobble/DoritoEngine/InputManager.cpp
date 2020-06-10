#include "DoritoPCH.h"
#include "InputManager.h"
#include <map>

void InputManager::ProcessInput(sf::RenderWindow& pWindow)
{
	//Check for controllers connected
	RefreshControllers();
	
	//Check for window closed
	sf::Event e;
	while (pWindow.pollEvent(e)) 
	{
		if (e.type == sf::Event::Closed) 
		{
			pWindow.close();
		}
	}

	RegisterGamepadInput();
}

void InputManager::AddGamePadEvent(GamePadEvent event)
{
	m_GamepadEvents.emplace(event.ActionDesc, event);
}

bool InputManager::IsGamepadEventTriggered(const std::string& event, PlayerControllers playerID)
{
	auto range = m_GamepadEvents.equal_range(event);

	for (auto it = range.first; it != range.second; it++)
	{
		auto element = *it;
		
		if (element.second.ControllerID == playerID)
		{
			return element.second.IsTriggered;
		}
	}

	return false;
}

void InputManager::RefreshControllers()
{
	DWORD dwResult;

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			m_GamepadStates.at(i) = state;
			m_ConnectedGamepads.at(i) = true;
		}
		else
		{
			m_ConnectedGamepads.at(i) = false;
		}
	}
}

void InputManager::RegisterGamepadInput()
{
	for (auto it = m_GamepadEvents.begin(); it != m_GamepadEvents.end(); ++it)
	{
		auto currEvent = &(it->second);

		currEvent->IsTriggered = false;

		if (!currEvent->IsTriggered && currEvent->GamepadButtonCode != 0)
		{
			if (IsGamePadButtonDown(currEvent->GamepadButtonCode, currEvent->ControllerID))
			{
				currEvent->IsTriggered = true;
			}
		}
	}
}

bool InputManager::IsGamePadButtonDown(WORD button, PlayerControllers playerID)
{
	UINT pi = static_cast<UINT>(playerID);

	if(!m_ConnectedGamepads[pi])
		return false;

	return (m_GamepadStates[pi].Gamepad.wButtons & button) != 0;
}

//TODO: Use SFML gamepad implementation? (INDEED(NOT))
//bool InputManager::IsControllerPressed(unsigned int controllerID, unsigned int button) const
//{
//	if (sf::Joystick::isConnected(controllerID))
//	{
//		if (sf::Joystick::isButtonPressed(controllerID, button))
//		{
//			return true;
//		}
//	}
//	return false;
//}