#include "Controls.h"
#include "WPILib.h"
#include "Constants.h"

Controls* Controls::m_instance = NULL;

Controls* Controls::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Controls();
  }
  return m_instance;
}

Controls::Controls() {
	m_leftStick = new Joystick(LEFT_JOYSTICK_PORT);
	m_rightStick = new Joystick(RIGHT_JOYSTICK_PORT);
}

float Controls::GetLeftY() {
	return m_leftStick->GetY();
}

float Controls::GetRightY() {
	return m_rightStick->GetY();
}

bool Controls::GetLeftTrigger() {
	return m_leftStick->GetTrigger();
}

bool Controls::GetRightTrigger() {
	return m_rightStick->GetTrigger();
}

bool Controls::GetLeftButton(int button) {
	return m_leftStick->GetRawButton(button);
}

bool Controls::GetRightButton(int button) {
	return m_rightStick->GetRawButton(button);
}
