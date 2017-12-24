#ifndef __OBS_H_ 
#define __OBS_H_

#include "sensor_msgs/LaserScan.h"
#include "Hough.h"
using namespace std;

class Observation{
public:
	Observation();
	Observation(const sensor_msgs::LaserScan::ConstPtr& msg);
	Observation(const sensor_msgs::LaserScan* msg);
	//void setValues(const raspimouse_gamepad_teach_and_replay_urg::sensor_msgs::LaserScan::ConstPtr& msg);
	void setValues(const sensor_msgs::LaserScan::ConstPtr& msg);
	void setValues(const sensor_msgs::LaserScan* msg);
	double compare(Observation *ref);

private:
	vector<double> scan;
	vector<double> log_scan;
	Hough hough;
};

#endif
