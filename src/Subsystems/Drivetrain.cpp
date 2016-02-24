// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Drivetrain.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/Drive/DriveJoystick.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() :
		Subsystem("Drivetrain")
{
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Talon1 = RobotMap::drivetrainTalon1;
	Talon2 = RobotMap::drivetrainTalon2;
	Talon3 = RobotMap::drivetrainTalon3;
	Talon4 = RobotMap::drivetrainTalon4;
	robotDrive = RobotMap::drivetrainRobotDrive;
	encoder = RobotMap::drivetrainEncoder;
	controls_inverted = false;
	robotDrive->SetSafetyEnabled(false);
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Drivetrain::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	/*SetTankDrive, SetArcadeDrive, and SetManualDrive are all methods that will be put in the Drivetrain subststem file. [HERE]
They will be called from commands. Commands are called in a few different ways.
They can be called automatically by a button press, they can be called by a command group,
or they can be called manually by calling the Command's Start() method. More info on how this works can be found here:
http://wpilib.screenstepslive.com/s/4485/m/13810/l/241904-running-commands-on-joystick-input*/
	// SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

	SetDefaultCommand(new DriveJoystick());
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::SetTankDrive(float leftPower, float rightPower)
{
	//if (RobotMap::isRobotReversed){
	//	robotDrive->TankDrive(-leftPower, -rightPower, true);
	//} else
	robotDrive->TankDrive(leftPower, rightPower, true);
	//should the bool value (SquaredInputs) be true? don't know what it does
}

void Drivetrain::SetArcadeDrive(float movePower, float rotatePower)
{
	//if (RobotMap::isRobotReversed) {
	//	robotDrive->ArcadeDrive(-movePower, -rotatePower, true);
	//}
	robotDrive->ArcadeDrive(movePower, rotatePower, true);
	//also don't know what squaredInputs (bool) does
}

void Drivetrain::SetManualDrive(float outputPower, float curveSharpness)
{
	//if (RobotMap::isRobotReversed) {
	//	robotDrive->Drive(-outputPower, -curveSharpness);
	//}
    robotDrive->Drive(outputPower, curveSharpness);
}

void Drivetrain::SetInversion(bool is_inverted)
{
	Talon1->SetInverted(is_inverted);
	Talon2->SetInverted(is_inverted);
	Talon3->SetInverted(is_inverted);
	Talon4->SetInverted(is_inverted);

	controls_inverted = is_inverted;
}

void Drivetrain::Stop() {
	SetManualDrive(0, 0);
}

bool Drivetrain::GetInversion()
{
	if (Talon1->GetInverted() && Talon2->GetInverted() && Talon3->GetInverted() && Talon4->GetInverted())
	{
		return true;
	}
	else if (!Talon1->GetInverted() && !Talon2->GetInverted() && !Talon3->GetInverted() && !Talon4->GetInverted())
	{
		return false;
	}
	else
	{
		SetInversion(false); // To ensure that output is predictible in the event of an unexpected issue, I did this
		return false;
	}
}

double Drivetrain::GetEncoderDistance()
{
	return encoder->GetDistance(); //this is so we can change this later
}

/*void Drivetrain::SetFlip(bool flipping) {
	RobotMap::isRobotReversed = flipping;
}
bool Drivetrain::ToggleFlip(void) {
	RobotMap::isRobotReversed = !RobotMap::isRobotReversed;
	return RobotMap::isRobotReversed;
}
bool Drivetrain::GetFlip(void) {
	return RobotMap::isRobotReversed;
}
*/
