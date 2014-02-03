#include "WPILib.h"
#include "Pickup.h"
#include "Constants.h"
#include "Controls.h"

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

    m_lowerArmLimit = 1024;
    m_upperArmLimit = 1024;

    buttonPressed = false;
}
void Pickup::EnableTeleopControls()
{
    float pickupSpeed = m_controls->GetPickupY();
    int armPosition = m_pickupArmPot->GetValue();

    if (pickupSpeed > 0.0 && armPosition < m_upperArmLimit) {
        MoveArm(pickupSpeed);
    } else if (pickupSpeed < 0.0 && armPosition > m_lowerArmLimit) {
        MoveArm(pickupSpeed);
    } else {
        MoveArm(0);
    }

    if (m_controls->GetPickupButton(PICKUP_BUTTON)) { // buttonPressed just ensures that pickup doesnt infinitly toggle if a button is held down
        if (m_pickupMotor->Get() == 0 && !buttonPressed) {
            buttonPressed = true;
            StartPickup();
        } else if (m_pickupMotor->Get() != 0 && !buttonPressed) {
            buttonPressed = true;
            StopPickup();
        }
    } else {
        buttonPressed = false;
    }
}

void Pickup::StartPickup()
{
    m_pickupMotor->Set(1.0);
}

void Pickup::StopPickup()
{
    m_pickupMotor->Set(0.0);
}

void Pickup::MoveArm(float speed)
{
    m_pickupArm->Set(1 * speed);
}
