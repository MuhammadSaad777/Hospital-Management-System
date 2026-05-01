#include"HospitalException.h"



HospitalException::HospitalException(const char* str)
{
	int i = 0;
	for (; str[i] != '\0'&& i<199;i++)
	{
		message[i] = str[i];
	}
	message[i] = '\0';
}



