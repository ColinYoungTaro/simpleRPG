#include "MapScene.h"
#include "DataStructure/UnionFindSet.h"
#include <chrono>
#include <graphics.h>
#include <algorithm>
#include <random>
#include <map>

using std::vector;
void CallBattleScene(Role* role);
PIMAGE getRsc(string key);
MapScene::MapScene(string name,int w,int h):
	Scene(name,w,h)
{	
	// isAstar = false;

	grass = getRsc("bg");
	block = getRsc("block");
	
	// 添加障碍
	tileMap = vector<vector<int> >(w, vector<int>(h, 0));
	init_maze();
	vector<Point> Pts;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (tileMap[i][j] == Game::block) {
				Object* blk = new Object("stone", i, j);
				objList.push_back(blk);
			}
			// 将没有障碍的节点加入
			else {
				Pts.push_back(Point(i, j));
			}
		}
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(Pts.begin(), Pts.end(), std::default_random_engine(seed));
	// 打乱所有没有障碍的节点
	string arr[] = { "Dragon","Bird","Undead","Devil" };
	for (int i = 0; i < 4; i++) {
		addEnemy(arr[i], Pts[i].x, Pts[i].y,i % 4);
	}
	addPlayer("Goblin", Pts[4].x, Pts[4].y);
	isAstar = false;
	destx = -1, desty = -1;
	// Astar();
}

MapScene::~MapScene()
{
}
void MapScene::draw() {
	int tw = getwidth(grass);
	int th = getheight(grass);
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			putimage(i*tw, j*th, grass);
		}
	}

	if (isAstar) {
		Astar(destx,desty);
	}
	Scene::draw();
}
// 初始化自己的map
void MapScene::init_maze() {
	std::vector<std::vector<int>>& maze = this->tileMap;
	int i, j, random;
	for (i = 0; i < w ; i++) {
		for (j = 0; j < h ; j++) {
			maze[i][j] = 1;
		}
	}
	for (i = 1; i < w ; i += 2) {
		for (j = 1; j < h; j += 2) {
			maze[i][j] = 0;
		}
	}
	unionfindset aset((w / 2) * (h / 2));
	const int removable = 2 * (w / 2) * ((h / 2) - 1);
	int* randomblock = new int[removable];
	for (i = 0; i < removable; i++) {
		randomblock[i] = i;
	}
	for (i = 0; i < removable; i++) {
		random = rand() % removable;
		int temp = randomblock[random];
		randomblock[random] = randomblock[i];
		randomblock[i] = temp;
	}
	int width, rx, ry, x1, y1, x2, y2;
	i = 0;
	while (aset.getcount() > 1) {
		rx = 0;
		ry = 0;
		if (randomblock[i] < removable / 2) {
			width = w / 2 - 1;
			x1 = randomblock[i] % width;
			y1 = randomblock[i] / width;
			rx = 1;
		}
		else {
			randomblock[i] = randomblock[i] - removable / 2;
			width = w / 2;
			x1 = randomblock[i] % width;
			y1 = randomblock[i] / width;
			ry = 1;
		}
		x2 = x1 + rx;
		y2 = y1 + ry;
		if (aset.unionset(y1 * (w / 2) + x1, y2 * (h / 2) + x2)) {
			maze[y1 + y2 + 1][x1 + x2 + 1] = 0;
		}
		i++;
	}
}
void MapScene::update() {
	
	//if ( player->x == w - 1 && player->y == h - 1) {
	//	// 内存泄露....
	//	Role *s = new Role("Dragon");
	//	CallBattleScene(s);
	//}

	Scene::update();
	// 开启寻路模式
	if (keystate(VK_LBUTTON)) {
		mousepos(&destx, &desty);
		destx = destx / Game::tw;
		desty = desty / Game::th;
		isAstar = true;
	}
	if (keystate(VK_RBUTTON))
		isAstar = false;
	if (keystate(VK_SPACE)) {
		for (auto& monster : monsters) {
			if (player->x == monster->x
				&& player->y == monster->y) {
				CallBattleScene(monster);
			}
		}
	}

}
Role* MapScene::addEnemy(string name, int x,int y,int dir) {

	Role* role = new Role(name);
	role->setMap(this->tileMap);
	monsters.push_back(role);
	role->setPos(x, y);
	role->turn(dir);
	objList.push_back(role);
	return role;
}
Player* MapScene::addPlayer(string name, int x, int y,int dir) {
	Player* role = new Player(name);
	role->setPos(x, y);
	role->setMap(this->tileMap);
	this->player = static_cast<Player*>(role);
	objList.push_back(role);
	return role;
}
// 相对的格子坐标
void MapScene::Astar(int x,int y) {
	list<Point> tmpPath;
	shortestPath(tileMap, Point(player->x,player->y),Point(x, y),tmpPath);
	Point start = Point(player->x, player->y);
	Point* prev = &start;
	setlinewidth(15);
	setcolor(RGB(0, 255, 255));
	for (auto& point : tmpPath) {
		line(prev->x*Game::tw + Game::tw / 2,
			 prev->y*Game::th + Game::th / 2,
			 point.x*Game::tw + Game::tw / 2,
			 point.y*Game::th + Game::th / 2);
		prev = &point;
	}
	//	setfillcolor(EGERGB(0xFF, 0x0, 0x0));
}
