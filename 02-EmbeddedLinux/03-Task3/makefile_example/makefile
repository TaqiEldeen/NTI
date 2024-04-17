CC := RPI4-gcc
CFLAGS := -Wall -Wextra -O2

static: main.c static_lib
	$(CC) $(CFLAGS) -o main_static main.c -L. -lstatic -I./include

dynamic: main.c dynamic_lib
	$(CC) $(CFLAGS) -shared -o main_dynamic main.c -L. -ldynamic -I./include

static_lib:
	$(CC) $(CFLAGS) -c ./lib/source/*.c
	ar rcs libstatic.a ./lib/source/*.o

dynamic_lib:
	$(CC) $(CFLAGS) -fPIC -c ./lib/source/*.c
	$(CC) -shared -o libdynamic.so ./lib/source/*.o