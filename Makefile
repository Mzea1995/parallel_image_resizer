CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread `pkg-config --cflags --libs opencv4`
TARGET = resize_image
SRC = resize_image.cpp
TEST_TARGET = test_resize_image
TEST_SRC = test_resize_image.cpp


compile: $(TARGET)

compile_test: $(TEST_TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)
