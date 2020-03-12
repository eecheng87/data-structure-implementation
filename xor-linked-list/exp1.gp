# This experiment is trying to find best 'S'
reset
set ylabel 'time(ms)'
set xlabel 'S'
set title 'Different S to sorting time'
set key left top
set term png enhanced font 'Verdana,10'
set output 'exp1.png'
plot [0:1000][:] \
'exp1.out' using 1:2 with linespoints linewidth 2 title "time of insert-merge sort",\
