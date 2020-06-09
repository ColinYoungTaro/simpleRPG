#ifndef __SKILL__
#define __SKILL__

#include <string>
class Skill
{
private:
	//char key;
	int power;
	std::string name; 
	std::string instruct;
public:
	Skill() {};
	//Skill(char key, int power, std::string name) :key(key), power(power), name(name) {};
	Skill(int power, std::string name,std::string instruct) 
		:power(power), name(name),instruct(instruct){};
	bool operator<(const Skill& s) {
		return this->instruct < s.instruct;
	}

	bool operator>(const Skill& s) {
		return this->instruct > s.instruct ;
	}

	int getPower() {
		return this->power;
	}
	string getName() {
		return this->name;
	}
};

#endif
