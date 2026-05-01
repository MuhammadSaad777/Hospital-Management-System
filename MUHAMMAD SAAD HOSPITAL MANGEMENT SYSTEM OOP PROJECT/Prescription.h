#pragma once
#include<ostream>

class Prescription
{
private:
	int pres_id;
	int app_id;
	int pat_id;
	int doc_id;
	char date[11];
	char medicines[500];
	char notes[300];
public:
	Prescription(int prid, int aid, int paid, int did, const char* dat, const char* med, const char* note);
	int getid() const;
	int getappointmentid() const;
	int getpatientid() const;
	int getdoctorid() const;
	const char* getdate() const;
	const char* getmedicines() const;
	const char* getnotes() const;
	friend std::ostream& operator<<(std::ostream&, const Prescription&);

};