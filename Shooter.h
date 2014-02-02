#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"
#include "Controls.h"

class Shooter {

private:
	static Shooter* m_instance;
	Controls* m_controls;
	bool m_triggerPressed1;
	bool m_triggerPressed2;
	
	Talon* m_shooterWheel1;
	Talon* m_shooterWheel2;
	
	Solenoid* m_tiltUp;
	Solenoid* m_tiltDown;
	
	Solenoid* m_bucketUp;
	Solenoid* m_bucketDown;
	
	Solenoid* m_launcherFire;
	Solenoid* m_launcherStore;
	
	bool m_launcherIsStored;
	
	bool m_bucketIsUp;
	bool m_tiltIsUp;
	bool m_shooterIsOn;
	
	Timer* m_timer;
	Timer* m_tiltTimer;
	Timer* m_rapidFireTimer;
	bool m_timerIsRunning;
	int m_rapidFireStep;
	
public:
	static Shooter* GetInstance();
	Shooter();
	
	void EnableTeleopControls();
	void TurnOn(float speed = 1.0);
	void TurnOff();
	void Shoot();
	void Reset();
	void TiltUp();
	void TiltDown();
	void BucketUp();
	void BucketDown();
	bool IsBucketUp();
	bool IsTiltUp();
};

#endif
