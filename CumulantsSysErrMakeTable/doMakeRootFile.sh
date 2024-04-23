#!/bin/zsh

RPATH=/Path/to/root/files/folder
TPATH=../output
WITHX=0

if [ ! -d $TPATH ]; then
    mkdir $TPATH
fi

# y scan
for x (1 2 3 4 5 6) {
    for WITHX (0 1) {
        ./MakeRootFile $RPATH y0p$x $TPATH $WITHX
    }
}
# pt scan
./MakeRootFile $RPATH pt0p8 $TPATH $WITHX
for x (0 2 4 6 8) {
    for WITHX (0 1) {
        ./MakeRootFile $RPATH pt1p$x $TPATH $WITHX
    }
}