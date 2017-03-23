#ifndef SIMULACAO_H
#define SIMULACAO_H

namespace Agentes {

void inicializarAgente(TIPO_AGENTE *agentes, int id, int e, int x, int y, int l,
                       int q, int s, int i) {
  SET_Q(id, q);
  SET_S(id, s);
  SET_I(id, i);
  SET_L(id, l);
  SET_X(id, x);
  SET_Y(id, y);
  SET_C(id, 0);
  SET_E(id, e);
}

void inserirAgentes(int quantAgentes, TIPO_AGENTE *agentes,
                    const double *parametros, const int *indexParametros,
                    const int *quantLotes, int quantQuadras,
                    const int *indexQuadras, const int *indexPosicoes,
                    const int *posicoes, int quantidade, int estado, int sexo,
                    int idade, int *i) {
  int q, l, posicoesLote, p, x, y;
  for (int j = 0; j < quantidade; ++j) {
    q = (int)(randomizarPercentual() * quantQuadras);
    l = (int)(randomizarPercentual() * quantLotes[q]);
    if (q == 0 || quantLotes[q] < 3) {
      j--;
      continue;
    }
    posicoesLote = (indexPosicoes[indexQuadras[2 * q] + l + 1] -
                    indexPosicoes[indexQuadras[2 * q] + l]) /
                   4;
    p = ENTRE_FAIXA(0, posicoesLote, randomizarPercentual());
    x = posicoes[indexPosicoes[indexQuadras[q * 2] + l] + p * 4 + 0];
    y = posicoes[indexPosicoes[indexQuadras[q * 2] + l] + p * 4 + 1];
    inicializarAgente(agentes, *i, estado, x, y, l, q, sexo, idade);
    (*i)++;
  }
}

TIPO_AGENTE *criarAgentes(int quantAgentes, const double *parametros,
                          const int *indexParametros, const int *quantLotes,
                          int quantQuadras, const int *indexQuadras,
                          const int *indexPosicoes, const int *posicoes) {
  int i = 0;
  TIPO_AGENTE *agentes = new TIPO_AGENTE[quantAgentes * ATRIBUTOS_AGENTE];
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO, SUSCETIVEL,
                 MASCULINO, CRIANCA, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO, EXPOSTO,
                 MASCULINO, CRIANCA, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO, INFECTADO,
                 MASCULINO, CRIANCA, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO, RECUPERADO,
                 MASCULINO, CRIANCA, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO, SUSCETIVEL,
                 FEMININO, CRIANCA, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO, EXPOSTO,
                 FEMININO, CRIANCA, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO, INFECTADO,
                 FEMININO, CRIANCA, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO, RECUPERADO,
                 FEMININO, CRIANCA, &i);

  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO, SUSCETIVEL,
                 MASCULINO, JOVEM, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO, EXPOSTO,
                 MASCULINO, JOVEM, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO, INFECTADO,
                 MASCULINO, JOVEM, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO, RECUPERADO,
                 MASCULINO, JOVEM, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO, SUSCETIVEL,
                 FEMININO, JOVEM, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO, EXPOSTO, FEMININO,
                 JOVEM, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO, INFECTADO,
                 FEMININO, JOVEM, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO, RECUPERADO,
                 FEMININO, JOVEM, &i);

  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO, SUSCETIVEL,
                 MASCULINO, ADULTO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO, EXPOSTO,
                 MASCULINO, ADULTO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO, INFECTADO,
                 MASCULINO, ADULTO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO, RECUPERADO,
                 MASCULINO, ADULTO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO, SUSCETIVEL,
                 FEMININO, ADULTO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO, EXPOSTO, FEMININO,
                 ADULTO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO, INFECTADO,
                 FEMININO, ADULTO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO, RECUPERADO,
                 FEMININO, ADULTO, &i);

  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO, SUSCETIVEL,
                 MASCULINO, IDOSO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO, EXPOSTO,
                 MASCULINO, IDOSO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO, INFECTADO,
                 MASCULINO, IDOSO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO, RECUPERADO,
                 MASCULINO, IDOSO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO, SUSCETIVEL,
                 FEMININO, IDOSO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO, EXPOSTO, FEMININO,
                 IDOSO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO, INFECTADO,
                 FEMININO, IDOSO, &i);
  inserirAgentes(quantAgentes, agentes, parametros, indexParametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO, RECUPERADO,
                 FEMININO, IDOSO, &i);
  return agentes;
}

int contarTotalAgentes(const int *quantLotes, int quantQuadras,
                       const double *parametros, const int *indexParametros) {
  int quantAgentes = 0;
  quantAgentes += QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO +
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO +

                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO +
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO +

                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO +
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO +

                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO +
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO;
  return quantAgentes;
}
}

