#include "WPILib.h"
#include "WillmanShooter2.h"
#include "Controls.h"
#include "Constants.h"

WillmanShooter* WillmanShooter::m_instance = NULL;

WillmanShooter* Shooter::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new WillmanShooter();
  }
  return m_instance;
}

void WillmanShooter::WillmanShooter ()
{
    m_controls = Controls::GetInstance();

    m_fireLauncher = new Solenoid(LAUNCHER_FIRE_SOLENOID);
    m_resetLauncher = new Solenoid(LAUNCHER_RESET_SOLENOID);

    m_shooterMotor = new Talon(SHOOTER_MOTOR);

    m_motorPot = new AnalogChannel(SHOOTER_MOTOR_POT)

    m_shooterLoadLimit = ;

    m_shooterLoading = false;

    timer = new Timer();

}

void WillmanShooter::EnableTelopControls ()
{
    if (m_controls->GetShooterButton(SHOOTER_BUTTON) && !IsSolenoidFired()) {
        Shoot();
    } else if (m_controls->GetShooterButton(SHOOTER_RESET_BUTTON) && !shooterLoading && !IsSolenoidFired()) {
        LoadShooter();
    } else if (shooterLoading) {
        LoadShooter(); // May want to replace this with throttle to use multiple distances
    }

    if (IsSolenoidFired() && timer->HasPeriodPassed(1.0)) { // Automatically reengage SuperShifter. May need a timer so it isn't reset mid-shot.
        Reset();
        timer->Stop();
        timer->Reset();
    }
}

void WillmanShooter::Shoot()
{
    m_resetLauncher->Set(false);
    m_fireLauncher->Set(true);
    timer->Reset();
    timer->Start();
}

void WillmanShooter::Reset()
{
    m_fireLauncher->Set(false);
    m_resetLauncher->Set(true);
}

void WillmanShooter::LoadShooter()
{
    int motorValue = m_motorPot->GetValue();
    if (motorValue < m_shooterLoadLimit) {
        m_shooterMotor->Set(0.5);
        shooterLoading = true;
    } else {
        m_shooterMotor->Set(0.0);
        shooterLoading = false;
    }
}

bool WillmanShooter::IsShooterResetting()
{
    return shooterLoading;
}

bool WillmanShooter::IsSolenoidFired()
{
    return m_fireLauncher->Get();
}
