CXX      := g++
TARGET   := ../bin/main
SRC      := main.cpp
OBJ      := $(SRC:.cpp=.o)

CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic
CXXFLAGS += -DCPPHTTPLIB_OPENSSL_SUPPORT

LDLIBS   := -lssl -lcrypto

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
