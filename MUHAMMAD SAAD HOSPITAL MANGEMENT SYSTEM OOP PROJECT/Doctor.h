#pragma once
#include"Person.h"
#include<iostream>

class Doctor : public Person
{
private:
	char specialization[50];
	char contact[12];
	float fee;
public:
	Doctor(int i, const char* nam, const char* special, const char* con, const char* pa, float fe);
	const char* getspecialization() const;
	const char* getcontact() const;
	float getfee() const;
	//void setfee(float)
	void Display() const override;
	void showmenu() override;
	bool operator ==(const Doctor& other) const;
	friend std::ostream& operator<<(std::ostream&, const Doctor&);

};
