#!/bin/bash 

# This is just a template of making LATEX table with root files.

# Exec. MakeRootFile arguments are showing below:
# :folder path: a string, the path to the root files (root path)
# :rapidity index: a string (indeed an integer), 1 to 7
# :out dir: a string, path to save the out put root file

FPATH=/Users/huangyige/Work/DataAnalysis/star/BES2/19p6/18AprSys/roots
# RIDX=y5
OPATH=roots

if [ ! -d $OPATH ]; then
        mkdir $OPATH
fi

for RIDX in y1 y2 y3 y4 y5 y6 y7 ; do
        ./MakeRootFile $FPATH $RIDX $OPATH
done;