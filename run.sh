#/usr/bin/bash

make

NUM_POINTS=${1:-6}
LEFT_BOUND=${2:--1}
RIGHT_BOUND=${3:-1}
METHOD=${4:-"ch"}

# генерируем сетку
./CreateLayout.out $NUM_POINTS $LEFT_BOUND $RIGHT_BOUND $METHOD > in.txt 
# строим полином
./PolynomialInterpolation.out < in.txt > out.txt 

# рисуем картинку
gnuplot -c PlotIt.gnuplot out.txt plot.png