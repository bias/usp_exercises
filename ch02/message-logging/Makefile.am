## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

INCLUDES = -I../../common

lib_LTLIBRARIES = liblog.la
liblog_la_SOURCES = log.c
liblog_la_LDFLAGS = -version-info 0:0:0

bin_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = ../../common/libcustom.la liblog.la
