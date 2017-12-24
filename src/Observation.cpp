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
        for(int i=0;i<step;i++){
                if(std::isnan(msg->ranges[i])){
			scan.push_back(6000.0);
			log_scan.push_back(log10(6000.0));
		}else{
			scan.push_back(msg->ranges[i]*1000);
			log_scan.push_back(log10(msg->ranges[i]*1000));
		}
	}

	/*
        for(int i=0;i<step;i+=2){
                if(std::isnan(msg->ranges[i]))
                        continue;

                double ang = msg->angle_min + msg->angle_increment*step;
                double x = msg->ranges[i]*cos(ang)*1000;
                double y = msg->ranges[i]*sin(ang)*1000;
                hough.set(x, y);
        }*/
}

void Observation::setValues(const sensor_msgs::LaserScan* msg) //XXX I don't know how to cast!!!
{
        int step = (int)floor( ( msg->angle_max - msg->angle_min ) / msg->angle_increment );
        for(int i=0;i<step;i++){
                if(std::isnan(msg->ranges[i])){
			scan.push_back(6000.0);
			log_scan.push_back(log10(6000.0));
		}else{
			scan.push_back(msg->ranges[i]*1000);
			log_scan.push_back(log10(msg->ranges[i]*1000));
		}
	}

	/*
        for(int i=0;i<step;i+=2){
                if(std::isnan(msg->ranges[i]))
                        continue;

                double ang = msg->angle_min + msg->angle_increment*step;
                double x = msg->ranges[i]*cos(ang)*1000;
                double y = msg->ranges[i]*sin(ang)*1000;
                hough.set(x, y);
        }*/
}

double Observation::compare(Observation *ref)
{
	double sum = 0.0;
	size_t step = log_scan.size();
        for(int i=0;i<step;i++){
		sum += fabs(log_scan[i] - ref->log_scan[i]);	
	}

	cout << sum << endl;
	return sum;

       // return hough.compare(&ref->hough);
}
