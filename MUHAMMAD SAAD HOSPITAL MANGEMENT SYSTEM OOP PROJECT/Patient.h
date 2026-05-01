#pragma once
#include"Person.h"
#include<iostream>

class Patient : public Person
{
private:
	int age;
	char gender;
	char contact[12];
	float balance;

public:
	Patient(int i, const char* nam, int ag, char gend, const char* con, const char* pa, float bal);
	int getage() const ;
	char getgender() const;
	const char* getcontact() const;
	float getbalance() const;
	void setbalance(float);
	void Display() const override;
	void showmenu() override;
	Patient& operator += ( float  v);
	Patient& operator -= (float v);
	bool operator ==(const Patient & other ) const;
	friend std::ostream& operator<<(std::ostream&, const Patient&);




};
