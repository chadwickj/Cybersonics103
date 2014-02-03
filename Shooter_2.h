#ifndef Shooter_2_H
#define Shooter_2_H

#include "WPILib.h"
#include "Controls.h"

class WillmanShooter {
	
private:
	static WillmanShooter* m_instance;

	Controls* m_controls;
	
	Solenoid* m_fireLauncher;
	Solenoid* m_resetLauncher;
	
	Talon* m_shooterMotor;
	
	AnalogChannel* m_motorPot;
	
	Timer* timer;
	
	bool m_shooterLoading;
	
	int m_shooterLoadLimit;

public:
	static WillmanShooter* GetInstance();
	
	WillmanShooter();
	
	void Shoot();
	void Reset();
	void LoadShooter();
	bool IsShooterResetting();
	bool IsSolenoidReset();
	
	void EnableTeleopControls();

};

#endif
