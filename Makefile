
coursework1: coursework1.o balancedTree.o eventClasses.o helper.o  
	g++ balancedTree.o eventClasses.o helper.o coursework1.o -o cw1

eventClasses.o: eventClasses.h eventClasses.cpp
	g++ -c eventClasses.cpp

helper.o: helper.h helper.cpp
	g++ -c helper.cpp


balancedTree.o: balancedTree.h balancedTree.cpp
	g++ -c balancedTree.cpp

coursework1.o: coursework1.cpp
	g++ -c coursework1.cpp

clean:
	rm *.o *.log *.stackdump *.exe tests *.h coursework1