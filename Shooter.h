#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"
#include "Controls.h"

class Shooter {
	
private:
    static Shooter* m_instance;

public:
	Shooter();
	Shooter* GetInstance();
	
	void EnableTeleopControls();
};

#endif
