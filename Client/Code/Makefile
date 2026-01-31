CXX      = c++
TARGET   = ../bin/main
SRC      = main.cpp
OBJ      = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic
CXXFLAGS += -DCPPHTTPLIB_OPENSSL_SUPPORT

LDLIBS   = -lssl -lcrypto

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
  PKG_CONFIG = /opt/homebrew/bin/pkg-config
else
  PKG_CONFIG = pkg-config
endif

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
