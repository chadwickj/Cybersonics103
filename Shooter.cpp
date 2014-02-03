#include "WPILib.h"
#include "Shooter.h"
#include "Controls.h"
#include "Constants.h"

Shooter* Shooter::m_instance = NULL;

Shooter* Shooter::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Shooter();
  }
  return m_instance;
}

Shooter::Shooter ()
{
    m_controls = Controls::GetInstance();

    m_fireLauncher = new Solenoid(LAUNCHER_FIRE_SOLENOID);
    m_resetLauncher = new Solenoid(LAUNCHER_RESET_SOLENOID);
    m_fireTrigger = new Solenoid(LAUNCHER_FIRE_TRIGGER_SOLENOID);
    m_resetTrigger = new Solenoid(LAUNCHER_RESET_TRIGGER_SOLENOID);


    m_timer = new Timer();

    shooterReset = Waiting;
    CheckReset(); // Make sure shooter is in the correct position (trigger on, firing Solenoids on)

}

void Shooter::EnableTeleopControls ()
{
    if (m_controls->GetShooterButton(SHOOTER_BUTTON) && shooterReset == Waiting) {
        Shoot();
    } else if (shooterReset != Waiting) {
    	Reset();
    }
    
}

void Shooter::Reset() // Pulls 'firing' solenoids back
{
	if (shooterReset == Firing && m_fireLauncher->Get()) { // May need to check if Get value is taken from  the last command recieved or current state
        PullBackLauncher();
    } else if (shooterReset == Resetting && m_resetLauncher->Get()) {
        Lock();
    } else if (shooterReset == Locking && m_fireTrigger->Get()) {
        Set();
    }
}

void Shooter::Shoot() // Pulls back trigger, set 'firing' solenoids launch ball
{
    m_fireTrigger->Set(false);
    m_resetTrigger->Set(true);
    shooterReset = Firing;

    m_timer->Reset();
    m_timer->Start();

}

void Shooter::PullBackLauncher() 
{
    m_fireLauncher->Set(false);
    m_resetLauncher->Set(true);
    shooterReset = Resetting;

    m_timer->Stop();
    m_timer->Reset();
    m_timer->Start();
}

void Shooter::Lock() // Fires trigger, to lock 'firing' solenoids
{
    m_fireTrigger->Set(true);
    m_resetTrigger->Set(false);
    shooterReset = Locking;

    m_timer->Stop();
    m_timer->Reset();
    m_timer->Start();
}

void Shooter::Set() // Fires 'firing' solenoids to prepare the launcher
{
    m_resetLauncher->Set(false);
    m_fireLauncher->Set(true);
    shooterReset = Waiting;

    m_timer->Stop();
    m_timer->Reset();
}

void Shooter::CheckReset()
{
    if (shooterReset != false) {
        if (m_fireLauncher->Get()) {
            if (!m_fireTrigger->Get()) {
                Reset();
            } else {
                // Ready to fire
            }
        } else if (m_resetLauncher->Get()) {
            if (!m_fireTrigger->Get()) {
                Lock();
            } else {
                Set();
            }
        } else {
            // Something is wrong.
            Reset();
        }
    } else {
        // Shooter is already being reset
    }
}
