# makefile simples - ainda nao compila nada (nao tem implementacao dos cpp)

CXX := g++
SRC_DIR := src
SRCS := $(shell find $(SRC_DIR) -name "*.cpp") # inclui todos os arquivos .cpp em src/
BUILD_DIR := build/obj
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o) # troca a extensao .cpp por .o para gerar a lista de objetos
TEST_DIR = ./tests
COVERAGE_DIR = ./coverage
TARGET := game
TARGET_TESTS=game_tests

CXXFLAGS := -Iinclude -g -O0 -Wall -Wextra -Wconversion -Wsign-conversion -Werror -Wno-unused-parameter -std=c++11 -pedantic-errors -fdiagnostics-color=always
# usa o pkg-config para obter as flags de compilacao e ligacao do SFML
PKG_CFLAGS := $(shell PKG_CONFIG_PATH=build pkg-config --cflags sfml-graphics sfml-window sfml-audio sfml-system nlohmann_json)
PKG_LIBS := $(shell PKG_CONFIG_PATH=build pkg-config --libs sfml-graphics sfml-window sfml-audio sfml-system nlohmann_json)

# adiciona as flags de compilacao do pkg-config para encontrar os headers do SFML
CXXFLAGS += $(PKG_CFLAGS)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(PKG_LIBS)

# gera arquivos .d para recompilar só o necessário
CXXFLAGS += -MMD -MP

# cria arquivos obj em uma estrutura de pastas igual do src
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

run: $(TARGET)
	./$(TARGET)

run_tests: tests
	./${TEST_DIR}/${TARGET_TESTS}

coverage: run_tests
	gcovr -r . --exclude="third_party/doctest.h"
	gcovr -r . --exclude="third_party/doctest.h" -b	

html_coverage: run_tests
	gcovr -r . --exclude="third_party/doctest.h" --html --html-details -o ${COVERAGE_DIR}/relatorio.html

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	rm -f ${TEST_DIR}/*.o ${TEST_DIR}/*.gcda ${TEST_DIR}/*.gcno ${TEST_DIR}/${TARGET_TESTS}
	rm -f ${COVERAGE_DIR}/*
	rm -rf ./doc/*
