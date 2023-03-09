#!/usr/bin/gnuplot --persist

data = ARG1
out = ARG2

set terminal png size 1200,800
set output out

plot data using 1:2 with linespoints title 'F', \
     data using 1:3 with linespoints title 'canonical'