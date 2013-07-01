CXX = g++
RM = rm -f
CPPFLAGS = -g -std=c++0x
LDFLAGS=
LDLIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx
SRCS = main.cpp moonlanding.cpp ship.cpp eagle.cpp
OBJS = $(subst .cpp,.o,$(SRCS))
TARGET = moonlanding

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CXX) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS)
	
dist_clean:
	$(RM) $(OBJS) $(TARGET)
