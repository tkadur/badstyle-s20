badstyle: gottagofast.o sort.o
	/usr/bin/env python3 -m pip install --user pexpect
	g++ gottagofast.o sort.o -o gottagofast

gottagofast.o: gottagofast.c
	gcc -std=c99 -c gottagofast.c

sort.o: sort.cpp
	g++ -std=c++11 -c sort.cpp

clean:
	/usr/bin/env python3 -m pip uninstall pexpect
	rm *.o
	rm gottagofast