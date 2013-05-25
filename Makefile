CXX = g++
RM = rm

CXXFLAGS = -pipe -std=gnu++0x -s -Ofast -flto -march=native -funroll-loops
LIBS = -pipe -std=gnu++0x -s -Ofast -flto -march=native

#CXXFLAGS = -pipe -std=gnu++0x -O2 -g
#LIBS = -pipe -std=gnu++0x -O2 -g

PROGRAM = wordfreq
OBJECTS = main.o frequencycounter.o

all: $(PROGRAM)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LIBS)

clean:
	$(RM) -rf *.o $(PROGRAM)
