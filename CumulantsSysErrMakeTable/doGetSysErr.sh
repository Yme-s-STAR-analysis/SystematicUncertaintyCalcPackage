#!/bin/bash 

# This is just a template of making LATEX table with root files.

# Exec. run arguments are showing below:
# :folder path: a string, the path to the root files (root path)
# :rapidity index: a string (indeed an integer), 1 to 7
# :particle tag: Netp, Pro or Pbar
# :var tag: C1 ~ C4, R21 ~ R42, k1 ~ k4, k21 ~ k41, ...
# :table path: to save the LATEX table source codes

FPATH=/Users/huangyige/Work/DataAnalysis/star/BES2/19p6/18AprSys/roots
RIDX=y5
PTAG=Netp
VTAG=C1
TPATH=tables

if [ ! -d $TPATH ]; then
        mkdir $TPATH
fi

./run $FPATH $RIDX $PTAG $VTAG $TPATH