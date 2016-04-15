
.SUFFIXES: .cpp .o

CC = g++
FLAGS = -std=c++11

.PHONY: all dir run

LIB_FLAGS = -framework GLUT -framework OpenGL

BUILD_DIR = build
SOURCE_DIR = src/lib
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)

OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

MAIN = src/main.cpp

EXECUTABLE = output

all: dir run

$(EXECUTABLE): dir $(OBJECTS) $(MAIN)
	$(CC) -o output $(LIB_FLAGS) $(OBJECTS) $(MAIN)

$(OBJECTS): $(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf build && rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

dir:
	mkdir -p $(BUILD_DIR)