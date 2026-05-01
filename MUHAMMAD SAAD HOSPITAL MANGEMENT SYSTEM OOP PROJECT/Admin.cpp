#include"Admin.h"
#include<iostream>
using namespace std;

Admin::Admin(int i, const char* nam, const char* pa) :Person(i, nam, pa)
{

}
ostream& operator<<(ostream& out, const Admin& Ad)
{
	out << "Id: " << Ad.id;
	out << "	Name: " << Ad.name;
	out << "	Password: " << Ad.pass;
	
	return out;
}
void Admin::Display() const
{
	cout << *this;
}
void Admin::showmenu()
{
	cout << "Admin Panel - MediCore " << endl << endl << endl;
	cout << "1.Add Doctor " << endl;
	cout << "2.Remove Doctor" << endl;
	cout << "3.View All Patients" << endl;
	cout << "4.View All Doctors" << endl;
	cout << "5.View All Appointments" << endl;
	cout << "6.View Unpaid Bills" << endl;
	cout << "7.Discharge Patient" << endl;
	cout << "8.View Security Log" << endl;
	cout << "9.Generate Daily Report" << endl;
	cout << "10.LogOut" << endl << endl << endl;


}