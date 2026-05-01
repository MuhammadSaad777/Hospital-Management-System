#pragma once
#include"Person.h"
#include<iostream>

class Admin : public Person
{
public:
	Admin(int i, const char* nam, const char* pa);
	void Display() const override;
	void showmenu() override;
	friend std::ostream& operator<<(std::ostream&, const Admin&);
};