namespace SaidasSimulacao {

void salvarSaidaEspacial(string pastaSaida, const int *saidaEspacial,
                         int quantLinhasSaidaEspacial,
                         int quantColunasSaidaEspacial) {
  string nomeArquivoSaida = pastaSaida + string("Espacial_Geo.csv");
  ofstream arquivoSaida(nomeArquivoSaida);
  if (arquivoSaida.is_open()) {
    for (int i = 0; i < quantLinhasSaidaEspacial; ++i) {
      for (int j = 0; j < quantColunasSaidaEspacial; ++j) {
        arquivoSaida << saidaEspacial[VEC(i, j, quantColunasSaidaEspacial)]
                     << ";";
      }
      arquivoSaida << endl;
    }
    arquivoSaida.close();
  } else {
    cerr << "Arquivo: " << nomeArquivoSaida << " nao foi aberto!" << endl;
    exit(1);
  }
}

#ifdef __GPU__

__global__ void gerarSaidaQuantidadeTotal(const TIPO_AGENTE *agentes,
                                          int quantAgentes,
                                          int *saidaQuantidadeTotal, int ciclo,
                                          int chunk) {
  int i = (threadIdx.x + blockIdx.x * blockDim.x) + chunk;
  if (i < quantAgentes) {
    if (GET_S(i) == MASCULINO) {
      switch (GET_I(i)) {
      case CRIANCA:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 1 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      case JOVEM:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 5 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      case ADULTO:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 9 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      case IDOSO:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 13 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      }
    } else {
      switch (GET_I(i)) {
      case CRIANCA:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 17 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      case JOVEM:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 21 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      case ADULTO:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 25 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      case IDOSO:
        atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 29 + GET_E(i),
                                            COLUNAS_SAIDAS_QUANTIDADES)],
                  1);
        break;
      }
    }
    atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, 33, COLUNAS_SAIDAS_QUANTIDADES)],
              1);
  }
}

__global__ void
gerarSaidaQuantidadeQuadras(const TIPO_AGENTE *agentes, int quantAgentes,
                            const int *indexSaidaQuantidadeQuadras,
                            int *saidaQuantidadeQuadras, int ciclo, int chunk) {
  int i = (threadIdx.x + blockIdx.x * blockDim.x) + chunk;
  if (i < quantAgentes) {
    if (GET_S(i) == MASCULINO) {
      switch (GET_I(i)) {
      case CRIANCA:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 1 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      case JOVEM:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 5 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      case ADULTO:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 9 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      case IDOSO:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 13 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      }
    } else {
      switch (GET_I(i)) {
      case CRIANCA:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 17 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      case JOVEM:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 21 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      case ADULTO:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 25 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      case IDOSO:
        atomicAdd(
            &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                    VEC(ciclo, 29 + GET_E(i),
                                        COLUNAS_SAIDAS_QUANTIDADES)],
            1);
        break;
      }
    }
    atomicAdd(
        &saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                                VEC(ciclo, 33, COLUNAS_SAIDAS_QUANTIDADES)],
        1);
  }
}

__global__ void gerarSaidaEspacial(const TIPO_AGENTE *agentes, int quantAgentes,
                                   int *saidaEspacial, int ciclo,
                                   int quantQuadras, int ciclos,
                                   const int *indexQuadras,
                                   const int *indexPosicoes,
                                   const int *posicoes, int chunk) {
  int pos = (threadIdx.x + blockIdx.x * blockDim.x) + chunk;
  if (pos < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4) {
    int x = posicoes[pos * 4 + 0];
    int y = posicoes[pos * 4 + 1];
    int l = posicoes[pos * 4 + 2];
    int q = posicoes[pos * 4 + 3];
    int e;
    for (int i = 0; i < quantAgentes; ++i) {
      if (GET_Q(i) == q && GET_L(i) == l && GET_X(i) == x && GET_Y(i) == y) {
        e = 2000;
        e += GET_E(i) + 1;
        e += (GET_I(i) + 1) * 10;
        if (e > saidaEspacial[VEC(pos, ciclo, ciclos)]) {
          saidaEspacial[VEC(pos, ciclo, ciclos)] = e;
        }
      }
    }
  }
}

#endif

#ifdef __CPU__

void gerarSaidaQuantidadeTotal(const TIPO_AGENTE *agentes, int quantAgentes,
                               int *saidaQuantidadeTotal, int ciclo) {
#pragma omp parallel for
  for (int i = 0; i < quantAgentes; i++) {
    if (GET_S(i) == MASCULINO) {
      switch (GET_I(i)) {
      case CRIANCA: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 1 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case JOVEM: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 5 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case ADULTO: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 9 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case IDOSO: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 13 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      }
    } else {
      switch (GET_I(i)) {
      case CRIANCA: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 17 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case JOVEM: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 21 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case ADULTO: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 25 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case IDOSO: {
#pragma omp atomic
        saidaQuantidadeTotal[VEC(ciclo, 29 + GET_E(i),
                                 COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      }
    }
#pragma omp atomic
    saidaQuantidadeTotal[VEC(ciclo, 33, COLUNAS_SAIDAS_QUANTIDADES)]++;
  }
}

void gerarSaidaQuantidadeQuadras(const TIPO_AGENTE *agentes, int quantAgentes,
                                 const int *indexSaidaQuantidadeQuadras,
                                 int *saidaQuantidadeQuadras, int ciclo) {
#pragma omp parallel for
  for (int i = 0; i < quantAgentes; i++) {
    if (GET_S(i) == MASCULINO) {
      switch (GET_I(i)) {
      case CRIANCA: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 1 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case JOVEM: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 5 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case ADULTO: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 9 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case IDOSO: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 13 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      }
    } else {
      switch (GET_I(i)) {
      case CRIANCA: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 17 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case JOVEM: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 21 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case ADULTO: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 25 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      case IDOSO: {
#pragma omp atomic
        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                               VEC(ciclo, 29 + GET_E(i),
                                   COLUNAS_SAIDAS_QUANTIDADES)]++;
      } break;
      }
    }
#pragma omp atomic
    saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(i)] +
                           VEC(ciclo, 33, COLUNAS_SAIDAS_QUANTIDADES)]++;
  }
}

