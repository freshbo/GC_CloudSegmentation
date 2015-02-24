cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

project      (Segmentation)
find_package (Qt4 REQUIRED)
find_package (VTK REQUIRED)
find_package (PCL 1.6.0 REQUIRED)


include_directories (${PCL_INCLUDE_DIRS} C:/Qt/4.8.0/include)
link_directories    (${PCL_LIBRARY_DIRS})
add_definitions     (${PCL_DEFINITIONS})

set  (project_SOURCES main.cpp mainwindow.cpp operation.cpp PCFrame.cpp graph.cpp maxflow.cpp global.cpp mainwindow.h operation.h PCFrame.h block.h graph.h global.h)
set  (project_FORMS   mainwindow.ui)
set  (VTK_LIBRARIES   vtkRendering vtkGraphics vtkHybrid QVTK)
set  (CMAKE_AUTOMOC TRUE)


QT4_WRAP_CPP (project_HEADERS_MOC   ${project_HEADERS})
QT4_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

ADD_EXECUTABLE  (VisualizerWidget ${project_SOURCES}
                                ${project_FORMS_HEADERS})
                                
TARGET_LINK_LIBRARIES (VisualizerWidget ${PCL_LIBRARIES} ${VTK_LIBRARIES})  

