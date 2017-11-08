 #!/bin/sh

for i in {0..9}
do
		echo $i
		echo "Gerando espaciais acumulados..." 
		./espacial_acumulado.py Saidas_GPU_BIT/MonteCarlo_0/Simulacao_$i/Espacial_Novo_Geo.csv 
done
