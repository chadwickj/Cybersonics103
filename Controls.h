#ifndef CONTROLS_H
#define CONTROLS_H

#include "WPILib.h"

class Controls {

private:
	static Controls* m_instance;
	Joystick* m_leftStick;
	Joystick* m_rightStick;

	//Joystick* m_shooterStick;
	//Joystick* m_climberStick;
	
	Joystick* m_operatorStick;
	
public:
	static Controls* GetInstance();
	Controls();
	
	float GetLeftY();
	float GetRightY();
	bool GetLeftTrigger();
	bool GetRightTrigger();
	bool GetLeftButton(int button);
	bool GetRightButton(int button);
	
	float GetShooterY();
	bool GetShooterButton(int button);
	bool GetShooterTrigger();
};
#endif
