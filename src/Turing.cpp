#include "Turing.h"

using namespace std;

Loggable::FAIL_COMMAND currentTooHigh(double cur)
{
	stringstream curString;
	curString<<cur;
	Logger::LogState("POWERDISTRIBUTIONPANEL", LEVEL_t::ALERT, string("Current level too high: ")+curString.str()+" amps");
	return Loggable::KILL;
}

class Turing: public IterativeRobot
{
private:
	PowerDistributionPanel PDP;

public:
	Turing()
	{
		cout<<"Starting Robot Program"<<endl;
		Logger::MakeLogValue("TIME", "BOOT_TICKS", &GetTime);
		Logger::MakeLogValue("VOLTAGE", &PDP, &PowerDistributionPanel::GetVoltage);
		Logger::MakeLogValue("TOTALCURRENT", &PDP, &PowerDistributionPanel::GetTotalCurrent,
				WatchLog<double>(currentTooHigh, [](double cur) {return cur > 100.0;}));
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Turing object constructed");
		Logger::LogState("GENERAL", LEVEL_t::NOTICE, string("Built: ")+__DATE__+' '+__TIME__);
	}

private:
	void RobotInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Robot init complete");
	}

	void DisabledInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Disabled Init Complete");
	}

	void DisabledPeriodic() override
	{
	}

	void AutonomousInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Autonomous Init Complete, ready to crack enigma.");
	}

	void AutonomousPeriodic() override
	{

	}

	void TeleopInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Teleop Init Complete");
	}

	void TeleopPeriodic() override
	{

	}

	void TestInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Test Init Complete");
	}

	void TestPeriodic() override
	{

	}
};

START_ROBOT_CLASS(Turing);
