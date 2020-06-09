#pragma once
class unionfindset {
private:
	int* set;
	int* weight;
	int size;
	int count;
public:
	unionfindset(int size) {
		this->size = size;
		set = new int[size];
		weight = new int[size];
		count = size;
		int i;
		for (i = 0; i < size; i++) {
			set[i] = i;
			weight[i] = 1;
		}
	}
	int getcount() const {
		return count;
	}
	~unionfindset() {
		delete[] set;
		delete[] weight;
	}
	int findset(int num) {
		int root = num, temp;
		while (root != set[root]) {//find the root
			root = set[root];
		}
		while (num != set[num]) {//路径压缩
			temp = num;
			num = set[num];
			set[temp] = root;
		}
		return root;
	}
	int unionset(int b1, int b2) {
		int root1, root2;
		root1 = findset(b1);
		root2 = findset(b2);
		if (root1 == root2) {//已经连通
			return 0;
		}
		else {
			if (weight[root1] < weight[root2]) {
				set[root1] = root2;
				weight[root2] += weight[root1];
			}
			else {
				set[root1] = root2;
				weight[root1] += weight[root2];
			}
			count--;
			return 1;
		}
	}
};


