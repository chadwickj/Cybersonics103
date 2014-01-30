#include "WPILib.h"
#include "Constants.h"
#include "Pickup.h"
#include "Controls.h"
//#include "Shooter2.h"
//#include "math.h"


Pickup* Pickup::m_instance = NULL;

Pickup* Pickup::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Pickup();
  }
  return m_instance;
}

Pickup::Pickup ()
{
    m_controls = Controls::GetInstance();

    pickup = new Talon(PICKUP_MOTOR);
    pickupArm = new Talon(PICKUP_ARM_MOTOR);

    //m_armSolenoid = new Solenoid(PICKUP_ARM_SOLENOID);

    //int pickupArmUpperLimit = ;
    //int pickupArmLowerLimit = ;
}
Pickup::EnableTeleopControls()
{
    int pickupSpeed = m_controls->GetPickupY();

    if (pickupSpeed < -.1 && pickupSpeed > .1) {
        pickup->MoveArm(pickupSpeed);
    } else {
        pickup->MoveArm(0);
    }
    if (m_controls->GetPickupButton(x)) {
        pickup->TurnOn();
    } else if (m_controls->GetPickupButton(x)) {
        pickup->TurnOff();
    } else {
        pickup->TurnOff();
    }
}

void Pickup::TurnOn()
{
    pickupMotor->Set(1.0);
}

void Pickup::TurnOff()
{
    pickupMotor->Set(0.0);
}

void Pickup::MoveArm(float speed)
{
    pickupArm->Set(1 * speed);
}
/*
Pickup::EnableEncoderPid()
{

}

Pickup::DisableEncoderPid()
{

}

Pickup::EncoderPidIsEnabled()
{

}

Pickup::GetEncoderCount()
{

}
*/
