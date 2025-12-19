# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
LDFLAGS = 
TEST_LDFLAGS = -lUnitTest++

# Имена файлов
SOURCES = modAlphaCipher.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = cipher


# Правило по умолчанию
all: $(TARGET) $(TEST_TARGET)

# Сборка основной программы
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Сборка тестовой программы
$(TEST_TARGET): $(TEST_OBJECTS) modAlphaCipher.o
	$(CXX) $(TEST_OBJECTS) modAlphaCipher.o -o $(TEST_TARGET) $(TEST_LDFLAGS)

# Компиляция modAlphaCipher.cpp
modAlphaCipher.o: modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c modAlphaCipher.cpp

# Компиляция main.cpp
main.o: main.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Компиляция тестов
test_modAlphaCipher.o: test_modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c test_modAlphaCipher.cpp

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET)

# Пересборка
rebuild: clean all

.PHONY: all test run clean rebuild
