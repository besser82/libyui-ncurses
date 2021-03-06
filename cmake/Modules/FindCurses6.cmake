# - Try to find curses6
# Once done this will define
#  CURSES_FOUND - System has Curses6
#  CURSES6_INCLUDE_DIR - The Curses6 include directory
#  CURSES6_LIBRARIES - The libraries needed to use Curses6
#  CURSES6_DEFINITIONS - Compiler switches required for using Curses6

FOREACH(path ${CMAKE_LIBRARY_PATH} /usr/${LIB_DIR})
  FIND_LIBRARY(CURSES6_NCURSESW_LIBRARY NAMES ncursesw PATHS ${path}/ncurses6 ${path} NO_DEFAULT_PATH)
  FIND_LIBRARY(CURSES6_PANELW_LIBRARY NAMES panelw PATHS ${path}/ncurses6 ${path} NO_DEFAULT_PATH)
  FIND_LIBRARY(CURSES6_TINFO_LIBRARY NAMES tinfo PATHS ${path}/ncurses6 ${path} NO_DEFAULT_PATH)
ENDFOREACH()

SET(CURSES6_LIBRARIES ${CURSES6_NCURSESW_LIBRARY} ${CURSES6_PANELW_LIBRARY})
# tinfo is optional (in 12.1 is not there)
IF(${CURSES6_TINFO_LIBRARY})
  SET(CURSES6_LIBRARIES "${CURSES6_LIBRARIES} ${CURSES6_TINFO_LIBRARY}")
ENDIF(${CURSES6_TINFO_LIBRARY})

FIND_PATH(CURSES6_INCLUDE_DIR ncurses.h PATH_SUFFIXES ncurses6)

SET( CURSES6_DEFINITIONS "-DNCURSES_INTERNALS=1" )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Curses6  DEFAULT_MSG
                                  CURSES6_LIBRARIES CURSES6_INCLUDE_DIR)

MARK_AS_ADVANCED(CURSES6_INCLUDE_DIR CURSES6_LIBRARIES CURSES6_DEFINITIONS)
