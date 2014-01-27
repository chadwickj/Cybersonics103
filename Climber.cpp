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
	
	m_hooksUp = new Solenoid(7);
	m_hooksDown = new Solenoid(8);
	
	m_climbSequenceStep = 0;
	
	shooter = Shooter::GetInstance();
}

void Climber::EnableTeleopControls() {
	
	// MAST
	int mastPosition = m_mastPot->GetValue();
	int lowerMastLimit = 45;
	int upperMastLimit = 875;
	
	// TILT
	int forwardTiltLimit = 615;
	int backTiltLimit = 430;
	
	float tiltSpeed = m_controls->GetClimberY();
	int tiltPosition = m_tiltPot->GetValue();
	
	if (m_controls->GetClimberButton(9)) {
		m_climbSequenceStep = 0;
	}
	
	if (m_controls->GetClimberButton(3) /*&& mastPosition < upperMastLimit*/) {
		// m_mast->Set(1.0);
		HooksUp();
	} else if (m_controls->GetClimberButton(2) /*&& mastPosition > lowerMastLimit*/) {
		// m_mast->Set(-1.0);
		HooksDown();
	} else if (m_controls->GetShooterButton(8)) {
		TiltToDrivingPosition();
	} else if (tiltSpeed < -0.1 && tiltPosition < forwardTiltLimit) {
		m_tilt->Set(tiltSpeed);
	} else if (tiltSpeed > 0.1 && tiltPosition > backTiltLimit) {
		m_tilt->Set(tiltSpeed);
	} else if (m_controls->GetClimberButton(10)) {		// Preset to load colored discs
		if (tiltPosition > 477) {
			m_tilt->Set(1.0);
		} else {
			m_tilt->Set(0.0);
		}
	} else if (m_controls->GetClimberButton(6)) { // TILT TO READY LEVEL 1 HANG
		if (tiltPosition < 486) {
			m_tilt->Set(-1.0);
		} else {
			m_tilt->Set(0.0);
		}
	} else if (m_controls->GetClimberButton(7)) {
		if (mastPosition < 395) {
			m_mast->Set(1.0);
		} else {
			m_mast->Set(0.0);
		}
	} else if (m_controls->GetClimberButton(8)) {
		printf("AUTO CLIMB SEQUENCE %d %d\n\n", m_climbSequenceStep, mastPosition);
		if (m_climbSequenceStep == 0) {	// Pull up to level 1
			if (mastPosition > 46) {
				shooter->TiltDown();
				shooter->BucketDown();
				shooter->Shoot();
				m_mast->Set(-1.0);
			} else {
				m_climbSequenceStep++;
				m_mast->Set(0.0);
			}
		} else if (m_climbSequenceStep == 1) {	// Tilt to put static hooks on level 1
			if (tiltPosition < 526) {
				m_tilt->Set(-1.0);
			} else {
				m_climbSequenceStep++;
				m_tilt->Set(0.0);
			}
		} else if (m_climbSequenceStep == 2) {	// Raise mast to lower robot onto level 1
			if (mastPosition < 57) {
				m_mast->Set(1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 3) {	// Tilt mast to clear second bar.
			if (tiltPosition < 566) {
				m_tilt->Set(-1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 4) {	// Raise mast to level 2
			if (mastPosition < 886) {
				m_mast->Set(1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 5) {
			if (tiltPosition > 543) {
				m_tilt->Set(1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 6) {
			if (mastPosition > 580) {	// was 592
				m_mast->Set(-1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 7) {
			if (tiltPosition < 610) {
				m_tilt->Set(-1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if(m_climbSequenceStep == 8) {
			if (mastPosition > 180) {
				m_mast->Set(-1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 9) {
			if (tiltPosition > 508) {
				m_tilt->Set(1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if(m_climbSequenceStep == 10) {
			if (mastPosition > 46) {
				m_mast->Set(-1.0);
			} else {
				m_climbSequenceStep++;
				m_mast->Set(0.0);
			}
		} else if (m_climbSequenceStep == 11) {
			if (tiltPosition < 530) {
				m_tilt->Set(-1.0);
			} else {
				m_climbSequenceStep++;
				m_tilt->Set(0.0);
			}
		} else if (m_climbSequenceStep == 12) {
			if (mastPosition < 882) {
				m_mast->Set(1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 13) {
			if (tiltPosition < 550) {
				m_tilt->Set(-1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 14) {
			shooter->TiltUp();
			m_climbSequenceStep++;
		} else {
			m_tilt->Set(0.0);
			m_mast->Set(0.0);
		}
	} else {
		m_tilt->Set(0.0);
		m_mast->Set(0.0);
	}
	
	if (m_controls->GetShooterY() > 0.5) {
		HooksUp();
	}
}

void Climber::TiltToDrivingPosition() {
	int tiltPosition = m_tiltPot->GetValue();
	int targetPosition = 428;
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

void Climber::HooksDown() {
	m_hooksUp->Set(true);
	m_hooksDown->Set(false);
}

void Climber::HooksUp() {
	m_hooksUp->Set(false);
	m_hooksDown->Set(true);
}
