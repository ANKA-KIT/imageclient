if (WIN32) 
            find_library(COS_LIB
                                     NAMES COS413_rt COS414_rt COS415_rt COS416_rt
                                     PATHS ${tango_libs})
            message("COS_LIB:                       ${COS_LIB}")
            find_library(COS_DYNAMIC_LIB 
                                     NAMES COSDynamic413_rt COSDynamic414_rt COSDynamic415_rt COSDynamic416_rt
                                     PATHS ${tango_libs})
            message("COS_DYNAMIC_LIB:               ${COS_DYNAMIC_LIB}")
           find_library(OMNI_DYNAMIC_LIB 
                                    NAMES omniDynamic413_rt omniDynamic414_rt omniDynamic415_rt omniDynamic416_rt
                                    PATHS ${tango_libs})
           message("OMNI_DYNAMIC_LIB:              ${OMNI_DYNAMIC_LIB}")
           find_library(OMNI_ORB_LIB 
                                    NAMES omniORB413_rt omniORB414_rt omniORB415_rt omniORB416_rt
                                    PATHS ${tango_libs})
           message("OMNI_ORB_LIB:          ${OMNI_ORB_LIB}")
           find_library(OMNI_THREAD_LIB 
                                    NAMES omnithread33_rt omnithread34_rt omnithread35_rt omnithread36_rt
                                    PATHS ${tango_libs})
           message("OMNI_THREAD_LIB:               ${OMNI_THREAD_LIB}")
           set (TANGO_LIBRARIES    tango 
                                                           log4tango 
                                                           ${COS_LIB}
                                                           ${COS_DYNAMIC_LIB}
                                                           ${OMNI_DYNAMIC_LIB}
                                                           ${OMNI_ORB_LIB}
                                                           ${OMNI_THREAD_LIB})
   else()
           set (TANGO_LIBRARIES    tango
                                   log4tango
                                   omniORB4
                                   omnithread)
   endif()
