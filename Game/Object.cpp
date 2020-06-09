#include "Object.h"
PIMAGE getRsc(string);
Object::~Object()
{
	delimage(this->animationImg);
}
void Object::update() {

}
void Object::setRsc(string name){
	this->animationImg = getRsc(name);
}
void Object::draw() {
	int tw = getwidth(animationImg);
	int th = getheight(animationImg);
	putimage_withalpha(NULL, animationImg, x*Game::tw,y*Game::th, 0, 0, tw, th);
}