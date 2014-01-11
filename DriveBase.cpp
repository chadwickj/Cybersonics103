#include "WPILib.h"
#include "DriveBase.h"
#include "Constants.h"

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
	m_leftDrive = new Victor(LEFT_DRIVE_PWM);
	m_rightDrive = new Victor(RIGHT_DRIVE_PWM);

	m_leftEncoder = new Encoder(LEFT_ENCODER_A, LEFT_ENCODER_B);
	m_rightEncoder = new Encoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B, true);
	
	m_leftEncoder->SetDistancePerPulse(INCHES_PER_COUNT);
	m_rightEncoder->SetDistancePerPulse(INCHES_PER_COUNT);
	
	m_leftEncoderController = new PIDController(0.0, 0.0, 0.0, m_leftEncoder, m_leftDrive);
	m_rightEncoderController = new PIDController(0.0, 0.0, 0.0, m_rightEncoder, m_rightDrive);
	
	LiveWindow* liveWindow = LiveWindow::GetInstance();
	liveWindow->AddComponent("Left Drive", "Left Encoder", m_leftEncoderController);
	liveWindow->AddComponent("Right Drive", "Right Encoder", m_rightEncoderController);
}

void DriveBase::EnableTeleopControls() {
	m_leftDrive->Set(m_controls->GetLeftY());
	m_rightDrive->Set(m_controls->GetRightY());
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

PIDController* DriveBase::GetLeftEncoderController() {
	return m_leftEncoderController;
}

PIDController* DriveBase::GetRightEncoderController() {
	return m_rightEncoderController;
}
