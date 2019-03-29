#include "russboxwidget.h"
#include "ui_russboxwidget.h"

#include <QDebug>

RussBoxWidget::RussBoxWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RussBoxWidget)
{
    ui->setupUi(this);

    //创建游戏区域pixmap
    pMyPixmap = new QPixmap(AREA_WIDTH,AREA_HEIGHT);
    pNextPixmap =new QPixmap(ui->labelNext->width(),ui->labelNext->height());

    connect(ui->BtnStart,SIGNAL(clicked(bool)),this,SLOT(BtnStartSlot()));
}

void RussBoxWidget::BtnStartSlot(void)
{

    DrawGameGrid();

    NewGame();  //开始游戏


}


//更新游戏画面
void RussBoxWidget::UpdateGameDisp(void)
{
    DrawGameGrid(); //重新绘制游戏方格
    QPainter myPaint(pMyPixmap);
    myPaint.setBrush(QColor(228,20,20));
    myPaint.setPen(QColor(128,120,120));

    curBoxGrp.DrawBoxGrp(myPaint,0,0);

    //画背景
    myPaint.setBrush(QColor(180,120,90));
    myPaint.setPen(QColor(180,120,120));
    backGroud.DrawBoxGrp(myPaint,0,0);

    ui->label->setPixmap(*pMyPixmap);
}


//显示下一个方块组
void RussBoxWidget::ShowNextBoxGrp(void)
{
    QPainter myPaint(pNextPixmap);

    pNextPixmap->fill(QColor(200,200,220));

    myPaint.setBrush(QColor(168,90,80));
    myPaint.setPen(QColor(98,190,120));

    nextBoxGrp.DrawBoxGrp(myPaint,50,50);

    ui->labelNext->setPixmap(*pNextPixmap);

}

//开始游戏
void RussBoxWidget::NewGame(void)
{

    backGroud.mPoints.clear(); //游戏背景方块清空

    qsrand(QTime::currentTime().msec()); //设置随机数种子

    ITEM_TYPE t1 = (ITEM_TYPE)(qrand()%ITEM_MAX);
    ITEM_TYPE t2 = (ITEM_TYPE)(qrand()%ITEM_MAX);
    int s1 = qrand()%4;
    int s2 = qrand()%4;

    //随机创建当前方块组和下一个方块组
    curBoxGrp.InitBoxGrp(t1,s1);
    nextBoxGrp.InitBoxGrp(t2,s2);

    curBoxGrp.Move(COL_NUM / 2 - 2,0);

    m_nScore = 0;
    m_nSpeed = 1;

    ShowNextBoxGrp();

    //启动一个定时器
    m_nTimerId = startTimer( (11-m_nSpeed)*100 );


}

//消除满行的功能
void RussBoxWidget::DeleteFullRows(void)
{
    int deleteRows = 0;
    for (int i = 0; i<=ROW_NUM-1; i++)
    {
        int nCount = 0;

        //判断是否满行
        for (int j = 0; j<=COL_NUM-1; j++)
        {
            if (backGroud.mPoints.contains(QPoint(j,i)))
            {
                nCount++;
            }
        }

        if (nCount == COL_NUM)
        {
            //满行  进行消行处理
            backGroud.DeleteRow(i);
            backGroud.MoveDown(i,1);	//消除行之上的内容下移一个单位

            deleteRows++;
        }

    }

    m_nScore += deleteRows*100;
    ui->label_3->setText(QString::number(m_nScore));
}


//将当前方块的点加入到背景方块组
void RussBoxWidget::AddToBackGroud(void)
{
    backGroud.AddPoints(curBoxGrp.mPoints, curBoxGrp.mCurPos);
}



void RussBoxWidget::timerEvent(QTimerEvent* e)
{
    if (e->timerId() == m_nTimerId)
    {
        //定时器超时
        curBoxGrp.Move(0,1); //向下移动一个位置
        if(HitBottom()) // 判断是否到达底部
        {

           //到达底部
           curBoxGrp.Move(0,-1);

           //将当前方块组加入背景方块组
           AddToBackGroud();

           //判断背景方块组是否满行，如果有就删除满行
           DeleteFullRows();

            //判断当前方块组是否到达了顶部
           if (HitTop())
           {
               //游戏结束
               killTimer(m_nTimerId);
               QMessageBox::information(NULL, "GAME OVER", "GAME OVER", QMessageBox::Yes , QMessageBox::Yes);
               return;
           }

           //设置下一个方块组成为当前方块组

           curBoxGrp.InitBoxGrp(nextBoxGrp.mType,nextBoxGrp.mCurStyle);
           curBoxGrp.MoveTo(COL_NUM / 2 - 2,0);

           //重新生成下一个方块组
           ITEM_TYPE t = (ITEM_TYPE)(qrand()%ITEM_MAX);
           int nShape = qrand()%4;
           nextBoxGrp.InitBoxGrp(t,nShape);
           ShowNextBoxGrp();

        }

        //更新显示
        UpdateGameDisp();
    }
}

