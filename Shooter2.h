#ifndef Shooter2_H
#define Shooter2_H

#include "WPILib.h"

class WillmanShooter {
private:
    Controls* m_controls;

    Solenoid* m_fireLauncher;
    Solenoid* m_resetLauncher;

    Talon* m_shooterMotor;

    AnalogChannel* m_motorPot;

    bool m_shooterLoading;

    int m_shooterLoadLimit;

    bool m_shooterResetting();

public:
    static WillmanShooter* GetInstance();

    WillmanShooter();

    void Shoot();
    void Reset();
    void LoadShooter();
    bool IsShooterResetting();

    void EnableTeleopControls();

};

#endif // Shooter2_H_INCLUDED
