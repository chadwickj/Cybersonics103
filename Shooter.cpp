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
    m_resetTrigger = new Solenoid(LAUNCHER_RESET_TRIGGER_SOLENOID)


    timer = new Timer();

    shooterReset = false;
    CheckReset(); // Make sure shooter is in the correct position (trigger on, firing Solenoids on)

}

Shooter::EnableTelopControls ()
{
    if (m_controls->GetShooterButton(SHOOTER_BUTTON) && shooterReset == false) {
        Shoot();
    } else if (shooterReset == Firing && m_fireLauncher->Get()) { // May need to check if Get value is taken from  the last command recieved or current state
        Reset();
    } else if (shooterReset == Resetting && m_resetLauncher->Get()) {
        Lock();
    } else if (shooterReset == Locking && m_fireTrigger->Get()) {
        Set();
    }
}

Shooter::Shoot() // Pulls back trigger, set 'firing' solenoids launch ball
{
    m_fireTrigger->(false);
    m_resetTrigger->(true);
    shooterReset = Firing;

    timer->Reset();
    timer->Start();

}

Shooter::Reset() // Pulls 'firing' solenoids back
{
    m_fireLauncher->Set(false);
    m_resetLauncher->Set(true);
    shooterReset = Resetting;

    timer->Stop();
    timer->Reset();
    timer->Start();
}

Shooter::Lock() // Fires trigger, to lock 'firing' solenoids
{
    m_fireTrigger->Set(true);
    m_resetTrigger->Set(false);
    shooterReset = Locking;

    timer->Stop();
    timer->Reset();
    timer->Start();
}

Shooter::Set() // Fires 'firing' solenoids to prepare the launcher
{
    m_resetLauncher->Set(false);
    m_fireLauncher->Set(true);
    shooterReset = false;

    timer->Stop();
    timer->Reset();
}

Shooter::CheckReset()
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
