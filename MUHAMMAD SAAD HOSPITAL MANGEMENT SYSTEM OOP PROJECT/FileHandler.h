#pragma once
#include"Storage.h"
#include"Patient.h"
#include"Doctor.h"
#include"Admin.h"
#include"Appointment.h"
#include"Bill.h"
#include"Prescription.h"

class FileHandler
{
public:
	static void Patientboot(Storage<Patient*>& store);
	static void Doctorboot(Storage<Doctor*>& store);
	static void Adminboot(Admin*& adm);
	static void Appointmentboot(Storage<Appointment*>& store);
	static void Billboot(Storage<Bill*>& store);
	static void Prescriptionboot(Storage<Prescription*>& store);
	static void appendrecord(const char* filename, const char* addline);
	static void modifyrecord(const char* filename, int id, const char* newline);
	static void deleterecord(const char* filename, int id);

};


