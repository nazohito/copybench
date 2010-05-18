#!/bin/bash

DIR=`pwd`

SRC=$DIR/srcfile
DST=$DIR/dstfile
TIMEX="/usr/bin/time -p"
PREPARE='rm $DST >& /dev/null ; sync; sync; sync; sudo sh -c "echo 3 > 
/proc/sys/vm/drop_caches"'
REPEAT=3

if [ ! -f $SRC ]; then
    echo "[ERROR] Please create src file: path=$SRC" 1>&2
    exit 1
fi

for test in rw_cp rw_fadv_cp mm_sync_cp mm_sync_madv_cp mw_cp mw_madv_cp; do
  echo $test
  for i in `seq 1 $REPEAT`; do
      eval $PREPARE;
      $TIMEX ./${test} ${SRC} ${DST} 2>&1 | grep real;
  done
  echo
done
