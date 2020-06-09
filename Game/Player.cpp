#include "Player.h"
#include<iostream>

using std::cout;
using std::endl;

Player::Player(string name):Role(name)
{
}

void Player::draw() {
	Role::draw();
}
void Player::update() {
	Role::update();
	key_msg k;
	if (kbhit()) {
		k = getkey();
		isMoving = true;
		//TODO:ÅÐ¶ÏÊÇ·ñ³ö½ç
		if (k.key == ege::key_left) {
			turn(Dir::left);
			if (withinBound(*map, x - 1, y)
				&& (*map)[x - 1][y] == Game::walkable
				 )
				setPos(x - 1, y);
		}
		else if (k.key == ege::key_right) {
			turn(Dir::right);
			if (withinBound(*map, x + 1, y) &&
				(*map)[x + 1][y] == Game::walkable)
				setPos(x + 1, y);
		}
		else if (k.key == ege::key_down) {
			turn(Dir::down);
			if (withinBound(*map, x, y + 1) &&
				(*map)[x][y + 1] == Game::walkable)
				setPos(x, y + 1);
		}
		else if (k.key == ege::key_up) {
			turn(Dir::up);
			if ( withinBound(*map, x, y - 1) && 
				(*map)[x][y - 1] == Game::walkable)
				setPos(x, y - 1);
		}
	}
	else {
		//isMoving = false;
	}
	
}