#!/bin/bash -x

SRC=/data/5Gfile
DST=/data2/5Gfile
TIMEX=time
PREPARE='rm $DST; sync; sync; sync; sudo sh -c "echo 3 > /proc/sys/vm/drop_caches"'
REPEAT=1

eval $PREPARE
(for i in `seq 0 $REPEAT`; do $TIMEX ./rw_cp ${SRC} ${DST}; done;)
eval $PREPARE
(for i in `seq 0 $REPEAT`; do $TIMEX ./rw_fadv_cp ${SRC} ${DST}; done;)
eval $PREPARE
(for i in `seq 0 $REPEAT`; do $TIMEX ./mm_sync_cp ${SRC} ${DST}; done;)
eval $PREPARE
(for i in `seq 0 $REPEAT`; do $TIMEX ./mm_sync_madv_cp ${SRC} ${DST}; done;)
eval $PREPARE
(for i in `seq 0 $REPEAT`; do $TIMEX ./mw_cp ${SRC} ${DST}; done;)
eval $PREPARE
(for i in `seq 0 $REPEAT`; do $TIMEX ./mw_madv_cp ${SRC} ${DST}; done;)
