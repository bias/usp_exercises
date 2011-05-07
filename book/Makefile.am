## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

lib_LTLIBRARIES = libatomic_logger.la
libatomic_logger_la_SOURCES = atomic_logger.c
libatomic_logger_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = atomic_logger.h