//判断当前方块组是超越 左右边界 如果是返回 true,否则返回false
bool RussBoxWidget::HitSide(void)
{
    for (int i = 0; i<curBoxGrp.mPoints.size(); i++)
    {
        QPoint pt = curBoxGrp.mPoints[i] + curBoxGrp.mCurPos ;

        if (pt.x() < 0 || pt.x() > COL_NUM - 1)
        {
            return true;
        }
    }
    return false;
}


//判断当前方块组是否移动到底部
bool RussBoxWidget::HitBottom(void)
{
    for (int i = 0; i<curBoxGrp.mPoints.size(); i++)
    {
        QPoint pt = curBoxGrp.mPoints[i] + curBoxGrp.mCurPos;

      //  qDebug()<<"pt_y:"<<pt.y()<<endl;

        if (pt.y() > ROW_NUM - 1)  //到达真正游戏区域底部
        {
            return true;
        }

        if (backGroud.mPoints.contains(pt)) //撞到了之前的游戏方块
        {
            return true;
        }

    }
    return false;
}

//判断是否撞击了顶部 只有在判断游戏结束才会用
bool RussBoxWidget::HitTop(void)
{
    for (int i = 0; i<curBoxGrp.mPoints.size(); i++)
    {
        QPoint pt = curBoxGrp.mPoints[i] + curBoxGrp.mCurPos;
        if (pt.y() < 1)
        {
            return true;
        }
    }
    return false;
}


//按键事件处理机制
void RussBoxWidget::keyPressEvent(QKeyEvent *e)
{
    int x = 0;
    int y = 0;

   // qDebug()<<"enter keyPressEvent"<<endl;

    switch(e->key())
    {
        case Qt::Key_Left:
                //按下左键，向左移动一个方格
                x = -1;
                break;

        case Qt::Key_Up: //变形 改变样式
                curBoxGrp.ChangeShape();
                if(HitSide() || HitBottom())
                { //变形过程中发现越界，恢复原来的样式
                    curBoxGrp.RecoverShape();
                }
                break;

        case Qt::Key_Right:
                //按下右键 向右移动一个方格
                x = 1;
                break;

        case Qt::Key_Down:
                //按下 down键，向下移动一个方格
                y = 1;
                break;

     }

     curBoxGrp.Move(x,y);

     if(HitSide() || HitBottom())
     {
         //方块组移动过程中越界, 恢复原来位置
         curBoxGrp.Move(-x,-y);
     }

    //更新显示
    UpdateGameDisp();
}


//绘制游戏局域背景格子
 void RussBoxWidget::DrawGameGrid(void)
 {
    int i = 0;
    QPainter myPaint(pMyPixmap);

    QPen myPen;
    myPen.setStyle(Qt::SolidLine);
    myPen.setWidth(3);
    myPen.setColor(Qt::black);


    myPaint.setBrush(QColor(228,228,228));

    myPaint.setPen(myPen);

    //绘制游戏区域外框
    myPaint.drawRect(0,0,AREA_WIDTH,AREA_HEIGHT);

    myPen.setStyle(Qt::DashLine);
    myPen.setColor(QColor(200,200,200));
    myPen.setWidth(1);

    myPaint.setPen(myPen);

    //绘制垂直线
    for(i = 1;i <= COL_NUM-1;i++)
    {
        myPaint.drawLine(BOX_WIDTH*i,0,BOX_WIDTH*i,AREA_HEIGHT);
    }

    //绘制水平线
    for(i = 1;i <= ROW_NUM-1;i++)
    {
        myPaint.drawLine(0,BOX_WIDTH*i,AREA_WIDTH,BOX_WIDTH*i);
    }


    //在label显示 pMyPixmap
    ui->label->setPixmap(*pMyPixmap);


 }

RussBoxWidget::~RussBoxWidget()
{
    delete ui;
}
