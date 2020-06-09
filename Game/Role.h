#ifndef ROLE_H
#define ROLE_H
#include<string>
#include<graphics.h>
#include"Object.h"
#include "Map.h"
using std::string;
class Role : public Object {
protected:
	int dir;
	int spriteW, spriteH;
	bool isMoving;
	string name;
	int div;
	int cnt;
	vector<vector<int> >* map;
	// ָ��ǰ��ͼ��ָ��
public:
	Role(string name,int dir = Dir::down);
	~Role();
	void update();
	string getName() {
		return name;
	}
	void draw();
	void turn(int dir);
	void setMap(vector<vector<int>> & map);

};
#endif // !ROLE_H