void gerarSaidaEspacial(const TIPO_AGENTE *agentes, int quantAgentes,
                        int *saidaEspacial, int ciclo, int quantQuadras,
                        int ciclos, const int *indexQuadras,
                        const int *indexPosicoes, const int *posicoes) {
#pragma omp parallel for
  for (int pos = 0; pos < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4;
       pos++) {
    int x = posicoes[pos * 4 + 0];
    int y = posicoes[pos * 4 + 1];
    int l = posicoes[pos * 4 + 2];
    int q = posicoes[pos * 4 + 3];
    int e;
    for (int i = 0; i < quantAgentes; ++i) {
      if (GET_Q(i) == q && GET_L(i) == l && GET_X(i) == x && GET_Y(i) == y) {
        e = 2000;
        e += GET_E(i) + 1;
        e += (GET_I(i) + 1) * 10;
        if (e > saidaEspacial[VEC(pos, ciclo, ciclos)]) {
          saidaEspacial[VEC(pos, ciclo, ciclos)] = e;
        }
      }
    }
  }
}

#endif
}

namespace Simulacao {

#ifdef __GPU__

__global__ void movimentacao(curandState *seeds, TIPO_AGENTE *agentes,
                             int quantAgentes, const int *indexQuadras,
                             const int *indexVizinhancas,
                             const int *vizinhancas, const double *parametros,
                             const int *indexParametros, const int *indexFronteiras, 
                             const int *fronteiras, int chunk) {
  int id = (threadIdx.x + blockIdx.x * blockDim.x) + chunk;
  if (id < quantAgentes) {
    int q = GET_Q(id);
    int l = GET_L(id);
    int x = GET_X(id);
    int y = GET_Y(id);
    double taxa;
    switch (GET_I(id)) {
    case CRIANCA:
      taxa = TAXA_MOBILIDADE_CRIANCA(curand_uniform_double(&seeds[id]));
      break;
    case JOVEM:
      taxa = TAXA_MOBILIDADE_JOVEM(curand_uniform_double(&seeds[id]));
      break;
    case ADULTO:
      taxa = TAXA_MOBILIDADE_ADULTO(curand_uniform_double(&seeds[id]));
      break;
    case IDOSO:
      taxa = TAXA_MOBILIDADE_IDOSO(curand_uniform_double(&seeds[id]));
      break;
    }
    if (curand_uniform_double(&seeds[id]) <= taxa) {
      int quantidade = 0;
      for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
           i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
        if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
          quantidade++;
        }
      }
      if (quantidade > 0) {
        int *posicoes = new int[quantidade * 4];
        int k = 0;
        for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
             i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
          if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
            posicoes[4 * k + 0] = vizinhancas[i + 2];
            posicoes[4 * k + 1] = vizinhancas[i + 3];
            posicoes[4 * k + 2] = vizinhancas[i + 4];
            posicoes[4 * k + 3] = vizinhancas[i + 5];
            k++;
          }
        }
        int indice = (int)(curand_uniform_double(&seeds[id]) * quantidade);
        x = posicoes[4 * indice + 0];
        y = posicoes[4 * indice + 1];
        l = posicoes[4 * indice + 2];
        q = posicoes[4 * indice + 3];
        delete[](posicoes);
        SET_X(id, x);
        SET_Y(id, y);
        SET_L(id, l);
        SET_Q(id, q);
      }
    }
  }
}

__global__ void contato(curandState *seeds, TIPO_AGENTE *agentes,
                        int quantAgentes, const int *quantLotes,
                        int quantQuadras, const double *parametros,
                        const int *indexParametros, const int *indexQuadras,
                        const int *indexPosicoes, const int *posicoes,
                        int chunk) {
  int pos = (threadIdx.x + blockIdx.x * blockDim.x) + chunk;
  if (pos < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4) {
    int x = posicoes[pos * 4 + 0];
    int y = posicoes[pos * 4 + 1];
    int l = posicoes[pos * 4 + 2];
    int q = posicoes[pos * 4 + 3];
    int suscetiveis = 0, infectados = 0;
    for (int i = 0; i < quantAgentes; ++i) {
      if (GET_Q(i) == q && GET_L(i) == l && GET_X(i) == x && GET_Y(i) == y) {
        if (GET_E(i) == SUSCETIVEL) {
          suscetiveis++;
        } else {
          if (GET_E(i) == INFECTADO) {
            infectados++;
          }
        }
      }
    }
    if (suscetiveis > 0 && infectados > 0) {
      for (int i = 0; i < quantAgentes; ++i) {
        if (GET_Q(i) == q && GET_L(i) == l && GET_X(i) == x && GET_Y(i) == y) {
          if (GET_E(i) == SUSCETIVEL) {
            double taxa;
            switch (GET_I(i)) {
            case CRIANCA:
              taxa = TAXA_INFECCAO_CRIANCA(curand_uniform_double(&seeds[pos]));
              break;
            case JOVEM:
              taxa = TAXA_INFECCAO_JOVEM(curand_uniform_double(&seeds[pos]));
              break;
            case ADULTO:
              taxa = TAXA_INFECCAO_ADULTO(curand_uniform_double(&seeds[pos]));
              break;
            case IDOSO:
              taxa = TAXA_INFECCAO_IDOSO(curand_uniform_double(&seeds[pos]));
              break;
            }
            if (curand_uniform_double(&seeds[pos]) <= taxa) {
              SET_E(i, EXPOSTO);
            }
          }
        }
      }
    }
  }
}

