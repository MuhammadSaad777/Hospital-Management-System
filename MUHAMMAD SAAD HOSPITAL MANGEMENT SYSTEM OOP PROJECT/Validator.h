#pragma once

// validateid
class Validator
{
public:
	static bool validateid(int i);
	static bool validatedate(int d, int m, int y);
	static bool validatetimeslot(const char *  slot);
	static bool validatecontact(const char * contact);
	static bool validatepassword(const char * password);
	static bool validateconsultationfee(float fee);
	static bool validatemenuchoices(int m, int l, int u);
	static int findlen(const char* str);
};
	


