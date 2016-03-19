#ifndef ShooterRotation_H
#define ShooterRotation_H
//#define DEBUG

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <CANTalon.h>
#include <AbsoluteEncoder/AbsoluteEncoder.h>

class ShooterRotation : public Subsystem
{
private:
	double PositionToVolts(double angle);

	std::shared_ptr<CANTalon> RotateMotor;

	//double pos = HOME_POS;

	double AngleToVolts(double angle);

public:
	//TODO: These angles should be the same, but check to make sure.
	const double MAX_ANGLE = 288; //full forwards
	const double MIN_ANGLE = 79.2; //full inwards

	//TODO: Find the actual potentiometer values.
	const double MIN_VOLTS = 1.17f;
	const double MAX_VOLTS = 4.0f;
	// Hardware
	std::shared_ptr<CANTalon> motor;
	PIDController* pid;
	AbsoluteEncoder* absEncoder;
	
	// PID Constants
	float kP = .1;
	float kI = 0;
	float kD = 0;
	
	// Common setpoints, tied to buttons.
	const float HOME_SETPOINT = 0;
	const float INTAKE_SETPOINT = 3;
	const float LOGOAL_SETPOINT = 0;
	const float HIGOAL_SETPOINT = 0;
	
	const float V_OVER_A = (5.0 / 360.0); // Constant to convert between voltage and angle.
	const float BIAS = 0; // Difference between home position and parallel with floor.
	
	float ConvertAngleToAbsolute(float angle)
	{
		return (angle * V_OVER_A) + HOME_SETPOINT + BIAS;
	}
	
public:
	//const double MAX_ANGLE = 288; //full forwards
	//const double MIN_ANGLE = 79.2; //full inwards

	//const double MIN_VOLTS = 1.17f;
	//const double MAX_VOLTS = 4.0f;

	//const double HOME_POS = 0; //full inwards
	//const double INTAKE_POS = 208.8; //full forwards

	ShooterRotation();
	/*void SetSpeed(float speed);
	void SetAngle(double pos); //in degrees range 0-208.8
	void IncrementAngle(double inc);
	void ShooterHome();
	float GetSpeed();
	void SetMode(CANTalon::ControlMode mode);
	void SetPIDEnabled(bool enabled);
	void SetPID(double p, double i, double d);*/
	/*
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	*/
	
	void InitDefaultCommand();
	
	// Teleop Axis Control
	void Gun(float gunner_axis);
	
	// Button/Auto Control
	void HomePos();
	void ShootPos(float position);
	void IntakePos();
	
	void Stop();
	void PIDEnable(bool enabled);
	
	void SmartDashboardOutput();

	PIDController* getShooterPID();
};

#endif
