#ifndef PICKUP_H
#define PICKUP_H

#include "WPILib.h"
#include "Controls.h"

class Pickup {

private:
	static Pickup* m_instance;

    Talon* m_pickupMotor;
    Talon* m_pickupArm;

    Controls* m_controls;

    AnalogChannel* m_pickupArmPot;

    int m_lowerArmLimit;
    int m_upperArmLimit;

    bool buttonPressed;

    //Solenoid* m_armSolenoid;

	
public:
	static Pickup* GetInstance();
	Pickup();

    void EnableTeleopControls();

    void MoveArm(float speed);
    void StartPickup();
    void StopPickup();
};

#endif
