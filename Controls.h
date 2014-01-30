#ifndef CONTROLS_H
#define CONTROLS_H

#include "WPILib.h"

class Controls {

private:
	static Controls* m_instance;
	Joystick* m_leftStick;
	Joystick* m_rightStick;
	Joystick* OperatorStick;


public:
	static Controls* GetInstance();
	Controls();

	float GetLeftY();
	float GetRightY();
	bool GetLeftTrigger();
	bool GetRightTrigger();
	bool GetLeftButton(int button);
	bool GetRightButton(int button);
	bool GetPickupButton(int button);
	float GetPickupY();
	bool GetShooterButton(int button);
	bool GetBrakesButton(int button);
	bool GetShifterButton(int button);


};
#endif
