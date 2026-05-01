#include"Person.h"

Person::Person(int nid, const char* n, const char * p)
{
	id = nid;
	int ln=0;
	for (int i = 0; n[i] != '\0';i++)
	{
		ln++;
	}
	int i = 0;
	for (; i < ln;i++)
	{
		name[i] = n[i];
	}
	name[i] = '\0';
	int pn = 0;
	for (int i = 0; p[i] != '\0';i++)
	{
		pn++;
	}
	int j = 0;
	for (; j < pn;j++)
	{
		pass[j] = p[j];
	}
	pass[j] = '\0';

}
int Person::getId() const
{
	return id;
}
const char * Person::getName() const
{
	return name;
}
const char *  Person::getPass() const
{
	return pass;
}

