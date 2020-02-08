# Configure compiler settings
CXX=clang++
CXXFLAGS=-g -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the program.
OFILES = \
	stringUtils.o \
	gui/cpipe.o \
	gui/subprocess.o \
	gui/dataReader.o \
	gui/dataWriter.o \
	gui/inroadsDataReader.o \
	gui/inroadsDataWriter.o \
	inroadsGUI.o \
	ioUtils.o \
	inroadsGame.o
# The header files for the program
HFILES = $(shell ls -1 *.h gui/*.h)

# unittest++ keeps its object files in this library.
UNITTEST_LIB = -lUnitTest++

all: inroads tests manualTests

# This target builds your main program.
inroads: $(HFILES) $(OFILES) main.o
	$(CXX) $(CXXFLAGS) -o $@ main.o $(OFILES)

# This target builds your tests.
tests: tests.o ioUtils.o stringUtils.o $(HFILES) test_data/
	$(CXX) $(CXXFLAGS) -o $@ tests.o ioUtils.o stringUtils.o $(UNITTEST_LIB)

# This target builds your manual testing program.
manualTests: manualTests.o $(HFILES) $(OFILES) test_data/
	$(CXX) $(CXXFLAGS) -o $@ manualTests.o $(OFILES)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp $(HFILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target deletes the temporary files we have built.
.PHONY: clean
clean:
	rm -f *.o
	rm -f gui/*.o
	rm -f inroads
	rm -f tests
	rm -f manualTests
