#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			std::cout << "Yump" << "\n";
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			std::cout << "Test" << "\n";
		}
	}

	return true;
}

bool InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

