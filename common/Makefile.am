## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

lib_LTLIBRARIES = libemalloc.la
libemalloc_la_SOURCES = emalloc.c
libemalloc_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = emalloc.h
