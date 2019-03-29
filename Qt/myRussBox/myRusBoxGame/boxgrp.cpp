#include "boxgrp.h"

BoxGrp::BoxGrp(QObject *parent) : QObject(parent)
{

    //初始化方块组的当前位置
    mCurPos.setX(0);
    mCurPos.setY(0);
}


//根据样式构建长条形的方块组
 void BoxGrp::SetupItem1(int nStyle)
 {
     if (nStyle%2 == 0)
     {
         //构建水平长条形
         for (int i = 0; i < 4; i++)
         {
             mPoints.append(QPoint(i,2));
         }
     }
     else
     {   //构建垂直长条形
         for (int i = 0; i < 4; i++)
         {
             mPoints.append(QPoint(2,i));
         }
     }
 }

//构建山字型方块组
 void BoxGrp::SetupItem2(int nStyle)
 {
     if (nStyle == 0)
     {
         mPoints.append( QPoint( 1,0));
         mPoints.append( QPoint( 0,1));
         mPoints.append( QPoint( 1,1));
         mPoints.append( QPoint( 2,1));
     }
     else if (nStyle == 1)
     {
         mPoints.append( QPoint( 1,0));
         mPoints.append( QPoint( 1,2));
         mPoints.append( QPoint( 1,1));
         mPoints.append( QPoint( 2,1));
     }
     else if (nStyle == 2)
     {
         mPoints.append( QPoint( 0,1));
         mPoints.append( QPoint( 1,2));
         mPoints.append( QPoint( 1,1));
         mPoints.append( QPoint( 2,1));
     }
     else if (nStyle == 3)
     {
         mPoints.append( QPoint( 1,0));
         mPoints.append( QPoint( 0,1));
         mPoints.append( QPoint( 1,1));
         mPoints.append( QPoint( 1,2));
     }
 }

 void BoxGrp::SetupItem3(int nStyle)
 {
     if (nStyle == 0)
     {
         mPoints.append( QPoint( 1,0));
         mPoints.append( QPoint( 1,1));
         mPoints.append( QPoint( 1,2));
         mPoints.append( QPoint( 2,2));
     }
     else if (nStyle == 1)
     {
         mPoints.append( QPoint( 1,1));
         mPoints.append( QPoint( 2,1));
         mPoints.append( QPoint( 3,1));
         mPoints.append( QPoint( 1,2));
     }
     else if (nStyle == 2)
     {
         mPoints.append( QPoint( 1,1));
         mPoints.append( QPoint( 2,1));
         mPoints.append( QPoint( 2,2));
         mPoints.append( QPoint( 2,3));
     }
     else
     {
         mPoints.append(QPoint( 2,1));
         mPoints.append(QPoint( 2,2));
         mPoints.append(QPoint( 1,2));
         mPoints.append(QPoint( 0,2));
     }

 }

  void BoxGrp::SetupItem4(int nStyle)
  {
      if (nStyle == 0)
      {
          mPoints.append( QPoint( 2,0));
          mPoints.append( QPoint( 2,1));
          mPoints.append( QPoint( 2,2));
          mPoints.append( QPoint( 1,2));
      }
      else if (nStyle == 1)
      {
          mPoints.append( QPoint( 1,1));
          mPoints.append( QPoint( 1,2));
          mPoints.append( QPoint( 2,2));
          mPoints.append( QPoint( 3,2));
      }
      else if (nStyle == 2)
      {
          mPoints.append( QPoint( 1,1));
          mPoints.append( QPoint( 2,1));
          mPoints.append( QPoint( 1,2));
          mPoints.append( QPoint( 1,3));
      }
      else if (nStyle == 3)
      {
          mPoints.append( QPoint( 0,1));
          mPoints.append( QPoint( 1,1));
          mPoints.append( QPoint( 2,1));
          mPoints.append( QPoint( 2,2));
      }
  }


  void BoxGrp::SetupItem5(int nStyle)
  {
      mPoints.append( QPoint( 0,0));
      mPoints.append( QPoint( 0,1));
      mPoints.append( QPoint( 1,0));
      mPoints.append( QPoint( 1,1));
  }

  void BoxGrp::SetupItem6(int nStyle)
  {
      if (nStyle == 0)
      {
          mPoints.append( QPoint( 1,0));
          mPoints.append( QPoint( 1,1));
          mPoints.append( QPoint( 2,1));
          mPoints.append( QPoint( 2,2));
      }
      else if (nStyle == 1)
      {
          mPoints.append( QPoint( 1,1));
          mPoints.append( QPoint( 2,1));
          mPoints.append( QPoint( 0,2));
          mPoints.append( QPoint( 1,2));
      }
      else if (nStyle == 2)
      {
          mPoints.append( QPoint( 2,0));
          mPoints.append( QPoint( 2,1));
          mPoints.append( QPoint( 1,1));
          mPoints.append( QPoint( 1,2));
      }
      else if (nStyle == 3)
      {
          mPoints.append( QPoint( 0,1));
          mPoints.append( QPoint( 1,1));
          mPoints.append( QPoint( 1,2));
          mPoints.append( QPoint( 2,2));
      }
  }


