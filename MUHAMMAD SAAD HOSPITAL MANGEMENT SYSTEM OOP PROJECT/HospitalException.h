#pragma once

class HospitalException
{
protected:
	char message[200];
public:
	HospitalException(const char* str);
	virtual const char* what() const
	{
		return message;
	}
	virtual ~HospitalException() {};

};
