EXTRA_DIST = test.sh

bin_PROGRAMS = rw_cp rw_fadv_cp mm_sync_cp mm_sync_madv_cp mw_cp mw_madv_cp
CFLAGS = -D__USE_FILE_OFFSET64

# read -> write
rw_cp_SOURCES = read-write.c

rw_fadv_cp_SOURCES = read-write.c
rw_fadv_cp_CFLAGS = -DUSE_FADVISE

# mmap -> mmap
mm_sync_cp_SOURCES = mmap-mmap.c

mm_sync_madv_cp_SOURCES = mmap-mmap.c
mm_sync_madv_cp_CFLAGS = -DUSE_MADVISE

# mmap -> write
mw_cp_SOURCES = mmap-write.c

mw_madv_cp_SOURCES = mmap-write.c
mw_madv_cp_CFLAGS = -DUSE_MADVISE
