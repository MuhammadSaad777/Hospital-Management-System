#include"Patient.h"
#include<iostream>
using namespace std;

Patient::Patient(int i, const char* nam, int ag, char gend, const char* con, const char* pa, float bal) :Person(i, nam, pa), age(ag), gender(gend), balance(bal)
{
	int l = 0;
	for (int i = 0; con[i] != '\0';i++)
	{
		l++;
	}
	int j = 0;
	for (; j < l;j++)
	{
		contact[j] = con[j];
	}
	contact[j] = '\0';
}
int Patient::getage() const
{
	return age;
}
char Patient::getgender() const
{
	return gender;
}
const char* Patient::getcontact() const
{
	return contact;
}
float Patient::getbalance() const
{
	return balance;
}
void Patient::setbalance(float balan)
{
	balance = balan;
}
Patient& Patient::operator+=(float v)
{
	balance += v;
	return *this;
}
Patient& Patient::operator-=(float v)
{
	balance -= v;
	return *this;
}
bool Patient::operator ==(const Patient& other) const
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
ostream& operator<<(ostream& out, const Patient& pat)
{
	out << "Id: " << pat.id;
	out << "	Name: " << pat.name;
	out << "	Age: " << pat.age;
	out << "	Gender: " << pat.gender;
	out << "	Contact: " << pat.contact;
	out << "	Password: " << pat.pass;
	out << "	Balance: " << pat.balance;
	return out;


}
void Patient:: Display() const
{
	cout << *this;
}
void Patient::showmenu()
{
	cout << "Welcome, " << name<<endl;
	cout << "Balance:  PKR  " << balance<<endl<<endl<<endl;
	cout << "1.Book Appointment " << endl;
	cout << "2.Cancel Appointment " << endl;
	cout << "3.View My Appointments " << endl;
	cout << "4.View My Medical Records " << endl;
	cout << "5. View My Bills " << endl;
	cout << "6. Pay Bill " << endl;
	cout << "7. Top Up Balance " << endl;
	cout << "8.LogOut " << endl<<endl<<endl;

}

