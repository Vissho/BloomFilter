#!/usr/bin/gnuplot
set termoption enhanced
set terminal png size 1000,800 font "Arial, 16"
set output "collisions.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Количество элементов"
set ylabel "Количество коллизий" rotate by 90
set xtics 100000
set mxtics
set format x "%6.0f"
set format y "%6.0f"
plot "test3.dat" using 1:2 title "Хеш-таблица" with linespoints ls 1, \
"test3.dat" using 1:3 title "Фильтр Блума" with linespoints ls 2