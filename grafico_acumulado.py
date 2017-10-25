#!/usr/bin/env python3

from sys import argv
from multiprocessing import Pool
from pathlib import Path
import matplotlib.pyplot as plt
import numpy as np

def criar_grafico_acumulado(nome_arquivo, ind):
  with open(nome_arquivo, 'r') as arquivo:
    linhas = [linha.split(';') for linha in arquivo]
    x = [int(i[0]) for i in linhas]
    # e = [int(i[ind]) for i in linhas]
    # s = np.cumsum(s)
    # e = [int(i[ind + 1]) for i in linhas]
    # e = np.cumsum(e)
    i = [int(i[ind + 2]) for i in linhas]
    i = np.cumsum(i)
    # r = [int(i[ind + 3]) for i in linhas]
    # r = np.cumsum(r)
    # plt.plot(x, s, color="green", label="S", linewidth=2)
    # plt.plot(x, e, color="yellow", label="E", linewidth=2)
    plt.plot(x, i, color="red", label="I", linewidth=2)
    # plt.plot(x, r, color="blue", label="R", linewidth=2)
    plt.legend(loc="upper right")
    

def criar_grafico_acumulado_total(nome_arquivo):
  with open(nome_arquivo, 'r') as arquivo:
    linhas = [linha.split(';') for linha in arquivo]
    x = [int(i[0]) for i in linhas]
    # s = [sum(int(j) for j in i[1::4]) for i in linhas]
    # s = np.cumsum(s)
    # e = [sum(int(j) for j in i[2::4]) for i in linhas]
    # e = np.cumsum(e)
    i = [sum(int(j) for j in i[3::4]) for i in linhas]
    i = np.cumsum(i)
    print(i)
    # r = [sum(int(j) for j in i[4::4]) for i in linhas]
    # r = np.cumsum(r)
    # plt.plot(x, s, color="green", label="S", linewidth=2)
    # plt.plot(x, e, color="yellow", label="E", linewidth=2)
    plt.plot(x, i, color="red", label="I", linewidth=2)
    # plt.plot(x, r, color="blue", label="R", linewidth=2)
    plt.legend(loc="upper right")


def plot(arquivo):
  criar_grafico_acumulado(str(arquivo.absolute()), 1)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Crianca_Masculino.png"), dpi=400)
  plt.close()
  criar_grafico_acumulado(str(arquivo.absolute()), 5)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Jovem_Masculino.png"), dpi=400)
  plt.close()
  criar_grafico_acumulado(str(arquivo.absolute()), 9)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Adulto_Masculino.png"), dpi=400)
  plt.close()
  criar_grafico_acumulado(str(arquivo.absolute()), 13)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Idoso_Masculino.png"), dpi=400)
  plt.close()
  
  criar_grafico_acumulado(str(arquivo.absolute()), 17)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Crianca_Feminino.png"), dpi=400)
  plt.close()
  criar_grafico_acumulado(str(arquivo.absolute()), 21)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Jovem_Feminino.png"), dpi=400)
  plt.close()
  criar_grafico_acumulado(str(arquivo.absolute()), 25)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Adulto_Feminino.png"), dpi=400)
  plt.close()
  criar_grafico_acumulado(str(arquivo.absolute()), 29)
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Idoso_Feminino.png"), dpi=400)
  plt.close()
  
  
  criar_grafico_acumulado_total(str(arquivo.absolute()))
  plt.savefig(str(arquivo.absolute()).replace(".csv", "_Acumulado_Total.png"), dpi=400)
  plt.close()
  

if len(argv) == 2:
  nome_arquivo = argv[1]
  if Path(nome_arquivo).is_dir():
    pool = Pool()
    pool.map(plot, Path(nome_arquivo).rglob('*.csv'))
  else:
    plot(Path(nome_arquivo))
        
else:
  print("Use:")
  print("python Gerador_Saidas_Quantidades.py diretorio\t\t\t")
  print("Para cada arquivo csv dentro do diretório gera uma imagem png")
  print("python Gerador_Saidas_Quantidades.py arquivo.csv\t\t")
  print("Exibe o gráfico de um arquivo csv em tela")
