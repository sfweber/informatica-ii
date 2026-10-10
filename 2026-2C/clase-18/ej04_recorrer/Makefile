# makefile | Informatica II
# Uso:
#   make        compila el proyecto -> ejecutable ./programa
#   make run    compila y ejecuta
#   make clean  borra objetos y ejecutable

CXX      = g++
CXXFLAGS  = -Wall -Wextra -std=c++17 -Iinclude -g
SRC     = $(wildcard src/*.cpp)
OBJ     = $(SRC:.cpp=.o)
BIN     = programa

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all run clean
