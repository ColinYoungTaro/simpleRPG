#pragma once
#include "Role.h"
class Player : public Role
{

public:
	Player(string name);
	//~Player();
	void update();
	void draw();
};

