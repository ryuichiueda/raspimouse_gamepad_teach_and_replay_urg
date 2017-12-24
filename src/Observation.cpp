#include "Observation.h"
#include "sensor_msgs/LaserScan.h"
//#include <iostream>
#include <cmath>

Observation::Observation()
{
}

Observation::Observation(const sensor_msgs::LaserScan::ConstPtr& msg)
{
	setValues(msg);
}

Observation::Observation(const sensor_msgs::LaserScan* msg)
{
	setValues(msg);
}

void Observation::setValues(const sensor_msgs::LaserScan::ConstPtr& msg)
{
        int step = (int)floor( ( msg->angle_max - msg->angle_min ) / msg->angle_increment );

        for(int i=0;i<step;i+=2){
                if(std::isnan(msg->ranges[i]))
                        continue;

                double ang = msg->angle_min + msg->angle_increment*step;
                double x = msg->ranges[i]*cos(ang)*1000;
                double y = msg->ranges[i]*sin(ang)*1000;
                hough.set(x, y);
        }
}

void Observation::setValues(const sensor_msgs::LaserScan* msg) //XXX I don't know how to cast!!!
{
        int step = (int)floor( ( msg->angle_max - msg->angle_min ) / msg->angle_increment );

        for(int i=0;i<step;i+=2){
                if(std::isnan(msg->ranges[i]))
                        continue;

                double ang = msg->angle_min + msg->angle_increment*step;
                double x = msg->ranges[i]*cos(ang)*1000;
                double y = msg->ranges[i]*sin(ang)*1000;
                hough.set(x, y);
        }
}

unsigned long int Observation::compare(Observation *ref)
{
        return hough.compare(&ref->hough);
}
