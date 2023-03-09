# Polynomial Interpolation

## Compile

```bash
make
```

## Create layout

```bash
./CreateLayout.out N a b m
```

where $N$ is number of points, $[a, b]$ is interval, m is method in $\{un, ch, rnd\}$. Save generated points in file use

```bash
./CreateLayout.out 6 -1 1 ch > in.txt
```

## Find Polynomail Interpolation

with points in in.txt use

```bash
./PolynomialInterpolation.out < in.txt
```

Save results in file use

```bash
./PolynomialInterpolation.out < in.txt > out.txt
```

## Plot result

with result in out.txt create plot.png use

```bash
gnuplot -c PlotIt.gnuplot out.txt plot.png
```

## Full pipeline

```bash
./CreateLayout.out 6 -1 1 ch | ./PolynomialInterpolation.out > out.txt && gnuplot -c PlotIt.gnuplot out.txt plot.png
```
