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
    public Main m = new Main();
        public void operatorControl() {
        m.chassis.setSafetyEnabled(true);
        while (m.isOperatorControl() && m.isEnabled()) {
            //Drive Controls
            m.chassis.tankDrive(m.leftDriveStick, m.rightDriveStick);
            Timer.delay(0.01);
            //Shooter Controls
            
        }
        
    }
}
