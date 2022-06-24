#include"levelMap.h"
#include"qdebug.h"
enum GridState { blank = 0, wall, enemy };
levelMap::levelMap(int row, int col, int stateMap[20][20]) :row(row), col(col) {
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++) {
            Map[i][j] = new grid(j, i, stateMap[i][j]); 
        }
}
//寻路算法
QStack<grid *>levelMap::search(grid *start, grid*end) {
    QVector < grid * > openlist;
    QVector < grid * > closelist;
this->goal=new grid(end->getx(),end->gety(),1);
    openlist.push_back(start);
    bool flag = 1;
    //迭代访问Open_list中的所有元素，直到Open_list为空，或者end节点存在于Open_list中时，才停止迭代
    while (!openlist.empty()) {
        if (!flag)
            break;
        //每次迭代开始时都选择F值最小的那个节点作为current节点
        int currentindex = findMinGrid(openlist);
        grid *currentgrid = openlist[currentindex];
        //将current节点从Open_list移到Close_list，避免while循环变成死循环
        closelist.push_back(openlist[currentindex]);
        openlist.erase(openlist.begin() + currentindex);
        QVector < grid * > neighbors = findNeighbors(currentgrid, openlist, closelist);
        for (auto v: neighbors) {
            if (!iscontain(openlist, currentgrid->getx(), currentgrid->gety())) {
                 //如果当前neighbor节点不在open_list则将其放入open_list
                v->init(currentgrid, end);
                openlist.push_back(v);
            }
        }

        for (auto v: openlist) {
            /*如果当前neighbor节点已存在于open_list，并且它通过current节点
            到达start节点的G值小于其本身原有的G值，则将这个neighbor节点的Father节点改成current节点，并刷新G值、H值、F值。否则什么都不做。*/
            if ((v->getx() == end->getx()) && (v->gety() == end->gety())) {
                end->init(v->getparent(), end);
                flag = 0;
            }
        }
    }
    grid *tempgrid = end;
    QStack < grid * > path;
    while (tempgrid->getparent() != nullptr) {
        path.push(tempgrid);
        tempgrid = tempgrid->getparent();
    }
    return path;
}

QVector<grid *>levelMap::findNeighbors(grid* node, QVector<grid*>openlist, QVector<grid*>closelist) {
    QVector < grid * > neighbors;
    //寻找该节点附近节点并试图加入openlist
    if (check(node->getx() + 1, node->gety(), openlist, closelist)) {
        neighbors.push_back(new grid(node->getx() + 1, node->gety(), Map[node->gety()][node->getx() + 1]->getstate()));
    }
    if (check(node->getx() - 1, node->gety(), openlist, closelist)) {
        neighbors.push_back(new grid(node->getx() - 1, node->gety(), Map[node->gety()][node->getx() - 1]->getstate()));
    }
    if (check(node->getx(), node->gety() + 1, openlist, closelist)) {
        neighbors.push_back(new grid(node->getx(), node->gety() + 1, Map[node->gety() + 1][node->getx()]->getstate()));
    }
    if (check(node->getx(), node->gety() - 1, openlist, closelist)) {
        neighbors.push_back(new grid(node->getx(), node->gety() - 1, Map[node->gety() - 1][node->getx()]->getstate()));
    }
    return neighbors;
}

bool levelMap::check(int x, int y, QVector<grid*>openlist, QVector<grid*>closelist) {
    //检查该节点是否合法
    if (x > col || x <= 0)
        return false;
    if (y > row || y <= 0)
        return false;
    if (Map[y][x]->getstate()>0)
    {
        if(Map[y][x]->getstate()==1)
        return false;
        else if(Map[y][x]->getstate()>1&&!(goal->getx()==x&&goal->gety()==y))//若经过节点为敌人但为目的地，则依旧前进
        return false;
    }
    if (iscontain(openlist, x, y))
        return false;
    if (iscontain(closelist, x, y))
        return false;
    return true;
}

bool levelMap::iscontain(QVector<grid*>list, int x, int y) {
    for (auto v: list) {
        if (v->getx() == x && v->gety() == y)
            return true;
    }
    return false;
}

int levelMap::findMinGrid(QVector<grid*>openlist) {
    if (openlist.empty())
        return -1;
    grid *tempgrid = openlist[0];
    int index = 0;
    for (int i = 0; i < openlist.size(); i++) {
        if (tempgrid->getf() > openlist[i]->getf()) {
            tempgrid = openlist[i];
            index = i;
        }
    }
    return index;
}

void levelMap::setState(int x, int y, int state)

{
    Map[y][x]->setState(state);
}

int levelMap::getState(int x,int y)
{
    return Map[y][x]->getstate();
}
