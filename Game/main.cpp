#include <graphics.h>
#include <string>
#include <time.h>
#include "Role.h"
#include "MapScene.h"
#include "BattleScene.h"
#include <math.h>
#include <stack>
#include <map>
using std::string;
using std::stack;
using std::map;
// 全局变量
namespace Global {
	stack<Scene*> g_sceneStack;
	map<string, PIMAGE> rsc;
}
// 初始化复用资源
void initGlobalresource() {
	using Global::rsc;
	string arr[] =
	{
		"bg","block","stone"
	};
	for (auto& str : arr) {
		rsc[str] = newimage();
		string tmpName = "Graphics/Maps/" + str + ".png";
		getimage(rsc[str],tmpName.c_str());
	}
	string characters[] = {
		"Devil","Dragon","Bird","Goblin","Undead"
	};
	for (auto& str : characters) {
		rsc[str] = newimage();
		string battler = "Graphics/Battlers/" + str + ".png";
		string tmpName = "Graphics/Characters/" + str + ".png";
		getimage(rsc[str], tmpName.c_str());
		string index = "battlers/" + str;
		rsc[index] = newimage();
		getimage(rsc[index], battler.c_str());
	}
	rsc["background"] = newimage();
	getimage(rsc["background"],"Graphics/Background/background.jpg");
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
	return Global::rsc[key];
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

