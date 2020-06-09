/*
 * Defination of Point,Map and so on
 * you can call Shortest Path to find the one path by Astar.
 */

#ifndef HEAP_ASTAR_H
#define HEAP_ASTAR_H
#include <iostream>
#include <vector>
#include <list>
using std::vector;
using std::list;
enum TileType{
    walkbale,
    block
};
struct MazeNode{
    int x;
    int y;
    TileType type;
    MazeNode(int x,int y):x(x),y(y),type(walkbale){}
    void setTileType(TileType t){
        this->type = t;
    }

};

struct Point{
    int x,y;
    Point(int x=0,int y=0):x(x),y(y){}
    friend std::ostream& operator<<(std::ostream& out,const Point& p){
        out << "(" << p.x << "," << p.y << ")";
        return out;
    }
    Point& operator=(const Point& p){
        x = p.x;
        y = p.y;
        return *this;
    }
    bool operator==(const Point& p){
        return x == p.x && y == p.y;
    }
    Point operator+(const Point& p){
        Point point;
        point.x = x + p.x;
        point.y = x + p.y;
        return point;
    }
    Point operator-(const Point& p){
        Point point;
        point.x = x - p.x;
        point.y = x - p.y;
        return point;
    }
    
};

bool shortestPath(vector<vector<int>>& map,Point start,Point dest,std::list<Point>& lst);

#endif //HEAP_ASTAR_H
