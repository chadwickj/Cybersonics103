#include "WPILib.h"
#include "Shooter.h"
#include "Constants.h"

Shooter* Shooter::m_instance = NULL;

Shooter* Shooter::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Shooter();
  }
  return m_instance;
}

Shooter::Shooter() {
	m_shooterWheel1 = new Talon(SHOOTER_BAG_PWM);
	m_shooterWheel2 = new Talon(SHOOTER_775_PWM);
	
	m_tiltUp = new Solenoid(5);
	m_tiltDown = new Solenoid(6);
	
	m_bucketUp = new Solenoid(2);
	m_bucketDown = new Solenoid(1);
	
	m_launcherFire = new Solenoid(3);
	m_launcherStore = new Solenoid(4);
	
	m_controls = Controls::GetInstance();
	m_triggerPressed1 = false;
	m_triggerPressed2 = false;
	
	m_bucketIsUp = true;
	m_tiltIsUp = false;
	m_shooterIsOn = false;
	
	m_timer = new Timer();
	m_timer->Reset();
			
	m_tiltTimer = new Timer();
	m_tiltTimer->Reset();
	
	m_rapidFireTimer = new Timer();
	m_rapidFireTimer->Reset();
	m_rapidFireStep = 0;
}

void Shooter::EnableTeleopControls() {
	if (m_controls->GetShooterTrigger()) { // Shoot
		m_shooterWheel1->Set(0.8);
		m_shooterWheel2->Set(0.8);
		m_shooterIsOn = true;
	} else {
		m_shooterWheel1->Set(0.0);
		m_shooterWheel2->Set(0.0);
		m_shooterIsOn = false;
	}
	
	// To reset for start of match.
	if (m_controls->GetLeftTrigger()) {
		Shoot();
	}
	
	if (m_controls->GetRightTrigger() && m_bucketIsUp && m_shooterIsOn) {
		Shoot();
		m_timer->Start();
	}
	
	if (m_timer->Get() > 0.15) {
		m_timer->Stop();
		m_timer->Reset();
		Reset();
	}
	
	if (m_controls->GetRightButton(2) && m_bucketIsUp && m_rapidFireStep < 4 && m_shooterIsOn) {
		m_rapidFireTimer->Start();
		if (m_rapidFireTimer->Get() > 0.15) {
			Reset();
		} else {
			Shoot();
			printf("Shot, Rapid Step: %d\n", m_rapidFireStep);
		}
		if (m_rapidFireTimer->Get() > 0.6) {
			m_rapidFireTimer->Reset();
			m_rapidFireStep++;
			printf("Reset & ++ Step: %d\n", m_rapidFireStep);
		}
	} 
	
	if (m_rapidFireTimer->Get() > 2.0 && m_rapidFireStep == 4) {
		m_rapidFireStep = 0;
		m_rapidFireTimer->Stop();
		m_rapidFireTimer->Reset();
	}
	
	if (m_controls->GetShooterY() > 0.5) {
		BucketUp();
		m_tiltTimer->Start();
	}
	
	if (m_tiltTimer->Get() > 0.5) {
		TiltUp();
		m_tiltTimer->Stop();
		m_tiltTimer->Reset();
	}
	
	if (m_controls->GetShooterY() < -0.5) {
		BucketDown();
		TiltDown();
	}
	
	if (m_controls->GetShooterButton(4)) {
		TiltDown();
	}
	
	if (m_controls->GetShooterButton(5)) {
		TiltUp();
	}
	
	if (m_controls->GetShooterButton(3)) {
		BucketUp();
	}
	
	if (m_controls->GetShooterButton(2)) {
		BucketDown();
	}
	
	if (m_controls->GetShooterButton(10)) {
		float sSpeed = ((m_controls->GetShooterThrottle()+1)/2);
		printf("Shooter speed: %f\n\n", sSpeed);
		TurnOn((m_controls->GetShooterThrottle()+1)/2);
	}
}

void Shooter::TurnOn(float speed) {
	m_shooterWheel1->Set(speed);
	m_shooterWheel2->Set(speed);
}

void Shooter::TurnOff() {
	m_shooterWheel1->Set(0.0);
	m_shooterWheel2->Set(0.0);
}

void Shooter::Shoot() {
	m_launcherFire->Set(true);
	m_launcherStore->Set(false);
}

void Shooter::Reset() {
	m_launcherFire->Set(false);
	m_launcherStore->Set(true);
}

void Shooter::TiltUp() {
	m_tiltUp->Set(true);
	m_tiltDown->Set(false);
	
	m_tiltIsUp = true;
}

void Shooter::TiltDown() {
	m_tiltUp->Set(false);
	m_tiltDown->Set(true);
	
	m_tiltIsUp = false;
}

void Shooter::BucketUp() {
	m_bucketUp->Set(true);
	m_bucketDown->Set(false);
	
	m_bucketIsUp = true;
}

void Shooter::BucketDown() {
	m_bucketUp->Set(false);
	m_bucketDown->Set(true);
	
	m_bucketIsUp = false;;
}

bool Shooter::IsBucketUp() {
	return m_bucketIsUp;
}

bool Shooter::IsTiltUp() {
	return m_tiltIsUp;
}
