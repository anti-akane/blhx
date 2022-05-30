#include"grid.h"
#include"math.h"
grid::grid(int x,int y,int state):x(x),y(y),state(state) {
    parent = nullptr;
};

void grid::init(grid *parent,grid *end) {
    this->parent = parent;
    if (parent == nullptr) {
        this->g = 1;
    } else {
        this->g = parent->g + 1;
    }
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
