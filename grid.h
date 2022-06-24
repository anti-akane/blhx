/* * * * * * * * * ** * * * * * * * * *
 * 网格节点类
 * 主要为关卡界面实现自动寻路而实现
 * 也用于实现关卡地图
 * * * * * * * * * * * * * * * * * * * */
#ifndef GRID_H
#define GRID_H
class grid {
public:
    //构造函数
    grid(int x, int y, int state = 0);
    //寻路时初始化
    void init(grid *parent, grid *end);
    //获取该单元格状态
    int getstate();
    //获取坐标横坐标值
    int getx();
    //获取坐标纵坐标值
    int gety();
    //获取节点F值
    int getf();
    //获取该节点的父节点
    grid *getparent();
    //改变节点状态（主要用于战斗胜利后清除该舰队
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