__global__ void transicao(curandState *seeds, TIPO_AGENTE *agentes,
                          int quantAgentes, const double *parametros,
                          const int *indexParametros, int chunk) {
  int i = (threadIdx.x + blockIdx.x * blockDim.x) + chunk;
  if (i < quantAgentes) {
    int c = GET_C(i);
    switch (GET_E(i)) {
    case EXPOSTO: {
      double periodo;
      switch (GET_I(i)) {
      case CRIANCA:
        periodo = PERIODO_EXPOSTO_CRIANCA(curand_uniform_double(&seeds[i]));
        break;
      case JOVEM:
        periodo = PERIODO_EXPOSTO_JOVEM(curand_uniform_double(&seeds[i]));
        break;
      case ADULTO:
        periodo = PERIODO_EXPOSTO_ADULTO(curand_uniform_double(&seeds[i]));
        break;
      case IDOSO:
        periodo = PERIODO_EXPOSTO_IDOSO(curand_uniform_double(&seeds[i]));
        break;
      }
      if (c >= periodo) {
        SET_E(i, INFECTADO);
        SET_C(i, 0);
      } else {
        SET_C(i, c + 1);
      }
    } break;
    case INFECTADO: {
      double periodo;
      switch (GET_I(i)) {
      case CRIANCA:
        periodo = PERIODO_INFECTADO_CRIANCA(curand_uniform_double(&seeds[i]));
        break;
      case JOVEM:
        periodo = PERIODO_INFECTADO_JOVEM(curand_uniform_double(&seeds[i]));
        break;
      case ADULTO:
        periodo = PERIODO_INFECTADO_ADULTO(curand_uniform_double(&seeds[i]));
        break;
      case IDOSO:
        periodo = PERIODO_INFECTADO_IDOSO(curand_uniform_double(&seeds[i]));
        break;
      }
      if (c >= periodo) {
        SET_E(i, RECUPERADO);
        SET_C(i, 0);
      } else {
        SET_C(i, c + 1);
      }
    } break;
    case RECUPERADO: {
      double periodo;
      switch (GET_I(i)) {
      case CRIANCA:
        periodo = PERIODO_RECUPERADO_CRIANCA(curand_uniform_double(&seeds[i]));
        break;
      case JOVEM:
        periodo = PERIODO_RECUPERADO_JOVEM(curand_uniform_double(&seeds[i]));
        break;
      case ADULTO:
        periodo = PERIODO_RECUPERADO_ADULTO(curand_uniform_double(&seeds[i]));
        break;
      case IDOSO:
        periodo = PERIODO_RECUPERADO_IDOSO(curand_uniform_double(&seeds[i]));
        break;
      }
      if (c >= periodo) {
        SET_E(i, SUSCETIVEL);
        SET_C(i, 0);
      } else {
        SET_C(i, c + 1);
      }
    } break;
    }
  }
}

__global__ void initCurand(curandState *seeds, const int *rands,
                           int maxThreads) {
  int i = threadIdx.x + blockIdx.x * blockDim.x;
  if (i < maxThreads) {
    curand_init(rands[i], i, 0, &seeds[i]);
  }
}

#endif

#ifdef __CPU__

void movimentacao(TIPO_AGENTE *agentes, int quantAgentes,
                  const int *indexQuadras, const int *indexVizinhancas,
                  const int *vizinhancas, const double *parametros,
                  const int *indexParametros, const int *indexFronteiras, 
                  const int *fronteiras) {
#pragma omp parallel for
  for (int id = 0; id < quantAgentes; id++) {
    int q = GET_Q(id);
    int l = GET_L(id);
    int x = GET_X(id);
    int y = GET_Y(id);
    double taxa;
    switch (GET_I(id)) {
    case CRIANCA:
      taxa = TAXA_MOBILIDADE_CRIANCA(randomizarPercentual());
      break;
    case JOVEM:
      taxa = TAXA_MOBILIDADE_JOVEM(randomizarPercentual());
      break;
    case ADULTO:
      taxa = TAXA_MOBILIDADE_ADULTO(randomizarPercentual());
      break;
    case IDOSO:
      taxa = TAXA_MOBILIDADE_IDOSO(randomizarPercentual());
      break;
    }
    if (randomizarPercentual() <= taxa) {
      int quantidade = 0;
      for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
           i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
        if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
          quantidade++;
        }
      }
      if (quantidade > 0) {
        int *posicoes = new int[quantidade * 4];
        int k = 0;
        for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
             i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
          if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
            posicoes[4 * k + 0] = vizinhancas[i + 2];
            posicoes[4 * k + 1] = vizinhancas[i + 3];
            posicoes[4 * k + 2] = vizinhancas[i + 4];
            posicoes[4 * k + 3] = vizinhancas[i + 5];
            k++;
          }
        }
        int indice = (int)(randomizarPercentual() * quantidade);
        x = posicoes[4 * indice + 0];
        y = posicoes[4 * indice + 1];
        l = posicoes[4 * indice + 2];
        q = posicoes[4 * indice + 3];
        delete[](posicoes);
        SET_X(id, x);
        SET_Y(id, y);
        SET_L(id, l);
        SET_Q(id, q);
      }
    }
  }
}

