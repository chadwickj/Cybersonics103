/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
/*
http://wpilib.screenstepslive.com/s/3120/m/7885/l/79459-the-hello-world-of-frc-robot-programming
http://first.wpi.edu/Images/CMS/First/Getting_Started_with_Java_for_FRC.pdf
*/
package edu.wpi.first.wpilibj.templates;


import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotTemplate extends SimpleRobot {
    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    RobotDrive chassis = new RobotDrive(1, 2);
    Joystick leftDriveStick = new Joystick(1);
    Joystick rightDriveStick = new Joystick(2);
    Joystick leftControlStick = new Joystick(3);
    Joystick rightControlStick = new Joystick(4);
    
    public void autonomous() {
        chassis.setSafetyEnabled(false);
        chassis.drive(-0.5, 0.0);
        Timer.delay(2.0);
        chassis.drive(0.0, 0.0);
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        chassis.setSafetyEnabled(true);
        while (isOperatorControl() && isEnabled()) {
            chassis.tankDrive(leftDriveStick, rightDriveStick);
            Timer.delay(0.01);
        }
    }
}
