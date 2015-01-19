cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

project      (Segmentation)
find_package (Qt4 REQUIRED)
find_package (VTK REQUIRED)
find_package (PCL 1.6.0 REQUIRED)
find_package (CGAL  COMPONENTS Qt4)
if(CGAL_FOUND)
    include(${CGAL_USE_FILE})
    include_directories (BEFORE "../../include")

else()

endif()

include_directories (${PCL_INCLUDE_DIRS} C:/Qt/4.8.0/include)
link_directories    (${PCL_LIBRARY_DIRS} L:/Libraries/CGAL-4.5.1/bin)
add_definitions     (${PCL_DEFINITIONS})

set  (project_SOURCES main.cpp mainwindow.cpp operation.cpp PCFrame.cpp
mainwindow.h header.h operation.h PCFrame.h)
set  (project_FORMS   mainwindow.ui)
set  (VTK_LIBRARIES   vtkRendering vtkGraphics vtkHybrid QVTK)
set  (CMAKE_AUTOMOC TRUE)


QT4_WRAP_CPP (project_HEADERS_MOC   ${project_HEADERS})
QT4_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

ADD_EXECUTABLE  (VisualizerWidget ${project_SOURCES}
                                ${project_FORMS_HEADERS})
                                
TARGET_LINK_LIBRARIES (VisualizerWidget ${PCL_LIBRARIES} ${VTK_LIBRARIES})  
TARGET_LINK_LIBRARIES (VisualizerWidget ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
