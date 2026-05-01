#pragma once
#include<ostream>

class Bill
{
private:
	int bill_id;
	int pat_id;
	int app_id;
	float amount;
	char status[15];
	char date[11];
public:
	Bill(int bid, int pid, int aid, float amo, const char* stat, const char* dat);
	int getid() const;
	int getpatid() const;
	int getappid() const;
	float getamount() const;
	const char* getstatus() const;
	const char* getdate() const;
	void setstatus(const char* stat);
	friend std::ostream& operator<<(std::ostream&, const Bill&);




};