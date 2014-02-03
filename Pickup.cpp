#include "WPILib.h"
#include "Pickup.h"
#include "Constants.h"

Pickup* Pickup::m_instance = NULL;

Pickup* Pickup::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Pickup();
  }
  return m_instance;
}

Pickup::Pickup() {
	
}

void Pickup::EnableTeleopControls() {
	
}
