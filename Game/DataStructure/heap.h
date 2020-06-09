#pragma once
/****************************
* Heap.h 模板类
* 功能：用树状数组实现heap数据结构
* 支持最小堆和最大堆的维护
* 前提，插入的元素必须有或者重载过<和>运算符
* 插入，删除元素
*******************************/
#include <vector>
using std::vector;
template<typename Comparable>

inline bool defaultCmp(const Comparable& A, const Comparable& B) {
	return A < B;
}

template<typename Comparable>
class Heap {
public:
	typedef bool(*CompFunc)(const Comparable& A, const Comparable& B);
	Heap(CompFunc cmp);
	Heap();
	~Heap() {}
	Comparable top();
	Comparable pop();
	bool push(Comparable val);
	bool empty() {
		return this->tail == 0;
	}
	int size() {
		return this->tail;
	}
	bool del(Comparable key) {
		if (tail >= 1) {
			for (int i = 1; i <= tail; i++) {
				if (heap[i] == key) {
					heap[i] = heap[tail--];
					shiftDown(i);
					heap.pop_back();
					return true;
				}
			}
		}
		return false;
	}
private:
	int tail;
	CompFunc cmp;
	vector<Comparable> heap;
	void shiftDown(int _index) {
		int index = _index;
		Comparable tmp = heap[index];
		int child;
		for (; index * 2 <= tail; index = child) {
			child = 2 * index;
			if (child != tail && cmp(heap[child + 1], heap[child]))
				child++;
			if (cmp(heap[child], tmp)) {
				heap[index] = heap[child];
			}
			else
				break;
		}
		heap[index] = tmp;
	}
};
template<typename Comparable>
Heap<Comparable>::Heap() :Heap(defaultCmp) {
}
template<typename Comparable>
Heap<Comparable>::Heap(CompFunc cmp) : tail(0) {
	this->cmp = cmp;
	this->heap = vector<Comparable>();
	//note that the Comparable type must have default constructor
	heap.push_back(Comparable());
	//insert the dummy head.
}

template<typename Comparable>
bool Heap<Comparable>::push(Comparable val) {
	tail++;
	heap.push_back(val);
	int index = tail;
	while (index > 1 && cmp(val, this->heap[index / 2])) {
		;
		heap[index] = heap[index / 2];
		index /= 2;
	}
	heap[index] = val;
	return true;
}
template<typename Comparable>
Comparable Heap<Comparable>::pop() {
	Comparable val = top();
	heap[1] = heap[tail--];
	shiftDown(1);
	heap.pop_back();
	return val;
}
template<typename Comparable>
Comparable Heap<Comparable>::top() {
	return heap[1];
}
