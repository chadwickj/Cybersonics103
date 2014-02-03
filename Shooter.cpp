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
   
}

void Shooter::EnableTeleopControls ()
{
 
}