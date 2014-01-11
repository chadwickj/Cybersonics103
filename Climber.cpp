#include "Climber.h"

Climber* Climber::m_instance = NULL;

Climber* Climber::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Climber();
  }
  return m_instance;
}

Climber::Climber() {
	m_controls = Controls::GetInstance();
	
	m_tilt = new Talon(CLIMB_WINDOW);
	m_mast = new Talon(CLIMB_CIM);
	
	m_tiltPot = new AnalogChannel(TILT_POT_CHAN);
	m_mastPot = new AnalogChannel(MAST_POT_CHAN);
}

void Climber::EnableTeleopControls() {
	
	// MAST
	int mastPosition = m_mastPot->GetValue();
	int lowerMastLimit = 580;
	int upperMastLimit = 30;

	if (m_controls->GetClimberButton(3) && mastPosition > upperMastLimit) {
		m_mast->Set(1.0);
	} else if (m_controls->GetClimberButton(2) && mastPosition < lowerMastLimit) {
		m_mast->Set(-1.0);
	} else {
		m_mast->Set(0.0);
	}
	
	// TILT
	int forwardTiltLimit = 590;
	int backTiltLimit = 439;
	
	float tiltSpeed = m_controls->GetClimberY();
	int tiltPosition = m_tiltPot->GetValue();
	
	if (m_controls->GetClimberButton(7)) {
		TiltToDrivingPosition();
	} else if (tiltSpeed < -0.1 && tiltPosition < forwardTiltLimit) {
		m_tilt->Set(tiltSpeed);
	} else if (tiltSpeed > 0.1 && tiltPosition > backTiltLimit) {
		m_tilt->Set(tiltSpeed);
	} else {
		m_tilt->Set(0.0);
	}
}

// TODO: Fix this. Set mast to a fixed speed if in the danger zone at each end.
void Climber::Tilt(float speed) {
	m_tilt->Set(speed);
	if (speed < -0.1) {
		m_mast->Set(0.3);
	} else if (speed > 0.1) {
		m_mast->Set(-0.3);
	} else {
		m_mast->Set(0.0);
	}
}

void Climber::TiltToDrivingPosition() {
	int tiltPosition = m_tiltPot->GetValue();
	int targetPosition = 432;
	int position1 = targetPosition + 30;
	int position2 = targetPosition + 20;
	int position3 = targetPosition + 10;
	
	if (tiltPosition > position1) {
		m_tilt->Set(1.0);
	} else if (tiltPosition <= position1 && tiltPosition > position2 ) {
		m_tilt->Set(0.7);
	} else if (tiltPosition <= position2 && tiltPosition > position3) {
		m_tilt->Set(0.5);
	} else if (tiltPosition <= position3 && tiltPosition > targetPosition) {
		m_tilt->Set(0.2);
	} else {
		m_tilt->Set(0.0);
	}
}

void Climber::Raise(float speed) {
	m_tilt->Set(speed);
}

int Climber::GetTiltPot(){
	return m_tiltPot->GetValue();
}

int Climber::GetMastPot(){
	return m_mastPot->GetValue();
}
