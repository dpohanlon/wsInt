CXX = clang++

CPPFLAGS = -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual \
        -Wstrict-prototypes -Wmissing-prototypes -g -O2

SOURCES = $(wildcard src/*.cpp)
SOURCES += $(wildcard src/parser/*.cpp)
SOURCES += $(wildcard src/vm/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))


TARGET = bin/wsInt

all: $(TARGET)

$(TARGET): build $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $(TARGET)

build:
	@mkdir -p bin

.PHONY: clean
clean:
	@-rm -rf src/*.o
	@-rm -rf src/parser/*.o
	@-rm -rf src/vm/*.o

	@if [ -d bin ] ; \
		then rm -rf bin; \
	fi