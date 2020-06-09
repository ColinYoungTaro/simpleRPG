#pragma once
// 游戏常量定义，全局的变量声明在这里
namespace Game {
	const int tw = 32;
	const int th = 32;
	const int spriteW = 32;
	const int spriteH = 48;
	const int walkable = 0;
	const int block = 1;
	const int divdly = 15;
}
namespace Dir{
	const int left	= 1;
	const int right = 2;
	const int down	= 0;
	const int up	= 3;
}

using RoleState = int;