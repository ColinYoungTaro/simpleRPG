#include"Scene.h"
#include "Player.h"
#include<algorithm>
Scene::Scene(string name, int w, int h)
	:sceneName(name), w(w), h(h)
{
}
void Scene::update() {
	for (auto& obj : objList) {
		obj->update();
	}
}
// ¿ìËÙÅÅĞò´úÂë
template<typename T>
void sort(vector<T>& arr, int l, int r,bool (*funcptr)( T& a,T& b)) {
	bool flag = true;
	for (int i = l; i < r; i++) {
		if (funcptr(arr[i+1], arr[i])) {
			flag = false;
			break;
		}
	}
	if (flag)return;
	if (r <= l)return;
	int i = l - 1, j = r + 1;
	int m = (l + r) / 2;
	T key = arr[m];
	while (i < j) {
		do { i++; } while (funcptr(arr[i],key));
		do { j--; } while (funcptr(key,arr[j]));
		if (i < j) {
			T tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	sort(arr, l, j, funcptr);
	sort(arr, j + 1, r,funcptr);
}
void Scene::draw() {
	//sort(objList.begin(), objList.end(), sortFunc);
	sort<Object*>(objList, 0, objList.size() - 1, sortFunc);
	for (auto& obj : objList) {
		obj->draw();
	}
}

