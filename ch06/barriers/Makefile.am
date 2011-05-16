## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

INCLUDES = -I../../common

bin_PROGRAMS = barrierd test

barrierd_SOURCES = barrierd.c
barrierd_LDADD = ../../common/libemalloc.la

test_SOURCES = test.c
test_LDADD = ../../common/libemalloc.la libbarrier.la

lib_LTLIBRARIES = libbarrier.la
libbarrier_la_SOURCES = barrier.c
libbarrier_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = barrier.h
