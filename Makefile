##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR                     := /usr/$(TARGET_DIR)/ar rcu
CXX                    := /usr/$(TARGET_DIR)/g++
# can be set in the env. vars, ie. export CC='ccccc'
CC                     ?= /usr/$(TARGET_DIR)/gcc
CXXFLAGS               :=  -g -O0 -Wall -Werror
CFLAGS                 :=  -g -O0 -Wall -Werror -std=c89 -pedantic
CFLAGSGTK       	   :=  -g -O0 -Wall -std=c11
ASFLAGS                := 
AS                     := /usr/$(TARGET_DIR)/as
# can be set in the env. vars, ie. export TARGET_DIR='xxxxx'
TARGET_DIR            ?= bin

SOBOUTILS_INSTALL_INCLUDE_PATH ?= /usr/local/share/soboutils
SOBO_COMMON_INCLUDE_PATH	   ?= /usr/local/share   # upper directory - always for using in other projects
SOBOUTILS_LIB_PATH     		   ?= /usr/local/lib/soboutils
.PHONY: clean

all: libsoboutils_static
alltest: libsoboutils_static test_utils_file test_utils_string test_utils_time


utils_time: src/utils_time.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_DIR)/utils_time.o \
	-c src/utils_time.c \
	-I include
	
	chmod 777 $(TARGET_DIR)/utils_time.o


utils_file: src/utils_file.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_DIR)/utils_file.o \
	-c src/utils_file.c \
	-I include

	chmod 777 $(TARGET_DIR)/utils_file.o

utils_list: src/utils_list.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_DIR)/utils_list.o \
	-c src/utils_list.c \
	-I include

	chmod 777 $(TARGET_DIR)/utils_list.o

common: src/common.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_DIR)/common.o \
	-c src/common.c \
	-I include

	chmod 777 $(TARGET_DIR)/common.o


utils_string: src/utils_string.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_DIR)/utils_string.o \
	-c src/utils_string.c \
	-I include
	
	chmod 777 $(TARGET_DIR)/utils_string.o


utils_gtk: src/utils_gtk.c
	$(CC) $(CFLAGSGTK) `pkg-config --cflags gtk4` -fpic -o \
	$(TARGET_DIR)/utils_gtk.o \
	-c src/utils_gtk.c \
	-I include

	$(CC) $(CFLAGSGTK) `pkg-config --cflags gtk4` -fpic -o \
	$(TARGET_DIR)/gtk_validator_helpers.o \
	-c src/gtk_validator_helpers.c \
	-I include
	
	ar rcs $(TARGET_DIR)/libsoboutils_gtk.a \
	$(TARGET_DIR)/utils_gtk.o \
	$(TARGET_DIR)/gtk_validator_helpers.o
	
	chmod 777 $(TARGET_DIR)/libsoboutils_gtk.a


OBJS_FOR_LIB = $(wildcard $(TARGET_DIR)/*.o)
libsoboutils_static: utils_time utils_file utils_string
	ar rcs $(TARGET_DIR)/libsoboutils.a \
		$(OBJS_FOR_LIB)
	rm -f $(OBJS_FOR_LIB)


test_utils_file: src/test/test_utils_file.c
	$(CC) $(CFLAGS) -o $(TARGET_DIR)/test_utils_file \
	src/test/test_utils_file.c \
	$(TARGET_DIR)/libsoboutils.a \
	-I include

test_utils_string: src/test/test_utils_string.c
	$(CC) $(CFLAGS) -o $(TARGET_DIR)/test_utils_string \
	src/test/test_utils_string.c \
	$(TARGET_DIR)/libsoboutils.a \
	-I include

test_utils_time: src/test/test_utils_time.c
	$(CC) $(CFLAGS) -o $(TARGET_DIR)/test_utils_time \
	src/test/test_utils_time.c \
	$(TARGET_DIR)/libsoboutils.a \
	-I include


install:
	@echo "\nThis operation requires the SUDO access.\n"
	sudo mkdir -p $(SOBOUTILS_LIB_PATH)
	sudo mkdir -p $(SOBOUTILS_INSTALL_INCLUDE_PATH)
	sudo cp -rf $(TARGET_DIR)/libsoboutils.a $(SOBOUTILS_LIB_PATH)/
	sudo cp -rf include/soboutils/* $(SOBOUTILS_INSTALL_INCLUDE_PATH)/


installgtk: utils_gtk install
	sudo cp -rf $(TARGET_DIR)/libsoboutils_gtk.a $(SOBOUTILS_LIB_PATH)/


clean:
	@echo "\nThis operation requires the SUDO access.\n"
	sudo rm -rf $(TARGET_DIR)
