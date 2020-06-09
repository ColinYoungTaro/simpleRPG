#ifndef __SKILLTREE__
#define __SKILLTREE__

#include "Skill.h"
#include "AvlTree.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::string;

typedef std::string SkillName;
typedef Skill* SkillAttr;


class SkillTree
{
public:
	SkillTree() {
		ifstream fin;
		skillTree = new AvlTree<SkillName, SkillAttr>;
		fin.open("skills.txt");
//		char keyTmp;
		int powerTmp;
		string nameTmp;
		fin >> nameTmp;
		string instructTmp;
		while (fin)
		{
			fin >> powerTmp >> instructTmp;
			Skill* tmpSkill = new Skill(powerTmp, nameTmp,instructTmp);
			skillTree->Insert(instructTmp,tmpSkill);
			fin >> nameTmp;
		}
		fin.close();
	}

	SkillAttr findSkill(SkillName instruct)
	{
		AvlNode<SkillName,SkillAttr> *obj = NULL ;
		obj = skillTree->Find(instruct);
		if (obj) {
			return obj->getVal();
		}
		else {
			return NULL;
		}
		
	}
	//void getAllValue(vector<string,Skill>& skills) {
	//	this->skillTree->getAllValue(skills);
	//}
	AvlTree<SkillName, SkillAttr> *skillTree;
};


#endif 