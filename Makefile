OBJECTS = DecayFunctions.o Be_11_Spline.o Be_11_Main.o Be_11_Functions.o dataExtraction.o
PREFLAGS = `root-config --cflags`
POSTFLAGS = -fPIC `root-config --glibs`

all:clean Be_11

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

DecayFunctions.o : DecayFunctions.c DecayFunctions.h
	g++ $(PREFLAGS) -c DecayFunctions.c $(POSTFLAGS)

clean :
	rm -f $(OBJECTS)
	rm -f Electron_Energy_Spectrum.txt Q_Value_Spectrum.txt Ex_Spectrum.txt Neutrino_Energies.txt Neutrino_Energy_Spectrum.txt Alpha_Energy_Spectrum.txt Decay_Spectrum.txt
	rm -f Normalized_Dot_Product.txt Term_2.txt Alpha_Lithium.txt total_kinetic.txt Final_Output.txt Gaussian.txt

test.o : test.cpp
	g++ -std=c++11 $(PREFLAGS) -c test.cpp

test: DecayFunctions.o Be_11_Spline.o Be_11_Functions.o dataExtraction.o test.o

	g++ $(PREFLAGS) -I./ $^ $(POSTFLAGS) -o $@