void contato(TIPO_AGENTE *agentes, int quantAgentes, const int *quantLotes,
             int quantQuadras, const double *parametros,
             const int *indexParametros, const int *indexQuadras,
             const int *indexPosicoes, const int *posicoes) {
#pragma omp parallel for
  for (int pos = 0; pos < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4;
       pos++) {
    int x = posicoes[pos * 4 + 0];
    int y = posicoes[pos * 4 + 1];
    int l = posicoes[pos * 4 + 2];
    int q = posicoes[pos * 4 + 3];
    int suscetiveis = 0, infectados = 0;
    for (int i = 0; i < quantAgentes; ++i) {
      if (GET_Q(i) == q && GET_L(i) == l && GET_X(i) == x && GET_Y(i) == y) {
        if (GET_E(i) == SUSCETIVEL) {
          suscetiveis++;
        } else {
          if (GET_E(i) == INFECTADO) {
            infectados++;
          }
        }
      }
    }
    if (suscetiveis > 0 && infectados > 0) {
      for (int i = 0; i < quantAgentes; ++i) {
        if (GET_Q(i) == q && GET_L(i) == l && GET_X(i) == x && GET_Y(i) == y) {
          if (GET_E(i) == SUSCETIVEL) {
            double taxa;
            switch (GET_I(i)) {
            case CRIANCA:
              taxa = TAXA_INFECCAO_CRIANCA(randomizarPercentual());
              break;
            case JOVEM:
              taxa = TAXA_INFECCAO_JOVEM(randomizarPercentual());
              break;
            case ADULTO:
              taxa = TAXA_INFECCAO_ADULTO(randomizarPercentual());
              break;
            case IDOSO:
              taxa = TAXA_INFECCAO_IDOSO(randomizarPercentual());
              break;
            }
            if (randomizarPercentual() <= taxa) {
              SET_E(i, EXPOSTO);
            }
          }
        }
      }
    }
  }
}

void transicao(TIPO_AGENTE *agentes, int quantAgentes, const double *parametros,
               const int *indexParametros) {
#pragma omp parallel for
  for (int i = 0; i < quantAgentes; i++) {
    int c = GET_C(i);
    switch (GET_E(i)) {
    case EXPOSTO: {
      double periodo;
      switch (GET_I(i)) {
      case CRIANCA:
        periodo = PERIODO_EXPOSTO_CRIANCA(randomizarPercentual());
        break;
      case JOVEM:
        periodo = PERIODO_EXPOSTO_JOVEM(randomizarPercentual());
        break;
      case ADULTO:
        periodo = PERIODO_EXPOSTO_ADULTO(randomizarPercentual());
        break;
      case IDOSO:
        periodo = PERIODO_EXPOSTO_IDOSO(randomizarPercentual());
        break;
      }
      if (c >= periodo) {
        SET_E(i, INFECTADO);
        SET_C(i, 0);
      } else {
        SET_C(i, c + 1);
      }
    } break;
    case INFECTADO: {
      double periodo;
      switch (GET_I(i)) {
      case CRIANCA:
        periodo = PERIODO_INFECTADO_CRIANCA(randomizarPercentual());
        break;
      case JOVEM:
        periodo = PERIODO_INFECTADO_JOVEM(randomizarPercentual());
        break;
      case ADULTO:
        periodo = PERIODO_INFECTADO_ADULTO(randomizarPercentual());
        break;
      case IDOSO:
        periodo = PERIODO_INFECTADO_IDOSO(randomizarPercentual());
        break;
      }
      if (c >= periodo) {
        SET_E(i, RECUPERADO);
        SET_C(i, 0);
      } else {
        SET_C(i, c + 1);
      }
    } break;
    case RECUPERADO: {
      double periodo;
      switch (GET_I(i)) {
      case CRIANCA:
        periodo = PERIODO_RECUPERADO_CRIANCA(randomizarPercentual());
        break;
      case JOVEM:
        periodo = PERIODO_RECUPERADO_JOVEM(randomizarPercentual());
        break;
      case ADULTO:
        periodo = PERIODO_RECUPERADO_ADULTO(randomizarPercentual());
        break;
      case IDOSO:
        periodo = PERIODO_RECUPERADO_IDOSO(randomizarPercentual());
        break;
      }
      if (c >= periodo) {
        SET_E(i, SUSCETIVEL);
        SET_C(i, 0);
      } else {
        SET_C(i, c + 1);
      }
    } break;
    }
  }
}

