#include <cstdio>
#include <QDebug>
#include <QFile>
#include "state.h"

int State::getV(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= n) {
        return -1;
    }
    return board[i][j];
}

int State::applySteps() {
    //TODO: 请在此添加你的代码

    return 0;

}

void State::readFromFile(QString fileName) {
    //TODO: 请在此添加你的代码
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList list = line.split(' ');
    if(list.size() == 2 ){
        n = list[0].toInt();
        left = list[1].toInt();
    }

    board.resize(n);
    for(int i = 0; i < n; i++){
        board[i].resize(n);
    }

    for(int i = n - 1; i >= 0; i--){
        QString line = in.readLine();
        QStringList list = line.split(" ");
        for(int j = 0; j < n; j++){
            board[i][j] = list[j].toInt();
        }
    }

    steps.resize(left);
    for(int i = 0; i < left; i++){
        QString line = in.readLine();
        QStringList list = line.split(" ");
        steps[i].first = list[0].toInt();
        steps[i].second = list[1].toInt();
    }

}

int State::getN(){
    return n;
}

void State::eliminate(){
    QVector<QVector<bool>> b(n, QVector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 2; j++){
            if(board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2]){
                b[i][j] = true;
                b[i][j + 1] = true;
                b[i][j + 2] = true;

            }
        }
    }

    for(int i = 0; i < n - 2; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j]){
                b[i][j] = true;
                b[i + 1][j] = true;
                b[i + 2][j] = true;

            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(b[i][j]){
                board[i][j] = 0;
            }
        }
    }


}

void State::swap(int i, int j){
    if(j < n - 1){
    int temp = board[i][j];
    board[i][j] = board[i][j + 1];
    board[i][j + 1] = temp;
    }
    eliminate();
    bool flag = false;
    while(!flag){
        flag = true;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i < n - 1 && board[i][j] == 0 && board[i + 1][j] != 0){
                   board[i][j] = board[i + 1][j];
                   board[i + 1][j] = 0;
                   flag = false;
                }
            }
        }
        eliminate();
    }
}

int State::getStepRow(int step){
    return steps[step].first;
}

int State::getStepCol(int step){
    return steps[step].second;
}
