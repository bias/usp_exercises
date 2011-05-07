## Non GNU complient  project
AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wformat=2 -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wwrite-strings -Wbad-function-cast -Wmissing-declarations 

INCLUDES = -I../../book

bin_PROGRAMS = chainopenfork chainopenforksleep chainforkopen chainforkopenseek chainforkappend chainforkappendsleep

chainopenfork_SOURCES = chainopenfork.c
chainopenfork_LDADD = ../../book/libatomic_logger.la

chainopenforksleep_SOURCES = chainopenforksleep.c
chainopenforksleep_LDADD = ../../book/libatomic_logger.la

chainforkopen_SOURCES = chainforkopen.c
chainforkopen_LDADD = ../../book/libatomic_logger.la

chainforkopenseek_SOURCES = chainforkopenseek.c
chainforkopenseek_LDADD = ../../book/libatomic_logger.la

chainforkappend_SOURCES = chainforkappend.c
chainforkappend_LDADD = ../../book/libatomic_logger.la

chainforkappendsleep_SOURCES = chainforkappendsleep.c
chainforkappendsleep_LDADD = ../../book/libatomic_logger.la
