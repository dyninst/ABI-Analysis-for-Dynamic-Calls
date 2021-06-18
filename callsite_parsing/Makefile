warnings := -Wall -Wextra -Wpedantic
std := -std=c11
opt := -O3
debug := -g -gdwarf-4
arch := -mavx512f

all:
	$(CC) $(std) $(warnings) $(opt) $(debug) $(arch) -fPIC -shared -o libfoo.so foo.c
	$(CC) $(std) $(warnings) $(opt) $(debug) $(arch) -o test test.c -L. -lfoo
	$(CC) $(std) $(warnings) $(opt) -o reader reader.c -ldw -lelf

.PHONY: clean
clean:
	rm -rf test libfoo.so *.o *.out reader

.PHONY: run
run:
	objdump -d -M intel test > obj.out
#	llvm-dwarfdump --all test > llvm-dwarf.out
	eu-readelf -aw test > dwarf.out
	./reader test > reader.out