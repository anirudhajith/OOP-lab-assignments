class BTech {
	RollNumber rollNumber;
	string hostel;
	Faculty facad;
	Faculty btpGuide;
	float cgpa;	

public:
	BTech(RollNumber r, string hostl, Faculty facd, float cg) {
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

	Faculty getBTPGuide() {
		return btpGuide;
	}

	setBTPGuide(Faculty btpg) {
		btpGuide = btpg;
	}
};
