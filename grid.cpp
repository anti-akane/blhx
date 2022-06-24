#include"grid.h"
#include"math.h"
#include"qdebug.h"
grid::grid(int x,int y,int state):x(x),y(y),state(state) {
    parent = nullptr;
};

void grid::init(grid *parent,grid *end) {
    this->parent = parent;
    //计算g值，即从出发点到达该地的路程
    if (parent == nullptr) {
        this->g = 1;
    } else {
        this->g = parent->g + 1;
    }
    //计算h值，即到达目的地的路程
    this->h = abs(this->x - end->x) + abs(this->y - end->y);
    this->f = this->h + this->g;
}

int grid::getstate() {
    return state;
}

int grid::getx() {
    return x;
}

int grid::gety() {
    return y;
}

int grid::getf() {
    return f;
}

grid* grid::getparent() {
    return parent;
}

void grid::setState(int State)
{
    this->state=State;
}
