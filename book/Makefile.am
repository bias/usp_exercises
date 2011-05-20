## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

lib_LTLIBRARIES = libatomic_logger.la libmakeargv.la librestart.la

libatomic_logger_la_SOURCES = atomic_logger.c
libatomic_logger_la_LDFLAGS = -version-info 0:0:0

libmakeargv_la_SOURCES = makeargv.c
libmakeargv_la_LDFLAGS = -version-info 0:0:0

librestart_la_SOURCES = restart.c
librestart_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = atomic_logger.h makeargv.h restart.h
