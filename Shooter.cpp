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

    fireLauncher = new Solenoid(LAUNCHER_FIRE_SOLENOID);
    resetLauncher = new Solenoid(LAUNCHER_RESET_SOLENOID);

}

Shooter::EnableTelopControls ()
{
    if (m_controls->GetShooterButton(x))
    {
        shooter->Shoot();
    } else {
        shooter->Reset();
    }
}

Shooter::Shoot()
{
    resetLauncher->(false);
    fireLauncher->Set(true);
}

Shooter::Reset();
{
    fireLauncher->Set(false);
    resetLauncher->Set(true);
}
