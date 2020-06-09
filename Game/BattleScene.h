#pragma once
#include "Scene.h"
#include "DataStructure/skillTree.h"
#include "DataStructure/Que.h"
class BattleScene : public Scene
{
private:
	int successflag;
	SkillTree* skillTree;
	PIMAGE backGround;
	PIMAGE enemyBattler;
	string instructions;
	string currentSkillName;
	int loopTurn;// 回合
	int enemyHp = 1000;
	int maxEnemyHp = 1000;
	int playerhp = 1000;
	int maxPlayerhp = 1000;
	Que infoList;
	// 1代表自己的回合，0代表对方的回合
public:
	BattleScene(Role& role);
	void update();
	void draw();
	void pushInfo(string info) {
		infoList.push(info);
	}
};

