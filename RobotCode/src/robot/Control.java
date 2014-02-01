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
        public void shooterControl() {
            //Initializes shooter input
            boolean btL1 = m.leftControlStick.getRawButton(1);
            boolean btL2 = m.leftControlStick.getRawButton(2);
            boolean btL3 = m.leftControlStick.getRawButton(3);
            boolean btL4 = m.leftControlStick.getRawButton(4);
            boolean btL5 = m.leftControlStick.getRawButton(5);
            boolean btL6 = m.leftControlStick.getRawButton(6);
            boolean btL7 = m.leftControlStick.getRawButton(7);
            boolean btL8 = m.leftControlStick.getRawButton(8);
            boolean btL9 = m.leftControlStick.getRawButton(9);
            boolean btR1 = m.rightControlStick.getRawButton(1);
            boolean btR2 = m.rightControlStick.getRawButton(2);
            boolean btR3 = m.rightControlStick.getRawButton(3);
            boolean btR4 = m.rightControlStick.getRawButton(4);
            boolean btR5 = m.rightControlStick.getRawButton(5);
            boolean btR6 = m.rightControlStick.getRawButton(6);
            boolean btR7 = m.rightControlStick.getRawButton(7);
            boolean btR8 = m.rightControlStick.getRawButton(8);
            boolean btR9 = m.rightControlStick.getRawButton(9);
            
            //Outputs action based on shooter input (Left Sticks)
            if(btL1){
                
            }
            if(btL2){
                
            }
            if(btL3){
                
            }
            if(btL4){
                
            }
            if(btL5){
                
            }
            if(btL6){
                
            }
            if(btL7){
                
            }
            if(btL8){
                
            }
            if(btL9){

            }            
            //Outputs action based on shooter input (Right Sticks)
            if(btR1){
                
            }
            if(btR2){
                
            }
            if(btR3){
                
            }
            if(btR4){
                
            }
            if(btR5){
                
            }
            if(btR6){
                
            }
            if(btR7){
                
            }
            if(btR8){
                
            }
            if(btR9){

            }
        }
}
