#include "Robot.h"

#include "Commands/Drive/DriveJoystick.h"
#include "Commands/Shooter/FireShooter.h"
#include "Commands/Shooter/ShooterTest.h"
#include "Commands/Drive/DriveSet.h"
#include "Commands/Drive/DriveDistance.h"
#include "Commands/FindTarget.h"
#include "Commands/AutoAlign.h"
#include "Commands/Shooter/SetShooterAngle.h"
#include "Commands/Shooter/Fire.h"
#include "SmartDashboard/SmartDashboard.h"

#include "Commands/Autonomous/Sequences/SimpleAutonomous.h"
#include "Commands/Autonomous/Sequences/AlignAutonomous.h"
#include <Commands/Shooter/ShooterControl.h>
#include "CameraServer.h"

std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<ShooterWheels> Robot::shooterwheels;
std::shared_ptr<ShooterRotation> Robot::shooterrotation;
std::shared_ptr<Shifter> Robot::shifter;
std::shared_ptr<ShooterActuator> Robot::shooteractuator;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Vision> Robot::vision;
std::shared_ptr<CameraServer> Robot::server;
std::shared_ptr<SendableChooser> Robot::autoChooser;
bool Robot::inverted;


void Robot::RobotInit()
{
	RobotMap::init();
	server.reset(CameraServer::GetInstance());
	drivetrain.reset(new Drivetrain());
	shooterwheels.reset(new ShooterWheels());
	shooterrotation.reset(new ShooterRotation());
	vision.reset(new Vision());
	shifter.reset(new Shifter());

	/*
	 * This MUST be here. If the OI creates Commands (which it very likely
	 * will), constructing it during the construction of CommandBase (from
	 * which commands extend), subsystems are not guaranteed to be
	 * yet. Thus, their requires() statements may grab null pointers. Bad
	 * news. Don't move it.
	 */

	/*
	 * ^ I'm not sure CommandBase exists any more...
	 */

	oi.reset(new OI());
	shooteractuator.reset(new ShooterActuator());
	shifter.reset(new Shifter());

	autoChooser.reset(new SendableChooser());
	InitSmartDashboard();
	SmartDashboard::PutData("Autonomous Defense Chooser", autoChooser.get());

	// instantiate the command used for the autonomous period
	//autonomousCommand.reset((Command *) chooser->GetSelected());
	//drivejoystick.reset(new DriveJoystick());
	//armjoystick.reset(new ArmJoystick());
	//armmove.reset(new ArmMove());
	//autowheels.reset(new AutoWheels());

	//server.get()->SetQuality(50);
	//server.get()->StartAutomaticCapture("cam1");
}

/*
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic()
{
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit()
{
	autonomousCommand.reset((Command *) autoChooser->GetSelected());
	std::printf("Info: Set Auto command!\n");

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();

}

void Robot::AutonomousPeriodic()
{
	Scheduler::GetInstance()->Run();
	vision->PullValues();
}

void Robot::TeleopInit()
{
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();

	//drivejoystick->Start();
	//armmove->Start();
	//autowheels->Start();
	//invertcontrols->Start();
	vision->PullValues();
}

void Robot::TeleopPeriodic()
{
	Scheduler::GetInstance()->Run();

#ifdef SHOOTERBACKUP
    auto gunner = -Robot::oi->getGunner()->GetRawAxis(1);
    if(gunner > TOLERANCE)
    {
    	printf("Fire\n");
        ;
    }
    else if (gunner < -TOLERANCE)
    {
    	printf("Intake\n");
        Intake();
    }
    else
    {
    	//printf("Stop\n");p
        Stop();
    }
	#endif
    PeriodicSmartDashboard();
}

void Robot::TestPeriodic()
{
	lw->Run();
	PeriodicSmartDashboard();
}

void Robot::InitSmartDashboard()
{
	//ShooterPID
	SmartDashboard::PutNumber("P", 0.0);
	SmartDashboard::PutNumber("I", 0.0);
	SmartDashboard::PutNumber("D", 0.0);
	SmartDashboard::PutNumber("Angle", 0.0);

	//Commands for debugging
	shooterrotation->SmartDashboardOutput();
	SmartDashboard::PutData("Stop Drivetrain", new DriveSet(0.0f, 0.0f));
	SmartDashboard::PutData("Drive Joystick", new DriveJoystick());
	SmartDashboard::PutData("Drive Distance", new DriveDistance(240));
	SmartDashboard::PutData("Shooter Test", new ShooterTest());
	SmartDashboard::PutData("Set Shooter Angle", new SetShooterAngle(TEST_ANGLE));
	SmartDashboard::PutData("Fire", new Fire());
	//Auto Align
		SmartDashboard::PutData("Auto Right", new AutoAlign(FindTarget::Direction::RIGHT));
		SmartDashboard::PutData("Auto Left", new AutoAlign(FindTarget::Direction::LEFT));
		SmartDashboard::PutData("Align Shooter", new SetShooterAngle());

	//autonomous
	autoChooser->AddDefault("Low Bar (align)", new AlignAutonomous());
	autoChooser->AddObject("Other Defense (align)", new AlignAutonomous(5, 0.8f));
	autoChooser->AddObject("Low Bar", new SimpleAutonomous());
	autoChooser->AddObject("Other Defense", new SimpleAutonomous(5, 0.8f));

	SmartDashboard::PutData("Autonomous Defense Chooser", autoChooser.get());
}

void Robot::PeriodicSmartDashboard()
{

	SmartDashboard::PutNumber("Shooter Absolute Encoder", RobotMap::shooterAbsEncoder.get()->GetVoltage());

	//Encoder
	SmartDashboard::PutNumber("Left encoder ticks", RobotMap::driveEncoderL->Get());
	//SmartDashboard::PutNumber("Left encoder 'distance'", RobotMap::drivetrainEncoder->GetDistance());
	SmartDashboard::PutNumber("Right encoder ticks", RobotMap::driveEncoderR->Get());
	//SmartDashboard::PutNumber("Right encoder 'distance'", RobotMap::drivetrainEncoder2->GetDistance());

	SmartDashboard::PutNumber("Average Distance", drivetrain->GetAverageEncoderDistance());
	SmartDashboard::PutNumber("Left Encoder Distance", drivetrain->GetEncoderDistance());
	SmartDashboard::PutNumber("Right Encoder Distance", drivetrain->GetEncoder2Distance());

	SmartDashboard::PutBoolean("Inverted Controls", inverted);

	SmartDashboard::PutNumber("Left Shifter", RobotMap::shifterL->Get());
	SmartDashboard::PutNumber("Right Shifter", RobotMap::shifterR->Get());

	SmartDashboard::PutNumber("Raw IR sensor voltage", RobotMap::shooterIR->GetVoltage());
	SmartDashboard::PutNumber("IR distance inches", ((27.86f * pow(RobotMap::shooterIR->GetVoltage(), -1.15f)) * 0.393701f));

	SmartDashboard::PutNumber("Rotation Speed", RobotMap::shooterRotateMotor->Get());
}

START_ROBOT_CLASS(Robot);
