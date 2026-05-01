#pragma once
#include<iostream>
using namespace std;

template <typename T>
class Storage
{
private:
	T data[100];
	int count;
public:
	Storage()
	{
		count = 0;
	}
	void Add(T value)
	{
		if (count > 99)
		{
			cout << "Cannot Add !! Already Full Storage";
			cout << endl;
			return;
		}
		else
		{
			data[count] = value;
			count++;
		}
	}
	void removebyid(int ids)
	{
		int val = -999;
		for (int i = 0; i < count;i++)
		{
			if (ids == data[i]->getId())
			{
				val = i;
				break;
			}
		}
		if (val != -999)
		{
			for (int i = val; i <= count - 2;i++)
			{
				data[i] = data[i + 1];
			}
			count--;
		}
		else
		{
			cout << "Unable to find this id ";
			return;
		}
	}

	T findbyid(int idd)
	{
		for (int i = 0; i < count;i++)
		{
			if (idd == data[i]->getId())
			{
				return data[i];
			}
		}
		return nullptr;
	}
	T* getall()
	{
		return data;
	}
	int getsize() const
	{
		return count;
	}
};