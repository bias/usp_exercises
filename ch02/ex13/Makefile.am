## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = liblog.la

liblog_la_SOURCES = liblog.c

include_HEADERS = log.h

liblog_la_LDFLAGS = -version-info 0:0:0

bin_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = liblog.la
