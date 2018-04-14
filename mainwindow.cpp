#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QKeySequence>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <qdebug.h>
#include "complex.h"
//#include "koch.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "bezier.h"
//#include <QStack> //fillArea
#include <QColor>
#include <QPainterPath>
#include <QImage>
//#include "fillarea.h"
#include <QVector>



#define ROUND(a) ((int)(a + 0.5)) //椭圆中的
#define PI 3.1415926 //PI

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{

    //状态栏
    msgLabel = new QLabel;
    msgLabel -> setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(msgLabel);

    //pushbutton
//    QPushButton *button = new QPushButton(this);//创建按钮
//    button->setObjectName("drawLine");




    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //Bresenham画线
    if(if_drawline== false)
    {
        QPainter painter(this);
    //    painter.drawLine(QPointF(1,1), QPointF(100,100));

        qDebug()<<if_drawline;
        int x0, y0, xEnd, yEnd;
        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        QPen pen(Qt::red, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        x0 = 10;// ui-> x->text().toInt();
        y0 = 10;//ui-> y->text().toInt();
        xEnd = 290;//ui->x1->text().toInt();
        yEnd = 290;//ui->y2->text().toInt();
        int x,y,dx,dy,e;
        float k;
        dx=xEnd-x0;
        dy=yEnd-y0;
        k=(float)dy/dx;
        e=-dx;x=x0;y=y0;
        if(k >= 0||k <= 1)
        {
            while (x <= xEnd) {
                painter.drawPoint(QPoint(x+100, y+100));
                x++;
                e = e + 2*dy;
                if(e > 0)
                {
                    y++;
                    e = e - 2*dx;
                }
            }
        }
        else if(k >= 1)
        {
            while (y <= yEnd) {
                painter.drawPoint(QPoint(x+100, y+100));
                y++;
                e = e + 2*dx;
                if(e >0)
                {
                    x++;
                    e = e - 2*dy;
                }
            }
        }

        qDebug()<<"L";//疯狂输出 已解决，原因为没有初始化

    }

    //Bresenham画圆 中点画圆
    if(if_drawcircle == true)
    {
        QPainter painter(this);
    //    painter.drawLine(QPointF(1,1), QPointF(100,100));


        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        QPen pen(Qt::red, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        int xCenter = 250;//圆心
        int yCenter = 250;
        int radius = 200;//半径
        int x = 0;
        int y = radius;
        int p = 1 - radius;
        painter.drawPoint(QPoint(250, 450));

        //painter.drawPoint(QPoint(252, 450));

        while (x < y) {
            x++;
            if(p < 0)
            {
                p += 2*x + 1;
                painter.drawPoint(QPoint(xCenter + x, yCenter + y));//画点
                painter.drawPoint(QPoint(xCenter - x, yCenter + y));
                painter.drawPoint(QPoint(xCenter - x, yCenter - y));
                painter.drawPoint(QPoint(xCenter + x, yCenter - y));
                painter.drawPoint(QPoint(xCenter + y, yCenter + x));
                painter.drawPoint(QPoint(xCenter - y, yCenter + x));
                painter.drawPoint(QPoint(xCenter - y, yCenter - x));
                painter.drawPoint(QPoint(xCenter + y, yCenter - x));
            }
            else {
                y--;
                p += 2*(x - y) + 1;
                painter.drawPoint(QPoint(xCenter + y, yCenter + x));//画点
                painter.drawPoint(QPoint(xCenter - y, yCenter + x));
                painter.drawPoint(QPoint(xCenter - y, yCenter - x));
                painter.drawPoint(QPoint(xCenter + y, yCenter - x));
                painter.drawPoint(QPoint(xCenter + x, yCenter + y));
                painter.drawPoint(QPoint(xCenter - x, yCenter + y));
                painter.drawPoint(QPoint(xCenter - x, yCenter - y));
                painter.drawPoint(QPoint(xCenter + x, yCenter - y));
            }
        }
        qDebug()<<"C";
    }

    //椭圆中点算法
    if(if_drawellipse == true)
    {
        int Rx = 150;//顶点
        int Ry = 200;
        int xCenter = 250; //椭圆中心
        int yCenter = 250; //
        int Rx2 = Rx * Rx;
        int Ry2 = Ry * Ry;
        int twoRx2 = 2 * Rx2;
        int twoRy2 = 2 * Ry2;
        int p;
        int x = 0;
        int y = Ry;
        int px = 0;
        int py = twoRx2 * y;
        QPainter painter(this);
        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        QPen pen(Qt::red, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        p = ROUND(Ry2 - (Rx2 * Ry) + (0.25 *Rx2));

//        painter.drawPoint(QPoint(300, 300));

        //Region 1
        while (px < py) {
            x++;
            px += twoRy2;
            if(p < 0)
            {
                p += Ry2 + px;
                painter.drawPoint(QPoint(xCenter + x, yCenter + y));//画点
                painter.drawPoint(QPoint(xCenter - x, yCenter + y));
                painter.drawPoint(QPoint(xCenter + x, yCenter - y));
                painter.drawPoint(QPoint(xCenter - x, yCenter - y));
            }
            else {
                y--;
                py -= twoRx2;
                p += Ry2 + px - py;
                painter.drawPoint(QPoint(xCenter + x, yCenter + y));//画点
                painter.drawPoint(QPoint(xCenter - x, yCenter + y));
                painter.drawPoint(QPoint(xCenter + x, yCenter - y));
                painter.drawPoint(QPoint(xCenter - x, yCenter - y));
            }
        }

        //Region 2
        p = ROUND(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
        while (y > 0) {
            y--;
            py -= twoRx2;
            if(p > 0)
            {
                p += Rx2 - py;
                painter.drawPoint(QPoint(xCenter + x, yCenter + y));//画点
                painter.drawPoint(QPoint(xCenter - x, yCenter + y));
                painter.drawPoint(QPoint(xCenter + x, yCenter - y));
                painter.drawPoint(QPoint(xCenter - x, yCenter - y));
            }
            else {
                x++;
                px += twoRy2;
                p += Rx2 - py + px;
                painter.drawPoint(QPoint(xCenter + x, yCenter + y));//画点
                painter.drawPoint(QPoint(xCenter - x, yCenter + y));
                painter.drawPoint(QPoint(xCenter + x, yCenter - y));
                painter.drawPoint(QPoint(xCenter - x, yCenter - y));
            }
        }
        qDebug()<<"E";
    }

    //fillArea
    /*if(if_fillarea == true)
    {
        QPainter painter(this);

        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        //QPen pen(Qt::red, 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        //painter.setPen(pen);
        //painter.drawPolygon(points, 6);

        //qDebug()<<QPoint(40,200);

        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        QPen pen1(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen1);


        //update();
        //fillarea.startPoint = fillarea.endPoint;
        //line->startPoint = points[0]
        qDebug()<<fillarea.lines.size();
        qDebug()<<"line.size";
        fillarea.generatePoints();
        //qDebug()<<1;
       // painter.drawPolygon(fillarea.ctrlPoints);
        //qDebug()<<fillarea.curvePoints;
        //qDebug()<<fillarea.curvePoints.size();
        for(int i=0;i<fillarea.curvePoints.size();i++){

        painter.drawPoint(fillarea.curvePoints[i]);

        }
        //painter.drawPoints(fillarea.generatePoints());

        //if(!polygon.isEmpty() && scanlines.isEmpty())
       // {
       //     scanlines = getScanlines(polygon);
        //    qDebug()<<"new scanlines";
        //}
        //painter.drawLines(scanlines);


        /*
        QPainter p{this};
        if (false) p.setRenderHint(QPainter::Antialiasing);
        p.setPen("cadetblue");
        if (!polygon.isEmpty() && scanlines.isEmpty()) {
           scanlines = getScanlines(polygon);
           qDebug() << "new scanlines";
        }
        p.drawLines(scanlines);
        if (outline.isChecked()) {
           p.setPen("orangered");
           p.setBrush(Qt::NoBrush);
           p.drawPolygon(polygon);
        }
        if (!lastPoint.isNull()) {
           p.setPen("navy");
           p.drawEllipse(lastPoint, 3, 3);
        }
     }*/




        //qDebug()<<"fA";
    //}

    //Bezier曲线
    if(if_bezier == true)
    {
        //QPainter painter(this);
        QPainter *painter = new QPainter(this);
        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        QPen pen1(Qt::darkBlue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        //painter.setPen(pen1);
        Bezier<QPointF>  *bezier;// = new Bezier<QPointF>;
        bezier = new Bezier<QPointF>();
        QPointF p[3];
        p[0] = QPointF(100,100);
        p[1] = QPointF(500,400);
        p[2]  = QPointF(100,500);
        painter->setPen(pen);
        painter->drawLine(p[0],p[1]);
        painter->drawLine(p[1],p[2]);
        bezier->appendPoint(p[0]);
        bezier->appendPoint(p[1]);
        bezier->appendPoint(p[2]);

        QPainterPath path = bezier->getPainterPath();
        painter->setPen(pen1);
        painter->drawPath(path);
        delete painter;

        qDebug()<<"Be";
    }

    //B样条
    if(if_b == true)
    {
        QPainter painter(this);
        int ctrlpoint_num = 6; //控制点数
        int points_num = 100; //曲线上点数
        int px[] = {30, 140, 380, 460, 540, 550};//控制点
        int py[] = {350, 240, 150, 260, 450, 150};
        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        //QPen pen1(Qt::darkBlue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

        QPainterPath path;
        path.moveTo(px[0], py[0]);
        for(int i = 0; i < ctrlpoint_num; i++)
        {
            path.lineTo(px[i], py[i]);
            painter.drawPath(path);
            painter.setPen(pen);
        }

        float T[ctrlpoint_num + 4];
        for(int i = 0; i < ctrlpoint_num + 4; i++)
            T[i] = i;
        float pointsX[ctrlpoint_num + 3][4], pointsY[ctrlpoint_num + 3][4];
        bool first = true;
        for(int i = 3; i < ctrlpoint_num; i++)
        {
            float delta = (T[i + 1] - T[i])/points_num;
            for(float t=T[i]; t<=T[i+1]; t+=delta)
            {
                for(int k=0; k<=3; k++)
                {
                    for(int j=i-3+k; j<=i; j++)
                    {
                    if(k==0)
                    {
                        pointsX[j][k] = px[j];
                        pointsY[j][k] = py[j];
                    }
                    else
                    {
                        float alpha = (t-T[j]) / (T[j+4-k]-T[j]);
                        pointsX[j][k] = (1.0 - alpha) * pointsX[j-1][k-1] + alpha * pointsX[j][k-1];
                        pointsY[j][k] = (1.0 - alpha) * pointsY[j-1][k-1] + alpha * pointsY[j][k-1];
                        if(j == i && k == 3)
                        {
                            if(first)
                            {
                                path.moveTo(pointsX[j][3], pointsY[j][3]);
                                painter.setPen(pen);
                                painter.drawPath(path);
                            }
                            else
                            {
                                path.lineTo(pointsX[j][3], pointsY[j][3]);
                                painter.setPen(pen);
                                painter.drawPath(path);
                            }
                            first = false;
                        }
                    }
                    }
                }
            }
        }


        qDebug()<<"B_s";
    }

    //Koch 曲线
    if(if_koch == true)
    {
        QPainter painter(this);

        QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        koch.ctrlPoints.push_back(QPointF(40,400));
        koch.ctrlPoints.push_back(QPointF(600,400));
        for (int i = 0; i < koch.ctrlPoints.size()-1; i++){
            koch.generateKoch(koch.ctrlPoints[i], koch.ctrlPoints[i + 1]);

            //koch.curvePoints1.clear();
            koch.k = 0;
        }
        for (int i = 0; i<koch.curveLine.size(); i++)
        {
            painter.drawLine(koch.curveLine[i]);
        }

    }


    //Mandelbrot Set
    if(if_mandelbrot == true)
    {
        QSize size = this->size();
        double width = size.width()/2;//横向位置
        double height = size.height()/2; //纵向位置
        double scale = 2; //放缩倍数，越小图越大
        int const max_time = 100;
        QPainter painter(this);
        QPen pen1;
        for(int a =- width; a <= width; a++)
        {
            for(int b =- height; b <= height; b++ )
            {
                int times = max_time;
                idComplex c0(a/width*scale, b/height*scale); //Mandelbrot 原
                idComplex c1(0, 0);// = c0;

                while(times--)
                {
                      c1 = c1 * c1 + c0;
                      if(c1.Operatmod() > 2)
                          break;
                }
                times = times < 0 ? 0 : times;
                //if(times>99){pen1.setColor(QColor(255, 255, 255, 255));}
                //else if(times>95){pen1.setColor(QColor(255, 255, 255, 255));}

                int gray = 255*times/max_time;

                //画刷，线宽，画笔风格，画笔端点，画笔连接风格
                painter.setPen(QPen(QColor(gray, gray, gray, 255)));

                int     x = a + width;
                int     y = b + height;
                painter.drawPoint(x,y);
            }
       }
       qDebug()<<"M"; //疯狂输出 已解决，原因为没有初始化
    }

    //Julia Set
    if(if_julia == true)
    {

        QPainter painter(this);
        QSize size = this->size();
        double width = size.width()/3; //调横向位置
        double height = size.height()/2; //调纵向位置
        double scale = 1.5; //放缩倍数，越小图越大
        int const max_time = 100;

        for(int a =- width; a <= width; a++)
        {
            for(int b =- height; b <= height; b++ )
            {
                int times = max_time;
                idComplex c1(a/width*scale, b/height*scale); //Julia
//                idComplex c0(0.285,0.001);
//                idComplex c0(-0.8,0.156);
//                idComplex c0(-0.7,-0.38);
//                idComplex c0(0.45,-0.14);
                idComplex c0(0.4,0.3);

                while(times--)
                {
                      c1 = c1 * c1 + c0;
                      if(c1.Operatmod() > 2)
                          break;
                }
                times = times < 0 ? 0 : times;
                int gray = 255*times/max_time;

                //画刷，线宽，画笔风格，画笔端点，画笔连接风格
                painter.setPen(QPen(QColor(gray, gray, gray, 255)));

                int     x = a + width;
                int     y = b + height;
                painter.drawPoint(x,y);
            }
        }

        qDebug()<<"J"; //疯狂输出 已解决，原因为没有初始化
    }

    //蕨类植物
    if(if_fern == true)
    {
        QPainter painter(this);
        QSize size = this->size();
        double width = size.width();
        double height  = size.height();
        unsigned long iter = 500000;// 迭代次数
        double x0 = 0, y0 = 0, x1, y1;
        int xp = 70;//x方向缩放参数
        int yp = 50;//y方向缩放参数
        int diceThrow;
        //timer_t t;
        //srand((unsigned)time(&t));
        //画刷，线宽，画笔风格，画笔端点，画笔连接风格
        QPen pen(Qt::darkGreen, 1.5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);

        while (iter > 0) {
            diceThrow = rand()%100;

            if(diceThrow == 0)
            {
                x1 = 0;
                y1 = 0.16 * y0;
            }
            else if(diceThrow >= 1 && diceThrow <= 7)
            {
                x1 = -0.15 * x0 + 0.28 * y0;
                y1 = 0.26 * x0 + 0.24 * y0 + 0.44;
            }
            else if(diceThrow>=8 && diceThrow<=15){
                x1 = 0.2 * x0 - 0.26 * y0;
                y1 = 0.23 * x0 + 0.22 * y0 + 1.6;
            }

            else{
                x1 = 0.85 * x0 + 0.04 * y0;
                y1 = -0.04 * x0 + 0.85 * y0 + 1.6;
            }

            x0 = x1;
            y0 = y1;
            iter--;
            painter.drawPoint(QPoint(xp * x1 + width/3, yp * y1 + height/6));

        }

    }
}



//判定参数
//图元
//直线判定
void MainWindow::on_drawLine_clicked()
{
    if_drawline = !ui->drawLine->isChecked();
//    qDebug()<<if_drawline;
//   close();
    qDebug()<<"line";
    update();
}

//圆判定
void MainWindow::on_drawCircle_clicked()
{
    if_drawcircle = ui->drawCircle->isChecked();
//    close();
    qDebug()<<"circle";
    update();
}

//椭圆判定
void MainWindow::on_drawEllipse_clicked()
{
    if_drawellipse = ui->drawEllipse->isChecked();
    qDebug()<<"ellipse";
    //close();
    update();
}

//区域填充
void MainWindow::on_fillArea_clicked()
{
    if_fillarea = ui->fillArea->isChecked();
//    fillarea.s = 0;
    /*myLine* firstline = MainWindow.fillarea.lines[0];
    myLine* line = new myLine;
    line->endPoint = firstline->startPoint;
    line->startPoint = MainWindow->fillarea.endPoint;
    MainWindow->fillarea.lines.push_back(line);
    MainWindow->fillarea.s = 2;
    MainWindow->generateCurve();
    MainWindow->update();*/
    qDebug()<<"fillArea";
    update();
}

//样条曲线
//Bezier样条
void MainWindow::on_BezierSpline_clicked()
{
    if_bezier = ui->BezierSpline->isChecked();
    qDebug()<<"Bezier";
    update();
}

//B样条
void MainWindow::on_B_Spline_clicked()
{
    if_b = ui->B_Spline->isChecked();
    qDebug()<<"B_Spline";
    update();
}

//分形
//Koch曲线
void MainWindow::on_Koch_clicked()
{
    if_koch = ui->Koch->isChecked();
    qDebug()<<"koch";
    //ctrlPoints.clear();
    //drawKoch = ui->checkBox_7->isChecked();
    koch.ctrlPoints.clear();
    koch.curveLine.clear();
    //generateCurve();
    //update();
    update();
}

//Mandelbrot集 书上有 p303
void MainWindow::on_Mandelbrot_clicked()
{
    if_mandelbrot = ui->Mandelbrot->isChecked();
    qDebug()<<"Mandelbrot";
    qDebug()<<if_mandelbrot;
    update();
}

//Julia集 书上有 p300
void MainWindow::on_Julia_clicked()
{
    if_julia = ui->Julia->isChecked();
    qDebug()<<"Julia";
    qDebug()<<if_julia;
    update();
}

//蕨类植物
void MainWindow::on_fern_clicked()
{
    if_fern = ui->fern->isChecked();
    qDebug()<<"fern";
    update();
}

//Koch函数
/*void MainWindow::drawKoch(QPainter* painterk)
{
    vector<vector<myLine*>> Koch;
    vector<myLine*> lines;
    for(int i = 0; i < points.size(); i+=2)
    {
        myLine *kline = new myLine;
        kline->startPoint = *points[i - 1];
        kline->endPoint = *points[i];
        lines.push_back(kline);
    }
    Koch.push_back(lines);
    int k = 0;
    for(int i = 0; i < d; i++)
    {
        vector<myLine*> K;
        for(int j = 0; j < Koch[i].size(); j++) //输入"."后没有跳出size()
        {
            double startx = (double)(Koch[i][j]->startPoint.x());
            double starty = (double)(Koch[i][j]->startPoint.y());
            double endx0 = (double)(Koch[i][j]->endPoint.x());
            double endy0 = (double)(Koch[i][j]->endPoint.y());

            double ax = startx*2/3 + endx0/3;
            double ay = starty*2/3 + endy0/3;
            double cx = startx/3 + endx0*2/3;
            double cy = starty/3 + endx0*2/3;
            double bx = ax/2 + cx/2 + sqrt(3)/2*(cy - ay);
            double by = ay/2 + cy/2 + sqrt(3)/2*(ax - cx);

            QPoint *P1 = new QPoint, *P2 = new QPoint, *P3 = new QPoint;
            P1->setX((int)(ax + 0.5));
            P1->setY((int)(ay + 0.5));
            P2->setX((int)(bx + 0.5));
            P2->setY((int)(by + 0.5));
            P3->setX((int)(cx + 0.5));
            P3->setY((int)(cy + 0.5));
            myLine *L1 = new myLine, *L2 = new myLine, *L3 = new myLine, *L4 = new myLine;

            L1->endPoint.setX(P1->x());
            L1->endPoint.setY(P2->y());
            K.push_back(L2);
            L2->startPoint.setX(P1->x());
            L2->startPoint.setY(P1->y());
            L2->endPoint.setX(P2->x());
            L2->endPoint.setY(P2->y());
            K.push_back(L2);
            L3->startPoint.setX(P2->x());
            L3->startPoint.setY(P2->y());
            L3->endPoint.setX(P2->x());
            L3->endPoint.setY(P3->y());
            K.push_back(L3);
            L4->startPoint.setX(P3->x());
            L4->startPoint.setY(P3->y());
            L4->endPoint.setX(Koch[i][j].endPoint.x());
            L4->endPoint.setY(Koch[i][j].endPoint.y());
            K.push_back(L4);

        }
        Koch.push_back(K);
        k++
    }

    for(int i = 0; i < Koch[k].size();i++)
    {
        myLine* kLine = Koch[d][i];
        QPoint P0 = kLine->startPoint, Pend = kLine->endPoint;
        int x0 = P0.x(), y0 = P0.y(), xend = Pend.x(), yend = Pend.y();
        int w = 0;
        if(x0 == xend && y0 == yend)
            painterk->drawPoint(x0,y0);
        else if(x0 == xend)
        {
            if(yend < y0)
            {
                int r = yend;
                yend = y0;
                y0 = r;
            }
            for(int yk = y0; yk <= yend; yk++)
            {
                painterk->drawPoint(x0, yk);
            }
        }
        else if(y0 == yend)
        {
            if(xend < x0)
            {
                int r = xend;
                xend = x0;
                x0 = r;
            }
            for(int xk = x0; xk <= xend; xk++)
                painterk->drawPoint(xk, y0);
        }
        else
        {
            if(abs(((double)yend - (double)y0)/((double)xend - (double)x0)) > 1)
            {
                int m0 = x0;
                int mend = xend;
                x0 = y0;
                xend = yend;
                y0 = m0;
                yend = mend;
                w = 1;
            }
            if(xend < x0)
            {
                int xm = x0, ym = y0;
                x0 = xend;
                y0 = yend;
                xend = xm;
                yend = ym;
            }
            int dx = xend - x0;
            int dy = yend - y0;
            int a, b, c, d, P;
            if(dy > 0)
            {
                a = 0;
                b = 1;
                c = 2*dy;
                d = c - 2*dx;
                P = 2*dy - dx;
            }
            else {
                a = -1;b = 0;c = 2*dy + 2*dx;
                d = 2*dy; P = 2*dy + dx;
            }
            vector<int> x, y;
            x.push_back(x0);
            y.push_back(y0);
            for(int j = 1; j < dx + 1; j++)
            {
                x.push_back(y[j - 1] + a);
                if(P <= 0)
                {
                    y.push_back(y[j-1] + a);
                    P += c;
                }
                else {
                    y.push_back(y[j-1] + b);
                    P += d;
                }
            }
            for(int k = 0; k < dx + 1; k++)
            {
                if(w == 1)
                    painterk->drawPoint(y[k],x[k]);
                else {
                    painterk->drawPoint(x[k], y[k]);
                }
            }

        }

    }
*/


   /*int c = 100;
   double cx, cy, dx, dy, ex, ey;
   double l, alfa;
   cx = ax + (bx - ax)/3;
   cy = ay + (by - ay)/3;
   ex = bx - (bx - ax)/3;
   ey = by - (by - ay)/3;
   drawKoch(ax, ay, bx, by);
   drawKoch(ex, ey, bx, by);
   l = sqrt((ex - cx) * (ex - cx) + (ey - cy) * (ey - cy));
   alfa = atan((ey - cy)/(ex - cx));
   if(alfa >= 0 && (ex - cx) < 0 || alfa < 0 && (ex - cx < 0))
       alfa = alfa + PI;
   dx = cx + cos(alfa + PI/3) * l;
   dy = cy + sin(alfa + PI/3) * l;
   drawKoch(cx, cy, dx, dy);
   drawKoch(dx, dy, ex, ey);*/
//}



