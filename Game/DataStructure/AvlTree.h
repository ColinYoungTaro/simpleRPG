#ifndef __AVLTREE__
#define __AVLTREE__

#include "AVLNode.h"
#include <vector>
using std::vector;
template <class KeyType, class ValueType>
class AvlTree
{
private:
	AvlNode<KeyType, ValueType> *root;

public:
	~AvlTree() { MakeEmpty(); }
	AvlTree():root(NULL) {}
	// ½Ó¿Ú
	void MakeEmpty();
	AvlNode<KeyType, ValueType>* Find(KeyType &X);
	AvlNode<KeyType, ValueType>* FindMin();
	AvlNode<KeyType, ValueType>* FindMax();
	void Insert(KeyType &key, ValueType &value);
	void Delete(KeyType &X);
	void getAllValue(vector<ValueType>&);

};
template <class KeyType, class ValueType>
void AvlTree<KeyType, ValueType>::getAllValue(vector<ValueType>& vctor)
{
	//root->traverse(vctor)
}
template <class KeyType, class ValueType>
void AvlTree<KeyType, ValueType>::MakeEmpty()
{
	if(root) root->DelNode();
	root = NULL;
}

template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlTree<KeyType, ValueType>::Find(KeyType &X)
{
	if (!root) return NULL;
	return root->Find(X);
}

template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> * AvlTree<KeyType, ValueType>::FindMin()
{
	if (!root)
		return NULL;
	return root->FindMin();
}

template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> * AvlTree<KeyType, ValueType>::FindMax()
{
	if (!root)
		return NULL;
	return root->FindMax();
}

template <class KeyType, class ValueType>
void AvlTree<KeyType, ValueType>::Insert(KeyType &key, ValueType &value) {
	if (!root)
		root = new AvlNode<KeyType, ValueType>(key, value);
	else
		root = root->Insert(key, value);
}

template <class KeyType, class ValueType>
void AvlTree<KeyType, ValueType>::Delete(KeyType &X) {
	if (root)
		root = root->Delete(X);
}

#endif