 #!/bin/sh

for i in {0..0}
do
		echo $i
		echo "Gerando espaciais acumulados..." 
		./espacial_acumulado.py Saidas_GPU_BIT/MonteCarlo_0/Simulacao_$i/Espacial_Geo.csv 
done
