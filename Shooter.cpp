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
    m_trigger = new Solenoid(LAUNCHER_TRIGGER_SOLENOID);

    timer = new Timer();

    shooterReset = false;
    shooter->CheckReset(); // Make sure shooter is in the correct position (trigger on, firing Solenoids on)

}

Shooter::EnableTelopControls ()
{
    if (m_controls->GetShooterButton(SHOOTER_BUTTON))
    {
        shooter->Shoot();
    } else {
        shooter->Reset();
    }

    if (shooterReset == Firing) {  // Timer is used to help ensure pneumatics have finished their operation before next solenoids moves
        if (timer->HasPeriodPassed(1.0)) {
            shooter->Reset();
        }
    } else if (shooterReset == Resetting) {
        if (timer->HasPeriodPassed(5.0)) {
            shooter->Lock();
        }
    } else if (shooterReset == Locking) {
        if (timer->HasPeriodPassed(1.0)) {
            shooter->Set();
        }
    }
}

Shooter::Shoot() // Pulls back trigger, set 'firing' solenoids launch ball
{
    m_trigger->(false);
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
    m_trigger->Set(true);
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
    if (m_fireLauncher->Get()) {
        shooter->Reset();
    } else if (m_resetLauncher->Get()) {
        if (!m_trigger->Get() {
        shooter->Lock();
        }
        shooter->Set();
    } else {
        // LauncherSolenoids were not fired, and LauncherSolenoids are not reset. Something may be wrong.
        shooter->Reset();
    }
}
