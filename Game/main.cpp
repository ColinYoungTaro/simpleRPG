#include <graphics.h>
#include <string>
#include <time.h>
#include "Role.h"
#include "MapScene.h"
#include "BattleScene.h"
#include <math.h>
#include <stack>
#include <map>
#include "DataStructure/AvlTree.h"
using std::string;
using std::stack;
using std::map;
// 全局变量
namespace Global {
	stack<Scene*> g_sceneStack;
	map<string, PIMAGE> rsc;
	AvlTree<string, PIMAGE> resrc;
}
// 初始化复用资源
void initGlobalresource() {
	using Global::rsc;
	using Global::resrc;
	string arr[] =
	{
		"bg","block","stone"
	};
	for (auto& str : arr) {
		PIMAGE pimg = newimage();
		string tmpName = "Graphics/Maps/" + str + ".png";
		getimage(pimg,tmpName.c_str());
		resrc.Insert(str, pimg);
	}
	string characters[] = {
		"Devil","Dragon","Bird","Goblin","Undead"
	};
	for (auto& str : characters) {
		PIMAGE battlerImg = newimage();
		PIMAGE chImg = newimage();
		string battler = "Graphics/Battlers/" + str + ".png";
		string tmpName = "Graphics/Characters/" + str + ".png";
		getimage(chImg, tmpName.c_str());
		getimage(battlerImg, battler.c_str());
		string index = "battlers/" + str;

		resrc.Insert(index, battlerImg);
		resrc.Insert(str, chImg);
	}
	PIMAGE bk = newimage();
	getimage(bk,"Graphics/Background/background.jpg");
	string s = "background";
	resrc.Insert(s,bk);
}
// 调用战斗场景
void CallBattleScene(Role* role) {
	Global::g_sceneStack.push(new BattleScene(*role));
}
// 回到上一个场景
void returnPrevScene() {
	Scene* tmp = Global::g_sceneStack.top();
	Global::g_sceneStack.pop();
	delete tmp;
}
// 释放所有资源
void Release() {
	while (!Global::g_sceneStack.empty()) {
		Scene* tmp = Global::g_sceneStack.top();
		Global::g_sceneStack.pop();
		delete tmp;
	}
	for (auto& iter : Global::rsc) {
		PIMAGE pimg = iter.second;
		delimage(pimg);
	}
	
}
PIMAGE getRsc(string key) {
	return Global::resrc.Find(key)->getVal();
}
int main()
{
	// basic configurations:
    initgraph( 640, 640 ,INIT_RENDERMANUAL);
    setcolor( RGB(0xff, 0xff, 0xff) );
    setfillcolor( RGB(0, 0, 0xff) );
    setrendermode(RENDER_MANUAL);
	// set up proceed
	initGlobalresource();
	Scene *scene = new MapScene("Basic", 20, 20);
	Global::g_sceneStack.push(scene);
	PIMAGE pimg = newimage();
	// main game loop
    for ( ; is_run(); delay_fps(60) )
    {
		Scene* current_scene = Global::g_sceneStack.top();
		cleardevice();
		current_scene->draw();
		current_scene->update();
    }
	//delete scene;
	Release();
    closegraph();
    return 0;
}

