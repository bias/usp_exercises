## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

INCLUDES = -I../../book

bin_PROGRAMS = pipeserver pipeclient 

pipeserver_SOURCES = pipeserver.c
pipeserver_LDADD = ../../book/librestart.la

pipeclient_SOURCES = pipeclient.c
pipeclient_LDADD = ../../book/librestart.la
