#ifndef __AVLNODE__
#define __AVLNODE__

#include <iostream>
#include<vector>
using std::vector;
template <class KeyType, class ValueType>
class AvlNode
{
public:
	// 结点的属性
	KeyType Key;
	ValueType Value;
	AvlNode<KeyType, ValueType> *Left;
	AvlNode<KeyType, ValueType> *Right;
	int Height;
	// 内部方法
	int LeftHeight() const { return Left ? Left->Height : 0; }
	int RightHeight() const { return Right ? Right->Height : 0; }
	AvlNode<KeyType, ValueType> *SingleRotateWithLeft();
	AvlNode<KeyType, ValueType> *SingleRotateWithRight();
	AvlNode<KeyType, ValueType> *DoubleRotateWithLeft();
	AvlNode<KeyType, ValueType> *DoubleRotateWithRight();
	inline void UpdateHeight() { Height = LeftHeight() > RightHeight() ? LeftHeight() + 1 : RightHeight() + 1; }
	// 供AvlTree类调用的方法
	void DelNode();
	AvlNode<KeyType, ValueType> *Find(KeyType X) ;
	AvlNode<KeyType, ValueType> *FindMin() ;
	AvlNode<KeyType, ValueType> *FindMax() ;
	AvlNode<KeyType, ValueType> *Insert(KeyType key, ValueType value);
	AvlNode<KeyType, ValueType> *Delete(KeyType X);
	int getHeight() const { return Height; }

public:
	// 构造函数
	AvlNode(KeyType key, ValueType value) : Key(key), Value(value), Left(NULL), Right(NULL), Height(1) {}
	// 将AvlTree声明为AvlNode的友元类
	template <class KeyType, class ValueTypeype> friend class AvlTree;
	// 取结点值的接口
	ValueType getVal() const { return Value; }

};

template<class KeyType, class ValueType>
void AvlNode<KeyType, ValueType>::DelNode()
{
	if (Left)
		Left->DelNode();
	if (Right)
		Right->DelNode();
	delete this;
}

template<class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlNode<KeyType, ValueType>::Find(KeyType X)
{
	if (Key < X)
		return Right ? Right->Find(X) : NULL;
	else if (Key > X)
		return Left ? Left->Find(X) : NULL;
	else
		return this;
}

template<class KeyType, class ValueType>
AvlNode<KeyType, ValueType>* AvlNode<KeyType, ValueType>::FindMin()
{
	AvlNode<KeyType, ValueType> *t = this;
	while (t->Left)
		t = t->Left;
	return t;
}

template<class KeyType, class ValueType>
AvlNode<KeyType, ValueType>* AvlNode<KeyType, ValueType>::FindMax()
{
	AvlNode<KeyType, ValueType> *t = this;
	while (t->Right)
		t = t->Right;
	return t;
}



template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlNode<KeyType, ValueType>::SingleRotateWithLeft()
{
	AvlNode<KeyType, ValueType> *temp;
	temp = Left;
	Left = temp->Right;
	temp->Right = this;
	temp->UpdateHeight();
	UpdateHeight();
	return temp;
}

template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlNode<KeyType, ValueType>::SingleRotateWithRight()
{
	AvlNode<KeyType, ValueType> *temp;
	temp = Right;
	Right = temp->Left;
	temp->Left = this;
	temp->UpdateHeight();
	UpdateHeight();
	return temp;
}
template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlNode<KeyType, ValueType>::DoubleRotateWithLeft()
{
	Left = Left->SingleRotateWithRight();
	return SingleRotateWithLeft();
}

template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlNode<KeyType, ValueType>::DoubleRotateWithRight()
{
	Right = Right->SingleRotateWithLeft();
	return SingleRotateWithRight();
}

template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlNode<KeyType, ValueType>::Insert(KeyType key, ValueType value)
{
	AvlNode<KeyType, ValueType> *t = this;
	if (key < Key)
	{
		if (Left)
			Left = Left->Insert(key, value);
		else
			Left = new AvlNode<KeyType, ValueType>(key, value);
		UpdateHeight();
		if (LeftHeight() - RightHeight() == 2)
		{
			if (key < Left->Key)
				t = SingleRotateWithLeft();
			else
				t = DoubleRotateWithLeft();
		}
	}
	else if (key > Key)
	{
		if (Right)
			Right = Right->Insert(key, value);
		else
			Right = new AvlNode<KeyType, ValueType>(key, value);
		UpdateHeight();
		if (RightHeight() - LeftHeight() == 2)
		{
			if (key < Right->Key)
				t = DoubleRotateWithRight();
			else
				t = SingleRotateWithRight();
		}
	}
	t->UpdateHeight();
	return t;
}

template <class KeyType, class ValueType>
AvlNode<KeyType, ValueType> *AvlNode<KeyType, ValueType>::Delete(KeyType X)
{
	AvlNode<KeyType, ValueType>* t = this;
	if (X < Key)
	{
		if (Left)
			Left = Left->Delete(X);
		else
			std::cout << "没有找到该结点！" << std::endl;
		UpdateHeight();
		if (RightHeight() - LeftHeight() == 2)
		{
			if (Right->LeftHeight() > Right->RightHeight())
				t = DoubleRotateWithRight();
			else
				t = SingleRotateWithRight();
		}
	}
	else if (X > Key)
	{
		if (Right)
			Right = Right->Delete(X);
		else
			std::cout << "没有找到该结点！" << std::endl;
		UpdateHeight();
		if (LeftHeight() - RightHeight() == 2)
		{
			if (Left->LeftHeight() < Left->RightHeight())
				t = DoubleRotateWithLeft();
			else
				t = SingleRotateWithLeft();
		}
	}
	else
	{
		if (Left && Right)
		{
			t = Right->FindMin();
			Key = t->Key;
			Right = Right->Delete(Key);
			return this;
		}
		else
		{
			if (Left == NULL)
				t = Right;
			else if (Right == NULL)
				t = Left;
			delete this;
		}
	}
	if (t) t->UpdateHeight();
	return t;
}

#endif