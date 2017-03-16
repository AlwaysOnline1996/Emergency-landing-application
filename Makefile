all: mayday testFacility testRunway
CXXFLAGS=-Wall
CXX=g++
mayday: mayday.o Facility.o Runway.o gcdistance.o
	$(CXX) -o $@ $^

testFacility: testFacility.o Facility.o gcdistance.o
	$(CXX) -o $@ $^

testRunway: testRunway.o Runway.o
	$(CXX) -o $@ $^

clean:
	rm -f *.o mayday testFacility testRunway
