OBJECTS = Be_11_Main.o Be_11_Functions.o dataExtraction.o\

Be_11 : $(OBJECTS)
	g++ -o Be_11 $(OBJECTS)

Be_11_Main.o : Be_11_Main.c Be_11_Functions.h
	g++ -c Be_11_Main.c 

Be_11_Functions.o : Be_11_Functions.c Be_11_Functions.h
	g++ -c Be_11_Functions.c

dataExtraction.o : dataExtraction.c dataExtraction.h
	g++ -c dataExtraction.c


clean :
	rm $(OBJECTS)
