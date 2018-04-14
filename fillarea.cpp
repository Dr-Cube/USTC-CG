#include "fillarea.h"

fillArea::fillArea(QObject *parent)
    : QObject(parent)
{

}

fillArea::~fillArea()
{

}
fillArea::fillArea()
{

}
void fillArea::generatePoints(){
    qDebug()<<lines.size();
    qDebug()<<"dadadqqqqqqq";
    static const QPoint points[6] = {QPoint(40,200), QPoint(80,470), QPoint(270, 300),
                                     QPoint(420,540), QPoint(500,190), QPoint(260, 30)};
    ctrlPoints.push_back(points[0]);
    ctrlPoints.push_back(points[1]);
    ctrlPoints.push_back(points[2]);
    ctrlPoints.push_back(points[3]);
    ctrlPoints.push_back(points[4]);
    ctrlPoints.push_back(points[5]);

    myLine* line = new myLine;

    for(int i = 0; i <= 4; i++)
    {
        line->startPoint = points[i];
        line->endPoint = points[i+1];
        this->lines.push_back(line);
        //update();
    }
    line->startPoint=points[5];
    line->endPoint=points[0];
    this->lines.push_back(line);
    for (int i = 0; i < lines.size();i++){
        myLine* pLine = lines[i];
        QPoint P0 = pLine->startPoint, Pend = pLine->endPoint;
        int x0 = P0.x(), y0 = P0.y(), xend = Pend.x(), yend = Pend.y(), w = 0;
        if (x0 == xend&&y0 == yend)
        {
            curvePoints.push_back(QPoint(x0, y0));
        }
        else if (x0==xend)
        {
            if (yend < y0){
                int r = yend;
                yend = y0, y0 = r;
            }
            for (int yk = y0; yk <= yend; yk++)
            {
                curvePoints.push_back(QPoint(x0, yk));
            }
        }
        else if (y0 == yend)
        {
            if (xend<x0)
            {
                int r = xend;
                xend = x0, x0 = r;
            }
            for (int xk = x0; xk <= xend; xk++)
            {
                curvePoints.push_back(QPoint(xk, y0));
            }
        }
        else{
            if (abs(((double)yend - (double)y0) / ((double)xend - (double)x0))>1)
            {
                int m0 = x0, mend = xend;
                x0 = y0, xend = yend, y0 = m0, yend = mend, w = 1;
            }
            if (xend<x0)//如果终点在起点的左端
            {
                int xm = x0, ym = y0;
                x0 = xend, y0 = yend, xend = xm, yend = ym;//交换起点和终点
            }
            int dx = xend - x0, dy = yend - y0, a, b, c, d, P;
            if (dy>0)
            {
                a = 0, b = 1, c = 2 * dy, d = c - 2 * dx, P = 2 * dy - dx;
            }
            else{
                a = -1, b = 0, c = 2 * dy + 2 * dx, d = 2 * dy, P = 2 * dy + dx;
            }
            vector<int> x, y;
            x.push_back(x0);
            y.push_back(y0);
            for (int j = 1; j<dx + 1; j++)
            {
                x.push_back(x[j - 1] + 1);
                if (P <= 0)
                {
                    y.push_back(y[j - 1] + a);
                    P += c;
                }
                else
                {
                    y.push_back(y[j - 1] + b);
                    P += d;
                }
            }
            for (int k = 0; k<dx + 1; k++)
            {
                if (w == 1)
                {
                    curvePoints.push_back(QPoint(y[k], x[k]));
                }
                else{
                    curvePoints.push_back(QPoint(x[k], y[k]));

                }

            }
        }
    }
    if (s == 0)
    {
        vector<int> Ystart, Yend, Xstart, Ystart1, Yend1;
        vector<double> f;
        int ymin, ymax, si = 0;
        for (int i = 0; i<lines.size(); i++){//逐条线段循环1
            myLine* pLine = lines[i];
            QPoint P0 = pLine->startPoint, Pend = pLine->endPoint;
            int x0 = P0.x(), y0 = P0.y(), xend = Pend.x(), yend = Pend.y();
            if (y0 != yend){//非水平直线
                Ystart.push_back(y0);//线段起点纵坐标
                Yend.push_back(yend);//线段终点纵坐标
                if (y0<yend)
                {
                    Xstart.push_back(x0);//线段下端点横坐标
                    if (i == 0)
                    {
                        ymin = y0;
                        ymax = yend;
                    }
                    else
                    {
                        if (y0<ymin)
                        {
                            ymin = y0;
                        }
                        if (yend>ymax)
                        {
                            ymax = yend;
                        }
                    }
                }//y0<yend
                else
                {
                    Xstart.push_back(xend);
                    if (i == 0)
                    {
                        ymin = yend;
                        ymax = y0;
                    }
                    else
                    {
                        if (yend<ymin)
                        {
                            ymin = yend;
                        }
                        if (y0>ymax)
                        {
                            ymax = y0;
                        }
                    }
                }//y0>yend
                f.push_back(((double)xend - (double)x0) / ((double)yend - (double)y0));
                si = si + 1;//斜率的倒数
            }//非水平直线
        }//所有线段循环结束

        //Xstart,Ystart,Yend,f,si
        for (int i = 0; i<si; i++){//每一条线段进行循环
            int a = i - 1, b = i + 1;
            if (i == 0)
            {
                a = si - 1;
            }
            if (i == si - 1)
            {
                b = 0;
            }
            //
            if (Ystart[a] >= Yend[a] && Ystart[i] >= Yend[i])//单调递减
            {
                Yend1.push_back(Ystart[i] - 1);
                Ystart1.push_back(Yend[i]);
            }
            else if (Ystart[i] <= Yend[i] && Ystart[b] <= Yend[b])//单调递增
            {
                Ystart1.push_back(Ystart[i]);
                Yend1.push_back(Yend[i] - 1);
            }
            else if (Ystart[i] <= Yend[i])
            {
                Ystart1.push_back(Ystart[i]);
                Yend1.push_back(Yend[i]);
            }
            else
            {
                Ystart1.push_back(Yend[i]);
                Yend1.push_back(Ystart[i]);
            }
        }//处理公共顶点

        //Xstart下端点横坐标，Ystart1下端点纵坐标，Yend1上端点纵坐标，f斜率的倒数
        vector<vector<myAET*> > AET;
        vector<int> Num;
        for (int yk = ymin; yk <= ymax; yk++)//逐行扫描
        {
            int num = 0;//记录该行相交线段数量
            vector<myAET*> myaet;//存放该行的数据
            for (int i = 0; i<si; i++)//逐条线段进行判断
            {
                if (Ystart1[i] == yk)//如果该点为某线段的最低点
                {
                    myAET* aet = new myAET;
                    aet->xstart = Xstart[i];
                    aet->yend = Yend1[i];
                    aet->f = f[i];
                    aet->C = Xstart[i];
                    myaet.push_back(aet);
                    num += 1;
                }
            }
            if (yk != ymin)
            {
                for (int i = 0; i<Num[yk - ymin - 1]; i++)
                {
                    int q = AET[yk - ymin - 1][i]->yend;
                    if (yk <= q)
                    {
                        myAET* aet = new myAET;
                        int c = 1;
                        aet->C = AET[yk - ymin - 1][i]->C + AET[yk - ymin - 1][i]->f;
                        aet->yend = AET[yk - ymin - 1][i]->yend;
                        aet->f = AET[yk - ymin - 1][i]->f;
                        aet->xstart = (int)(AET[yk - ymin - 1][i]->C + 0.5);
                        myaet.push_back(aet);
                        num += 1;
                    }
                }
            }
            AET.push_back(myaet);
            Num.push_back(num);
        }
        //建立AET
        int x, xxmin, nmin;
        for (int yk = ymin; yk <= ymax; yk++)//扫描行
        {
            vector<int> xx, xn;
            int l = yk - ymin;//AET桶的l行
            for (int nk = 0; nk<Num[l]; nk++)
            {
                x = AET[l][nk]->xstart;
                xx.push_back(x);
            }
            for (int j = 0; j<xx.size(); j++)
            {
                xxmin = -1;
                for (int i = 0; i<xx.size(); i++)
                {
                    if (xxmin == -1 && xx[i]>0)
                    {
                        xxmin = xx[i];
                        nmin = i;
                    }
                    else if (xx[i]>0 && xx[i] <= xxmin)
                    {
                        xxmin = xx[i];
                        nmin = i;
                    }
                }
                xn.push_back(xxmin);
                xx[nmin] = -1;
            }
            //qDebug()<<xn.size();
            //qDebug()<<"dadadadadad";
           // for (int i = 0; i <= xn.size() - 2; i = i + 2)
            //{

                //for (int j = xn[i]; j <= xn[i + 1]; j++)
                //{
                  //  curvePoints.push_back(QPoint(j, yk));
                //}
            //}
        }//扫描行
    }//填充过程
}
