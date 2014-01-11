#ifndef DRIVEBASE_H_
#define DRIVEBASE_H_

#include "WPILib.h"
#include "Controls.h"

class DriveBase {

private:
	static DriveBase* m_instance;
	
	Controls* m_controls;
	
	// These Victors should be changed to Talons for the actual robot
	Victor* m_leftDrive;
	Victor* m_rightDrive;
	
	Encoder* m_leftEncoder;
	Encoder* m_rightEncoder;
	
	PIDController* m_leftEncoderController;
	PIDController* m_rightEncoderController;

public:
	static DriveBase* GetInstance();
	DriveBase();
	void EnableTeleopControls();
	int GetLeftEncoderCount();
	int GetRightEncoderCount();
	void ResetEncoders();
	
	PIDController* GetLeftEncoderController();
	PIDController* GetRightEncoderController();
};

#endif
