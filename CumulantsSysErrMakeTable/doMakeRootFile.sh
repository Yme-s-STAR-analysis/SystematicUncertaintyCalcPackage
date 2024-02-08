#!/bin/zsh

RPATH=/Users/huangyige/Work/DataAnalysis/star/BES2/14p6/cumulant/240206Sys/roots
TPATH=../output
WITHX=0

if [ ! -d $TPATH ]; then
        mkdir $TPATH
fi

# y scan
for x (1 2 3 4 5 6) {
    ./MakeRootFile $RPATH y0p$x $TPATH $WITHX
}
# pt scan
./MakeRootFile $RPATH pt0p8 $TPATH $WITHX
for x (0 2 4 6 8) {
    ./MakeRootFile $RPATH pt1p$x $TPATH $WITHX
}