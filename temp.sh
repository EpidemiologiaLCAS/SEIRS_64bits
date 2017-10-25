 #!/bin/sh

for i in 'Saidas_CPU_BIT' 'Saidas_CPU_CONV' 'Saidas_GPU_BIT_K20' 'Saidas_GPU_BIT_TITAN' 'Saidas_GPU_CONV_K20' 'Saidas_GPU_CONV_TITAN'
do
    echo $i
		echo "Gerando graficos de quantidades..."
		./grafico.py $i/MonteCarlo_0/Quantidades_Total.csv 
		./grafico_acumulado.py $i/MonteCarlo_0/Quantidades_Novo_Total.csv

		echo "Gerando espaciais acumulados..." 
		./espacial_acumulado.py $i/MonteCarlo_0/Simulacao_0/Espacial_Geo.csv 

		echo "Resumindo saidas espaciais..."
		./resumo_saidas.py $i/MonteCarlo_0/Simulacao_0/Espacial_Geo.csv 10
		./resumo_saidas.py $i/MonteCarlo_0/Simulacao_0/Espacial_Geo_Infectantes.csv 10
		./resumo_saidas.py $i/MonteCarlo_0/Simulacao_0/Espacial_Geo_Infectantes_Acumulado.csv 10
done
