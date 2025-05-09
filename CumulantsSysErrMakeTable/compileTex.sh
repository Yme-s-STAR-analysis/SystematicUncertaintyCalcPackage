cd ../table
echo "Compiling LaTeX files: pt scan"
pdflatex -interaction=batchmode pt_Concated.tex
echo "Compiling LaTeX files: y scan"
pdflatex -interaction=batchmode y_Concated.tex
echo "Now renaming: energy = $1"
mv ../table/pt_Concated.pdf ../table/ptscan_${1}GeV_pfm.pdf
mv ../table/y_Concated.pdf ../table/yscan_${1}GeV_pfm.pdf