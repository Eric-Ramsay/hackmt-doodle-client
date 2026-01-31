CXX      := g++
TARGET   := ../bin/main
SRC      := main.cpp
OBJ      := $(SRC:.cpp=.o)

CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic
CXXFLAGS += -DCPPHTTPLIB_OPENSSL_SUPPORT

LDLIBS   := -lssl -lcrypto

PKG_CONFIG ?= pkg-config

SFML_CFLAGS  := $(shell $(PKG_CONFIG) --cflags sfml-all 2>/dev/null)
SFML_LDFLAGS := $(shell $(PKG_CONFIG) --libs sfml-all 2>/dev/null)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS) $(SFML_CFLAGS) $(SFML_LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
