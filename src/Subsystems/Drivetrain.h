// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "RobotDrive.h"
#include "WPILib.h"

/**
 *
 *bool controls_inverted;
 * @author ExampleAuthor
 */
class Drivetrain: public Subsystem
{
private:
	bool controls_inverted;
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<Talon> Talon1;
	std::shared_ptr<Talon> Talon2;
	std::shared_ptr<Talon> Talon3;
	std::shared_ptr<Talon> Talon4;
	std::shared_ptr<RobotDrive> robotDrive;
	std::shared_ptr<Encoder> encoder;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	Drivetrain();
	void SetManualDrive(float outputPower, float curveSharpness);
	void SetArcadeDrive(float movePower, float rotatePower);
	void SetTankDrive(float leftPower, float rightPower);
	void SetInversion(bool is_inverted);
	void Stop();
	bool GetInversion();
	double GetEncoderDistance();
	void InitDefaultCommand();
	std::shared_ptr<Talon> GetTalons(int id);

	//void SetFlip(bool flipping);
	//bool ToggleFlip(void);
	//bool GetFlip(void);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
