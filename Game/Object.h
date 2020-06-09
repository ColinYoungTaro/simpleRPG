#pragma once
#include "GameEngine.h"
#include <string>
#include <vector>
#include <graphics.h>
using std::vector;
using std::string;
class Object
{
protected:
	PIMAGE animationImg;
	void setRsc(string name);
public:
	int x, y; // 参考坐标
	/*****************************************
	* TODO : 文件资源统一整合到全局，避免重复加载
	******************************************/
	Object(int x = 0, int y = 0) :x(x), y(y) {}
	Object(string name, int x, int y) :Object(x, y) {
		setRsc(name);
	}
	~Object();
	virtual void update();
	virtual void draw();
	virtual void setPos(int x, int y) {
		this->x = x;
		this->y = y;
	}
	virtual bool withinBound(vector<vector<int> >&maze,int x,int y) {
		if (maze.size() == 0)return false;
		return x < static_cast<int>(maze.size()) 
			&& y < static_cast<int>(maze.front().size()) 
			&& x >= 0 
			&& y >= 0;
	}
};

