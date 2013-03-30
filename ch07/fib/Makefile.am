## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

INCLUDES = -I../../common

bin_PROGRAMS = fib

fib_SOURCES = fib.c
fib_LDADD = ../../common/libemalloc.la

## Specs for a library
##lib_LTLIBRARIES = libbarrier.la
##libbarrier_la_SOURCES = barrier.c
##libbarrier_la_LDFLAGS = -version-info 0:0:0
##include_HEADERS = barrier.h
