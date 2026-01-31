CXX      = c++
TARGET   = ../bin/main
SRC      = main.cpp
OBJ      = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic
CXXFLAGS += -DCPPHTTPLIB_OPENSSL_SUPPORT

LDLIBS   = -lssl -lcrypto

PKG_CONFIG = pkg-config

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ \
	  `$(PKG_CONFIG) --cflags sfml-all 2>/dev/null` \
	  `$(PKG_CONFIG) --libs sfml-all 2>/dev/null` \
	  $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
