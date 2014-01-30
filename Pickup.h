#ifndef PICKUP_H
#define PICKUP_H

#include "WPILib.h"

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

    //Encoder* m_pickupEncoder;
    //PIDController m_pickupEncoderController;

public:
	static Pickup* GetInstance();
	Pickup();

    void EnableTeleopControls();

    void MoveArm(float speed);
    void TurnOn();
    void TurnOff();


    //void SetPickupEncoderSetpoint(float setpoint);
    //int GetEncoderCount();
    //void ResetEncoder();
    //void EnableEncoderPid();
	//void DisableEncoderPid();
	//bool EncoderPidIsEnabled();



}


#endif // PICKUP_H_INCLUDED
