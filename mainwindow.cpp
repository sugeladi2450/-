#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("Game");
    resize(400,400);

    QMenuBar *menuBar = this->menuBar();

    QAction *readFileAction = new QAction("Read File", this);
    menuBar->addAction(readFileAction);

    connect(readFileAction, &QAction::triggered, this, &MainWindow::readFile);

}

MainWindow::~MainWindow() {
    state.clear();
}

void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int n = state.getN();
    if(n <= 0) {
        return;
    }

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

            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 14));

            QString text = QString::number(value);
            QRect rect = painter.boundingRect(j * cellWidth, (n - 1 - i) * cellHeight, cellWidth, cellHeight, Qt::AlignCenter, text);

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


void MainWindow::keyPressEvent(QKeyEvent* event){
    switch(event->key()){
    case Qt::Key_S:
        if(state.step < state.stepsNum()){
            state.swap(state.getStepRow(state.step),state.getStepCol(state.step));
            update();
            state.step++;
        }
        break;
    case Qt::Key_R:
        QMessageBox::information(this, "Message", QString("Point: %1").arg(state.point));
        break;
    }
}

void MainWindow::readFile(){
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Read File",
        "C:/Users/Administrator/Desktop/sep/input",
        "Text Files (*.txt);;Image Files (*.png *.jpg *.jpeg);;All Files (*)"
        );

    if (!filePath.isEmpty()) {
        state.clear();
        state.readFromFile(filePath);
        update();
    } else {
    }
}
