#ifndef __BTECH_H_INCLUDED__
#define __BTECH_H_INCLUDED__

#include <RollNumber.h>
#include <Faculty.h>

class BTech {
	RollNumber rollNumber;
	string hostel;
	Faculty facad;
	Faculty btpGuide;
	float cgpa;	

public:
	BTech(RollNumber r, string hostl, Faculty facd, float cg);
	string getHostel();
	Faculty getFacad();
	void changeHostel(string newHostel);
	Faculty getBTPGuide();
	setBTPGuide(Faculty btpg);
};

#endif