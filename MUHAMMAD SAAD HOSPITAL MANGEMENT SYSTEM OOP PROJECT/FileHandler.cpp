#include"FileHandler.h"
#include"FileNotFoundException.h"
#include<fstream>
#include<iostream>
#include<cstdlib>

void FileHandler::Patientboot(Storage<Patient*>& store)
{
	ifstream fin("patients.txt");
	if (!fin)
	{
		throw FileNotFoundException("Unable to open patients.txt");
	}
	char p_id[10];
	char p_name[50];
	char p_age[4];
	char p_gender[3];
	char p_contact[12];
	char p_pass[50];
	char p_balance[25];
	while (fin.getline(p_id, 10, ','))
	{
		fin.getline(p_name, 50, ',');
		fin.getline(p_age, 4, ',');
		fin.getline(p_gender, 3, ',');
		fin.getline(p_contact, 12, ',');
		fin.getline(p_pass, 50, ',');
		fin.getline(p_balance, 25, '\n');

		if (p_id[0] == '\0')
		{
			continue;
		}

		int id = atoi(p_id);
		int age = atoi(p_age);
		char gender = p_gender[0];
		float balance = atof(p_balance);


		Patient* pat = new Patient(id, p_name, age, gender, p_contact, p_pass, balance);
		store.Add(pat);

	}
	fin.close();
}
void FileHandler::Doctorboot(Storage<Doctor*>& store)
{
	ifstream fin("doctors.txt");
	if (!fin)
	{
		throw FileNotFoundException("Unable to open doctors.txt");
	}
	char d_id[10];
	char d_name[50];
	char d_specialization[50];
	char d_contact[12];
	char d_pass[50];
	char d_fee[25];
	while (fin.getline(d_id, 10, ','))
	{
		fin.getline(d_name, 50, ',');
		fin.getline(d_specialization, 50, ',');
		fin.getline(d_contact, 12, ',');
		fin.getline(d_pass, 50, ',');
		fin.getline(d_fee, 25, '\n');

		if (d_id[0] == '\0')
		{
			continue;
		}

		int id = atoi(d_id);
		float fee = atof(d_fee);


	   Doctor* doc = new Doctor(id, d_name, d_specialization, d_contact, d_pass, fee);
		store.Add(doc);

	}
	fin.close();
}
void FileHandler::Adminboot(Admin*& adm)
{
	ifstream fin("admin.txt");
	if (!fin)
	{
		throw FileNotFoundException("Unable to open admin.txt");
	}
	char a_id[10];
	char a_name[50];
	char a_pass[50];
	if (fin.getline(a_id, 10, ','))
	{
		fin.getline(a_name, 50, ',');
		fin.getline(a_pass, 50, '\n');


		int id = atoi(a_id);


		adm = new Admin(id, a_name, a_pass);

	}
	fin.close();
}
void FileHandler::Appointmentboot(Storage<Appointment*>& store)
{
	ifstream fin("appointments.txt");
	if (!fin)
	{
		throw FileNotFoundException("Unable to open appointments.txt");
	}
	char a_id[10];
	char p_id[10];
	char d_id[10];
	char a_date[11];
	char a_slot[6];
	char a_status[15];
	while (fin.getline(a_id, 10, ','))
	{
		fin.getline(p_id, 10, ',');
		fin.getline(d_id, 10, ',');
		fin.getline(a_date, 11, ',');
		fin.getline(a_slot, 6, ',');
		fin.getline(a_status, 15, '\n');

		if (a_id[0] == '\0')
		{
			continue;
		}

		int aid = atoi(a_id);
		int pid = atoi(p_id);
		int did = atoi(d_id);


		Appointment * app = new Appointment(aid, pid, did, a_date, a_slot, a_status);
		store.Add(app);

	}
	fin.close();
}
void FileHandler::Billboot(Storage<Bill*>& store)
{
	ifstream fin("bills.txt");
	if (!fin)
	{
		throw FileNotFoundException("Unable to open bills.txt");
	}
	char b_id[10];
	char p_id[10];
	char a_id[10];
	char b_amount[25];
	char b_status[15];
	char b_date[11];

	while (fin.getline(b_id, 10, ','))
	{
		fin.getline(p_id, 10, ',');
		fin.getline(a_id, 10, ',');
		fin.getline(b_amount, 25, ',');
		fin.getline(b_status, 15, ',');
		fin.getline(b_date, 11, '\n');

		if (b_id[0] == '\0')
		{
			continue;
		}

		int bid = atoi(b_id);
		int pid = atoi(p_id);
		int aid = atoi(a_id);
		float amount = atof(b_amount);

		Bill * bil = new Bill (bid, pid, aid, amount, b_status,b_date);
		store.Add(bil);

	}
	fin.close();
}
void FileHandler::Prescriptionboot(Storage<Prescription*>& store)
{
	ifstream fin("prescriptions.txt");
	if (!fin)
	{
		throw FileNotFoundException("Unable to open prescriptions.txt");
	}
	char pr_id[10];
	char a_id[10];
	char p_id[10];
	char d_id[10];
	char pr_date[11];
	char pr_medicines[500];
	char pr_notes[300];

	while (fin.getline(pr_id, 10, ','))
	{
		fin.getline(a_id, 10, ',');
		fin.getline(p_id, 10, ',');
		fin.getline(d_id, 10, ',');
		fin.getline(pr_date, 11, ',');
		fin.getline(pr_medicines, 500, ',');
		fin.getline(pr_notes, 300, '\n');

		if (pr_id[0] == '\0')
		{
			continue;
		}

		int prid = atoi(pr_id);
		int aid = atoi(a_id);
		int pid = atoi(p_id);
		int did = atoi(d_id);

		Prescription * pres = new Prescription(prid, aid, pid,did, pr_date, pr_medicines, pr_notes);
		store.Add(pres);

	}
	fin.close();
}
//it is used to add record after the last line 
void FileHandler::appendrecord(const char* filename, const char* addline)
{
	ofstream fout(filename, ios::app);
	if (!fout)
	{
		throw FileNotFoundException("Could not append record as file cannot be opened");
	}
	fout << addline << "\n";
	fout.close();

}
//it is used to replace a line whos id is matched
void  FileHandler::modifyrecord(const char* filename, int id, const char* newline)
{
	ifstream fin(filename);
	if (!fin)
	{
		throw FileNotFoundException("Unable to open the file");
	}
	ofstream fout("temp.txt");
	if (!fout)
	{
		fin.close();
		throw FileNotFoundException("Unable to open temp.txt file");
	}

	char words[1000];
	while (fin.getline(words, 1000))
	{
		if (words[0] == '\0')
		{
			continue;
		}
		char n_id[10] = {};
		int k = 0;
		while (words[k] != ',' && words[k] != '\0')
		{
			n_id[k] = words[k];
			k++;
		}
		n_id[k] = '\0';
		if (id == atoi(n_id))
		{
			fout << newline << "\n";
		}
		else
		{
			fout << words << "\n";
		}
	}
	fin.close();
	fout.close();
	remove(filename);
	rename("temp.txt", filename);
}
void FileHandler::deleterecord(const char* filename, int id)
{
	ifstream fin(filename);
	if (!fin)
	{
		throw FileNotFoundException("Unable to open the file");
	}
	ofstream fout("temp.txt");
	if (!fout)
	{
		fin.close();
		throw FileNotFoundException("Unable to open temp.txt file");
	}
	char words[1000];
	bool check = false;
	while (fin.getline(words, 1000))
	{
		if (words[0] == '\0')
		{
			continue;
		}
		char n_id[10] = {};
		int k = 0;
		while (words[k] != ',' && words[k] != '\0')
		{
			n_id[k] = words[k];
			k++;
		}
		n_id[k] = '\0';

		if (id == atoi(n_id))
		{
			check = true;//we will do no writing so records will delete themselves as they are not written
		}
		else
		{
			fout << words << "\n";
		}
	}
	fin.close();
	fout.close();
	remove(filename);
	rename("temp.txt", filename);

	if (check == false)
	{
		cout << "Could not find record of id : " << id << " inside : " << filename << endl;
	}

}
