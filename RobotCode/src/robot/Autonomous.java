/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package robot;

import edu.wpi.first.wpilibj.*;
import robot.Main;
/**
 *
 * @author Razim Zavac
 */
public class Autonomous {

        public void autonomous() {
        chassis.setSafetyEnabled(false);
        chassis.drive(-0.5, 0.0);
        Timer.delay(2.0);
        chassis.drive(0.0, 0.0);
    }
}
