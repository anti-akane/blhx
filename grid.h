#ifndef GRID_H
#define GRID_H
class grid {
public:
    grid(int x, int y, int state = 0);

    void init(grid *parent, grid *end);

    int getstate();

    int getx();

    int gety();

    int getf();

    grid *getparent();

    void setState(int State);

private:
    int x;
    int y;
    int g;
    int f;
    int h;
    int state;
    grid *parent;
};
#endif // GRID_H
