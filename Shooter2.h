#ifndef Shooter2_H
#define Shooter2_H

#include "WPILib.h"

class WillmanShooter {
private:
    static WillmanShooter* m_instance;

    Controls* m_controls;

    Solenoid* m_fireLauncher;
    Solenoid* m_resetLauncher;

    Talon* m_shooterMotor;

    AnalogChannel* m_motorPot;

    Timer* timer;

    bool m_shooterLoading;

    int m_shooterLoadLimit;

public:
    static WillmanShooter* GetInstance();

    WillmanShooter();

    void Shoot();
    void Reset();
    void LoadShooter();
    bool IsShooterResetting();
    bool IsSolenoidFired();

    void EnableTeleopControls();

};

#endif // Shooter2_H_INCLUDED
