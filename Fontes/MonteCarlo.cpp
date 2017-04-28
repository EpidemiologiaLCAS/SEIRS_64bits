#ifndef __MONTE_CARLO__
#define __MONTE_CARLO__

#include "Parametros.cpp"
#include "Simulacao.cpp"

namespace SaidasMonteCarlo {

void gerarSaidaQuantidadeTotal(int idMonteCarlo, int ciclos, int simulacoes,
                               int *saidaQuantidadeTotal) {
  std::string nomeArquivoSaida = std::string("Saidas") + SEPARADOR +
                                 "MonteCarlo_" + std::to_string(idMonteCarlo) +
                                 SEPARADOR +
                                 std::string("Quantidades_Total.csv");
  std::ofstream arquivoSaida(nomeArquivoSaida);
  if (arquivoSaida.is_open()) {
    for (int i = 0; i < ciclos; ++i) {
      arquivoSaida << i;
      for (int j = 0; j < COLUNAS_SAIDAS_QUANTIDADES; ++j) {
        arquivoSaida
            << ";"
            << saidaQuantidadeTotal[VEC(i, j, COLUNAS_SAIDAS_QUANTIDADES)] /
                   simulacoes;
      }
      arquivoSaida << std::endl;
    }
    arquivoSaida.close();
  } else {
    std::cerr << "Arquivo: " << nomeArquivoSaida << " nao foi aberto!"
              << std::endl;
    exit(1);
  }
}

void gerarSaidaQuantidadeQuadras(int idMonteCarlo, int quantQuadras, int ciclos,
                                 int simulacoes,
                                 const int *indexSaidaQuantidadeQuadras,
                                 int *saidaQuantidadeQuadras) {
  for (int idQuadra = 0; idQuadra < quantQuadras; ++idQuadra) {
    std::string nomeArquivoSaida =
        std::string("Saidas") + SEPARADOR + std::string("MonteCarlo_") +
        std::to_string(idMonteCarlo) + SEPARADOR +
        std::string("Quantidades_Quadra-") + std::to_string(idQuadra) +
        std::string(".csv");
    std::ofstream arquivoSaida(nomeArquivoSaida);
    if (arquivoSaida.is_open()) {
      for (int i = 0; i < ciclos; ++i) {
        arquivoSaida << i;
        for (int j = 0; j < COLUNAS_SAIDAS_QUANTIDADES; ++j) {
          arquivoSaida
              << ";"
              << saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[idQuadra] +
                                        VEC(i, j, COLUNAS_SAIDAS_QUANTIDADES)] /
                     simulacoes;
        }
        arquivoSaida << std::endl;
      }
      arquivoSaida.close();
    } else {
      std::cerr << "Arquivo: " << nomeArquivoSaida << " nao foi aberto!"
                << std::endl;
      exit(1);
    }
  }
}

int *calcularIndexSaidaQuantidadeQuadras(int quantQuadras, int ciclos) {
  int i = 0, size = 0;
  int *deslocamentos = new int[quantQuadras + 1];
  for (int k = 0; k < quantQuadras; ++k) {
    deslocamentos[i++] = size;
    size += ciclos * COLUNAS_SAIDAS_QUANTIDADES;
  }
  deslocamentos[quantQuadras] = size;
  return deslocamentos;
}
}

namespace MonteCarlo {

void iniciarSimulacao(int idMonteCarlo, std::string pastaEntrada,
                      std::string pastaSaida) {
  std::string pastaEntradaMonteCarlo = pastaEntrada,
              pastaSaidaMonteCarlo = pastaSaida;

  int quantQuadras, *quantLotes, *indexQuadras;
  int *indexVizinhancas, *vizinhancas;
  int *indexPosicoes, *posicoes;
  int *indexFronteiras, *fronteiras;
  int *indexEsquinas, *esquinas;
  int *indexCentrosEsquinas, *centrosEsquinas;
  int quantRotas, *indexRotas, *rotas;
  int quantTrajetos, *indexTrajetos, *trajetos;
  int *indexPeriodos, *periodos;
  int *indexTrajetosFaixaEtaria;
  std::tie(quantQuadras, quantLotes, indexQuadras, indexVizinhancas,
           vizinhancas, indexPosicoes, posicoes, indexFronteiras, fronteiras,
           indexEsquinas, esquinas, indexCentrosEsquinas, centrosEsquinas,
           quantRotas, indexRotas, rotas, quantTrajetos, indexTrajetos,
           trajetos, indexPeriodos, periodos, indexTrajetosFaixaEtaria) = Parametros::lerVetores();
  int sizeParametros;
  double *parametros;
  std::tie(sizeParametros, parametros) = Parametros::lerParametros(
      pastaEntradaMonteCarlo, quantLotes, quantQuadras);

  int ciclos = NUMERO_CICLOS_SIMULACAO + 1;
  int simulacoes = QUANTIDADE_SIMULACOES;

  int *saidaQuantidadeTotal = new int[ciclos * COLUNAS_SAIDAS_QUANTIDADES]();
  int *indexSaidaQuantidadeQuadras =
      SaidasMonteCarlo::calcularIndexSaidaQuantidadeQuadras(quantQuadras,
                                                            ciclos);
  int *saidaQuantidadeQuadras =
      new int[indexSaidaQuantidadeQuadras[quantQuadras]]();

  for (int idSimulacao = 0; idSimulacao < simulacoes; ++idSimulacao) {
    std::string pastaSaidaSimulacao = pastaSaidaMonteCarlo +
                                      std::string("Simulacao_") +
                                      std::to_string(idSimulacao) + SEPARADOR;
    Simulacao::iniciarSimulacao(
        idSimulacao, parametros, sizeParametros,
        pastaSaidaSimulacao, saidaQuantidadeTotal, quantLotes, quantQuadras,
        indexQuadras, indexVizinhancas, vizinhancas, indexPosicoes, posicoes,
        indexFronteiras, fronteiras, indexEsquinas, esquinas,
        indexCentrosEsquinas, centrosEsquinas, indexSaidaQuantidadeQuadras,
        saidaQuantidadeQuadras, quantRotas, indexRotas, rotas, quantTrajetos,
        indexTrajetos, trajetos, indexPeriodos, periodos, indexTrajetosFaixaEtaria);
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
  delete[](indexRotas);
  delete[](rotas);
  delete[](indexTrajetos);
  delete[](trajetos);
  delete[](indexPeriodos);
  delete[](periodos);
  delete[](indexCentrosEsquinas);
  delete[](centrosEsquinas);
  delete[](indexTrajetosFaixaEtaria);
  delete[](indexSaidaQuantidadeQuadras);
  delete[](saidaQuantidadeQuadras);
  delete[](parametros);
  delete[](quantLotes);
}
}

#endif
