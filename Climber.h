#ifndef CLIMBER_H
#define CLIMBER_H

#include "WPILib.h"
#include "Controls.h"
#include "Constants.h"

class Climber {
private:
	static Climber* m_instance;
	Controls* m_controls;
	Talon* m_tilt;
	Talon* m_mast;
	
	AnalogChannel* m_tiltPot;
	AnalogChannel* m_mastPot;
	
	Climber* climber;
	
public:
	static Climber* GetInstance();
	Climber();
	
	void EnableTeleopControls();
	void Tilt(float speed);
	void TiltToDrivingPosition();
	void Raise(float speed);
	int GetTiltPot();
	int GetMastPot();
};

#endif
