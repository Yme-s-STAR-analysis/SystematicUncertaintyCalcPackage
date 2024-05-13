#!/bin/zsh

RPATH=/Path/to/root/files/folder
TPATH=../output

if [ ! -d $TPATH ]; then
    mkdir $TPATH
fi

# y scan
for x (1 2 3 4 5 6) {
    WITHX=0
    ./MakeRootFile $RPATH y0p$x $TPATH $WITHX $nPart3
    WITHX=1
    ./MakeRootFile $RPATH y0p$x $TPATH $WITHX $nPart3X
}
# pt scan
./MakeRootFile $RPATH pt0p8 $TPATH $WITHX
for x (0 2 4 6 8) {
    WITHX=0
    ./MakeRootFile $RPATH pt1p$x $TPATH $WITHX $nPart3
    WITHX=1
    ./MakeRootFile $RPATH pt1p$x $TPATH $WITHX $nPart3X
}