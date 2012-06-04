CC=gcc
CXX=/usr/lib/gcc-snapshot/bin/g++
DEBUGFLAGS=-ggdb
CXXFLAGS=-std=c++0x -I/usr/boost/include -Wall
LDFLAGS=-L/usr/boost/lib -lboost_regex

SRCS=$(wildcard *.cpp)
OBJS=${SRCS:%.cpp=%.o}
EXECS=${OBJS:%.o=%}

all: alltargets

%: %.cpp
	@echo "building $@ from $<"
	$(eval _OBJ=${<:%.cpp=%.o})
	$(eval _EXEC=${_OBJ:%.o=%})
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c -o $(_OBJ) $<
	$(CXX) -o $(_EXEC) $(_OBJ) $(LDFLAGS)
	@echo "$@ done"

alltargets: $(EXECS)

clean:
	rm -f $(OBJS) $(EXECS)
