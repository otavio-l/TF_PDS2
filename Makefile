# makefile simples - ainda nao compila nada (nao tem implementacao dos cpp)

CXX := /usr/bin/g++
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp) # wildcard inclui todos os arquivos .cpp em src/
OBJS := $(SRCS:.cpp=.o) # troca a extensao .cpp por .o para gerar a lista de objetos
TARGET := src/main

CXXFLAGS := -Iinclude -g -Wall -Wextra -Wconversion -Wsign-conversion -Werror -std=c++11 -pedantic-errors -fdiagnostics-color=always
# usa o pkg-config para obter as flags de compilacao e ligacao do SFML
PKG_CFLAGS := $(shell PKG_CONFIG_PATH=build pkg-config --cflags sfml-graphics)
PKG_LIBS := $(shell PKG_CONFIG_PATH=build pkg-config --libs sfml-graphics)

# adiciona as flags de compilacao do pkg-config para encontrar os headers do sf
CXXFLAGS += $(PKG_CFLAGS)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(PKG_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
