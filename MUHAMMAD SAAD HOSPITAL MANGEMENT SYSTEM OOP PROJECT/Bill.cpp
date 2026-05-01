#include"Bill.h"
#include<iostream>
using namespace std;

Bill::Bill(int bid, int pid, int aid, float amo, const char* stat, const char* dat)
{
	bill_id = bid;
	pat_id = pid;
	app_id = aid;
	amount = amo;

	int ls = 0;
	for (int i = 0; stat[i] != '\0';i++)
	{
		ls++;
	}
	int l = 0;
	for (; l < ls;l++)
	{
		status[l] = stat[l];
	}
	status[l] = '\0';

	int ld = 0;
	for (int i = 0; dat[i] != '\0';i++)
	{
		ld++;
	}
	int j = 0;
	for (; j < ld;j++)
	{
		date[j] = dat[j];
	}
	date[j] = '\0';
}
int Bill::getid() const
{
	return bill_id;
}
int Bill::getpatid() const
{
	return pat_id;
}
int Bill::getappid() const
{
	return app_id;
}
float Bill::getamount() const
{
	return amount;
}
const char* Bill::getdate() const
{
	return date;
}
const char* Bill::getstatus() const
{
	return status;
}
void Bill::setstatus(const char* sta)
{
	int lss = 0;
	for (int i = 0; sta[i] != '\0';i++)
	{
		lss++;
	}
	int i = 0;
	for (; i < lss;i++)
	{
		status[i] = sta[i];
	}
	status[i] = '\0';
}
ostream& operator<<(ostream& out, const Bill& bil)
{
	out << "Bill Id: " << bil.bill_id;
	out << "	Patient Id: " << bil.pat_id;
	out << "	Appointment Id: " << bil.app_id;
	out << "	Amount: " << bil.amount;
	out << "	Status: " << bil.status;
	out << "	Date: " << bil.date;
	return out;

}