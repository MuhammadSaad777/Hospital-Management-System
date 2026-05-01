#pragma once
#include<ostream>
class Appointment
{
private:
	int app_id;
	int pat_id;
	int doc_id;
	char date[11];
	char slot[6];
	char status[15];
public:
	Appointment(int aid, int pid, int did, const char* dat, const char* time, const char* stat);
	int getid() const;
	int getpatid() const;
	int getdocid() const;
	const char* getdate() const;
	const char* getslot() const;
	const char* getstatus() const;
	void setstatus(const char* sta);
	friend std::ostream& operator<<(std::ostream&, const Appointment&);
	bool operator ==(const Appointment& other) const;
	void Display() const;
	static bool Comparechars(const char* a, const char* b);



};
