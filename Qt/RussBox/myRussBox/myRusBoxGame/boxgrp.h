#ifndef BOXGRP_H
#define BOXGRP_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QPainter>

//方块组类,主要功能就是构建各种形状的方块组

#define  BOX_WIDTH   20
#define  ROW_NUM     25
#define  COL_NUM     15

//定义方块组的类型
enum ITEM_TYPE{
    ITEM_1 = 0,		//长条
    ITEM_2,			//山字形
    ITEM_3,			//手枪形1
    ITEM_4,			//手枪形2
    ITEM_5,			//田
    ITEM_6,			//Z字形1
    ITEM_MAX,
};


class BoxGrp : public QObject
{
    Q_OBJECT
public:
    explicit BoxGrp(QObject *parent = 0);

    //初始化方块组包含的点
    void InitBoxGrp(ITEM_TYPE nType,int nStyle = 0);

    //绘制当前方块组
    void DrawBoxGrp(QPainter& painter,int nStartX,int nStartY);

     //方块组相对移位
    void Move(int x,int y);
    void Move(QPoint pos);

    //方块组绝对移位函数
    void MoveTo(int x,int y);
    void MoveTo(QPoint pos);

    //改变方块组的样式
    void ChangeShape(void);
    void RecoverShape(void);

    void AddPoints(QVector<QPoint>& points, QPoint pos);

    //删除第y行
    void DeleteRow(int y );
    void MoveDown(int nRow,int y);

private:
     void SetupItem1(int nStyle);
     void SetupItem2(int nStyle);
     void SetupItem3(int nStyle);
     void SetupItem4(int nStyle);
     void SetupItem5(int nStyle);
     void SetupItem6(int nStyle);

public:
    QVector<QPoint> mPoints;  //方块组包含的点的坐标
    QPoint mCurPos; //当前方块组位置

public:
    ITEM_TYPE mType; //方块组类型
    int mCurStyle;  //保存方块组的样式,旋转角度 0 ~ 3

};

#endif // BOXGRP_H
