#ifndef __HOUGH_H_ 
#define __HOUGH_H_

class Hough{
public:
	Hough();
	unsigned short int space[36][20]; //5deg, 10steps of log_e(rho)
	void init(void);
	void set(double x, double y);
	void print(void);
	unsigned long int compare(Hough *ref);
};

#endif
