#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <limits>
#include "Hough.h"
using namespace ros;

Hough::Hough()
{
	init();
}

void Hough::init(void)
{
	for(int j=0;j<20;j++)
		for(int i=0;i<36;i++)
			space[i][j] = 0;
}

void Hough::set(double x, double y)
{
	for(int i=0;i<36;i++){
		double theta = 3.141592*i*5/180;
		double rho = x*cos(theta) + y*sin(theta);
		if(rho >= 1.0){
			int log_rho = (int)log(rho) + 10;
			space[i][log_rho]++;
		}else if(rho <= -1.0){
			int log_rho = 10 - (int)log(-rho);
			space[i][log_rho]++;
		}else
			space[i][0]++;

	}
}

void Hough::print(void)
{
	for(int j=0;j<20;j++){
		for(int i=0;i<36;i++){
			std::cout << space[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

unsigned long int Hough::compare(Hough *ref)
{
	unsigned long int score = 0;
	for(int j=0;j<20;j++){
		for(int i=0;i<36;i++){
			int diff = space[i][j] - ref->space[i][j];
			score += diff*diff;
		}
	}
	return sqrt(score/(20*36));
}
