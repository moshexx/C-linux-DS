CC = gcc

#EXTRA: let us add flags from the terminal. ex. make EXTRA=-Dheap_based
EXTRA = 
FLAGS = -ansi -pedantic-errors -Wall -Wextra $(EXTRA)
DEBUG_FLAGS = $(FLAGS) -g
RELEASE_FLAGS = $(FLAGS) -DNDEBUG -O3
INCLUDES = -I./include -lm
FILE_NAME = hoffman

VLG = valgrind --leak-check=yes --track-origins=yes

SRC = $(wildcard src/*.c)
OBJ = $(addprefix obj/,$(notdir $(SRC:.c=.o)))

#$(warning $(OBJ))

debug: $(FILE_NAME)_debug

$(FILE_NAME)_debug: bin/$(FILE_NAME)_debug

bin/$(FILE_NAME)_debug: test/test_$(FILE_NAME).c $(PWD)/lib/libds_debug.so
	$(CC) $(DEBUG_FLAGS) -o $@ $^ $(INCLUDES) -Wl,-rpath=$(PWD)/lib

$(PWD)/lib/libds_debug.so: $(OBJ)
	$(CC) $(DEBUG_FLAGS) -o $@ -shared $^ $(INCLUDES)

obj/%.o: src/%.c
	$(CC) $(DEBUG_FLAGS) -c -o $@ -fPIC $< $(INCLUDES)

run:
	./bin/$(FILE_NAME)_debug
vlg:
	$(VLG) ./bin/$(FILE_NAME)_debug


#release: bin/$(FILE_NAME)_release

#$(FILE_NAME)_release: bin/$(FILE_NAME)_release

#bin/$(FILE_NAME)_release: test/test_$(FILE_NAME).c $(PWD)/lib/libds_release.so
#	$(CC) $(RELEASE_FLAGS) -o $@ $^ $(INCLUDES) -Wl,-rpath=$(PWD)/lib \

#$(PWD)/lib/libds_release.so: $(OBJ)
#	$(CC) $(RELEASE_FLAGS) -o $@ -shared $^ $(INCLUDES)

#obj/%.o: src/%.c
#	$(CC) $(RELEASE_FLAGS) -c -o $@ -fPIC $< $(INCLUDES)

#run_release:
#	./bin/$(FILE_NAME)_release
#vlg_release:
#	$(VLG) ./bin/$(FILE_NAME)_release

.PHONY: clean
clean:
	rm -f obj/* lib/* bin/* *.o */*.o
