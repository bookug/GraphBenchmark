run: run.cpp
	#no need to use -O6 optimization here
	g++ -c run.cpp -I/home/zengli/vflib2/include -o run.o
	g++ -o run run.o -I/home/zengli/vflib2/include -L/home/zengli/vflib2/lib -lvf -lstdc++ -lm 
test: test.cpp
	#NOTICE:using g++ -c -o directly will cause error: invalid ELF
	g++ -c test.cpp -I/home/zengli/vflib2/include -o test.o
	g++ -o test test.o -I/home/zengli/vflib2/include -L/home/zengli/vflib2/lib -lvf -lstdc++ -lm 

clean:
	rm -f *.o

