EXE_NAME := Mesh_World

CFLAGS = -std=c++17 -O2
LDFLAGS = -L"/usr/lib" ../src/libIrrKlang.so -ldl -lglfw -lGLU -pthread

VPATH = src:

BUILD_DIR := ../build/$(EXE_NAME)
SRC_DIR := src


# Source files
C_SRCS := $(wildcard *.cpp) \
	$(wildcard *.c) \


$(EXE_NAME): $(C_SRCS)
	g++ -Wall -g $(CFLAGS) -o $(BUILD_DIR) $(C_SRCS) $(LDFLAGS)

debug:
	g++ -Wall -g $(CFLAGS) -o $(BUILD_DIR) $(C_SRCS) $(LDFLAGS)
	
release:
	g++ $(CFLAGS) -o $(BUILD_DIR) $(C_SRCS) $(LDFLAGS)

test:
	./../build/$(EXE_NAME)

clean:
	rm -f ../build/*.*
	rm -f ../build/*