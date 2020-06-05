#pragma once
#include <XInput.h>

enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY
};

class InputManager 
{
public:
	static InputManager& GetInstance()
	{
		static InputManager instance{};
		return instance;
	}

	~InputManager() = default;

	bool ProcessInput();
	bool IsPressed(ControllerButton button) const;

private:
	InputManager() = default;

	XINPUT_STATE m_CurrentState{};
};
