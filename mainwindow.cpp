#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("Game");
    resize(400,400);

    QMenuBar *menuBar = this->menuBar();

    QAction *readFileAction = new QAction("Read File", this);
    menuBar->addAction(readFileAction);

    connect(readFileAction, &QAction::triggered, this, &MainWindow::readFile);

}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int n = state.getN();

    int cellWidth = width() / n;
    int cellHeight = height() / n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int value = state.getV(i,j);
            QColor cellColor;
            switch(value){
            case 0: cellColor = Qt::transparent; break;
            case 1: cellColor = Qt::green; break;
            case 2: cellColor = "lightblue"; break;
            case 3: cellColor = QColor(128, 0, 128); break;
            case 4: cellColor = "darkblue"; break;
            case 5: cellColor = Qt::yellow; break;
            }

            painter.fillRect(j * cellWidth, (n - 1 - i) * cellHeight, cellWidth, cellHeight, cellColor);


            // 设置字体
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 14));

            // 计算文本的居中位置
            QString text = QString::number(value);
            QRect rect = painter.boundingRect(j * cellWidth, (n - 1 - i) * cellHeight, cellWidth, cellHeight, Qt::AlignCenter, text);

            // 绘制文本，使其居中
            painter.drawText(rect, Qt::AlignCenter, text);
        }
    }


    painter.setPen(QColor(Qt::black));

    for(int i = 0; i < n; i++){
        painter.drawLine(0, i * cellHeight, width(), i * cellHeight);
    }
    for(int j = 0; j < n; j++){
        painter.drawLine(j * cellWidth, 0, j * cellWidth, height());
    }

}

int step = 0;
void MainWindow::keyPressEvent(QKeyEvent* event){
    switch(event->key()){
    case Qt::Key_S:
        if(step < state.getLeft()){
            state.swap(state.getStepRow(step),state.getStepCol(step));
            update();
            step++;
            break;
        }

    }

}

void MainWindow::readFile(){
    // 这里是“读取文件”的逻辑，示例：打开文件选择对话框
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Read File",          // 对话框标题
        "C:/Users/Administrator/Desktop/sep/input",                   // 默认打开路径（空表示当前工作目录）
        "Text Files (*.txt);;Image Files (*.png *.jpg *.jpeg);;All Files (*)"  // 文件类型过滤
        );

    if (!filePath.isEmpty()) {
        qDebug() << "Selected file:" << filePath;
        // TODO: 在这里添加“读取文件内容并更新界面”的逻辑
        // 例如：解析文件内容，刷新棋盘颜色和数字
    } else {
        qDebug() << "File selection canceled.";
    }

    state.readFromFile(filePath);
    step = 0;
    update();
}

