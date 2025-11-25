CXX := g++

SRC_DIR := src
TEST_DIR = tests
BUILD_DIR := build/obj
COVERAGE_DIR = coverage

SRCS := $(shell find $(SRC_DIR) -name "*.cpp") # inclui recursivamente todos os arquivos .cpp em src/
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o) # troca a extensao .cpp por .o para gerar a lista de objetos
TEST_SRCS := $(shell find $(TEST_DIR) -name "*.cpp")
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/tests/%.o)
OBJS_NO_MAIN := $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) # todos os objetos exceto o main.o p/ nao dar multiple definition em testes


TARGET := game
TARGET_TESTS=game_tests

CXXFLAGS := -Iinclude -g -O0 -Wall -Wextra -Wconversion -Wsign-conversion -Werror -Wno-unused-parameter -std=c++11 -pedantic-errors -fdiagnostics-color=always --coverage
# usa o pkg-config para obter as flags de compilacao e ligacao do SFML
PKG_CFLAGS := $(shell PKG_CONFIG_PATH=build pkg-config --cflags sfml-graphics sfml-window sfml-audio sfml-system nlohmann_json)
PKG_LIBS := $(shell PKG_CONFIG_PATH=build pkg-config --libs sfml-graphics sfml-window sfml-audio sfml-system nlohmann_json)

# adiciona as flags de compilacao do pkg-config para encontrar os headers do SFML
CXXFLAGS += $(PKG_CFLAGS)


.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(PKG_LIBS)

tests: $(TEST_OBJS) $(OBJS_NO_MAIN) # linka os objetos dos testes com todos os objetos exceto o main.o
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_DIR)/$(TARGET_TESTS) $(PKG_LIBS)

# gera arquivos .d para recompilar só o necessário
CXXFLAGS += -MMD -MP


# cria arquivos obj em uma estrutura de pastas igual do src
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(TEST_OBJS:.o=.d)


run: $(TARGET)
	./$(TARGET)

run_tests: tests
	${TEST_DIR}/${TARGET_TESTS}

coverage: run_tests
	gcovr -r . --exclude="$(TEST_DIR)/doctest.h"

html_coverage: run_tests
	gcovr -r . --exclude=$(TEST_DIR)/doctest.h --html --html-details -o ${COVERAGE_DIR}/relatorio.html

clean:
	rm -rf $(BUILD_DIR) 
	rm -f $(TARGET)
	rm -f $(TEST_DIR)/$(TARGET_TESTS)
	rm -f ${COVERAGE_DIR}/*
	rm -rf ./doc/*
