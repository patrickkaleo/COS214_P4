TARGET=taskforge
FLAGS= -g -std=c++11 -Werror -Wall -Iinclude -Isrc
CXX = g++
OBJ_DIR=obj

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=$(OBJ_DIR)/%.o)

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

run : $(TARGET)
	./$(TARGET)

mem : $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) 2> memory.log

compress: bin/compress bin/pdf
	./bin/compress
	
clean:
	rm -rf $(OBJ_DIR) $(TARGET) 
	clear


