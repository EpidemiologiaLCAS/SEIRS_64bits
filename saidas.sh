 #!/bin/sh

for i in {0..0}
do
		echo $i

		echo "Gerando graficos de quantidades..."
		./grafico.py Saidas_GPU_BIT/MonteCarlo_$i/Quantidades_Total.csv 
		./grafico_acumulado.py Saidas_GPU_BIT/MonteCarlo_$i/Quantidades_Novo_Total.csv

		echo "Gerando espaciais acumulados..." 
		./espacial_acumulado.py Saidas_GPU_BIT/MonteCarlo_$i/Simulacao_0/Espacial_Geo.csv 

		echo "Resumindo saidas espaciais..."
		./resumo_saidas.py Saidas_GPU_BIT/MonteCarlo_$i/Simulacao_0/Espacial_Geo.csv 10
		./resumo_saidas.py Saidas_GPU_BIT/MonteCarlo_$i/Simulacao_0/Espacial_Geo_Infectantes.csv 10
		./resumo_saidas.py Saidas_GPU_BIT/MonteCarlo_$i/Simulacao_0/Espacial_Geo_Infectantes_Acumulado.csv 10
done
