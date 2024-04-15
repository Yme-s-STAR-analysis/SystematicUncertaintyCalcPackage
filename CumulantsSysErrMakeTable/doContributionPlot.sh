#!/bin/zsh 

# This is just a template of making diff. plots with root files.

# :folder path: a string, the path to the root files (root path)
# :rapidity index: a string (indeed an integer), 1 to 7
# :particle tag: Netp, Pro or Pbar
# :var tag: C1 ~ C4, R21 ~ R42, k1 ~ k4, k21 ~ k41, ...
# :cent tag: centrality index, 0 to 8
# :save path: to save the contribution plots
# :withX: 0 for RefMult3, 1 for RefMult3X

FPATH=/Users/huangyige/Work/DataAnalysis/star/BES2/OverAll/3cum/19/roots
RIDX=y0p5
PTAG=Netp
# VTAG=6
CENTIDX=0
TPATH=../cplot

if [ ! -d $TPATH ]; then
        mkdir $TPATH
fi
# cumulants
for (( WITHX=0; WITHX<=1; WITHX++)) {
    for (( VTAG=0; VTAG<7; VTAG++ )) {
        ./PlotContribution $FPATH $RIDX $PTAG $VTAG $CENTIDX $TPATH $WITHX
    }
}

# if [[ $PTAG != "Netp" ]] {
#     for (( VTAG=7; VTAG<=13; VTAG++ )) {
#         ./PlotContribution $FPATH $RIDX $PTAG $VTAG $CENTIDX $TPATH $WITHX
#     }
# }