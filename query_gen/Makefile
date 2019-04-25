#compile parameters

CC = g++
CFLAGS = -c -Wall -O6 #-fprofile-arcs -ftest-coverage -coverage #-pg
EXEFLAG = -O6 #-fprofile-arcs -ftest-coverage -coverage #-pg #-O2
#CFLAGS = -c -Wall -g #-fprofile-arcs -ftest-coverage -coverage #-pg
#EXEFLAG = -g #-fprofile-arcs -ftest-coverage -coverage #-pg #-O2
	 
#add -lreadline -ltermcap if using readline or objs contain readline
library = #-lgcov -coverage

objdir = ./objs/
objfile = $(objdir)Util.o $(objdir)IO.o $(objdir)Match.o $(objdir)Graph.o \
$(objdir)IO_data.o $(objdir)Line_query.o $(objdir)Clique_query.o $(objdir)Ring_query.o

all: run.exe

run.exe: main/run.cpp $(objfile) patterns/Query_patterns.h 
	$(CC) $(EXEFLAG) -o run.exe main/run.cpp $(objfile) $(library)

$(objdir)Util.o: util/Util.cpp util/Util.h
	$(CC) $(CFLAGS) util/Util.cpp -o $(objdir)Util.o

$(objdir)Graph.o: graph/Graph.cpp graph/Graph.h
	$(CC) $(CFLAGS) graph/Graph.cpp -o $(objdir)Graph.o

$(objdir)IO.o: io/IO.cpp io/IO.h
	$(CC) $(CFLAGS) io/IO.cpp -o $(objdir)IO.o

$(objdir)Match.o: match/Match.cpp match/Match.h
	$(CC) $(CFLAGS) match/Match.cpp -o $(objdir)Match.o

$(objdir)IO_data.o: io/IO_data.cpp io/IO_data.h
	$(CC) $(CFLAGS) io/IO_data.cpp -o $(objdir)IO_data.o

$(objdir)Line_query.o: patterns/Line_query.cpp patterns/Line_query.h
	$(CC) $(CFLAGS) patterns/Line_query.cpp -o $(objdir)Line_query.o

$(objdir)Clique_query.o: patterns/Clique_query.cpp patterns/Clique_query.h
	$(CC) $(CFLAGS) patterns/Clique_query.cpp -o $(objdir)Clique_query.o

$(objdir)Ring_query.o: patterns/Ring_query.cpp patterns/Ring_query.h
	$(CC) $(CFLAGS) patterns/Ring_query.cpp -o $(objdir)Ring_query.o


.PHONY: clean dist tarball test sumlines

clean:
	rm -f $(objdir)*
dist: clean
	rm -f *.txt dig

tarball:
	tar -czvf vf2.tar.gz main util match io graph Makefile README.md objs script vflib2

test: main/test.o $(objfile)
	$(CC) $(EXEFLAG) -o test main/test.cpp $(objfile) $(library)

sumline:
	bash script/sumline.sh

