# FindCRF sets the following vars:
# CRF_FOUND
# CRF_INCLUDE_DIR
# CRF_LIBRARIES

# Look for CRF includes by searching for crfPipe.h
FIND_PATH(CRF_INCLUDE_DIR crf/Pipe.h
  PATH_SUFFIXES include
  PATHS
  /usr/local
  /usr
  /opt
  ../../build/${CMAKE_SYSTEM_NAME}
  "C:/Programme/CRF/include"
  "C:/Program Files/CRF/include"
)

# Search for the CRF library by searching libcrf.so / CRF.lib
FIND_LIBRARY(CRF_LIBRARY
  NAMES crf
  PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
  PATHS
  /usr/local
  /usr
  /opt
  ../../build/${CMAKE_SYSTEM_NAME}
  "C:/Programme/CRF/lib"
  "C:/Program Files/CRF/lib"
)

# The variable CRF_LIBRARIES will contain all libraries which have to be
# linked when using CRF.
SET(CRF_LIBRARIES ${CRF_LIBRARY})

# CRF needs librt for clock_gettime, but only on Linux.
# Therefore search for librt and add it to CRF_LIBRARIES
#IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
#  FIND_LIBRARY(RT_LIBRARY NAMES rt)
#  IF(NOT RT_LIBRARY)
#    MESSAGE(FATAL_ERROR "librt was NOT found!")
#  ELSE(NOT RT_LIBRARY)
#    MESSAGE(STATUS "Found librt: Library at ${RT_LIBRARY}")
#  ENDIF(NOT RT_LIBRARY)
#  SET(CRF_LIBRARIES ${CRF_LIBRARIES} ${RT_LIBRARY})
#ENDIF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")


# This apparently is needed, because otherwise the compiler fails with
# things like "undefined reference to '__sync_sub_and_fetch_4".
# See also http://n2.nabble.com/Build-Issue-with-0.6-td1555631.html.
#IF(UNIX AND CMAKE_SIZEOF_VOID_P EQUAL 4)
  #message("Detected UNIX with 32 bit.")
  #  SET(CMAKE_CXX_FLAGS "-msse3 -march=i686 -mtune=i686 ${CMAKE_CXX_FLAGS}")
  #  SET(CMAKE_C_FLAGS "-msse3 -march=686 -mcpu=i686 ${CMAKE_CXX_FLAGS}")
  #ENDIF(UNIX AND CMAKE_SIZEOF_VOID_P EQUAL 4)

# Set CRF_FOUND to YES if the includes and the libraries have been found.
SET(CRF_FOUND "NO")
IF(CRF_LIBRARIES AND CRF_INCLUDE_DIR)
  SET(CRF_FOUND "YES")
ENDIF(CRF_LIBRARIES AND CRF_INCLUDE_DIR)

