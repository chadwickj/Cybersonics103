#ifndef AUTON_CONTROLLER_H
#define AUTON_CONTROLLER_H

#include "WPILib.h"
#include "DriveBase.h"
#include "Shooter.h"
#include "Pickup.h"

class AutonController {
	
private:
	static AutonController* m_instance;
	
	DriveBase* drivebase;
	Shooter* shooter;
	Pickup* pickup;
	
	bool m_turnComplete;
	bool m_driveStraightComplete;
	
	Timer* m_timer;
	int m_step;
	
public:
	static AutonController* GetInstance();
	AutonController();
	void Reset();
	
	void Test();
	
	void CliffDey();
	void JimTheWelder();
	void JackTusman();
	void MikeLube();
	void WayneCokeley();
	
	void DoNothing();
};

#endif
