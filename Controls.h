#ifndef CONTROLS_H
#define CONTROLS_H

#include "WPILib.h"

class Controls {

private:
	static Controls* m_instance;
	Joystick* m_leftStick;
	Joystick* m_rightStick;

public:
	static Controls* GetInstance();
	Controls();
	
	Joystick* GetLeftStick();
	Joystick* GetRightStick();
	
	float GetLeftY();
	float GetRightY();
	bool GetLeftTrigger();
	bool GetRightTrigger();
	bool GetLeftButton(int button);
	bool GetRightButton(int button);
};
#endif
