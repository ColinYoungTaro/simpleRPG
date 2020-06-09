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
	int loopTurn;// �غ�
	int enemyHp = 1000;
	int maxEnemyHp = 1000;
	int playerhp = 1000;
	int maxPlayerhp = 1000;
	Que infoList;
	// 1�����Լ��Ļغϣ�0����Է��Ļغ�
public:
	BattleScene(Role& role);
	void update();
	void draw();
	void pushInfo(string info) {
		infoList.push(info);
	}
};

