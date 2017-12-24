#ifndef __OBS_H_ 
#define __OBS_H_

#include <string>
#include <vector>
#include <fstream>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "Hough.h"
using namespace std;

class Observation{
public:
	Observation();
	Observation(const sensor_msgs::LaserScan::ConstPtr& msg);
	//void setValues(const raspimouse_gamepad_teach_and_replay_urg::sensor_msgs::LaserScan::ConstPtr& msg);
	void setValues(const sensor_msgs::LaserScan::ConstPtr& msg);
	unsigned long int compare(Observation *ref);

private:
	Hough hough;
};

#endif
