CXX := g++
CXXFLAGS := -g -std=c++17 -Wall -Wextra -pedantic
INCLUDE := -I ../libs/include
LDFLAGS  := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
VALGRINDFLAGS = --trace-children=yes --leak-check=full --show-leak-kinds=all

.PHONY: all clean run valgrind

all: main run clean

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# Add all objects here!
OBJECTS= main.o map.o tile.o projectile.o tower.o game.o enemy.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o main.out $(OBJECTS) $(LDFLAGS)

clean:
	$(RM) *.o main.out

run:
	@./main.out

valgrind: main
	@valgrind $(VALGRINDFLAGS) ./main.out