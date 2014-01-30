package robot;


import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.*;

public class Main extends SimpleRobot {

    public RobotDrive chassis = new RobotDrive(1, 2);
    public Joystick leftDriveStick = new Joystick(1);
    public Joystick rightDriveStick = new Joystick(2);
    public Joystick leftControlStick = new Joystick(3);
    public Joystick rightControlStick = new Joystick(4);
    
    public void doSomething(){
        chassis.drive(-0.5,0.0);
        Timer.delay(2.0);
        //or use this
        //Thread.sleep(2000);
        chassis.drive(0.0,0.0)
    }
    
}
