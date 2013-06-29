CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-g
LDLIBS=-lSDL -lSDL_image -lSDL_ttf -lSDL_gfx

SRCS=main.cpp moonlanding.cpp ship.cpp eagle.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
TARGET=moonlanding

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(TARGET) $(OBJS)

eagle.o: eagle.cpp eagle.hpp
	$(CXX) $(CPPFLAGS) -c eagle.cpp

ship.o: ship.cpp ship.hpp eagle.o
	$(CXX) $(CPPFLAGS) -c ship.cpp

moonlanding.o: moonlanding.cpp moonlanding.hpp ship.o
	$(CXX) $(CPPFLAGS) -c moonlanding.cpp

main.o: main.cpp moonlanding.o
	$(CXX) $(CPPFLAGS) -c main.cpp

clean:
	$(RM) $(OBJS)