/*
 * 功能: 根据方块组类型和样式 构建一个方块组(设置方块的点集合)
 * nType: 方块组的类型
 * nStyle: 方块组的样式
 *
 * mPoints 记录方块字每个小方块的位置
 *
*/
 void BoxGrp::InitBoxGrp(ITEM_TYPE nType,int nStyle)
 {
     mPoints.clear();

     mType = nType;
     mCurStyle  = nStyle;

     switch(mType)
     {
        case ITEM_1:
            //构建长条形的方块组
            SetupItem1(nStyle); //根据样式构建长条形的方块组
            break;

        case ITEM_2:
            SetupItem2(nStyle);
            break;

        case ITEM_3:
            SetupItem3(nStyle);
            break;

        case ITEM_4:
            SetupItem4(nStyle);
            break;

        case ITEM_5:
            SetupItem5(nStyle);
            break;

        case ITEM_6:
            SetupItem6(nStyle);
            break;

        default:
            break;

     }

 }


 //改变当前方块样式
 void BoxGrp::ChangeShape(void)
 {
     mCurStyle = (mCurStyle + 1)%4;
     InitBoxGrp(mType,mCurStyle);
 }

 //恢复之前的样式
 void BoxGrp::RecoverShape(void)
 {
     mCurStyle = (mCurStyle - 1)%4;
     InitBoxGrp(mType,mCurStyle);
 }

 //将当前方块组的点 加入 到背景方块组中
 void BoxGrp::AddPoints(QVector<QPoint>& points, QPoint pos)
 {
     for (int i = 0; i<points.size(); i++)
     {
         if (!mPoints.contains((points[i]+pos)))
         {
             mPoints.append((points[i]+pos));
         }
     }
 }


 //消除第y行
 void BoxGrp::DeleteRow(int y )
 {
     QVector<QPoint> newPoints;

     for (int i=0; i<mPoints.size(); i++)
     {
         if (mPoints[i].y() != y)
         {
             newPoints.append(mPoints[i]);
         }
     }
     mPoints = newPoints;
 }


 /*
  *  将nRow 之上的行全部下移y个单位
  *
 */

 void BoxGrp::MoveDown(int nRow,int y)
 {
     for (int i = 0; i<mPoints.size(); i++)
     {
         if(mPoints[i].y() < nRow)
         {
             mPoints[i].setY(mPoints[i].y()+ y);
         }
     }
 }


 /*
 画当前方块
 painter 绘图工具

 绘制方块组的位置，相对与绘图设备的坐标
 nStartX ->0
 nStartY -->0

 */
 void BoxGrp::DrawBoxGrp(QPainter& painter,int nStartX,int nStartY)
 {
     for (int i = 0; i< mPoints.size(); i++)
     {
         QPoint pt = mPoints[i];
         pt += mCurPos;
         painter.drawRect(QRect(nStartX + pt.x() * BOX_WIDTH, nStartY + pt.y() * BOX_WIDTH,
                                BOX_WIDTH,BOX_WIDTH));
     }
 }


 //相对移位
 void BoxGrp::Move(int x,int y)
 {
     mCurPos += QPoint(x,y);
 }

 void BoxGrp::Move(QPoint pos)
 {
     Move(pos.x(),pos.y());
 }


 //绝对移位
 void BoxGrp::MoveTo(int x,int y)
 {

     mCurPos = QPoint(x,y);
 }

 void BoxGrp::MoveTo(QPoint pos)
 {
     MoveTo(pos.x(),pos.y());
 }





