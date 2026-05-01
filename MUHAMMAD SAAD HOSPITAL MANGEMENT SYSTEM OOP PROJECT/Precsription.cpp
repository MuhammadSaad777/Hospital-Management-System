#include"Prescription.h"
#include<iostream>
using namespace std;

Prescription::Prescription(int prid, int aid, int paid, int did, const char* dat, const char* med, const char* note)
{
	pres_id = prid;
	app_id = aid;
	pat_id = paid;
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

	int lm = 0;
	for (int i = 0; med[i] != '\0';i++)
	{
		lm++;
	}
	int k = 0;
	for (; k< lm;k++)
	{
		medicines[k] = med[k];
	}
	medicines[k] = '\0';

	int ln = 0;
	for (int i = 0; note[i] != '\0';i++)
	{
		ln++;
	}
	int l = 0;
	for (; l < ln;l++)
	{
		notes[l] = note[l];
	}
	notes[l] = '\0';
}

int Prescription::getid() const
{
	return pres_id;
}

int Prescription::getappointmentid() const
{
	return app_id;
}
int Prescription::getpatientid() const
{
	return pat_id;
}
int Prescription::getdoctorid() const
{
	return doc_id;
}
const char* Prescription::getdate() const
{
	return date;
}
const char* Prescription::getmedicines() const
{
	return medicines;
}
const char* Prescription::getnotes() const
{
	return notes;
}
ostream& operator<<(ostream& out, const Prescription& pre)
{
	out << "Prescription Id: " << pre.pres_id;
	out << "	Appointment Id: " << pre.app_id;
	out << "	Patient Id: " << pre.pat_id;
	out << "	Doctor Id: " << pre.doc_id;
	out << "	Date: " << pre.date;
	out << "	Medicines: " << pre.medicines;
	out << "	Notes: " << pre.notes;

	return out;

}