#include "WPILib.h"
#include "AutonController.h"
#include "Constants.h"
#include "HelperFunctions.h"

AutonController* AutonController::m_instance = NULL;

AutonController* AutonController::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new AutonController();
  }
  return m_instance;
}

AutonController::AutonController() {
	drivebase = DriveBase::GetInstance();

	m_turnComplete = false;
	m_driveStraightComplete = false;

	m_timer = new Timer();
	m_step = 0;
}

void AutonController::Reset() {
	m_step = 0;
}

void AutonController::Test() {

	if (m_step == 0) {
		m_driveStraightComplete = drivebase->DriveStraight(200, 2.0, 0.0002);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else {
		drivebase->SetSpeed(0.0);
	}

	/*
	float turnTolerance = 2.0;
	float driveStraightTolerance = 3.0;

	if (m_step == 0) {
		m_driveStraightComplete = drivebase->DriveStraight(89.0, driveStraightTolerance, DRIVE_STRAIGHT_P);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 1) {
		m_turnComplete = drivebase->Turn(80, turnTolerance);
		if(m_turnComplete) {
			m_turnComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 2) {
		m_driveStraightComplete = drivebase->DriveStraight(-130, driveStraightTolerance, DRIVE_STRAIGHT_P);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 3) {
		m_turnComplete = drivebase->Turn(-105, turnTolerance);
		if(m_turnComplete) {
			m_turnComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else {
		drivebase->SetSpeed(0.0);
	}*/
}

void AutonController::DoNothing() {
	drivebase->SetSpeed(0.0);
	// TODO: Make other components do nothing.
}

void AutonController::CliffDey() {

}

void AutonController::JimTheWelder() {

}

void AutonController::JackTusman() {

}

void AutonController::MikeLube() {

}

void AutonController::WayneCokeley() {

}