#endif

void iniciarSimulacao(int idSimulacao, const double *parametros,
                      int sizeParametros, const int *indexParametros,
                      string pastaSaida, int *saidaQuantidadeTotal,
                      const int *quantLotes, int quantQuadras,
                      const int *indexQuadras, const int *indexVizinhancas,
                      const int *vizinhancas, const int *indexPosicoes,
                      const int *posicoes, const int *indexFronteiras, 
                      const int *fronteiras,
                      const int *indexSaidaQuantidadeQuadras,
                      int *saidaQuantidadeQuadras) {
  int ciclos = NUMERO_CICLOS_SIMULACAO + 1;

  int quantLinhasSaidaEspacial =
      indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4;
  int *saidaEspacial = new int[quantLinhasSaidaEspacial * ciclos]();

  int quantAgentes = Agentes::contarTotalAgentes(quantLotes, quantQuadras,
                                                 parametros, indexParametros);
  TIPO_AGENTE *agentes = Agentes::criarAgentes(
      quantAgentes, parametros, indexParametros, quantLotes, quantQuadras,
      indexQuadras, indexPosicoes, posicoes);

  if (idSimulacao == 0) {
    int totMem = (quantAgentes * ATRIBUTOS_AGENTE * sizeof(TIPO_AGENTE));
    totMem += (ciclos * COLUNAS_SAIDAS_QUANTIDADES * sizeof(int));
    totMem += (sizeParametros * sizeof(double));
    totMem +=
        (indexVizinhancas[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int));
    totMem += indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int);
    totMem += indexFronteiras[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int);
    cout << totMem << endl;
  }

