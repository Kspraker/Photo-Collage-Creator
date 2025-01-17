#/*******************
#*Kaleb Spraker
#*CPSC 1020 001, F18
#*ksprake@clemson.edu
#********************/

CC=gcc
CFLAGS=-Wall -g
LFLAGS= -lm
TARGET= out


# Generate source and object lists
C_SRCS := \
	$(wildcard *.c) \
	$(wildcard src/*.c) \
	$(wildcard src/**/*.c)

HDRS := \
	$(wildcard *.h) \
	$(wildcard src/*.h) \
		$(wildcard src/**/*.h)

OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))

all: build
								 @echo "All Done"

# Link all built objects
build: $(OBJS)
								 $(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

# Catch root directory src files
bin/%.o: %.c $(HDRS)
								 @mkdir -p $(dir $@)
								 $(CC) $(CFLAGS) -c $< -o $@

# Catch all nested directory files
bin/%.o: src/%.c $(HDRS)
									@mkdir -p $(dir $@)
									$(CC) $(CFLAGS) -c $< -o $@

clean:
									rm -f $(TARGET)
									rm -rf bin

run: build
									./$(TARGET) sky.ppm out_file.ppm
which:
									@echo "FOUND SOURCES: ${C_SRCS}"
									@echo "FOUND HEADERS: ${HDRS}"
									@echo "TARGET OBJS: ${OBJS}"
