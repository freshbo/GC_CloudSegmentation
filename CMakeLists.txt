cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

project      (Segmentation)
find_package (Qt4 REQUIRED)
find_package (VTK REQUIRED)
find_package (PCL 1.6.0 REQUIRED)

include_directories (${PCL_INCLUDE_DIRS} C:/Qt/4.8.0/include)
link_directories    (${PCL_LIBRARY_DIRS})
add_definitions     (${PCL_DEFINITIONS})

set  (project_SOURCES main.cpp mainwindow.cpp operation.cpp PCFrame.cpp
mainwindow.h header.h operation.h PCFrame.h)
set  (project_FORMS   mainwindow.ui)
set  (VTK_LIBRARIES   vtkRendering vtkGraphics vtkHybrid QVTK)
set  (CMAKE_AUTOMOC TRUE)

#this line should surpress all "SHOT is deprecated" warnings, but results in ERROR
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations") 

QT4_WRAP_CPP (project_HEADERS_MOC   ${project_HEADERS})
QT4_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

ADD_EXECUTABLE  (VisualizerWidget ${project_SOURCES}
                                ${project_FORMS_HEADERS})
                                
TARGET_LINK_LIBRARIES (VisualizerWidget ${PCL_LIBRARIES} ${VTK_LIBRARIES})                                