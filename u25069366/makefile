TARGET=taskforge
FLAGS= -g -std=c++11 -Werror -Wall
CXX = g++
OBJ_DIR=obj

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

run : $(TARGET)
	./$(TARGET)

mem : $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) 2> memory.log

clean:
	rm -rf $(OBJ_DIR) $(TARGET)