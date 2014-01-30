/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package robot;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Razim Zavac
 */
public class DriveControl {
    public Joystick leftDriveStick = new Joystick(1);
    public Joystick rightDriveStick = new Joystick(2);
    public Joystick leftControlStick = new Joystick(3);
    public Joystick rightControlStick = new Joystick(4);
        public void operatorControl() {
        chassis.setSafetyEnabled(true);
        while (isOperatorControl() && isEnabled()) {
            //Drive Controls
            chassis.tankDrive(leftDriveStick, rightDriveStick);
            Timer.delay(0.01);
            //Shooter Controls
            
        }
        
    }
}
