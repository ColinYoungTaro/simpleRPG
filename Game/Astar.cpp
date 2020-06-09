#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include "DataStructure/heap.h"
#include "Map.h"

using namespace std;

//enumeration of directions
int dirs[8][3] = {
        {1,0,10},
        {-1,0,10},
        {0,1,10},
        {0,-1,10},
        {1,1,14},
        {-1,-1,14},
        {1,-1,14},
        {-1,1,14}
};
struct HeapNode{
    MazeNode maze_node;
    int fx,fy;
    int f,g,h;
    bool vis,inOpen;
    HeapNode():HeapNode(0,0){}
    HeapNode(int x,int y,int fx=-1,int fy=-1)
            :maze_node(MazeNode(x,y)),fx(fx),fy(fy),
             f(0),g(0),h(0),vis(false),inOpen(false){}

    void setFather(int fx,int fy){
        this->fx = fx,this->fy=fy;
    }
    void setgh(int g,int h){
        this->g = g;
        this->h = h;
        f = this->g + this->h;
    }
    bool operator<(const HeapNode& h)const{
        return this->f < h.f;
    }
    bool operator>(const HeapNode& h)const{
        return this->f > h.f;
    }
    bool operator==(const HeapNode& h)const{
        return (h.maze_node.x == this->maze_node.x
                && h.maze_node.y == this->maze_node.y);
    }
};
//heuristic function.
int hval(int sx,int sy,int ex,int ey){
    return (int)(abs(ex-sx)+abs(ey-sy)) * 10 ;
}
class Maze{
public:
    Maze():Maze(-1,-1){}
    Maze(int w,int h):w(w),h(h){
        for(int i = 0; i < w ; i++){
            maze.emplace_back(vector<HeapNode>());
            for(int j = 0 ; j < h; j++){
                maze[i].push_back(HeapNode(i,j));
            }
        }
    }
    MazeNode& getMazeNode(int x,int y){
        return this->maze[x][y].maze_node;
    }
    vector<vector<HeapNode>> maze;
    int w,h;
};

/*
 * The perfect A_star funciton
 */
bool A_star(Maze& maze,int startx, int starty,int endx,int endy){

    Heap<HeapNode> heap;
    HeapNode& tnode = maze.maze[startx][starty];
    int h = hval(startx,starty,endx,endy);
    tnode.setgh(0,h);
    heap.push(tnode);

    while (!heap.empty()){
        
        HeapNode node = heap.pop();
        if(node.maze_node.x == endx && node.maze_node.y == endy){
            return true; // reach the final position.
        }
        int curx =  node.maze_node.x;
        int cury =  node.maze_node.y;

        maze.maze[curx][cury].inOpen = false;

        for(auto & dir : dirs){
            int dx = dir[0];
            int dy = dir[1];
            int dis = dir[2];
            int cx,cy;
            //traverse 8 dirs
            cx = dx + curx;
            cy = dy + cury;
            h = hval(cx,cy,endx,endy);
            if(cx>=0 && cy >= 0 && cx<maze.w && cy < maze.h
               && maze.maze[cx][cy].maze_node.type == walkbale
               && !maze.maze[cx][cy].vis){

                if(maze.maze[cx][cy].inOpen){
                    //update if it is better.
                    if(dis + maze.maze[curx][cury].g < maze.maze[cx][cy].g){
                        HeapNode& n = maze.maze[cx][cy];
                        heap.del(n);
                        n.setFather(curx,cury);
                        n.setgh(dis+maze.maze[curx][cury].g,h);
                        heap.push(n);
                    }
                }
                else{
                    HeapNode& n = maze.maze[cx][cy];
                    n.setFather(curx,cury);
                    n.setgh(dis + maze.maze[curx][cury].g,h);
                    n.inOpen = true;
                    heap.push(n);
                }
            }
        }
		maze.maze[curx][cury].vis = true;
    }
    //is empty:
    return false;
}
/*
 * interface of shortest path
 * input the int type map and two point type positions
 * and append with a linked_list
 * return the result that if it has found a path
 * and the list stores the Point type paths.
 */
bool shortestPath(vector<vector<int>>& map,Point start,Point dest,list<Point>& lst){
    Maze maze(map.size(),map.back().size());
    for(int i = 0 ; i < maze.w ; i++){
        for (int j = 0 ; j < maze.h ; j++){
            TileType t = map[i][j] == 0 ? walkbale : block;
            maze.maze[i][j].maze_node.setTileType(t);
        }
    }
    bool flag = A_star(maze,start.x,start.y,dest.x,dest.y);
    if(!flag)
        return false;
    Point ptr;
    ptr = dest;
    while(!(ptr == start)){
        HeapNode& node = maze.maze[ptr.x][ptr.y];
        lst.push_front(ptr);
        ptr.x = node.fx;
        ptr.y = node.fy;
    }
    return true;
}