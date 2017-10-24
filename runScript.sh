#!/bin/sh

if [ "$#" -ne 3 ]; then
    echo "3 parametros: <arquivo> <quantidade de itens> <quantidade de execuções>"
    return
fi

mkdir -p resultados

execucoes=$3
tamanho=$2
script=$1

for p in 1 2 4 8 10
do
	sum=0
	echo Inicando execução do script "$script" com "$execucoes" execuções, utilizando "$p" threads
	for i in $(seq 1 $execucoes)
	do
		output=$(./"$script" "$tamanho" "$p")
		echo "$p" $output >> resultados/"$script".txt
	done

done

#gnuplot -e "set xrange [0:10]; set term png; set output 'print.png'; stats \$data using ;plot 'resultados/$script.txt'"
