#include"Menu.h"
#include"Patient.h"
#include"Doctor.h"
#include"Admin.h"
#include"Storage.h"
#include"Appointment.h"
#include"Bill.h"
#include"Prescription.h"
#include"FileHandler.h"
#include"FileNotFoundException.h"
#include<iostream>
using namespace std;

int main()
{
	Storage<Patient*> patients;
	Storage<Doctor*> doctors;
	Storage<Appointment*> appointments;
	Storage<Bill*> bills;
	Storage<Prescription*> prescriptions;
	Admin* admin = nullptr;
	
	try
	{
		FileHandler::Patientboot(patients);

	}
	catch (FileNotFoundException& e)
	{
		cout << e.what() << endl;
		return 1;// error so program ends here
	}
	try
	{
		FileHandler::Doctorboot(doctors);

	}
	catch (FileNotFoundException& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	try
	{
		FileHandler::Adminboot(admin);

	}
	catch (FileNotFoundException& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	try
	{
		FileHandler::Appointmentboot(appointments);

	}
	catch (FileNotFoundException& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	try
	{
		FileHandler::Billboot(bills);

	}
	catch (FileNotFoundException& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	try
	{
		FileHandler::Prescriptionboot(prescriptions);

	}
	catch (FileNotFoundException& e)
	{
		cout << e.what() << endl;
		return 1;
	}

    DisplayCompleteMenu(patients,doctors,appointments,bills,prescriptions,admin);


	
	
	for (int i = 0; i < patients.getsize(); i++)
	{
		if (patients.getall()[i] != nullptr)
		{
			delete patients.getall()[i];
			patients.getall()[i] = nullptr; 
		}
	}

	
	for (int i = 0; i < doctors.getsize(); i++)
	{
		if (doctors.getall()[i] != nullptr)
		{
			delete doctors.getall()[i];
			doctors.getall()[i] = nullptr;
		}
	}

	
	if (admin != nullptr)
	{
		delete admin;
		admin = nullptr;
	}

	
	for (int i = 0; i < appointments.getsize(); i++)
	{
		if (appointments.getall()[i] != nullptr)
		{
			delete appointments.getall()[i];
			appointments.getall()[i] = nullptr;
		}
	}

	
	for (int i = 0; i < bills.getsize(); i++)
	{
		if (bills.getall()[i] != nullptr)
		{
			delete bills.getall()[i];
			bills.getall()[i] = nullptr;
		}
	}

	
	for (int i = 0; i < prescriptions.getsize(); i++)
	{
		if (prescriptions.getall()[i] != nullptr)
		{
			delete prescriptions.getall()[i];
			prescriptions.getall()[i] = nullptr;
		}
	}

	return 0;
}