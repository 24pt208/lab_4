# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -Wno-sign-compare
LDFLAGS = 
TEST_LDFLAGS = -lUnitTest++

# Имена файлов
SOURCES = module.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = route_cipher

# Правило по умолчанию
all: $(TARGET) $(TEST_TARGET)

# Сборка основной программы
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Сборка тестовой программы
$(TEST_TARGET): $(TEST_OBJECTS) module.o
	$(CXX) $(TEST_OBJECTS) module.o -o $(TEST_TARGET) $(TEST_LDFLAGS)

# Компиляция module.cpp
module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -c module.cpp

# Компиляция main.cpp
main.o: main.cpp module.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Компиляция тестов
test_routeCipher.o: test_routeCipher.cpp module.h
	$(CXX) $(CXXFLAGS) -c test_routeCipher.cpp

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET)


.PHONY: all test test_key test_encrypt test_decrypt test_specific run clean rebuild
