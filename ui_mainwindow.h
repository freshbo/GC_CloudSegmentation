/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 18. Jan 23:40:14 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionExit;
    QAction *actionClear_Clouds;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QSlider *horizontalSlider_p;
    QSpacerItem *horizontalSpacer_2;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QVTKWidget *qvtkWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QPushButton *computeCurvature;
    QCheckBox *ColorCode;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QPushButton *computeTriangulation;
    QCheckBox *ShowMesh;
    QSpacerItem *horizontalSpacer;
    QPushButton *testButton;
    QFrame *line_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1048, 600);
        MainWindow->setMinimumSize(QSize(300, 100));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionClear_Clouds = new QAction(MainWindow);
        actionClear_Clouds->setObjectName(QString::fromUtf8("actionClear_Clouds"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSlider_p = new QSlider(centralWidget);
        horizontalSlider_p->setObjectName(QString::fromUtf8("horizontalSlider_p"));
        horizontalSlider_p->setMaximumSize(QSize(150, 20));
        horizontalSlider_p->setMinimum(1);
        horizontalSlider_p->setMaximum(3);
        horizontalSlider_p->setValue(1);
        horizontalSlider_p->setSliderPosition(1);
        horizontalSlider_p->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_p);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMinimumSize(QSize(20, 0));
        progressBar->setMaximumSize(QSize(1677721, 16777215));
        progressBar->setValue(0);

        horizontalLayout_3->addWidget(progressBar);


        verticalLayout_2->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_2, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));

        horizontalLayout_2->addWidget(qvtkWidget);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_4->addWidget(label);

        computeCurvature = new QPushButton(centralWidget);
        computeCurvature->setObjectName(QString::fromUtf8("computeCurvature"));
        sizePolicy.setHeightForWidth(computeCurvature->sizePolicy().hasHeightForWidth());
        computeCurvature->setSizePolicy(sizePolicy);
        computeCurvature->setMinimumSize(QSize(1, 1));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        computeCurvature->setFont(font);
        computeCurvature->setIconSize(QSize(30, 16));

        verticalLayout_4->addWidget(computeCurvature);

        ColorCode = new QCheckBox(centralWidget);
        ColorCode->setObjectName(QString::fromUtf8("ColorCode"));

        verticalLayout_4->addWidget(ColorCode);


        horizontalLayout->addLayout(verticalLayout_4);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy2);
        line_3->setMinimumSize(QSize(0, 100));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label_2);

        computeTriangulation = new QPushButton(centralWidget);
        computeTriangulation->setObjectName(QString::fromUtf8("computeTriangulation"));

        verticalLayout_3->addWidget(computeTriangulation);

        ShowMesh = new QCheckBox(centralWidget);
        ShowMesh->setObjectName(QString::fromUtf8("ShowMesh"));

        verticalLayout_3->addWidget(ShowMesh);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        testButton = new QPushButton(centralWidget);
        testButton->setObjectName(QString::fromUtf8("testButton"));

        horizontalLayout->addWidget(testButton);


        verticalLayout->addLayout(horizontalLayout);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1048, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionClear_Clouds);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionClear_Clouds->setText(QApplication::translate("MainWindow", "Clear Clouds", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Curvature", 0, QApplication::UnicodeUTF8));
        computeCurvature->setText(QApplication::translate("MainWindow", "Calculate", 0, QApplication::UnicodeUTF8));
        ColorCode->setText(QApplication::translate("MainWindow", "Color Code", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Triangulation", 0, QApplication::UnicodeUTF8));
        computeTriangulation->setText(QApplication::translate("MainWindow", "Calculate", 0, QApplication::UnicodeUTF8));
        ShowMesh->setText(QApplication::translate("MainWindow", "Show Mesh", 0, QApplication::UnicodeUTF8));
        testButton->setText(QApplication::translate("MainWindow", "Test", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
