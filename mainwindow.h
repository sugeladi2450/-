#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include "State.h"
#include <QFile>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>

class MainWindow: public QMainWindow {
    Q_OBJECT
private:
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    State state;
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void readFile();
};
#endif // MAINWINDOW_H
