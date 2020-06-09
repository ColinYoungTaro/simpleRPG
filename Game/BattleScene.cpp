#include "BattleScene.h"
#include "DataStructure/skillTree.h"
#include <sstream>
#include <random>
#include <ctime>
void returnPrevScene();
PIMAGE getRsc(string name);
BattleScene::BattleScene(Role& role)
	:Scene("Battle",0,0),instructions("")
{
	loopTurn = 1;
	successflag = 0;
	skillTree = new SkillTree();
	backGround = getRsc("background");
	enemyBattler = getRsc("battlers/" + role.getName());
}
void BattleScene::update() {
	if (!successflag) {
		if (loopTurn == 1) {
			key_msg k;
			if (kbhit()) {
				k = getkey();
				if (k.key != ege::key_enter)
					instructions = instructions + static_cast<char>(k.key);
				else {
					Skill* skill = NULL;
					skill = skillTree->findSkill(instructions);
					if (skill) {
						currentSkillName = skill->getName();
						int power = skill->getPower();
						enemyHp -= power;

						std::stringstream ss;
						ss << power;
						string nextInfo = "你发动了技能" + currentSkillName
							+ "给对方造成了" + ss.str() + "点伤害";
						pushInfo(nextInfo);
					}
					else {
						pushInfo("没有找到技能，发动失败");
					}
					instructions = "";
					loopTurn = 0;
				}
			}
			if (enemyHp <= 0) {
				enemyHp = 0;
				successflag = 1;
				pushInfo("恭喜你赢得战斗");
				pushInfo("按ESC退出");
			}
		}
		else {
			std::default_random_engine e;//随机数引擎对象
			e.seed(time(NULL)); //初始化种子
			std::uniform_int_distribution<unsigned> u(100, 200);//随机数分布对象，控制随机数范围5-15
			int hurt = u(e);
			playerhp -= hurt;
			std::stringstream ss;
			ss << hurt;
			string info = "敌人对你造成了" + ss.str() + "点伤害";
			pushInfo(info);
			loopTurn = 1;
			if (playerhp <= 0) {
				playerhp = 0;
				successflag = -1;
				pushInfo("胜败乃兵家常事 大侠重新来过");
				pushInfo("按ESC退出");
			}
		}
	}
	else {
		if (keystate(VK_ESCAPE)) {
			returnPrevScene();
		}
	}

}
void BattleScene::draw() {
	setlinewidth(2);
	setcolor(BLACK);
	putimage(0, 0, backGround);
	int spriteW = getwidth(enemyBattler);
	int spriteH = getheight(enemyBattler);
	putimage_withalpha(NULL,enemyBattler,
		320-spriteW/2,240-spriteH/2,0,0,spriteW,spriteH);


	setfillcolor(RGB(89, 93, 148));
	string out = instructions + "_";	
	bar(0,480,640,640);
	setbkcolor(RGB(89, 93, 148));
	outtextrect(20, 500, 300, 50, "技能指令");
	outtextrect(20, 530, 300, 100, out.c_str());

	// 绘制血条
	// 敌人的血条
	setfillcolor(RGB(0, 0, 255));
	rectangle(240, 50, 400, 70);
	bar(240, 50, 240 + 160 * enemyHp / maxEnemyHp, 70);
	// 玩家的血条

	rectangle(20, 600, 180, 620);
	bar(20, 600, 20 + 160 * playerhp / maxPlayerhp, 620);

	int index = 0;
	for (int i = infoList.head; i != infoList.tail; i = (i + 1) % infoList.maxsize) {
		outtextrect(240,500+index*25,380,100,infoList.element[i].c_str());
		index++;
	}
}

