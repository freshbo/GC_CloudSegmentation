cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

project      (Segmentation)
find_package (Qt4 REQUIRED)
find_package (VTK REQUIRED)
find_package (PCL 1.6.0 REQUIRED)


#DISABLE ALL WARNINGS
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W0" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()


include_directories (${PCL_INCLUDE_DIRS} C:/Qt/4.8.0/include L:/Libraries/GeometricTools/WildMagic5/SDK/Include)
link_directories    (${PCL_LIBRARY_DIRS} L:/Libraries/GeometricTools/WildMagic5/SDK/Library/v100)
add_definitions     (${PCL_DEFINITIONS})

set  (project_SOURCES 
        main.cpp mainwindow.cpp operation.cpp 
        PCFrame.cpp graph.cpp maxflow.cpp global.cpp
        GCoptimization.cpp LinkedBlockList.cpp
        mainwindow.h operation.h PCFrame.h 
        block.h graph.h global.h energy.h 
        GCoptimization.h LinkedBlockList.h)
        
set  (project_FORMS   mainwindow.ui)
set  (VTK_LIBRARIES   vtkRendering vtkGraphics vtkHybrid QVTK)
set  (CMAKE_AUTOMOC TRUE)


QT4_WRAP_CPP (project_HEADERS_MOC   ${project_HEADERS})
QT4_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

ADD_EXECUTABLE  (VisualizerWidget ${project_SOURCES}
                                ${project_FORMS_HEADERS})
                                
TARGET_LINK_LIBRARIES (VisualizerWidget ${PCL_LIBRARIES} ${VTK_LIBRARIES})  

