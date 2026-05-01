#include"Appointment.h"
#include<iostream>
using namespace std;

Appointment::Appointment(int aid, int pid, int did, const char* dat, const char* time, const char* stat)
{
	app_id = aid;
	pat_id = pid;
	doc_id = did;
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

	int lt = 0;
	for (int i = 0; time[i] != '\0';i++)
	{
		lt++;
	}
	int k = 0;
	for (; k < lt;k++)
	{
		slot[k] = time[k];
	}
	slot[k] = '\0';

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
}
int Appointment::getid() const
{
	return app_id;
}
int Appointment::getpatid() const
{
	return pat_id;
}
int Appointment::getdocid() const
{
	return doc_id;
}
const char* Appointment::getdate() const
{
	return date;
}
const char* Appointment::getslot() const
{
	return slot;
}
const char* Appointment::getstatus() const
{
	return status;
}
void Appointment::setstatus(const char* sta)
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
ostream& operator<<(ostream& out, const Appointment& App)
{
	out << "Appointment Id: " << App.app_id;
	out << "	Patient Id: " << App.pat_id;
	out << "	Doctor Id: " << App.doc_id;
	out << "	Date: " << App.date;
	out << "	Slot: " << App.slot;
	out << "	Status: " << App.status;
	return out;

}
void Appointment::Display() const
{
	cout << *this;
}
bool Appointment::operator ==(const Appointment& other) const
{
	if (doc_id != other.doc_id)
	{
		return false;
	}
	if (!Comparechars(date, other.date))
	{
		return false;
	}
	if (!Comparechars(slot, other.slot))
	{
		return false;
	}
	if (Comparechars(status, "cancelled") || Comparechars(other.status, "cancelled"))
	{
		return false;
	}

		return true;
}
bool Appointment::Comparechars(const char* first, const char* second)
{
	int i = 0;
	while (first[i] != '\0' && second[i] != '\0')
	{
		if (first[i] != second[i])
		{
			return false;
		}
		i++;
	}
	if (first[i] == '\0' && second[i] == '\0')
	{
		return true;
	}
	return false;
}


