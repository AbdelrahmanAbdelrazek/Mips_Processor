#include <iostream>
#include <string>
#include "dbc.h"

using namespace std;

class Dictionary
{
private:
	string names[100];
	int addresses[100];
	int size;
public:

//Queries
	int get_size() {
		return size;
	}

	bool is_empty() {
		return get_size() == 0;
	}

	bool is_name_exist(string name) {
		INVARIANT0(get_size() >= 0);
		
		if (size == 0) {
			return false;
		}
		else {
			for (int i = 0; i < size; i++) {
				if (names[i] == name)
					return true;
			}
			return false;
		}
		
		INVARIANT0(get_size() >= 0);
	}

	bool is_address_exist(int address) {
		INVARIANT0(get_size() >= 0);
		
		if (size == 0) {
			return false;
		}
		else {
			for (int i = 0; i < size; i++) {
				if (addresses[i] == address)
					return true;
			}
			return false;
		}
		
		INVARIANT0(get_size() >= 0);
	}

	int get_address(string name) {
		INVARIANT0(get_size() >= 0);
		REQUIRE(is_name_exist(name), name + " is not in the dictionary");
		
		for (int i = 0; i < size; i++) {
			if (names[i] == name)
				return addresses[i];
		}

		INVARIANT0(get_size() >= 0);
	}

	string get_name(int address) {
		INVARIANT0(get_size() >= 0);
		REQUIRE(is_address_exist(address), address + " is not in the dictionary");
		
		for (int i = 0; i < size; i++) {
			if (addresses[i] == address)
				return names[i];
		}

		INVARIANT0(get_size() >= 0);
	}

//Commands
	
	Dictionary()
	{
		size = 0;
		ENSURE0(get_size() == 0);
	}

	void Add(string name, int address)
	{
		INVARIANT0 ( get_size() >= 0);
		REQUIRE(!is_name_exist(name), name + " is already in the dictionary");
		REQUIRE(!is_address_exist(address), address + " is already in the dictionary");
		int size_before = get_size();
		
		names[size] = name;
		addresses[size] = address;
		size++;
		
		ENSURE0(get_size() == size_before + 1);
		ENSURE0(get_address(name) == address); 
		ENSURE0(get_name(address) == name);
		INVARIANT0(get_size() >= 0);
	}

	void Remove(string name)
	{
		INVARIANT0(get_size() >= 0);
		REQUIRE(is_name_exist(name), name + " is not in the dictionary");
		int size_before = get_size();
		int address_to_be_removed = get_address(name);

		// a simple example on removing array of numbers
		// if the array is  {1,5,3,4,2,6,7,8,9,10}
		// and its size is 10 elements
		// and i want to remove entry "2"
		// i'll find its index first through the following code segment
		int indextoberemoved;

		for (int i = 0; i<size; i++)
		{
			if (names[i] == name)
			{
				indextoberemoved = i;
				break;
			}
		}
		// then i'll move all elements after that index backword one step
		// and with decrementing the size, this is equivalent to removing that element
		size--;
		for (int i = indextoberemoved; i<size; i++)
		{
			names[i] = names[i + 1];
			addresses[i] = addresses[i + 1];
		}

		ENSURE0(get_size() == size_before - 1);
		ENSURE0(!is_name_exist(name));
		ENSURE0(!is_address_exist(address_to_be_removed));
		INVARIANT0(get_size() >= 0);
	}

	void printentries()
	{
		INVARIANT0(get_size() >= 0);
		REQUIRE(!is_empty(), "dictionary is empty");
		for (int i = 0; i<size; i++)
		{
			cout << "Entry #" << i + 1 << ":" << endl << names[i] << ": " << addresses[i] << endl;
		}

		INVARIANT0(get_size() >= 0);
	}



};
