#ifndef DRIVEBASE_H_
#define DRIVEBASE_H_

#include "WPILib.h"
#include "Controls.h"

class DriveBase {

private:
	static DriveBase* m_instance;
	
	Controls* m_controls;
	
	Talon* m_leftDrive;
	Talon* m_rightDrive;
	
	Encoder* m_leftEncoder;
	Encoder* m_rightEncoder;
	
	PIDController* m_leftEncoderController;
	PIDController* m_rightEncoderController;
	
	Gyro* m_gyro;
	
	AnalogChannel* m_ultrasonic;
	
	Relay* m_led;
	
	PIDController* m_gyroController;
	
	bool m_isTurning;
	bool m_isDrivingStraight;
	
	Timer* m_timer;
	bool m_timerStopped;

public:
	static DriveBase* GetInstance();
	DriveBase();
	void EnableTeleopControls();
	
	void SetSpeed(float speed);
	void SetLeftSpeed(float speed);
	void SetRightSpeed(float speed);
	
	float GetLeftSpeed();
	float GetRightSpeed();
	
	int GetLeftEncoderCount();
	int GetRightEncoderCount();
	void ResetEncoders();
	
	void SetEncoderSetpoint(float inches);
	void EnableEncoderPid();
	void DisableEncoderPid();
	bool EncoderPidIsEnabled();
	
	void ResetGyro();
	float GetGyroAngle();
	bool Turn(float setpoint, float tolerance, float maxSpeed = 1.0);
	bool IsTurning();
	void EnableGyroPid();
	void DisableGyroPid();
	void SetGyroSetpoint(float angle);
	
	float DriveBase::GetUltrasonicDistance();
	
	// TODO: REMOVE HACK
	PIDController* GetGyroController();
	void SetEncoderPID(float p, float i, float d);
	void SetLeftEncoderPID(float p, float i, float d);
	void SetRightEncoderPID(float p, float i, float d);
	
	bool DriveStraight(float setpoint, float tolerance, float p, float maxSpeed = 1.0);
	bool DriveForward(float setpoint, float tolerance);
};

#endif
