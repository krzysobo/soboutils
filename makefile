##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR                     := /usr/bin/ar rcu
CXX                    := /usr/bin/g++
# can be set in the env. vars, ie. export CC='ccccc'
CC                     := /usr/bin/gcc
CXXFLAGS               :=  -g -O0 -Wall -Werror
CFLAGS                 :=  -g -O0 -Wall -Werror
ASFLAGS                := 
AS                     := /usr/bin/as
# can be set in the env. vars, ie. export TARGET_PATH='xxxxx'
TARGET_PATH            ?= 'bin'
SOBOUTILS_INCLUDE_PATH ?= '/usr/local/share/soboutils'
SOBOUTILS_LIB_PATH     ?= '/usr/local/lib/soboutils'
.PHONY: clean

all: libsoboutils_static
alltest: libsoboutils_static test_utils_file test_utils_string test_utils_time

utils_time: src/utils_time.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_PATH)/utils_time.o \
	-c src/utils_time.c \
	-I include
	
	chmod 777 $(TARGET_PATH)/utils_time.o


utils_file: src/utils_file.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_PATH)/utils_file.o \
	-c src/utils_file.c \
	-I include

	chmod 777 $(TARGET_PATH)/utils_file.o


utils_string: src/utils_string.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_PATH)/utils_string.o \
	-c src/utils_string.c \
	-I include
	
	chmod 777 $(TARGET_PATH)/utils_string.o


libsoboutils_static: utils_time utils_file utils_string
	ar rcs $(TARGET_PATH)/libsoboutils.a \
	$(TARGET_PATH)/utils_time.o \
	$(TARGET_PATH)/utils_file.o \
	$(TARGET_PATH)/utils_string.o \

	rm -f $(TARGET_PATH)/utils_time.o
	rm -f $(TARGET_PATH)/utils_file.o
	rm -f $(TARGET_PATH)/utils_string.o


test_utils_file: src/test/test_utils_file.c
	$(CC) $(CFLAGS) -o bin/test_utils_file \
	src/test/test_utils_file.c \
	$(TARGET_PATH)/libsoboutils.a \
	-I include

test_utils_string: src/test/test_utils_string.c
	$(CC) $(CFLAGS) -o bin/test_utils_string \
	src/test/test_utils_string.c \
	$(TARGET_PATH)/libsoboutils.a \
	-I include

test_utils_time: src/test/test_utils_time.c
	$(CC) $(CFLAGS) -o bin/test_utils_time \
	src/test/test_utils_time.c \
	$(TARGET_PATH)/libsoboutils.a \
	-I include


install:
	@echo "\nThis operation requires the SUDO access.\n"
	sudo mkdir -p $(SOBOUTILS_LIB_PATH)
	sudo mkdir -p $(SOBOUTILS_INCLUDE_PATH)
	sudo cp -rf $(TARGET_PATH)/libsoboutils.a $(SOBOUTILS_LIB_PATH)/
	sudo cp -rf include/soboutils/* $(SOBOUTILS_INCLUDE_PATH)/


clean:
	@echo "\nThis operation requires the SUDO access.\n"
	sudo rm -rf $(TARGET_PATH)
