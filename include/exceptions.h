#pragma once
#include <exception>
using namespace std;

class BadRace : public exception {
	virtual const char* what() const throw() {
		return "Invalid Race";
	}
};

class UnitNotFound : public exception {
	virtual const char* what() const throw() {
		return "Unit Not Found";
	}
};

class NotEnoughLarva : public exception {
	virtual const char* what() const throw() {
		return "Not Enough Larva";
	}
};
