OBJECTS = Be_11_Spline.o Be_11_Main.o Be_11_Functions.o dataExtraction.o
PREFLAGS = `root-config --cflags`
POSTFLAGS = -fPIC `root-config --glibs`

Be_11 : $(OBJECTS)
	g++ $(PREFLAGS) -o Be_11 $(OBJECTS) $(POSTFLAGS)

Be_11_Main.o : Be_11_Main.c Be_11_Functions.h
	g++ $(PREFLAGS) -c Be_11_Main.c $(POSTFLAGS)

Be_11_Functions.o : Be_11_Functions.c Be_11_Functions.h
	g++ $(PREFLAGS) -c Be_11_Functions.c $(POSTFLAGS)

dataExtraction.o : dataExtraction.c dataExtraction.h
	g++ -c dataExtraction.c

Be_11_Spline.o : Be_11_Spline.c Be_11_Spline.h
	g++ $(PREFLAGS) -c Be_11_Spline.c $(POSTFLAGS)

clean :
	rm -f $(OBJECTS)
