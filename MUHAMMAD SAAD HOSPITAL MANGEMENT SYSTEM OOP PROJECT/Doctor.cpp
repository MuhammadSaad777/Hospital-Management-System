#include"Doctor.h"
#include<iostream>
using namespace std;


Doctor::Doctor(int i, const char* nam, const char* special, const char* con, const char* pa, float fe) :Person(i, nam, pa), fee(fe)
{
	int lc = 0;
	for (int i = 0; con[i] != '\0';i++)
	{
		lc++;
	}
	int j = 0;
	for (; j < lc;j++)
	{
		contact[j] = con[j];
	}
	contact[j] = '\0';


	int ls = 0;
	for (int i = 0; special[i] != '\0';i++)
	{
		ls++;
	}
	int k= 0;
	for (; k < ls;k++)
	{
		specialization[k] = special[k];
	}
	specialization[k] = '\0';

}

const char*Doctor:: getspecialization() const
{
	return specialization;
}

const char* Doctor::getcontact() const
{
	return contact;
}

float Doctor::getfee() const
{
	return fee;
}

bool Doctor::operator ==(const Doctor& other) const
{
	if (id == other.id)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& out, const Doctor& Doc)
{
	out << "Id: " << Doc.id;
	out << "	Name: " << Doc.name;
	out << "	Specialization: " << Doc.specialization;
	out << "	Contact: " << Doc.contact;
	out << "	Password: " << Doc.pass;
	out << "	Fee: " << Doc.fee;
	return out;
}
void Doctor::Display() const
{
	cout << *this;
}
void Doctor::showmenu()
{
	cout << "Welcome, Dr. " << name;
	cout << "  |  Specialization:  " << specialization << endl << endl << endl;
	cout << "1.View Today's Appointment " << endl;
	cout << "2.Mark Appointment Complete" << endl;
	cout << "3.Mark Appointment No-show " << endl;
	cout << "4.Write Prescription " << endl;
	cout << "5. View Patient Medical Hstory" << endl;
	cout << "6.LogOut " << endl;
	

}