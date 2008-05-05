#!/bin/bash -x

SRC=/data/5Gfile
DST=/data2/5Gfile
TIMEX=time
PREPARE='rm $DST; sync; sync; sync; sudo sh -c "echo 3 > /proc/sys/vm/drop_caches"'
REPEAT=1

(for i in `seq 1 $REPEAT`; do eval $PREPARE; $TIMEX ./rw_cp ${SRC} ${DST}; done;)
(for i in `seq 1 $REPEAT`; do eval $PREPARE; $TIMEX ./rw_fadv_cp ${SRC} ${DST}; done;)
(for i in `seq 1 $REPEAT`; do eval $PREPARE; $TIMEX ./mm_sync_cp ${SRC} ${DST}; done;)
(for i in `seq 1 $REPEAT`; do eval $PREPARE; $TIMEX ./mm_sync_madv_cp ${SRC} ${DST}; done;)
(for i in `seq 1 $REPEAT`; do eval $PREPARE; $TIMEX ./mw_cp ${SRC} ${DST}; done;)
(for i in `seq 1 $REPEAT`; do eval $PREPARE; $TIMEX ./mw_madv_cp ${SRC} ${DST}; done;)
