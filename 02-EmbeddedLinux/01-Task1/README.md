# Static Linking

## Steps

### 1- Compile your library source files to get object files
```bash
gcc -c <source_files>
```
> This will compile the source file into object files



### 2- Archive the object files
```bash
ar rcs liblibrary.a library.o
```
> r --->  Insert the files member... into archive (with replacement). This operation differs from q in that any previously existing members are deleted if their names match those being added.

> c ---> Create the archive. The specified archive is always created if it did not exist, when you request an update. But a warning is issued unless you specify in advance that you expect to create it, by using this modifier.

> s --->Write an object-file index into the archive, or update an existing one, even if no other change is made to the archive. You may use this modifier flag either with any operation, or alone. Running "ar s" on an archive is equivalent to running ranlib on it.


### 3- Compile your project files with this library static way

```bash
gcc -c main.c -I ./Include 
```
> Get the main object file. Also specifing the include folder

```bash
gcc main.o Lib/lib[name].a -o main_static.elf
```

> Note you can make static linking for all libraries by using -static when compiling

# Dynamic Linking

## Steps

### 1- Compile the library source files using position independent code flag

```bash
gcc -c -fpic *.c
```
> fpic flag is used to indicate a position independent code. This makes a flag for the system loader to put this at any position in the RAM


### 2- Produce the dynamic library

```bash
gcc -shared -o lib[name].so *.o
```

> This will produce the dynamic library. Notice that dynamic lib has .so extension

### 3- link with your applicaion

```bash
gcc main.c -I./Include -L./Lib -l[name] 
```

> -L./lib is the location of the dynamic library. While -l[name] is the name of the library -it will expand to libname.so-


# Differences 

```bash
ldd main_static
ldd main_dynamic
ldd main_all_static
```

- ldd command will specify which libraries is being linked dynamically

- Also the size of statically linked program is larger

