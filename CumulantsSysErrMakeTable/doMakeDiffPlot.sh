#!/bin/zsh 

# This is just a template of making diff. plots with root files.

# :folder path: a string, the path to the root files (root path)
# :scan tag: a string, like y0p5
# :particle tag: Netp, Pro or Pbar
# :var idx: 0 to 3 for C1 ~ C4, 4 to 6 for R21 ~ R42, 7 to 10 for k1 ~ k4, 11 to 13 fork21 ~ k41, ...
# :cent tag: centrality tag 0 to 8
# :fig path: to save the plot
# :withX: with RefMult3: 0, with RefMult3X: 1

FPATH=/Path/to/root/files/folder
RIDX=y0p5
# PTAG=Netp
# VTAG=6
CENTIDX=0
TPATH=../fig
WITHX=1

if [ ! -d $TPATH ]; then
        mkdir $TPATH
fi
# cumulants
for WITHX (0 1) {
    for PTAG (Netp Pro Pbar) {
        for (( VTAG=0; VTAG<7; VTAG++ )) {
            ./MakeDiffPlot $FPATH $RIDX $PTAG $VTAG $CENTIDX $TPATH $WITHX
        }
        if [[ $PTAG != "Netp" ]] {
            for (( VTAG=7; VTAG<=13; VTAG++ )) {
                ./MakeDiffPlot $FPATH $RIDX $PTAG $VTAG $CENTIDX $TPATH $WITHX
            }
        }
    }
}