class DualDegree {
	RollNumber rollNumber;
	string hostel;
	Faculty facad;
	Faculty ddpGuide;
	Faculty taSupervisor;
	float cgpa;	

public:
	DualDegree(RollNumber r, string hostl, Faculty facd, float cg) {
		rollNumber = r;
		hostel = hostl;
		facad = facd;
		cgpa = cg;
	}

	string getHostel() {
		return hostel;
	}

	Faculty getFacad() {
		return facad;
	}

	void changeHostel(string newHostel) {
		hostel = newHostel;
	}

	Faculty getDDPGuide() {
		return ddpGuide;
	}

	Faculty getTASupervisor() {
		return taSupervisor;
	}


	setDDPGuide(Faculty ddpg) {
		ddpGuide = ddpg;
	}

	setTASupervisor(Faculty tasup) {
		taSupervisor = tasup;
	}
};