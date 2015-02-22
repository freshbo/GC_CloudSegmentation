#pragma once

#include <string>

#include "operation.h"
#include "PCFrame.h"

//Qt
#include <QtGui\qfiledialog.h>
#include <QtGui\QMainWindow>
#include <QtCore\qstring.h>
#include "ui_mainwindow.h"

//Visualization Tool Kit
#include <vtkRenderWindow.h>




namespace Ui 
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	public slots:
		void frameScroll(int value);
		void pSliderValueChanged (int value);
		void loadPC(void);
		void loadFrame(void);

		void statisticalOutliers(void);
		void radiusOutliers(void);
		void downsample(void);
		void computeCurvature(void);
		void showCurvature(bool);
		void showbinSegmentation(bool);
		void exit(void);
		void showCloud(void);
		void BinSeg(void);
	

	protected:
		boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
		int t ;
		vector<boost::shared_ptr<hypothesis>> Frame;

	private:
		Ui::MainWindow	*ui;
};