#if defined(__GPU__)

  TIPO_AGENTE *agentesDev;
  int *saidaQuantidadeTotalDev;
  int *indexSaidaQuantidadeQuadrasDev;
  int *saidaQuantidadeQuadrasDev;
  int *saidaEspacialDev;
  int *quantLotesDev;
  double *parametrosDev;
  int *indexParametrosDev;
  int *indexQuadrasDev;
  int *indexVizinhancasDev;
  int *vizinhancasDev;
  int *indexPosicoesDev;
  int *posicoesDev;
  int *indexFronteirasDev;
  int *fronteirasDev;

  cudaMalloc((void **)&agentesDev,
             quantAgentes * ATRIBUTOS_AGENTE * sizeof(TIPO_AGENTE));
  cudaMalloc((void **)&saidaQuantidadeTotalDev,
             ciclos * COLUNAS_SAIDAS_QUANTIDADES * sizeof(int));
  cudaMalloc((void **)&indexSaidaQuantidadeQuadrasDev,
             (quantQuadras + 1) * sizeof(int));
  cudaMalloc((void **)&saidaQuantidadeQuadrasDev,
             indexSaidaQuantidadeQuadras[quantQuadras] * sizeof(int));
  cudaMalloc((void **)&saidaEspacialDev,
             quantLinhasSaidaEspacial * ciclos * sizeof(int));
  cudaMalloc((void **)&quantLotesDev, quantQuadras * sizeof(int));
  cudaMalloc((void **)&parametrosDev, sizeParametros * sizeof(double));
  cudaMalloc((void **)&indexParametrosDev, quantQuadras * sizeof(int));
  cudaMalloc((void **)&indexQuadrasDev, quantQuadras * 2 * sizeof(int));
  cudaMalloc((void **)&indexVizinhancasDev,
             (indexQuadras[quantQuadras * 2 - 1] + 1) * sizeof(int));
  cudaMalloc((void **)&vizinhancasDev,
             indexVizinhancas[indexQuadras[quantQuadras * 2 - 1]] *
                 sizeof(int));
  cudaMalloc((void **)&indexPosicoesDev,
             (indexQuadras[quantQuadras * 2 - 1] + 1) * sizeof(int));
  cudaMalloc((void **)&posicoesDev,
             indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int));
  cudaMalloc((void **)&indexFronteirasDev,
             (indexQuadras[quantQuadras * 2 - 1] + 1) * sizeof(int));
  cudaMalloc((void **)&fronteirasDev,
             indexFronteiras[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int));


  cudaMemcpy(agentesDev, agentes,
             quantAgentes * ATRIBUTOS_AGENTE * sizeof(TIPO_AGENTE),
             cudaMemcpyHostToDevice);
  cudaMemcpy(saidaQuantidadeTotalDev, saidaQuantidadeTotal,
             ciclos * COLUNAS_SAIDAS_QUANTIDADES * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexSaidaQuantidadeQuadrasDev, indexSaidaQuantidadeQuadras,
             (quantQuadras + 1) * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(saidaQuantidadeQuadrasDev, saidaQuantidadeQuadras,
             indexSaidaQuantidadeQuadras[quantQuadras] * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(saidaEspacialDev, saidaEspacial,
             quantLinhasSaidaEspacial * ciclos * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(quantLotesDev, quantLotes, quantQuadras * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(parametrosDev, parametros, sizeParametros * sizeof(double),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexParametrosDev, indexParametros, quantQuadras * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexQuadrasDev, indexQuadras, quantQuadras * 2 * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexVizinhancasDev, indexVizinhancas,
             (indexQuadras[quantQuadras * 2 - 1] + 1) * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(vizinhancasDev, vizinhancas,
             indexVizinhancas[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexPosicoesDev, indexPosicoes,
             (indexQuadras[quantQuadras * 2 - 1] + 1) * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(posicoesDev, posicoes,
             indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexFronteirasDev, indexFronteiras,
             (indexQuadras[quantQuadras * 2 - 1] + 1) * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(fronteirasDev, fronteiras,
             indexFronteiras[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int),
             cudaMemcpyHostToDevice);

  int numThreads = 1024;
  int f1 = (int)((quantAgentes / numThreads) + 1);
  int f2 = (int)((indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4 /
                  numThreads) +
                 1);
  int f = (f1 > f2) ? f1 : f2;
  int maxThreads = f * numThreads;

  curandState *seedsDev;
  cudaMalloc((void **)&seedsDev, maxThreads * sizeof(curandState));
  int *rands = new int[maxThreads];
  int *randsDev;
  cudaMalloc((void **)&randsDev, maxThreads * sizeof(int));
  for (int i = 0; i < maxThreads; ++i) {
    rands[i] = (int)ENTRE_FAIXA(0, 100000, randomizarPercentual());
  }
  cudaMemcpy(randsDev, rands, maxThreads * sizeof(int), cudaMemcpyHostToDevice);
  initCurand<<<f, numThreads>>>(seedsDev, randsDev, maxThreads);
  delete[](rands);
  cudaFree(randsDev);

#endif

#ifdef __GPU__

  cudaStream_t stream0, stream1;

  cudaStreamCreate(&stream0);
  cudaStreamCreate(&stream1);

  int b1 = f1 / 2 + 1;
  int c1 = b1 * numThreads;
  int d1 = f1 - b1;

  int b2 = f2 / 2 + 1;
  int c2 = b2 * numThreads;
  int d2 = f2 - b2;

  SaidasSimulacao::gerarSaidaQuantidadeTotal<<<b1, numThreads, 0, stream0>>>(
      agentesDev, quantAgentes, saidaQuantidadeTotalDev, 0, 0);
  SaidasSimulacao::gerarSaidaQuantidadeTotal<<<d1, numThreads, 0, stream1>>>(
      agentesDev, quantAgentes, saidaQuantidadeTotalDev, 0, c1);

  SaidasSimulacao::gerarSaidaQuantidadeQuadras<<<b1, numThreads, 0, stream0>>>(
      agentesDev, quantAgentes, indexSaidaQuantidadeQuadrasDev,
      saidaQuantidadeQuadrasDev, 0, 0);
  SaidasSimulacao::gerarSaidaQuantidadeQuadras<<<d1, numThreads, 0, stream1>>>(
      agentesDev, quantAgentes, indexSaidaQuantidadeQuadrasDev,
      saidaQuantidadeQuadrasDev, 0, c1);

  SaidasSimulacao::gerarSaidaEspacial<<<b2, numThreads, 0, stream0>>>(
      agentesDev, quantAgentes, saidaEspacialDev, 0, quantQuadras, ciclos,
      indexQuadrasDev, indexPosicoesDev, posicoesDev, 0);
  SaidasSimulacao::gerarSaidaEspacial<<<d2, numThreads, 0, stream1>>>(
      agentesDev, quantAgentes, saidaEspacialDev, 0, quantQuadras, ciclos,
      indexQuadrasDev, indexPosicoesDev, posicoesDev, c2);

  for (int ciclo = 1; ciclo < ciclos; ++ciclo) {

    movimentacao<<<b1, numThreads, 0, stream0>>>(
        seedsDev, agentesDev, quantAgentes, indexQuadrasDev,
        indexVizinhancasDev, vizinhancasDev, parametrosDev, indexParametrosDev, 
        indexFronteirasDev, fronteirasDev, 0);
    movimentacao<<<d1, numThreads, 0, stream1>>>(
        seedsDev, agentesDev, quantAgentes, indexQuadrasDev,
        indexVizinhancasDev, vizinhancasDev, parametrosDev, indexParametrosDev,
        indexFronteirasDev, fronteirasDev, c1);

    contato<<<b2, numThreads, 0, stream0>>>(
        seedsDev, agentesDev, quantAgentes, quantLotesDev, quantQuadras,
        parametrosDev, indexParametrosDev, indexQuadrasDev, indexPosicoesDev,
        posicoesDev, 0);
    contato<<<d2, numThreads, 0, stream1>>>(
        seedsDev, agentesDev, quantAgentes, quantLotesDev, quantQuadras,
        parametrosDev, indexParametrosDev, indexQuadrasDev, indexPosicoesDev,
        posicoesDev, c2);

    transicao<<<b1, numThreads, 0, stream0>>>(seedsDev, agentesDev,
                                              quantAgentes, parametrosDev,
                                              indexParametrosDev, 0);
    transicao<<<d1, numThreads, 0, stream1>>>(seedsDev, agentesDev,
                                              quantAgentes, parametrosDev,
                                              indexParametrosDev, c1);

    SaidasSimulacao::gerarSaidaQuantidadeTotal<<<b1, numThreads, 0, stream0>>>(
        agentesDev, quantAgentes, saidaQuantidadeTotalDev, ciclo, 0);
    SaidasSimulacao::gerarSaidaQuantidadeTotal<<<d1, numThreads, 0, stream1>>>(
        agentesDev, quantAgentes, saidaQuantidadeTotalDev, ciclo, c1);

    SaidasSimulacao::
        gerarSaidaQuantidadeQuadras<<<b1, numThreads, 0, stream0>>>(
            agentesDev, quantAgentes, indexSaidaQuantidadeQuadrasDev,
            saidaQuantidadeQuadrasDev, ciclo, 0);
    SaidasSimulacao::
        gerarSaidaQuantidadeQuadras<<<d1, numThreads, 0, stream1>>>(
            agentesDev, quantAgentes, indexSaidaQuantidadeQuadrasDev,
            saidaQuantidadeQuadrasDev, ciclo, c1);

    SaidasSimulacao::gerarSaidaEspacial<<<b2, numThreads, 0, stream0>>>(
        agentesDev, quantAgentes, saidaEspacialDev, ciclo, quantQuadras, ciclos,
        indexQuadrasDev, indexPosicoesDev, posicoesDev, 0);
    SaidasSimulacao::gerarSaidaEspacial<<<d2, numThreads, 0, stream1>>>(
        agentesDev, quantAgentes, saidaEspacialDev, ciclo, quantQuadras, ciclos,
        indexQuadrasDev, indexPosicoesDev, posicoesDev, c2);
  }

  cudaStreamSynchronize(stream0);
  cudaStreamSynchronize(stream1);

  cudaStreamDestroy(stream0);
  cudaStreamDestroy(stream1);

#endif

#ifdef __CPU__

  SaidasSimulacao::gerarSaidaQuantidadeTotal(agentes, quantAgentes,
                                             saidaQuantidadeTotal, 0);
  SaidasSimulacao::gerarSaidaQuantidadeQuadras(agentes, quantAgentes,
                                               indexSaidaQuantidadeQuadras,
                                               saidaQuantidadeQuadras, 0);
  SaidasSimulacao::gerarSaidaEspacial(agentes, quantAgentes, saidaEspacial, 0,
                                      quantQuadras, ciclos, indexQuadras,
                                      indexPosicoes, posicoes);

  for (int ciclo = 1; ciclo < ciclos; ++ciclo) {
    movimentacao(agentes, quantAgentes, indexQuadras, indexVizinhancas,
                 vizinhancas, parametros, indexParametros, indexFronteiras, fronteiras);
    contato(agentes, quantAgentes, quantLotes, quantQuadras, parametros,
            indexParametros, indexQuadras, indexPosicoes, posicoes);
    transicao(agentes, quantAgentes, parametros, indexParametros);

    SaidasSimulacao::gerarSaidaQuantidadeTotal(agentes, quantAgentes,
                                               saidaQuantidadeTotal, ciclo);
    SaidasSimulacao::gerarSaidaQuantidadeQuadras(agentes, quantAgentes,
                                                 indexSaidaQuantidadeQuadras,
                                                 saidaQuantidadeQuadras, ciclo);
    SaidasSimulacao::gerarSaidaEspacial(agentes, quantAgentes, saidaEspacial,
                                        ciclo, quantQuadras, ciclos,
                                        indexQuadras, indexPosicoes, posicoes);
  }

#endif

#if defined(__GPU__)

  cudaMemcpy(saidaQuantidadeTotal, saidaQuantidadeTotalDev,
             ciclos * COLUNAS_SAIDAS_QUANTIDADES * sizeof(int),
             cudaMemcpyDeviceToHost);
  cudaMemcpy(saidaQuantidadeQuadras, saidaQuantidadeQuadrasDev,
             indexSaidaQuantidadeQuadras[quantQuadras] * sizeof(int),
             cudaMemcpyDeviceToHost);
  cudaMemcpy(saidaEspacial, saidaEspacialDev,
             quantLinhasSaidaEspacial * ciclos * sizeof(int),
             cudaMemcpyDeviceToHost);

  cudaFree(seedsDev);
  cudaFree(agentesDev);
  cudaFree(saidaQuantidadeTotalDev);
  cudaFree(indexSaidaQuantidadeQuadrasDev);
  cudaFree(saidaQuantidadeQuadrasDev);
  cudaFree(saidaEspacialDev);
  cudaFree(quantLotesDev);
  cudaFree(parametrosDev);
  cudaFree(indexParametrosDev);
  cudaFree(indexQuadrasDev);
  cudaFree(indexVizinhancasDev);
  cudaFree(vizinhancasDev);
  cudaFree(indexPosicoesDev);
  cudaFree(posicoesDev);
  cudaFree(indexFronteirasDev);
  cudaFree(fronteirasDev);

#endif

  system((COMANDO_CRIAR_PASTA + pastaSaida).c_str());
  SaidasSimulacao::salvarSaidaEspacial(pastaSaida, saidaEspacial,
                                       quantLinhasSaidaEspacial, ciclos);

  delete[](saidaEspacial);
  delete[](agentes);
}
}

#endif
