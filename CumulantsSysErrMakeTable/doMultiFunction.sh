#!/bin/zsh

FPATH=$(PWD)/../../roots
# STAG=y0p5
LPATH=../table
RPATH=../output
CPATH=../cplot
BPATH=../barlow

if [ ! -d $LPATH ]; then
        mkdir $LPATH
fi

if [ ! -d $RPATH ]; then
        mkdir $RPATH
fi

if [ ! -d $CPATH ]; then
        mkdir $CPATH
fi

if [ ! -d $BPATH ]; then
        mkdir $BPATH
fi

for STAG (y0p1 y0p2 y0p3 y0p4 y0p6 pt0p8 pt1p0 pt1p2 pt1p4 pt1p6 pt1p8) {
        echo "CURRENT TAG: $STAG"
        ./LongNoteItems $FPATH 1 $STAG $LPATH $RPATH $CPATH $BPATH
}
