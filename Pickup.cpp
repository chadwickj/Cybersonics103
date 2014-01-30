#include "WPILib.h"
#include "Constants.h"
#include "Pickup.h"
#include "Controls.h"
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

    m_pickupMotor = new Talon(PICKUP_MOTOR);
    m_pickupArm = new Talon(PICKUP_ARM_MOTOR);
    m_pickupArmPot = new AnalogChannel(PICKUP_ARM_POT);

    m_lowerArmLimit = ;
    m_upperArmLimit = ;

    buttonPressed = false;

    //m_armSolenoid = new Solenoid(PICKUP_ARM_SOLENOID);

    //int pickupArmUpperLimit = ;
    //int pickupArmLowerLimit = ;
}
Pickup::EnableTeleopControls()
{
    int pickupSpeed = m_controls->GetPickupY();
    int armPosition = m_pickupArmPit->GetValue();

    if (pickupSpeed > 0.0 && armPosition < m_upperArmLimit) {
        MoveArm(pickupSpeed);
    } else if (pickupSpeed < 0.0 && armPosition > m_lowerArmLimit) {
        MoveArm(pickupSpeed);
    else {
        MoveArm(0);
    }

    if (m_controls->GetPickupButton(PICKUP_BUTTON)) { // buttonPressed just ensures that pickup doesnt infinitly toggle if a button is held down
        if (pickupMotor->Get() == 0 && !buttonPressed) {
            buttonPressed = true;
            TurnOn();
        } else if (pickupMotor->Get() != 0 && !buttonPressed) {
            buttonPressed = true;
            TurnOff();
        }
    } else {
        buttonPressed = false;
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
