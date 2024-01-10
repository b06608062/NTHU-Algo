CC = g++
CFLAGS = -std=c++17 -O2 -Wall
TARGET = 112062636_bonus3
SRCS = 112062636_bonus3.cpp
OBJS = 112062636_bonus3.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)