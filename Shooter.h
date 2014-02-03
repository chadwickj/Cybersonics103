#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"
#include "Controls.h"

class Shooter {
	
private:
    static Shooter* m_instance;

    Solenoid* m_fireLauncher;
    Solenoid* m_resetLauncher;
    Solenoid* m_fireTrigger;
    Solenoid* m_resetTrigger;

    Controls* m_controls;

    Timer* m_timer;

   enum ResetSequence {
    	Waiting,
        Firing,
        Resetting,
        Locking
    } shooterReset;

    

public:
    static Shooter* GetInstance();

    Shooter();

    void Reset();
    
    void Shoot();
    void PullBackLauncher();
    void Lock();
    void Set();
    void CheckReset();

    void EnableTeleopControls();
	
};

#endif
