#!/bin/zsh -x

SRC=/data/5Gfile
DST=/data2/5Gfile
TIMEX=time
PREPARE='rm $DST; sync; sync; sync; sudo sh -c "echo 3 > /proc/sys/vm/drop_caches"'
REPEAT=1

eval $PREPARE
(repeat $REPEAT $TIMEX ./rw_cp ${SRC} ${DST})
eval $PREPARE
(repeat $REPEAT $TIMEX ./rw_fadv_cp ${SRC} ${DST})
eval $PREPARE
(repeat $REPEAT $TIMEX ./mm_sync_cp ${SRC} ${DST})
eval $PREPARE
(repeat $REPEAT $TIMEX ./mm_sync_madv_cp ${SRC} ${DST})
eval $PREPARE
(repeat $REPEAT $TIMEX ./mw_cp ${SRC} ${DST})
eval $PREPARE
(repeat $REPEAT $TIMEX ./mw_madv_cp ${SRC} ${DST})
