#ifndef RUSSBOXWIDGET_H
#define RUSSBOXWIDGET_H

#include <QWidget>

#include <QPixmap>
#include <QPainter>
#include <QTime>
#include <QKeyEvent>
#include <QMessageBox>

#include "boxgrp.h"


//定义游戏区域
#define  ROW_NUM     25
#define  COL_NUM     15
#define  BOX_WIDTH   20

#define  AREA_HEIGHT    (ROW_NUM*BOX_WIDTH)
#define  AREA_WIDTH     (COL_NUM*BOX_WIDTH)



namespace Ui {
class RussBoxWidget;
}

class RussBoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RussBoxWidget(QWidget *parent = 0);
    ~RussBoxWidget();

    void DrawGameGrid(void);
    void NewGame(void);
    void UpdateGameDisp(void);
    bool HitSide(void);
    bool HitBottom(void);
    bool HitTop(void);

    void AddToBackGroud(void);

    void DeleteFullRows(void);

    void ShowNextBoxGrp(void);

public slots:
    void BtnStartSlot(void);

private:
    Ui::RussBoxWidget *ui;


    QPixmap *pMyPixmap;
    QPixmap *pNextPixmap;

    BoxGrp  backGroud; //记录背景方块信息,point就可以不止4个
    BoxGrp  curBoxGrp; //表示当前方块组
    BoxGrp  nextBoxGrp; //表示下一个方块组

    int m_nTimerId;  //定时器
    int m_nSpeed;    //游戏的速度

    int m_nScore;   //得分
    int m_nLevel;

protected:

    //定时器事件处理函数
    void timerEvent(QTimerEvent*);

    //实现按键事件处理函数
    void keyPressEvent(QKeyEvent *);


};

#endif // RUSSBOXWIDGET_H
