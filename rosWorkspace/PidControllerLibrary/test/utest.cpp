#include "../include/PidControllerLibrary/PidController.hpp"
#include <gtest/gtest.h>
/*
Unit tests for the pid controller library.

Running the tests under rosbuild
make test
*/
TEST(PIDController, setLimits)
{
	PIDController pid;
	pid.setLimits(-125, 200);
	EXPECT_EQ(-125, pid.getOutputMin());
	EXPECT_EQ(200, pid.getOutputMax());

	pid.setLimits(125, 150);
	EXPECT_EQ(125, pid.getOutputMin());
	EXPECT_EQ(150, pid.getOutputMax());
}

TEST(PIDController, SetTunnings)
{
	PIDController pid;
	pid.setSampleTime(1000);
	pid.setTunnings(0.2, 0.6, 0.5);
	EXPECT_EQ(0.2, pid.getKP());
	EXPECT_EQ(0.6, pid.getKI() * pid.getSampleTimeSeconds());
	EXPECT_EQ(0.5, pid.getKD() / pid.getSampleTimeSeconds());
}

TEST(PIDController, SetSampleTime)
{
	PIDController pid;
	pid.setSampleTime(1000);
	pid.setTunnings(0.8, 0.8, 0.8);
	pid.setSampleTime(500);
	EXPECT_EQ(0.8, pid.getKP());
	EXPECT_EQ(0.4, pid.getKI());
	EXPECT_EQ(1.6, pid.getKD());
	EXPECT_EQ(500, pid.getSampleTime());
}

TEST(PIDController, NegSampleTime)
{
	PIDController pid;
	pid.setSampleTime(1000);
	pid.setSampleTime(-250);
	EXPECT_EQ(1000, pid.getSampleTime());
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
