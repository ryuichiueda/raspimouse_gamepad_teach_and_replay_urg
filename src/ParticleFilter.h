#ifndef __PF_H__
#define __PF_H__

#include <vector>
#include "Particle.h"
#include "ProbDistribution.h"
#include "raspimouse_gamepad_teach_and_replay_urg/PFoEOutput.h"
using namespace ros;

class Episodes;
class Observation;
class Action;

class ParticleFilter
{
public:
	ParticleFilter(int num, Episodes *ep);
	void init(void);
	void print(void);

//	Action sensorUpdate(Observation *obs, Episodes *ep, raspimouse_gamepad_teach_and_replay_urg::PFoEOutput *out);
	Action sensorUpdate(Observation *obs, Action *act, Episodes *ep);//, raspimouse_gamepad_teach_and_replay_urg::PFoEOutput *out);
	Action mode(Episodes *ep);
	Action modeParticle(Episodes *ep);
	Action average(Episodes *ep);
	void motionUpdate(Episodes *ep);
private:
	vector<Particle> particles;
	ProbDistributions prob;

	Episodes *episodes;

	double likelihood(Observation *past, Observation *last);

	void resampling(vector<Particle> *ps);
	void normalize(void);
};

#endif
