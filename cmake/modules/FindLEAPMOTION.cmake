# Locate LEap Motion library
# This module defines
# LEAP_LIBRARY, the name of the library to link against
# LEAP_FOUND, if false, do not try to link to Leap
# LEAP_INCLUDE_DIR, where to find Leap.h
#
# $LEAP_SDK is an environment variable 
#

SET(LEAP_SEARCH_PATHS
	
)

FIND_LIBRARY(LEAP_LIBRARY
	NAMES LEAP
	HINTS
	$ENV{LEAP_SDK}
	PATH_SUFFIXES lib lib/x86 lib/x64
	PATHS ${LEAP_SEARCH_PATHS}
)

FIND_PATH(LEAP_INCLUDE_DIR Leap.h
	HINTS
	$ENV{LEAP_SDK}
	PATH_SUFFIXES include
	PATHS ${LEAP_SEARCH_PATHS}
)


INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LEAP REQUIRED_VARS LEAP_LIBRARY LEAP_INCLUDE_DIR)
