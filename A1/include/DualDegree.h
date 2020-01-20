#ifndef __DUALDEGREE_H_INCLUDED__
#define __DUALDEGREE_H_INCLUDED__

#include <RollNumber.h>
#include <Faculty.h>

class DualDegree {
	RollNumber rollNumber;
	string hostel;
	Faculty facad;
	Faculty ddpGuide;
	Faculty taSupervisor;
	float cgpa;
	
	public:
		DualDegree(RollNumber r, string hostl, Faculty facd, float cg);
		string getHostel();
		Faculty getFacad();
		void changeHostel(string);
		Faculty getDDPGuide();
		Faculty getTASupervisor();
		setDDPGuide(Faculty);
		setTASupervisor(Faculty);
};

#endif