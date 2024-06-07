#!/bin/zsh

FPATH=/Users/huangyige/Work/DataAnalysis/star/BES2/OverAll/3cum/17/roots
STAG=y0p5
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

for WITHX (0 1) {
    ./MultiFunction $FPATH $WITHX $STAG $LPATH $RPATH $CPATH $BPATH
}
