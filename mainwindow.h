#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include "koch.h"
//#include "fillarea.h"
#include <QPoint>
#include <QPointF>
#include <QVector>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <fillarea.h>
#include <iostream>
#include <QtGui>
#include <cmath>
#include <QtWidgets/QApplication>
#include <QObject>

//#include <QDoubleSpinBox>
//#include <QPixmap>
using namespace std;
typedef struct myLine{
    QPoint startPoint;
    QPoint endPoint;
}myLine;
//class QDoubleSpinBox;
//class QPixmap;
class QAction; //前向声明
class QLabel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /*QPointF lastPoint;
    QPolygonF polygon;
    LineVector scanlines;
    QGridLayout layout{this};
    QPushButton reset{"Reset"};
    QCheckBox outline{"Outline"};*/

public:
    explicit MainWindow(QWidget *parent = 0);
    Koch koch;
    //void drawKoch;
    //fillArea fillarea;
    //QVector points;
    ~MainWindow();

//判定参数
private:
    bool if_drawline = true;
    bool if_drawcircle = false;
    bool if_drawellipse = false;
    bool if_drawcurve = false;
    bool if_fillarea = false;
    bool if_bezier = false;
    bool if_b = false;
    bool if_koch = false;
    bool if_mandelbrot = false;
    bool if_julia = false;
    bool if_fern = false;

//自动连接信号
private slots:

    void on_drawLine_clicked();



    void on_drawCircle_clicked();

   // void on_drawEllipse_clicked(bool checked);

    void on_drawEllipse_clicked();

    void on_fillArea_clicked();

    void on_BezierSpline_clicked();

    void on_B_Spline_clicked();

    void on_Koch_clicked();

    void on_Mandelbrot_clicked();

    void on_Julia_clicked();

    void on_fern_clicked();

    //void updater();

private:
    Ui::MainWindow *ui;

private:
    QAction *openAction;

private:
    QLabel *msgLabel;

protected:
    void paintEvent(QPaintEvent *);

};


#endif // MAINWINDOW_H
