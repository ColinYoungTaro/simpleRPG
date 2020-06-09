#ifndef _SCENE_H_
#define _SCENE_H_
#include<vector>
#include<string>
#include"Player.h"
#include"Map.h"
using std::string;
using std::vector;
class Node {
public:
private:
	string sceneName;
	int id;
};
class Scene : public Object{

public:
	Scene(string name,int w,int h);
	virtual ~Scene() {
		for (int i = objList.size() - 1; i >= 0; i++) {
			delete objList[i];
			objList.pop_back();
		}
	}
	void update();
	void draw();
	Player* player;
	
protected:
	int w, h;
	string sceneName;
	vector<Object*>objList;
	static inline bool sortFunc(Object*& A,Object*& B) {
		return A->y < B->y;
	}

};
#endif
