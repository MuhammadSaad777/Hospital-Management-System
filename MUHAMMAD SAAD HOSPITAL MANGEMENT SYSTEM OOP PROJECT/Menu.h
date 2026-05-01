#pragma once
#include"Patient.h"
#include"Doctor.h"
#include"Admin.h"
#include"Storage.h"
#include"Appointment.h"
#include"Bill.h"
#include"Prescription.h"



void DisplayCompleteMenu(Storage<Patient*>& patients, Storage<Doctor*>& doctors, Storage<Appointment*>& appointments,
	Storage<Bill*>& bills, Storage<Prescription*>& prescriptions, Admin* & admin);
