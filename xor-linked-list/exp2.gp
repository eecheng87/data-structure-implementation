# This experiment is trying to compare speed of sorting algo
reset
set ylabel 'time(ms)'
set xlabel '# of experiments'
set title 'Different algo. to time'
set key left top
set term png enhanced font 'Verdana,10'
set output 'exp2.png'
plot [0:21][:] \
'exp2.out' using 1:2 with linespoints linewidth 2 title "optimize merge sort",\
'' using 1:3 with linespoints linewidth 2 title "merger sort",\
'' using 1:4 with linespoints linewidth 2 title "insertion sort",\