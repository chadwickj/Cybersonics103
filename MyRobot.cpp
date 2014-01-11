#include "WPILib.h"
#include "DriveBase.h"
#include "Pickup.h"
#include "Shooter.h"
#include "Climber.h"
#include "Controls.h"
#include "HelperFunctions.h"
#include "AutonController.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	AutonController* autonController;
	
	DriveBase* drivebase;
	Pickup* pickup;
	Shooter* shooter;
	Controls* controls;
	Climber* climber;
	
	Relay* compressor;
	DigitalInput* pressureSwitch;
	
	DriverStationLCD* dsLCD; 
	DriverStation* driverStation;
	
	Timer* timer;
	
	SendableChooser *autonSelector;

public:
	RobotDemo(void)
	{
		autonController = AutonController::GetInstance();
		
		drivebase = DriveBase::GetInstance();
		shooter = Shooter::GetInstance();
		pickup = Pickup::GetInstance();
		climber = Climber::GetInstance();
		controls = Controls::GetInstance();
		
		compressor = new Relay(COMPRESSOR_RELAY_CHAN, Relay::kForwardOnly);
		pressureSwitch = new DigitalInput(PRESSURE_SWITCH_CHAN);
		
		dsLCD = DriverStationLCD::GetInstance();
		driverStation = DriverStation::GetInstance();
		
		timer = new Timer();
		
		autonSelector = new SendableChooser();
		autonSelector->AddObject("1. Test - Test Auton", (void*)1);
		autonSelector->AddObject("2. Wayne Cokeley - Bottom Left, Front Pickup", (void*)2);
		autonSelector->AddObject("3. Mike L. NOT FINISHED 7 SHOT", (void*)3);
		autonSelector->AddObject("4. Jack Tusman NOT FINISHED", (void*)4);
		autonSelector->AddObject("5. Jim the Welder - Bottom Right, Pyramid Pickup", (void*)5);
		autonSelector->AddObject("6. Cliff Dey - Shoot from back of pyramid ONLY", (void*)6);
		//autonSelector->AddObject("7. ", (void*)7);
		autonSelector->AddDefault("0. DEFAULT - Do Nothing", (void*)0);
		
		SmartDashboard::init();
		SmartDashboard::PutData("Autonomous Mode", autonSelector);
		
		GetWatchdog().Kill();
	}

	/**
	 * TODO: Win.
	 */
	void Autonomous(void)
	{
		compressor->Set(Relay::kOn);
		int selectedAutoMode = (int)(autonSelector->GetSelected());
		
		while (IsAutonomous() && IsEnabled()) 
		{	
			climber->TiltToDrivingPosition();
			switch (selectedAutoMode) {
				case 0: autonController->DoNothing(); break;
				case 1: autonController->Test(); break;
				case 2: autonController->WayneCokeley(); break;
				case 3: autonController->MikeLube(); break;
				case 4: autonController->JackTusman(); break;
				case 5: autonController->JimTheWelder(); break;
				case 6: autonController->CliffDey(); break;
		}
			
			// Print Encoder Values to Driver station LCD
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			// For Debug Purposes
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", leftEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", rightEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Left In. %f      ", encoderCountToInches(leftEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Right In. %f     ", encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Gyro: %f         ", drivebase->GetGyroAngle());
			//dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "L: %f R: %f      ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "Auto: %d            ", (int)(autonSelector->GetSelected()));
			dsLCD->UpdateLCD();
		}
	}

	/**
	 * TODO
	 */
	void OperatorControl(void)
	{
		drivebase->DisableEncoderPid();
		drivebase->ResetEncoders();
		drivebase->DisableGyroPid();
		
		while (IsOperatorControl() && IsEnabled())
		{	
			autonController->Reset();
			drivebase->EnableTeleopControls();
			pickup->EnableTeleopControls();
			shooter->EnableTeleopControls();
			climber->EnableTeleopControls();
			
			// Pneumatics
			if(pressureSwitch->Get() == 1){
				compressor->Set(Relay::kOff);
			} else {
				compressor->Set(Relay::kOn);
			}
			
			// Print Encoder Values to Driver station LCD
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
				drivebase->ResetGyro();
			}
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Tilt Pot %d ", climber->GetTiltPot());
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Mast Pot %d ", climber->GetMastPot());
			//dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", leftEncoderCount);
			//dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", rightEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Left In. %f      ", encoderCountToInches(leftEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Right In. %f     ", encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Gyro: %f         ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "Sonic: %f      ",  drivebase->GetUltrasonicDistance());
			//dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "PSwitch: %d      ",  pressureSwitch->Get());
			//dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "L: %f R: %f      ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->UpdateLCD();
			
			// Wait(0.005);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		float p = 0.015;
		float i = 0.0;
		float d = 0.0;
		
		// Test Gyro PID
		//float p = 0.013022;
		//float i = 0.0;
		//float d = 0.002116;
		
		float encoderSetpoint = 200.0;
		float turnSetpoint = 90.0;
		float distanceIncrement = 0.01;
		float increment = 0.000001;
		
		bool timerStopped = false;
		bool timerRunning = false;
		
		while (IsTest() && IsEnabled()) {
			
			if (controls->GetLeftButton(3)) {
				p += increment;
			}
			if (controls->GetLeftButton(2)) {
				p -= increment;
			}
			
			if (controls->GetLeftButton(8)) {
				i += increment;
			}
			if (controls->GetLeftButton(9)) {
				i -= increment;
			}
			
			if (controls->GetRightButton(3)) {
				d += increment;
			}
			if (controls->GetRightButton(2)) {
				d -= increment;
			}
			
			if (controls->GetRightButton(3)) {
				encoderSetpoint += distanceIncrement;
			}
			if (controls->GetRightButton(2)) {
				encoderSetpoint -= distanceIncrement;
			}
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
				drivebase->ResetGyro();
			}
		/*	
			// Controls for gyro
			PIDController* gyroController = drivebase->GetGyroController();
			//gyroController->SetPID(p, i, d);
			
			//gyroController->SetPID(GYRO_P, GYRO_I, GYRO_D);
			gyroController->SetSetpoint(turnSetpoint);
			
			if(gyroController->IsEnabled()) {
				drivebase->SetRightSpeed(gyroController->Get());
				
			} else if (!gyroController->IsEnabled() && !drivebase->EncoderPidIsEnabled()) {
				drivebase->SetRightSpeed(0.0);
			}

			bool onTarget = fabs(gyroController->GetSetpoint() - drivebase->GetGyroAngle()) < 2.0;
			if(onTarget) {
				if (timerStopped) {
					timer->Reset();
				}
				timer->Start();
				timerStopped = false;
				if (timer->Get() > 0.50) {
					// TODO: instead of disable, set speed to 0 and make it hold its position.
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Gyro: DONE             ");
					dsLCD->UpdateLCD();
					gyroController->Disable();
				}
			} else {
				timer->Stop();
				timerStopped = true;
			}
			
			if (controls->GetRightButton(4)) {
				gyroController->Enable();
			}
			if (controls->GetRightButton(5)) {
				gyroController->Disable();
				//drivebase->Turn(turnSetpoint, 2);
			}
			*/
			
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
		//	drivebase->SetEncoderSetpoint(encoderSetpoint);
			// drivebase->SetEncoderPID(p,i,d);
		//	drivebase->SetLeftEncoderPID(p, i, d);
		//	drivebase->SetRightEncoderPID(p, i, d);
			
			if (controls->GetLeftButton(4)) {
			/*	timer->Start();
				timer->Reset();
				timerRunning = true;
				printf("Timer Running: %s \n", timerRunning ? "True" : "false");*/
				//drivebase->EnableEncoderPid();
				//drivebase->DriveStraight(encoderSetpoint, 2.0, DRIVE_STRAIGHT_P);
				drivebase->DriveStraight(encoderSetpoint, 2.0, p);
			}
			/*
			float t = 0.75;
			if (timerRunning) {
				drivebase->SetSpeed(timer->Get() / t);
				printf("Speed: %f \n", drivebase->GetLeftSpeed());
			}
			
			if (timer->Get() > t) {
				drivebase->EnableEncoderPid();
				timer->Stop();
				timer->Reset();
				timerRunning = false;
				printf("Timer Expired: %s \n", !timerRunning ? "True" : "false");
			}
			*/
			if (controls->GetLeftButton(5)) {
				drivebase->DisableEncoderPid();
			}
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "L %f, R: %f      ", encoderCountToInches(leftEncoderCount), encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Gyro %f     ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "L: %f R: %f        ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "p: %f              ",  p);
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "i: %f              ", i);
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "d: %f              ", d);
			
			dsLCD->UpdateLCD();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

