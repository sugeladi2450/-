#ifndef STATE_H
#define STATE_H

#include <QPair>
#include <QVector>

class State {
private:
    //请使用这四个变量存储State状态
    int n; // 棋盘行列数
    int left; // 剩余步数
    int point = 0;
    QVector<QVector<int>> board; // 棋盘状态
    QVector<QPair<int, int>> steps; // 剩余移动步骤
public:
    //以下接口请不要修改
    int getV(int i, int j); // 安全地访问board的第i行和第j列的元素
    int applySteps(); // 移动所有的步骤，并返回得分，和更新board
    void readFromFile(QString fileName); // 读取文件
    int getN();
    void eliminate();
    void swap(int i, int j);
    int getStepRow(int step);
    int getStepCol(int step);
    int getLeft(){
        return left;
    };
    int getPoint(){
        return point;
    }
};

#endif // STATE_H
