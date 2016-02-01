# Description #
copybench includes various filecopy programs in different implementations for UNIX environment.

# Purpose #
copybench may be used as the benchmarking program for Storage Hardware and Operationg System (e.g. I/O, Memory, File System).

# Detail #
copybench includes following implementations.

  * mmap -> mmap -> memcpy (default, +madvise)
  * mmap -> write (default, +madvice)
  * read -> write (default, +posix\_fadvise)

# Build #

You can build copybench by the following commands.

```
$ ./configure
$ make
```

If you got the source code from svn, you need to execute `./autogen.sh` before executing `configure` script.

# Execute #

First, you need to create large empty file by `dd` command. This command creates 5G file.

```
$ dd if=/dev/zero of=5Gfile bs=1G count=5
```

Then, edit following part of `test.sh` to appropriate path.

```
SRC=/data/5Gfile
DST=/data2/5Gfile
```

Finnaly, please execute test.sh.

```
$ ./test.sh
```

During execution, you need to input sudo password for clearing buffer cache.

# Contact #
http://kzk9.net/