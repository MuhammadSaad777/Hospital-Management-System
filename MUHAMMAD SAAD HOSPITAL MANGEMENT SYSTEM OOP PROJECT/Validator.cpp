#define _CRT_SECURE_NO_WARNINGS
#include"Validator.h"
#include<ctime>
using namespace std;

// validateid


int Validator::findlen(const char * str)
{
	int l = 0;
	while (str[l] != '\0')
	{
		l++;
	}
	return l;

}
 bool Validator::validateid(int i)
{
	 bool status = false;
	 if (i <= 0)
	 {
		 return status;
	 }
	 status = true;
	 return status;
}

bool Validator::validatedate(int d, int m, int y)
{
	bool status = false;
	time_t tim = time(0);
	tm* now = localtime(&tim);
	int presentyear = now->tm_year + 1900;
	if (d < 1 || d>31)
	{
		return status;
	}
	if (m < 1 || m>12)
	{
		return status;
	}
	if (y < presentyear)
	{
		return status;
	}
	status = true;
	return status;
}

bool Validator:: validatetimeslot(const char * slot)
{
	const char* validtimes[8] = 
	{
	   "09:00",
	   "10:00",
	   "11:00",
	   "12:00",
	   "13:00",
	   "14:00",
	   "15:00",
	   "16:00"
	};
	for (int i = 0; i < 8; i++)
	{
		int j = 0;
		bool match = true;
		while (validtimes[i][j] != '\0' && slot[j] != '\0')
		{
			if (validtimes[i][j] != slot[j])
			{
				match = false;
				break; 
			}
			j++;
		}

		if (match)
		{
			return true;
		}

	}

	return false;
}

bool Validator:: validatecontact(const char* contact)
{
	bool status = false;
	int length = findlen(contact);
	if (length != 11)
	{
		return status;
	}
	for (int i = 0; i < length;i++)
	{
		if (contact[i] < '0' || contact[i]>'9')
		{
			return status;
		}
	}
	status = true;
	return status;
}

	
bool Validator:: validatepassword(const char * password)
{
	bool status = false;
	int length = findlen(password);
		if (length < 6)
		{
			return status;
	    }
		status = true;
		return status;
}
bool Validator::validateconsultationfee(float fee)
{
	bool status = false;
	if (fee <= 0)
	{
		return status;
	}
	status = true;
	return status;

}
bool Validator::validatemenuchoices(int m, int l, int u)
{
	bool status = false;
	if (m<l || m>u)
	{
		return status;
	}
	status = true;
	return status;
}



