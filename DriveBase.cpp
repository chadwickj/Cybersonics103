#include "WPILib.h"
#include "HelperFunctions.h"
#include "DriveBase.h"
#include "Constants.h"
#include "Math.h"

DriveBase* DriveBase::m_instance = NULL;

DriveBase* DriveBase::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new DriveBase();
  }
  return m_instance;
}

DriveBase::DriveBase() {
	m_controls = Controls::GetInstance();
	
	// Remember to change these to Talons
	m_leftDrive = new Talon(LEFT_DRIVE_PWM);
	m_rightDrive = new Talon(RIGHT_DRIVE_PWM);

	// Encoders
	m_leftEncoder = new Encoder(LEFT_ENCODER_A, LEFT_ENCODER_B);
	m_rightEncoder = new Encoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B, true);
	
	m_leftEncoder->SetDistancePerPulse(INCHES_PER_COUNT);
	m_rightEncoder->SetDistancePerPulse(INCHES_PER_COUNT);
	
	m_leftEncoderController = new PIDController(0.0, 0.0, 0.0, m_leftEncoder, m_leftDrive);
	m_rightEncoderController = new PIDController(0.0, 0.0, 0.0, m_rightEncoder, m_rightDrive);
	
	m_leftEncoderController->SetPID(LEFT_ENCODER_P, LEFT_ENCODER_I, LEFT_ENCODER_D);
	m_rightEncoderController->SetPID(RIGHT_ENCODER_P, RIGHT_ENCODER_I, RIGHT_ENCODER_D);	
	
	// Gyro
	m_gyro = new Gyro(GYRO_CHANNEL);
	m_gyro->SetSensitivity(GYRO_SENSITIVITY);

	// Ultrasonic
	m_ultrasonic = new AnalogChannel(ULTRASONIC_CHANNEL);
	
	m_led = new DigitalOutput(LED_DIGITAL_OUTPUT);
	
	m_gyroController = new PIDController(0.0, 0.0, 0.0, m_gyro, m_leftDrive);
	m_gyroController->SetPID(GYRO_P, GYRO_I, GYRO_D);
	
	m_isTurning = false;
	m_isDrivingStraight = false;
	
	m_timer = new Timer();
	m_timerStopped = false;
}

void DriveBase::EnableTeleopControls() {
	m_leftDrive->Set(-1*m_controls->GetLeftY());
	m_rightDrive->Set(-1*m_controls->GetRightY());
	
	if (GetUltrasonicDistance() > 500 && GetUltrasonicDistance() < 560) {
		m_led->Set(1);
	} else {
		m_led->Set(0);
	}
}

void DriveBase::SetSpeed(float speed) {
	m_leftDrive->Set(speed);
	m_rightDrive->Set(speed);
}

void DriveBase::SetLeftSpeed(float speed) {
	m_leftDrive->Set(speed);
}

void DriveBase::SetRightSpeed(float speed) {
	m_rightDrive->Set(speed);
}

float DriveBase::GetLeftSpeed() {
	return m_leftDrive->Get();
}

float DriveBase::GetRightSpeed() {
	return m_rightDrive->Get();
}

int DriveBase::GetLeftEncoderCount() {
	m_leftEncoder->Start();
	return m_leftEncoder->Get();
}

int DriveBase::GetRightEncoderCount() {
	m_rightEncoder->Start();
	return m_rightEncoder->Get();
}

void DriveBase::ResetEncoders() {
	m_leftEncoder->Reset();
	m_rightEncoder->Reset();
}

void DriveBase::SetEncoderSetpoint(float inches) {
	m_leftEncoderController->SetSetpoint(inches);
	m_rightEncoderController->SetSetpoint(inches);
}

void DriveBase::EnableEncoderPid() {
	m_leftEncoderController->Enable();
	m_rightEncoderController->Enable();
}

void DriveBase::DisableEncoderPid() {
	m_leftEncoderController->Disable();
	m_rightEncoderController->Disable();
}

bool DriveBase::EncoderPidIsEnabled() {
	return m_leftEncoderController->IsEnabled() && m_rightEncoderController->IsEnabled();
}

void DriveBase::ResetGyro() {
	m_gyro->Reset();
}

float DriveBase::GetGyroAngle() {
	return m_gyro->GetAngle();
}

float DriveBase::GetUltrasonicDistance() {
	return m_ultrasonic->GetValue();
}

/**
 * @param {float} setpoint - The target angle for the gyro in degrees.
 * @param {float} tolerance - An absolute tolerance in degrees.
 * 
 * @return True if turn has completed, false otherwise.
 */
/*
bool DriveBase::Turn(float setpoint, float tolerance, float maxSpeed) {
	if (!m_isTurning) {
		m_gyroController->SetOutputRange(-1.0, maxSpeed);
		m_gyroController->SetSetpoint(setpoint);
		m_gyroController->Enable();
		m_isTurning = true;
	}
	
	if (m_isTurning) {
		m_rightDrive->Set(-1*m_gyroController->Get());

		bool onTarget = fabs(setpoint - m_gyro->GetAngle()) < tolerance;

		if(onTarget) {
			if (m_timerStopped) {
				m_timer->Reset();
			}
			m_timer->Start();
			m_timerStopped = false;
			
			// On Target
			if (m_timer->Get() > 0.5) {	//TODO: KILL MAGIC NUMBER
				m_gyroController->Disable();
				m_timer->Reset();
				m_isTurning = false;
				return true;
			}
		} else {
			m_timer->Stop();
			m_timerStopped = true;
		}
	}
	
	return false;
} */

