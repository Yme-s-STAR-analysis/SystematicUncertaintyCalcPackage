#!/bin/zsh

RPATH=/Users/huangyige/Work/DataAnalysis/star/BES2/14p6/cumulant/240111Sys/roots
TPATH=../output

if [ ! -d $TPATH ]; then
        mkdir $TPATH
fi

# y scan
for x (1 2 3 4 5) {
    ./MakeRootFile $RPATH cum.cbwc.y0p$x $TPATH
}
# pt scan
./MakeRootFile $RPATH cum.cbwc.pt0p8 $TPATH
for x (0 2 4 6 8) {
    ./MakeRootFile $RPATH cum.cbwc.pt1p$x $TPATH
}