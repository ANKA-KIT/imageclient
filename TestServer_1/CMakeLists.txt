project(mytesting_project)
   
   cmake_minimum_required(VERSION 2.6)
    
    find_package(Tango
            PATHS ${CMAKE_CURRENT_SOURCE_DIR})
    
    include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${tango_includes} /usr/local/include/opencv /usr/include)
    link_directories(${tango_libs} /usr/local/lib /usr/lib64)
   
   add_definitions(-Wall)
   
   set(source_files 
     main.cpp
     ClassFactory.cpp
     MytestClass.cpp
     Mytest.cpp
     MytestStateMachine.cpp)
   
   add_executable(Mytest ${source_files})
   
   target_link_libraries(Mytest ${TANGO_LIBRARIES} omniORB4 omnithread dl yat jpeg opencv_core opencv_highgui tiff)
   
   install(TARGETS Mytest
           RUNTIME
           DESTINATION bin)