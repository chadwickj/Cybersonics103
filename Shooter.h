#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"

class Shooter {
private:
    Solenoid* m_fireLauncher;
    Solenoid* m_resetLauncher;
    Solenoid* m_trigger;
    Controls* m_controls;

    Timer* timer;

    enum ResetSequence {
        false,
        Firing,
        Resetting,
        Locking
    } shooterReset;

    void Lock();
    void Set();

public:
    static Shooter* GetInstance();

    Shooter();

    void Shoot();
    void Reset();
    void CheckReset();

    void EnableTeleopControls();

};

#endif // SHOOTER_H_INCLUDED
