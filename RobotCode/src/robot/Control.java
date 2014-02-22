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
public class Control {
    public Main m = new Main();
    public void driveControl() {
        m.chassis.setSafetyEnabled(true);
        while (m.isOperatorControl() && m.isEnabled()) {
            //Drive Controls
            m.chassis.tankDrive(m.leftDriveStick, m.rightDriveStick);
            Timer.delay(0.01);
        }
    }
    public void shooterControl(int button) {
        //Initializes shooter input
        boolean btL = m.leftControlStick.getRawButton(button);
        boolean btR = m.rightControlStick.getRawButton(button);
        //Outputs action based on shooter input (Left Sticks)
        if(btL){
            
        }
        if(btR){
            
        }
    }
}
