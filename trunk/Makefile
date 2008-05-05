GCC = gcc -Wall -O2 -D__USE_FILE_OFFSET64

all: rw_cp rw_fadv_cp mm_sync_cp mm_sync_madv_cp mw_cp mw_madv_cp
clean:
	rm rw_cp rw_fadv_cp mm_sync_cp mm_sync_madv_cp mw_cp mw_madv_cp

rw_cp: read-write.c
	$(GCC) -o rw_cp read-write.c

rw_fadv_cp: read-write.c
	$(GCC) -DUSE_FADVISE -o rw_fadv_cp read-write.c

mm_sync_cp: mmap-mmap.c
	$(GCC) -o mm_sync_cp mmap-mmap.c

mm_sync_madv_cp: mmap-mmap.c
	$(GCC) -DUSE_MADVISE -o mm_sync_madv_cp mmap-mmap.c

mw_cp: mmap-write.c
	$(GCC) -o mw_cp mmap-write.c

mw_madv_cp: mmap-write.c
	$(GCC) -DUSE_MADVISE -o mw_madv_cp mmap-write.c