/**
 * Turn using dead reckoning and the gyro to know when to stop.
 */
bool DriveBase::Turn(float setpoint, float tolerance, float maxSpeed) {
	if (!m_isTurning) {
		if (setpoint > 0 ) {
			m_leftDrive->Set(maxSpeed);
			m_rightDrive->Set(-1.0 * maxSpeed);
		} else if (setpoint < 0) {
			m_leftDrive->Set(-1.0 * maxSpeed);
			m_rightDrive->Set(maxSpeed);
		} 
		m_isTurning = true;
	}
	
	if (m_isTurning) {
		if ((setpoint > 0 && m_gyro->GetAngle() > setpoint) || (setpoint < 0 && m_gyro->GetAngle() < setpoint)) {
			SetSpeed(0.0);
			m_isTurning = false;
			return true;
		}
	}
	return false;
}

bool DriveBase::IsTurning() {
	return m_isTurning;
}

void DriveBase::EnableGyroPid() {
	m_gyroController->Enable();
}

void DriveBase::DisableGyroPid() {
	m_gyroController->Disable();
}

void DriveBase::SetGyroSetpoint(float angle) {
	m_gyroController->SetSetpoint(angle);
}

// TODO: REMOVE
PIDController* DriveBase::GetGyroController() {
	return m_gyroController;
}

// TODO: REMOVE
void DriveBase::SetEncoderPID(float p, float i, float d) {
	m_leftEncoderController->SetPID(p,i,d);
	m_rightEncoderController->SetPID(p,i,d);
}

void DriveBase::SetLeftEncoderPID(float p, float i, float d) {
	m_leftEncoderController->SetPID(p, i, d);
}

void DriveBase::SetRightEncoderPID(float p, float i, float d) {
	m_rightEncoderController->SetPID(p, i, d);
}

/**
 * Important: Reset the gyro before calling this function.
 * @param {float} setpoint - The setpoint for the encoders in inches.
 * @param {float} tolerance - The tolerance for the encoders in inches.
 */
bool DriveBase::DriveStraight(float setpoint, float tolerance, float p, float maxSpeed) {
	if (!m_isDrivingStraight) {
		m_leftEncoderController->SetOutputRange(-1.0, maxSpeed);
		m_rightEncoderController->SetOutputRange(-1.0, maxSpeed);
		SetEncoderSetpoint(setpoint);
		EnableEncoderPid();
		m_rightDrive->Set(m_leftEncoderController->Get());
		
		// TODO: Get rid of reset Gyro?
		m_gyro->Reset();
		m_isDrivingStraight = true;
	}
	
	if (m_isDrivingStraight) {
		float angleError = m_gyro->GetAngle();
		
		float leftSpeed = m_leftDrive->Get() + (angleError * p);
		float rightSpeed = m_rightDrive->Get() - (angleError * p);
				
		if (leftSpeed > 1.0) {
			leftSpeed = 1.0;
		} else if (leftSpeed < -1.0) {
			leftSpeed = -1.0;
		}
		
		if (rightSpeed > 1.0) {
			rightSpeed = 1.0;
		} else if (rightSpeed < -1.0) {
			rightSpeed = -1.0;
		}
		
		m_leftDrive->Set(leftSpeed);
		m_rightDrive->Set(rightSpeed);
		
		if (setpoint > 0) {
			if ((encoderCountToInches(m_leftEncoder->Get()) >= setpoint) || (encoderCountToInches(m_rightEncoder->Get()) >= setpoint)) {
				DisableEncoderPid();
				m_isDrivingStraight = false;
				return true;
			}
		} else {
			if ((encoderCountToInches(m_leftEncoder->Get()) <= setpoint) || (encoderCountToInches(m_rightEncoder->Get()) <= setpoint)) {
				DisableEncoderPid();
				m_isDrivingStraight = false;
				return true;
			}
		}
	}
	return false;
}

bool DriveBase::DriveForward(float setpoint, float tolerance) {
	if (!m_isDrivingStraight) {
		SetEncoderSetpoint(setpoint);
		EnableEncoderPid();
		m_isDrivingStraight = true;
	}
	
	if (m_isDrivingStraight) {
		
		// Determine when to disable PID
		bool leftOnTarget = fabs(setpoint - encoderCountToInches(m_leftEncoder->Get())) < tolerance;
		bool rightOnTarget = fabs(setpoint - encoderCountToInches(m_rightEncoder->Get())) < tolerance;
		
		
		if (leftOnTarget && rightOnTarget) {
			DisableEncoderPid();
			m_isDrivingStraight = false;
			return true;
		}
	}
	return false;
}
