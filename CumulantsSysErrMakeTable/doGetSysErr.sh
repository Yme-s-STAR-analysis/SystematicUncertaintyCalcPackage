#!/bin/zsh 

# This is just a template of making LATEX table with root files.

# Exec. run arguments are showing below:
# :folder path: a string, the path to the root files (root path)
# :rapidity index: a string (indeed an integer), 1 to 7
# :particle tag: Netp, Pro or Pbar
# :var tag: C1 ~ C4, R21 ~ R42, k1 ~ k4, k21 ~ k41, ...
# :table path: to save the LATEX table source codes

FPATH=/Users/huangyige/Work/DataAnalysis/star/BES2/14p6/cumulant/240111Sys/roots
RIDX=y0p5
PTAG=Pbar
# VTAG=R42
TPATH=../tables

if [ ! -d $TPATH ]; then
        mkdir $TPATH
fi

# cumulants
for x (1 2 3 4) {
        echo C$x
        ./run $FPATH cum.cbwc.$RIDX $PTAG C$x $TPATH
        if [[ $PTAG != "Netp" ]] {
                echo k$x
                ./run $FPATH cum.cbwc.$RIDX $PTAG k$x $TPATH
        }
}
# cumulant ratios
for x (21 32 42) {
        echo R$x
        ./run $FPATH cum.cbwc.$RIDX $PTAG R$x $TPATH
}
# kappa ratios
for x (21 31 41) {
        if [[ $PTAG != "Netp" ]] {
                echo k$x
                ./run $FPATH cum.cbwc.$RIDX $PTAG k$x $TPATH
        }
}