/********************************************************************************
** Form generated from reading UI file 'russboxwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUSSBOXWIDGET_H
#define UI_RUSSBOXWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RussBoxWidget
{
public:
    QLabel *label;
    QPushButton *BtnStart;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelNext;

    void setupUi(QWidget *RussBoxWidget)
    {
        if (RussBoxWidget->objectName().isEmpty())
            RussBoxWidget->setObjectName(QStringLiteral("RussBoxWidget"));
        RussBoxWidget->resize(566, 577);
        RussBoxWidget->setFocusPolicy(Qt::StrongFocus);
        label = new QLabel(RussBoxWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 300, 500));
        label->setStyleSheet(QStringLiteral("background-color:  rgb(211, 211, 158);"));
        BtnStart = new QPushButton(RussBoxWidget);
        BtnStart->setObjectName(QStringLiteral("BtnStart"));
        BtnStart->setGeometry(QRect(400, 300, 111, 51));
        label_2 = new QLabel(RussBoxWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(360, 190, 71, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_3 = new QLabel(RussBoxWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(440, 190, 111, 31));
        label_3->setFont(font);
        label_3->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        labelNext = new QLabel(RussBoxWidget);
        labelNext->setObjectName(QStringLiteral("labelNext"));
        labelNext->setGeometry(QRect(370, 20, 161, 131));
        labelNext->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 255);"));

        retranslateUi(RussBoxWidget);

        QMetaObject::connectSlotsByName(RussBoxWidget);
    } // setupUi

    void retranslateUi(QWidget *RussBoxWidget)
    {
        RussBoxWidget->setWindowTitle(QApplication::translate("RussBoxWidget", "RussBoxWidget", 0));
        label->setText(QApplication::translate("RussBoxWidget", "area", 0));
        BtnStart->setText(QApplication::translate("RussBoxWidget", "\345\274\200\345\247\213\346\270\270\346\210\217", 0));
        label_2->setText(QApplication::translate("RussBoxWidget", "\346\270\270\346\210\217\345\276\227\345\210\206:", 0));
        label_3->setText(QApplication::translate("RussBoxWidget", "0", 0));
        labelNext->setText(QApplication::translate("RussBoxWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class RussBoxWidget: public Ui_RussBoxWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUSSBOXWIDGET_H
