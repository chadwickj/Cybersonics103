#include "WPILib.h"
#include "DriveBase.h"
#include "Controls.h"
#include "HelperFunctions.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	DriveBase* drivebase;
	Controls* controls;
	
	DriverStationLCD* dsLCD; 
	DriverStation* driverStation;
	
	LiveWindow* liveWindow;

public:
	RobotDemo(void)
	{
		drivebase = DriveBase::GetInstance();
		controls = Controls::GetInstance();
		
		dsLCD = DriverStationLCD::GetInstance();
		driverStation = DriverStation::GetInstance();
		
		liveWindow = LiveWindow::GetInstance();
		
		GetWatchdog().Kill();
	}

	/**
	 * TODO: Win.
	 */
	void Autonomous(void)
	{
		while (IsAutonomous() && IsEnabled()) {
			
		}
	}

	/**
	 * TODO
	 */
	void OperatorControl(void)
	{
		while (IsOperatorControl() && IsEnabled())
		{	
			drivebase->EnableTeleopControls();
			// Print Encoder Values to Driver station LCD
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
			}
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", leftEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", rightEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Left In. %f      ", encoderCountToInches(leftEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Right In. %f     ", encoderCountToInches(rightEncoderCount));
			dsLCD->UpdateLCD();
			
			// Wait(0.005);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		PIDController* leftEncoderController = drivebase->GetLeftEncoderController();
		PIDController* rightEncoderController = drivebase->GetRightEncoderController();
		float p = 0.019;
		float i = 0.0;
		float d = 0.016;
		float f = 0.0;
		float increment = 0.0001;
		float speedIncrement = 0.001;
		float setpoint = 300.0;
		
		while (IsTest() && IsEnabled()) {
			// Comment out teleop controls to test PID
			// drivebase->EnableTeleopControls();
			
			// Print Encoder Values to Driver station LCD
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
			}
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", leftEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", rightEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Left In. %f      ", encoderCountToInches(leftEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Right In. %f     ", encoderCountToInches(rightEncoderCount));

			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "P %f I %f", p, i);
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "D %f F %f", d, f);
			dsLCD->UpdateLCD();
			
			// Testing encoder PID control
			if (controls->GetRightTrigger()) {
				p = 0.0;
				i = 0.0;
				d = 0.0;
				f = 0.0;
			}
			
			if (controls->GetRightButton(4)) {
				leftEncoderController->Enable();
				rightEncoderController->Enable();
			} 
			if (controls->GetRightButton(5)){
				leftEncoderController->Disable();
				rightEncoderController->Disable();
			}

			printf("PID %s\n", leftEncoderController->IsEnabled() ? "Enabled" : "Disabled");
			
			if (controls->GetLeftButton(3)) {
				p += increment;
			} else if (controls->GetLeftButton(2)) {
				p -= increment;
			}
			
			if (controls->GetLeftButton(9)) {
				i += increment;
			} else if (controls->GetLeftButton(8)) {
				i -= increment;
			}
			
			if (controls->GetRightButton(3)) {
				d += increment;
			} else if (controls->GetRightButton(2)) {
				d -= increment;
			}
			
			if (controls->GetRightButton(9)) {
				f += speedIncrement;
			} else if (controls->GetRightButton(8)) {
				f -= speedIncrement;
			}
			
			leftEncoderController->SetPID(p, i, d);
			rightEncoderController->SetPID(p, i, d);
			
			leftEncoderController->SetSetpoint(setpoint);
			rightEncoderController->SetSetpoint(setpoint);

			liveWindow->Run();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

