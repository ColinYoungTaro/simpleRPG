#pragma once
#include<string>
using std::string;
// Ñ­»·¶ÓÁÐ
class Que {
public:
	int maxsize;
	int head, tail = 0;
	string* element;
	int inc(int val) {
		return (val + 1) % maxsize;
	}
	Que(int size = 6) {
		this->maxsize = size;
		element = new string[size];
	}
	void push(string s) {
		element[tail] = s;
		if (inc(tail) != head) {
			tail = inc(tail);
		}
		else {
			head = inc(head);
			tail = inc(tail);
		}
	}
};