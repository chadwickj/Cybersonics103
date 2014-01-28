#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"

class Shooter {
    private:
    Solenoid* fireLauncher;
    Solenoid* resetLauncher;
    Controls* m_controls;


    public:
    static Shooter* GetInstance();

    Shooter();

    void Shoot();
    void Reset();

    void EnableTeleopControls();

};

#endif // SHOOTER_H_INCLUDED
