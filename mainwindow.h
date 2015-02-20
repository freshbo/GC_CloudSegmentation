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
#include <pcl/visualization/pcl_visualizer.h>


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
		void pSliderValueChanged (int value);
		void loadPC(void);
		void loadFrame(void);

		void cleanPC(void);
		void downsample(void);
		void computeNormals(void);
		void showCurvature(bool);
		void showOriginal(bool);
		void showSampling(bool);
		void exit(void);

		void test(void);
	

	protected:
		boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
		vector<boost::shared_ptr<container>> Frame;

	private:
		Ui::MainWindow	*ui;
};
