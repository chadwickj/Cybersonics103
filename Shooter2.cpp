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

}

void WillmanShooter::EnableTelopControls ()
{
    if (m_controls->GetWillmanShooterButton(SHOOTER_BUTTON))
    {
        WillmanShooter->Shoot();
    } else {
        WillmanShooter->Reset();
        WillmanShooter->LoadShooter(); // May need to be used in pickup
    }

    if (shooterLoading) {
        WillmanShooter->LoadShooter();
    }
}

void WillmanShooter::Shoot()
{
    m_resetLauncher->Set(false);
    m_fireLauncher->Set(true);
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
        m_shooterMotor->Set(1.0);
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
