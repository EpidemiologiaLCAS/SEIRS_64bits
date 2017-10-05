 #!/bin/sh

echo "Gerando graficos de quantidades..."
./grafico.py Saidas_GPU_BIT/MonteCarlo_0/Quantidades_Total.csv 
./grafico_acumulado.py Saidas_GPU_BIT/MonteCarlo_0/Quantidades_Novo_Total.csv

echo "Gerando espaciais acumulados..." 
./espacial_acumulado.py Saidas_GPU_BIT/MonteCarlo_0/Simulacao_0/Espacial_Geo.csv 

echo "Resumindo saidas espaciais..."
./resumo_saidas.py Saidas_GPU_BIT/MonteCarlo_0/Simulacao_0/Espacial_Geo.csv 10
./resumo_saidas.py Saidas_GPU_BIT/MonteCarlo_0/Simulacao_0/Espacial_Geo_Infectantes.csv 10
./resumo_saidas.py Saidas_GPU_BIT/MonteCarlo_0/Simulacao_0/Espacial_Geo_Infectantes_Acumulado.csv 10
