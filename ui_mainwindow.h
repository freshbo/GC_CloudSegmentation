/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 27. Feb 02:51:44 2015
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
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollBar>
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
    QAction *ShowLeafss;
    QAction *actionStems;
    QAction *deleteAction;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *Operations_Line_LAYOUT;
    QHBoxLayout *Operations_LAYOUT;
    QFrame *line_9;
    QVBoxLayout *General_LAYOUT;
    QLabel *General_LABEL;
    QPushButton *loadButton;
    QRadioButton *ShowOriginal;
    QFrame *line_4;
    QVBoxLayout *Curvature_LAYOUT;
    QLabel *CurvatureLAYOUT;
    QPushButton *computeCurvature;
    QRadioButton *CurvColorCode;
    QFrame *line_3;
    QVBoxLayout *BinarySeg_LAYOUT;
    QLabel *BinarySeg_LABEL;
    QPushButton *SegmentButton;
    QRadioButton *SegColorCode;
    QFrame *line_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QPushButton *MultiLeafButton;
    QRadioButton *ShowLeafs;
    QFrame *line_8;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *Sampling_LAYOUT;
    QLabel *Sampling_LABEL;
    QPushButton *sampleButton;
    QLineEdit *sampleNumberField;
    QPushButton *SampleSaveButton;
    QVBoxLayout *Triangulation_LAYOUT;
    QLabel *label_2;
    QPushButton *triangulationButton;
    QCheckBox *ShowMesh;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QVTKWidget *qvtkWidget;
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QSlider *horizontalSlider_p;
    QFrame *line_6;
    QVBoxLayout *FrameControllVerticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLabel *CloudSizeLABEL;
    QLabel *InfoBox;
    QLabel *label_7;
    QLabel *PCNumberLABEL;
    QScrollBar *FrameScrollBar;
    QFrame *line_7;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1048, 598);
        MainWindow->setMinimumSize(QSize(300, 100));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionClear_Clouds = new QAction(MainWindow);
        actionClear_Clouds->setObjectName(QString::fromUtf8("actionClear_Clouds"));
        ShowLeafss = new QAction(MainWindow);
        ShowLeafss->setObjectName(QString::fromUtf8("ShowLeafss"));
        ShowLeafss->setCheckable(true);
        actionStems = new QAction(MainWindow);
        actionStems->setObjectName(QString::fromUtf8("actionStems"));
        deleteAction = new QAction(MainWindow);
        deleteAction->setObjectName(QString::fromUtf8("deleteAction"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Operations_Line_LAYOUT = new QVBoxLayout();
        Operations_Line_LAYOUT->setSpacing(6);
        Operations_Line_LAYOUT->setObjectName(QString::fromUtf8("Operations_Line_LAYOUT"));
        Operations_LAYOUT = new QHBoxLayout();
        Operations_LAYOUT->setSpacing(6);
        Operations_LAYOUT->setObjectName(QString::fromUtf8("Operations_LAYOUT"));
        line_9 = new QFrame(centralWidget);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setFrameShape(QFrame::VLine);
        line_9->setFrameShadow(QFrame::Sunken);

        Operations_LAYOUT->addWidget(line_9);

        General_LAYOUT = new QVBoxLayout();
        General_LAYOUT->setSpacing(6);
        General_LAYOUT->setObjectName(QString::fromUtf8("General_LAYOUT"));
        General_LABEL = new QLabel(centralWidget);
        General_LABEL->setObjectName(QString::fromUtf8("General_LABEL"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(General_LABEL->sizePolicy().hasHeightForWidth());
        General_LABEL->setSizePolicy(sizePolicy);

        General_LAYOUT->addWidget(General_LABEL);

        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        General_LAYOUT->addWidget(loadButton);

        ShowOriginal = new QRadioButton(centralWidget);
        ShowOriginal->setObjectName(QString::fromUtf8("ShowOriginal"));
        ShowOriginal->setChecked(true);

        General_LAYOUT->addWidget(ShowOriginal);


        Operations_LAYOUT->addLayout(General_LAYOUT);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        Operations_LAYOUT->addWidget(line_4);

        Curvature_LAYOUT = new QVBoxLayout();
        Curvature_LAYOUT->setSpacing(6);
        Curvature_LAYOUT->setObjectName(QString::fromUtf8("Curvature_LAYOUT"));
        CurvatureLAYOUT = new QLabel(centralWidget);
        CurvatureLAYOUT->setObjectName(QString::fromUtf8("CurvatureLAYOUT"));
        sizePolicy.setHeightForWidth(CurvatureLAYOUT->sizePolicy().hasHeightForWidth());
        CurvatureLAYOUT->setSizePolicy(sizePolicy);
        CurvatureLAYOUT->setLayoutDirection(Qt::LeftToRight);

        Curvature_LAYOUT->addWidget(CurvatureLAYOUT);

        computeCurvature = new QPushButton(centralWidget);
        computeCurvature->setObjectName(QString::fromUtf8("computeCurvature"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(computeCurvature->sizePolicy().hasHeightForWidth());
        computeCurvature->setSizePolicy(sizePolicy1);
        computeCurvature->setMinimumSize(QSize(1, 1));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        computeCurvature->setFont(font);
        computeCurvature->setIconSize(QSize(30, 16));

        Curvature_LAYOUT->addWidget(computeCurvature);

        CurvColorCode = new QRadioButton(centralWidget);
        CurvColorCode->setObjectName(QString::fromUtf8("CurvColorCode"));

        Curvature_LAYOUT->addWidget(CurvColorCode);


        Operations_LAYOUT->addLayout(Curvature_LAYOUT);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        Operations_LAYOUT->addWidget(line_3);

        BinarySeg_LAYOUT = new QVBoxLayout();
        BinarySeg_LAYOUT->setSpacing(6);
        BinarySeg_LAYOUT->setObjectName(QString::fromUtf8("BinarySeg_LAYOUT"));
        BinarySeg_LABEL = new QLabel(centralWidget);
        BinarySeg_LABEL->setObjectName(QString::fromUtf8("BinarySeg_LABEL"));
        sizePolicy.setHeightForWidth(BinarySeg_LABEL->sizePolicy().hasHeightForWidth());
        BinarySeg_LABEL->setSizePolicy(sizePolicy);

        BinarySeg_LAYOUT->addWidget(BinarySeg_LABEL);

        SegmentButton = new QPushButton(centralWidget);
        SegmentButton->setObjectName(QString::fromUtf8("SegmentButton"));

        BinarySeg_LAYOUT->addWidget(SegmentButton);

        SegColorCode = new QRadioButton(centralWidget);
        SegColorCode->setObjectName(QString::fromUtf8("SegColorCode"));

        BinarySeg_LAYOUT->addWidget(SegColorCode);


        Operations_LAYOUT->addLayout(BinarySeg_LAYOUT);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        Operations_LAYOUT->addWidget(line_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_3);

        MultiLeafButton = new QPushButton(centralWidget);
        MultiLeafButton->setObjectName(QString::fromUtf8("MultiLeafButton"));

        verticalLayout_3->addWidget(MultiLeafButton);

        ShowLeafs = new QRadioButton(centralWidget);
        ShowLeafs->setObjectName(QString::fromUtf8("ShowLeafs"));

        verticalLayout_3->addWidget(ShowLeafs);


        Operations_LAYOUT->addLayout(verticalLayout_3);

        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        Operations_LAYOUT->addWidget(line_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Operations_LAYOUT->addItem(horizontalSpacer);

        Sampling_LAYOUT = new QVBoxLayout();
        Sampling_LAYOUT->setSpacing(6);
        Sampling_LAYOUT->setObjectName(QString::fromUtf8("Sampling_LAYOUT"));
        Sampling_LABEL = new QLabel(centralWidget);
        Sampling_LABEL->setObjectName(QString::fromUtf8("Sampling_LABEL"));
        sizePolicy.setHeightForWidth(Sampling_LABEL->sizePolicy().hasHeightForWidth());
        Sampling_LABEL->setSizePolicy(sizePolicy);

        Sampling_LAYOUT->addWidget(Sampling_LABEL);

        sampleButton = new QPushButton(centralWidget);
        sampleButton->setObjectName(QString::fromUtf8("sampleButton"));

        Sampling_LAYOUT->addWidget(sampleButton);

        sampleNumberField = new QLineEdit(centralWidget);
        sampleNumberField->setObjectName(QString::fromUtf8("sampleNumberField"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sampleNumberField->sizePolicy().hasHeightForWidth());
        sampleNumberField->setSizePolicy(sizePolicy2);
        sampleNumberField->setReadOnly(false);

        Sampling_LAYOUT->addWidget(sampleNumberField);

        SampleSaveButton = new QPushButton(centralWidget);
        SampleSaveButton->setObjectName(QString::fromUtf8("SampleSaveButton"));

        Sampling_LAYOUT->addWidget(SampleSaveButton);


        Operations_LAYOUT->addLayout(Sampling_LAYOUT);

        Triangulation_LAYOUT = new QVBoxLayout();
        Triangulation_LAYOUT->setSpacing(6);
        Triangulation_LAYOUT->setObjectName(QString::fromUtf8("Triangulation_LAYOUT"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        Triangulation_LAYOUT->addWidget(label_2);

        triangulationButton = new QPushButton(centralWidget);
        triangulationButton->setObjectName(QString::fromUtf8("triangulationButton"));

        Triangulation_LAYOUT->addWidget(triangulationButton);

        ShowMesh = new QCheckBox(centralWidget);
        ShowMesh->setObjectName(QString::fromUtf8("ShowMesh"));

        Triangulation_LAYOUT->addWidget(ShowMesh);


        Operations_LAYOUT->addLayout(Triangulation_LAYOUT);


        Operations_Line_LAYOUT->addLayout(Operations_LAYOUT);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        Operations_Line_LAYOUT->addWidget(line_2);


        gridLayout->addLayout(Operations_Line_LAYOUT, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));

        horizontalLayout_2->addWidget(qvtkWidget);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

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

        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_6);

        FrameControllVerticalLayout = new QVBoxLayout();
        FrameControllVerticalLayout->setSpacing(6);
        FrameControllVerticalLayout->setObjectName(QString::fromUtf8("FrameControllVerticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        CloudSizeLABEL = new QLabel(centralWidget);
        CloudSizeLABEL->setObjectName(QString::fromUtf8("CloudSizeLABEL"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(CloudSizeLABEL->sizePolicy().hasHeightForWidth());
        CloudSizeLABEL->setSizePolicy(sizePolicy3);
        CloudSizeLABEL->setLayoutDirection(Qt::LeftToRight);
        CloudSizeLABEL->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(CloudSizeLABEL);

        InfoBox = new QLabel(centralWidget);
        InfoBox->setObjectName(QString::fromUtf8("InfoBox"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(InfoBox->sizePolicy().hasHeightForWidth());
        InfoBox->setSizePolicy(sizePolicy4);
        InfoBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(InfoBox);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy5);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_7);

        PCNumberLABEL = new QLabel(centralWidget);
        PCNumberLABEL->setObjectName(QString::fromUtf8("PCNumberLABEL"));
        sizePolicy3.setHeightForWidth(PCNumberLABEL->sizePolicy().hasHeightForWidth());
        PCNumberLABEL->setSizePolicy(sizePolicy3);
        PCNumberLABEL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(PCNumberLABEL);


        FrameControllVerticalLayout->addLayout(horizontalLayout_5);

        FrameScrollBar = new QScrollBar(centralWidget);
        FrameScrollBar->setObjectName(QString::fromUtf8("FrameScrollBar"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(FrameScrollBar->sizePolicy().hasHeightForWidth());
        FrameScrollBar->setSizePolicy(sizePolicy6);
        FrameScrollBar->setMaximum(0);
        FrameScrollBar->setOrientation(Qt::Horizontal);

        FrameControllVerticalLayout->addWidget(FrameScrollBar);


        horizontalLayout_3->addLayout(FrameControllVerticalLayout);

        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_7);


        verticalLayout_2->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_2, 5, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(true);
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
        menuEdit->addAction(deleteAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("MainWindow", "Load Frame", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionClear_Clouds->setText(QApplication::translate("MainWindow", "Clear Clouds", 0, QApplication::UnicodeUTF8));
        ShowLeafss->setText(QApplication::translate("MainWindow", "Leafs", 0, QApplication::UnicodeUTF8));
        actionStems->setText(QApplication::translate("MainWindow", "Stems", 0, QApplication::UnicodeUTF8));
        deleteAction->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        General_LABEL->setText(QApplication::translate("MainWindow", "PointCloud", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("MainWindow", "Load", 0, QApplication::UnicodeUTF8));
        ShowOriginal->setText(QApplication::translate("MainWindow", "Original", 0, QApplication::UnicodeUTF8));
        CurvatureLAYOUT->setText(QApplication::translate("MainWindow", "Curvature", 0, QApplication::UnicodeUTF8));
        computeCurvature->setText(QApplication::translate("MainWindow", "Calculate", 0, QApplication::UnicodeUTF8));
        CurvColorCode->setText(QApplication::translate("MainWindow", "Curvature", 0, QApplication::UnicodeUTF8));
        BinarySeg_LABEL->setText(QApplication::translate("MainWindow", "Leaf- Stem", 0, QApplication::UnicodeUTF8));
        SegmentButton->setText(QApplication::translate("MainWindow", "Segmentation", 0, QApplication::UnicodeUTF8));
        SegColorCode->setText(QApplication::translate("MainWindow", "Binary Seg.", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Multi-Leaf", 0, QApplication::UnicodeUTF8));
        MultiLeafButton->setText(QApplication::translate("MainWindow", "Segmentation", 0, QApplication::UnicodeUTF8));
        ShowLeafs->setText(QApplication::translate("MainWindow", "Multi-Leaf", 0, QApplication::UnicodeUTF8));
        Sampling_LABEL->setText(QApplication::translate("MainWindow", "DownSampling", 0, QApplication::UnicodeUTF8));
        sampleButton->setText(QApplication::translate("MainWindow", "Sample", 0, QApplication::UnicodeUTF8));
        sampleNumberField->setText(QString());
        sampleNumberField->setPlaceholderText(QString());
        SampleSaveButton->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Triangulation", 0, QApplication::UnicodeUTF8));
        triangulationButton->setText(QApplication::translate("MainWindow", "Calculate", 0, QApplication::UnicodeUTF8));
        ShowMesh->setText(QApplication::translate("MainWindow", "Show Mesh", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Points: ", 0, QApplication::UnicodeUTF8));
        CloudSizeLABEL->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        InfoBox->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "PointCloud Nr. : ", 0, QApplication::UnicodeUTF8));
        PCNumberLABEL->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
