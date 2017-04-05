#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include "Parametros.cpp"
#include "Simulacao.cpp"

namespace SaidasMonteCarlo {

void gerarSaidaQuantidadeTotal(int idMonteCarlo, int ciclos, int simulacoes,
                               int *saidaQuantidadeTotal) {
  for (int i = 0; i < ciclos; ++i) {
    for (int j = 0; j < COLUNAS_SAIDAS_QUANTIDADES; ++j) {
      saidaQuantidadeTotal[VEC(i, j, COLUNAS_SAIDAS_QUANTIDADES)] /=
          (double)simulacoes;
    }
  }
  for (int i = 0; i < ciclos; ++i) {
    saidaQuantidadeTotal[VEC(i, 0, COLUNAS_SAIDAS_QUANTIDADES)] = i;
  }
  string nomeArquivoSaida = string("Saidas") + SEPARADOR + "MonteCarlo_" +
                            to_string(idMonteCarlo) + SEPARADOR +
                            string("Quantidades_Total.csv");
  ofstream arquivoSaida(nomeArquivoSaida);
  if (arquivoSaida.is_open()) {
    for (int i = 0; i < ciclos; ++i) {
      arquivoSaida
          << saidaQuantidadeTotal[VEC(i, 0, COLUNAS_SAIDAS_QUANTIDADES)];
      for (int j = 1; j < COLUNAS_SAIDAS_QUANTIDADES; ++j) {
        arquivoSaida
            << ";"
            << saidaQuantidadeTotal[VEC(i, j, COLUNAS_SAIDAS_QUANTIDADES)];
      }
      arquivoSaida << endl;
    }
    arquivoSaida.close();
  } else {
    cerr << "Arquivo: " << nomeArquivoSaida << " nao foi aberto!" << endl;
    exit(1);
  }
}

void gerarSaidaQuantidadeQuadras(int idMonteCarlo, int quantQuadras, int ciclos,
                                 int simulacoes,
                                 const int *indexSaidaQuantidadeQuadras,
                                 int *saidaQuantidadeQuadras) {
  for (int idQuadra = 0; idQuadra < quantQuadras; ++idQuadra) {
    for (int i = 0; i < ciclos; ++i) {
      for (int j = 0; j < COLUNAS_SAIDAS_QUANTIDADES; ++j) {
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[idQuadra] +
                               VEC(i, j, COLUNAS_SAIDAS_QUANTIDADES)] /=
            (double)simulacoes;
      }
    }
    for (int i = 0; i < ciclos; ++i) {
      saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[idQuadra] +
                             VEC(i, 0, COLUNAS_SAIDAS_QUANTIDADES)] = i;
    }
    string nomeArquivoSaida = string("Saidas") + SEPARADOR +
                              string("MonteCarlo_") + to_string(idMonteCarlo) +
                              SEPARADOR + string("Quantidades_Quadra-") +
                              to_string(idQuadra) + string(".csv");
    ofstream arquivoSaida(nomeArquivoSaida);
    if (arquivoSaida.is_open()) {
      for (int i = 0; i < ciclos; ++i) {
        arquivoSaida
            << saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[idQuadra] +
                                      VEC(i, 0, COLUNAS_SAIDAS_QUANTIDADES)];
        for (int j = 1; j < COLUNAS_SAIDAS_QUANTIDADES; ++j) {
          arquivoSaida
              << ";"
              << saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[idQuadra] +
                                        VEC(i, j, COLUNAS_SAIDAS_QUANTIDADES)];
        }
        arquivoSaida << endl;
      }
      arquivoSaida.close();
    } else {
      cerr << "Arquivo: " << nomeArquivoSaida << " nao foi aberto!" << endl;
      exit(1);
    }
  }
}

int *calcularIndexSaidaQuantidadeQuadras(int quantQuadras, int ciclos) {
  int i = 0, size = 0;
  int *deslocamentos = new int[quantQuadras + 1];
  for (int k = 0; k < quantQuadras; ++k) {
    deslocamentos[i] = size;
    i++;
    size += ciclos * COLUNAS_SAIDAS_QUANTIDADES;
  }
  deslocamentos[quantQuadras] = size;
  return deslocamentos;
}
}

namespace MonteCarlo {

void iniciarSimulacao(int idMonteCarlo, string pastaEntrada,
                      string pastaSaida) {
  string pastaEntradaMonteCarlo = pastaEntrada,
         pastaSaidaMonteCarlo = pastaSaida;

  int quantQuadras;
  int *quantLotes;
  int *indexQuadras;
  int *indexVizinhancas;
  int *vizinhancas;
  int *indexPosicoes;
  int *posicoes;
  int *indexFronteiras;
  int *fronteiras;
  int *indexEsquinas;
  int *esquinas;
  tie(quantQuadras, quantLotes, indexQuadras, indexVizinhancas, vizinhancas,
      indexPosicoes, posicoes, indexFronteiras, fronteiras, 
      indexEsquinas, esquinas) = Parametros::lerVetores();
  int sizeParametros;
  double *parametros;
  tie(sizeParametros, parametros) = Parametros::lerParametros(
      pastaEntradaMonteCarlo, quantLotes, quantQuadras);
  int *indexParametros =
      Parametros::calcularIndexParametros(quantLotes, quantQuadras);

  int ciclos = NUMERO_CICLOS_SIMULACAO + 1;
  int simulacoes = QUANTIDADE_SIMULACOES;

  int *saidaQuantidadeTotal = new int[ciclos * COLUNAS_SAIDAS_QUANTIDADES]();
  int *indexSaidaQuantidadeQuadras =
      SaidasMonteCarlo::calcularIndexSaidaQuantidadeQuadras(quantQuadras,
                                                            ciclos);
  int *saidaQuantidadeQuadras =
      new int[indexSaidaQuantidadeQuadras[quantQuadras]]();

  for (int idSimulacao = 0; idSimulacao < simulacoes; ++idSimulacao) {
    string pastaSaidaSimulacao = pastaSaidaMonteCarlo + string("Simulacao_") +
                                 to_string(idSimulacao) + SEPARADOR;
    Simulacao::iniciarSimulacao(
        idSimulacao, parametros, sizeParametros, indexParametros,
        pastaSaidaSimulacao, saidaQuantidadeTotal, quantLotes, quantQuadras,
        indexQuadras, indexVizinhancas, vizinhancas, indexPosicoes, posicoes, 
        indexFronteiras, fronteiras, indexEsquinas, esquinas, 
        indexSaidaQuantidadeQuadras, saidaQuantidadeQuadras);
  }

  SaidasMonteCarlo::gerarSaidaQuantidadeQuadras(
      idMonteCarlo, quantQuadras, ciclos, simulacoes,
      indexSaidaQuantidadeQuadras, saidaQuantidadeQuadras);
  SaidasMonteCarlo::gerarSaidaQuantidadeTotal(idMonteCarlo, ciclos, simulacoes,
                                              saidaQuantidadeTotal);

  delete[](saidaQuantidadeTotal);
  delete[](indexQuadras);
  delete[](indexVizinhancas);
  delete[](vizinhancas);
  delete[](indexPosicoes);
  delete[](posicoes);
  delete[](indexFronteiras);
  delete[](fronteiras);
  delete[](indexEsquinas);
  delete[](esquinas);
  delete[](indexSaidaQuantidadeQuadras);
  delete[](saidaQuantidadeQuadras);
  delete[](parametros);
  delete[](indexParametros);
  delete[](quantLotes);
}
}

#endif
