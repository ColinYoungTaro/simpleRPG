#include"Role.h"

Role::Role(string name,int dir):
	Object(0, 0), cnt(0), isMoving(false), name(name),dir(dir){
	isMoving = true;	
	// 读取文件中的图片
	this->animationImg = newimage();
	string tmpName = "Graphics/Characters/" + name + ".png";
	getimage(this->animationImg,tmpName.c_str());

	spriteW = getwidth(this->animationImg) / 4;
	spriteH = getheight(this->animationImg) / 4;
}
Role::~Role() {
	delimage(this->animationImg);
}
void Role::update() {
	div = (div + 1) % Game::divdly;
	if (div == 0) {
		if (isMoving) {
			cnt = (cnt + 1) % 4;
		}
		else {
			cnt = 0;
		}
	}

}
void Role::turn(int dir) {
	this->dir = dir;
}
void Role::draw() {
	putimage_withalpha(NULL, this->animationImg,
		this->x*Game::tw - spriteW/2 +Game::tw / 2, this->y*Game::th - spriteH + Game::th ,
		cnt*spriteW,dir*spriteH, spriteW, spriteH);
	//putimage_withalpha(NULL, this->animationImg,200,200,0,0,100,100);
}
void Role::setMap(vector<vector<int> >& map) {
	this->map = &map;
}