CXX = "C:\Program Files\MinGW\bin\g++.exe"
CXXFLAGS = -O2 -static
TARGET = build/test.dll
SRC = test.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) -shared -o $(TARGET) $(SRC) $(CXXFLAGS)

