   find_path(tango_includes
             NAME tango.h
             PATHS ${tango_include_path} /usr/include /usr/include/tango /usr/local/include /usr/local/include/tango)
   if (NOT tango_includes)
     message(FATAL_ERROR "TANGO header not found. Please use -Dtango_include_path=<path to tango headers>")
   endif()
    
    message("TANGO include path: ${tango_includes}")
    
   find_library(tango_lib
             NAME tango
             PATHS ${tango_lib_path} ${tango_include_path}/../lib /usr/lib /usr/local/lib)
   if (NOT tango_lib)
     message(FATAL_ERROR "TANGO libraries not found. Please use -Dtango_lib_path=<path to tango libraries>")
   endif()
   
   get_filename_component(tango_libs
             ${tango_lib}
             PATH)
   message("TANGO lib path: ${tango_libs}")
   
   find_package(TangoLibs)
   
   macro (win32CompilerFlags)
           if (WIN32)
                   ADD_DEFINITIONS(-DLOG4TANGO_HAS_DLL -DTANGO_HAS_DLL)
           endif()
   endmacro()