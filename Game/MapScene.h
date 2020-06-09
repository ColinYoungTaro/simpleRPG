#pragma once
#include "Scene.h"
using Maze = vector<vector<int> >;
class MapScene :public Scene
{
	PIMAGE grass;
	PIMAGE block;
	list<Role*> monsters;
	bool isAstar;
	int destx, desty;
public:
	MapScene(string name,int w,int h);
	~MapScene();
	vector<vector<int> > tileMap;

	void	init_maze();
	Role*	addEnemy(string name, int x=0, int y=0,int dir=Dir::down);
	Player*	addPlayer(string name, int x=0, int y=0,int dir=Dir::down);
	void	draw();
	void	update();
	void	Astar(int x,int y);
};

