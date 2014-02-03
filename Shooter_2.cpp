#include "WPILib.h"
#include "Shooter_2.h"
#include "Controls.h"
#include "Constants.h"

WillmanShooter* WillmanShooter::m_instance = NULL;

WillmanShooter* WillmanShooter::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new WillmanShooter();
  }
  return m_instance;
}

WillmanShooter::WillmanShooter ()
{
    m_controls = Controls::GetInstance();

    m_fireLauncher = new Solenoid(LAUNCHER_FIRE_SOLENOID);
    m_resetLauncher = new Solenoid(LAUNCHER_RESET_SOLENOID);

    m_shooterMotor = new Talon(SHOOTER_MOTOR);

    m_motorPot = new AnalogChannel(SHOOTER_MOTOR_POT);

    m_shooterLoadLimit = 1024;

    m_shooterLoading = false;

    timer = new Timer();

}

void WillmanShooter::EnableTeleopControls ()
{
    if (m_controls->GetShooterButton(SHOOTER_BUTTON) && IsSolenoidReset()) { // Cannot fire until solenoid is reset
        Shoot();
    } else if (( m_controls->GetShooterButton(SHOOTER_RESET_BUTTON) || m_shooterLoading ) && IsSolenoidReset() ) {
        LoadShooter();
    }

    if (!IsSolenoidReset() && timer->HasPeriodPassed(0.5)) { // Automatically reengage SuperShifter. Timer is just there so it isn't reset mid-shot.
        Reset();
        timer->Stop();
        timer->Reset();
    }
}

void WillmanShooter::Shoot()
{
    m_resetLauncher->Set(true);
    m_fireLauncher->Set(false);
    //Reset motor pot?

    timer->Reset();
    timer->Start();
}

void WillmanShooter::Reset()
{
    m_resetLauncher->Set(false);
    m_fireLauncher->Set(true);
}

void WillmanShooter::LoadShooter()
{
    int motorValue = m_motorPot->GetValue();
    if (motorValue < m_shooterLoadLimit) {
        m_shooterMotor->Set(0.5);
        m_shooterLoading = true;
    } else {
        m_shooterMotor->Set(0.0);
        m_shooterLoading = false;
    }
}

bool WillmanShooter::IsShooterResetting()
{
    return m_shooterLoading;
}

bool WillmanShooter::IsSolenoidReset()
{
    return m_fireLauncher->Get();
}
