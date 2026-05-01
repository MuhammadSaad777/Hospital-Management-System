#pragma once
class Person
{
protected :
	int id;
	char name[50];
	char pass[50];
	Person(int, const char*, const char *);
public:
	int getId() const;
	const char *  getName() const;
	const char * getPass() const;
	virtual void Display() const = 0;
	virtual void showmenu()=0;
	virtual ~Person() {};
};