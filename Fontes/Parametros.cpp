#ifndef PARAMETROS_H
#define PARAMETROS_H

#define QUANTIDADE_PARAMETROS_GERAIS 2
#define QUANTIDADE_PARAMETROS_LOTE 52
#define PARAMETRO(idLote, idQuadra)                                            \
  (indexParametros[idQuadra] + (idLote)*QUANTIDADE_PARAMETROS_LOTE * 2)
#define ENTRE_FAIXA(min, max, percentual)                                      \
  ((min) + ((max) - (min)) * (percentual))

#define QUANTIDADE_SIMULACOES (int)(parametros[0])
#define NUMERO_CICLOS_SIMULACAO (int)(parametros[2])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO(idLote, idQuadra)     \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 0])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 2])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO(idLote, idQuadra)      \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 4])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO(idLote, idQuadra)     \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 6])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO(idLote, idQuadra)      \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 8])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO(idLote, idQuadra)         \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 10])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 12])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO(idLote, idQuadra)      \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 14])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 16])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO(idLote, idQuadra)          \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 18])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 20])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 22])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 24])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO(idLote, idQuadra)           \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 26])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO(idLote, idQuadra)         \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 28])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 30])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO(idLote, idQuadra)      \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 32])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO(idLote, idQuadra)         \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 34])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 36])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO(idLote, idQuadra)      \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 38])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 40])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO(idLote, idQuadra)          \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 42])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 44])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 46])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 48])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO(idLote, idQuadra)          \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 50])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 52])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO(idLote, idQuadra)       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 54])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 56])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO(idLote, idQuadra)           \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 58])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO(idLote, idQuadra)         \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 60])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO(idLote, idQuadra)        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 62])

#define TAXA_INFECCAO_CRIANCA(idLote, idQuadra, percentual)                    \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 64],           \
                       parametros[PARAMETRO(idLote, idQuadra) + 65],           \
                       percentual))
#define PERIODO_EXPOSTO_CRIANCA(idLote, idQuadra, percentual)                  \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 66],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 67], percentual))
#define PERIODO_INFECTADO_CRIANCA(idLote, idQuadra, percentual)                \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 68],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 69], percentual))
#define PERIODO_RECUPERADO_CRIANCA(idLote, idQuadra, percentual)               \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 70],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 71], percentual))

#define TAXA_INFECCAO_JOVEM(idLote, idQuadra, percentual)                      \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 72],           \
                       parametros[PARAMETRO(idLote, idQuadra) + 73],           \
                       percentual))
#define PERIODO_EXPOSTO_JOVEM(idLote, idQuadra, percentual)                    \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 74],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 75], percentual))
#define PERIODO_INFECTADO_JOVEM(idLote, idQuadra, percentual)                  \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 76],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 77], percentual))
#define PERIODO_RECUPERADO_JOVEM(idLote, idQuadra, percentual)                 \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 78],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 79], percentual))

#define TAXA_INFECCAO_ADULTO(idLote, idQuadra, percentual)                     \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 80],           \
                       parametros[PARAMETRO(idLote, idQuadra) + 81],           \
                       percentual))
#define PERIODO_EXPOSTO_ADULTO(idLote, idQuadra, percentual)                   \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 82],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 83], percentual))
#define PERIODO_INFECTADO_ADULTO(idLote, idQuadra, percentual)                 \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 84],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 85], percentual))
#define PERIODO_RECUPERADO_ADULTO(idLote, idQuadra, percentual)                \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 86],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 87], percentual))

#define TAXA_INFECCAO_IDOSO(idLote, idQuadra, percentual)                      \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 88],           \
                       parametros[PARAMETRO(idLote, idQuadra) + 89],           \
                       percentual))
#define PERIODO_EXPOSTO_IDOSO(idLote, idQuadra, percentual)                    \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 90],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 91], percentual))
#define PERIODO_INFECTADO_IDOSO(idLote, idQuadra, percentual)                  \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 92],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 93], percentual))
#define PERIODO_RECUPERADO_IDOSO(idLote, idQuadra, percentual)                 \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 94],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 95], percentual))

#define TAXA_MOBILIDADE_CRIANCA(idLote, idQuadra, percentual)                  \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 96],           \
                       parametros[PARAMETRO(idLote, idQuadra) + 97],           \
                       percentual))
#define TAXA_MOBILIDADE_JOVEM(idLote, idQuadra, percentual)                    \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 98],           \
                       parametros[PARAMETRO(idLote, idQuadra) + 99],           \
                       percentual))
#define TAXA_MOBILIDADE_ADULTO(idLote, idQuadra, percentual)                   \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 100],          \
                       parametros[PARAMETRO(idLote, idQuadra) + 101],          \
                       percentual))
#define TAXA_MOBILIDADE_IDOSO(idLote, idQuadra, percentual)                    \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 102],          \
                       parametros[PARAMETRO(idLote, idQuadra) + 103],          \
                       percentual))

default_random_engine
    gen(chrono::system_clock::now().time_since_epoch().count());
uniform_real_distribution<double> dis(0.0, 1.0);

double randomizarPercentual() { return dis(gen); }

namespace Parametros {

tuple<int, int *, int *, int *, int *, int *, int *> lerVetores() {
  int quantQuadras;
  int *quantLotes;
  int *indexQuadras;
  int *indexVizinhancas;
  int *vizinhancas;
  int *indexPosicoes;
  int *posicoes;
  string nomeArquivoEntrada =
      string("Entradas") + SEPARADOR + string("Vetores.csv");
  ifstream arquivoEntrada(nomeArquivoEntrada);
  if (arquivoEntrada.is_open()) {
    arquivoEntrada >> quantQuadras;
    arquivoEntrada.get();
    quantLotes = new int[quantQuadras];
    for (int i = 0; i < quantQuadras; ++i) {
      arquivoEntrada >> quantLotes[i];
      arquivoEntrada.get();
    }
    indexQuadras = new int[quantQuadras * 2];
    for (int i = 0; i < quantQuadras * 2; ++i) {
      arquivoEntrada >> indexQuadras[i];
      arquivoEntrada.get();
    }
    indexVizinhancas = new int[indexQuadras[quantQuadras * 2 - 1] + 1];
    for (int i = 0; i < indexQuadras[quantQuadras * 2 - 1] + 1; ++i) {
      arquivoEntrada >> indexVizinhancas[i];
      arquivoEntrada.get();
    }
    vizinhancas = new int[indexVizinhancas[indexQuadras[quantQuadras * 2 - 1]]];
    for (int i = 0; i < indexVizinhancas[indexQuadras[quantQuadras * 2 - 1]];
         ++i) {
      arquivoEntrada >> vizinhancas[i];
      arquivoEntrada.get();
    }
    indexPosicoes = new int[indexQuadras[quantQuadras * 2 - 1] + 1];
    for (int i = 0; i < indexQuadras[quantQuadras * 2 - 1] + 1; ++i) {
      arquivoEntrada >> indexPosicoes[i];
      arquivoEntrada.get();
    }
    posicoes = new int[indexPosicoes[indexQuadras[quantQuadras * 2 - 1]]];
    for (int i = 0; i < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]];
         ++i) {
      arquivoEntrada >> posicoes[i];
      arquivoEntrada.get();
    }
    arquivoEntrada.close();
  } else {
    cerr << "Arquivo: " << nomeArquivoEntrada << " nao foi aberto!" << endl;
    exit(1);
  }
  return make_tuple(quantQuadras, quantLotes, indexQuadras, indexVizinhancas,
                    vizinhancas, indexPosicoes, posicoes);
}

tuple<int, double *> lerParametros(string pastaEntrada, const int *quantLotes,
                                   int quantQuadras) {
  int quantParametros = QUANTIDADE_PARAMETROS_GERAIS;
  for (int i = 0; i < quantQuadras; i++) {
    quantParametros += (QUANTIDADE_PARAMETROS_LOTE * quantLotes[i]);
  }
  double *retorno = new double[quantParametros * 2];
  string pastaEntradaAux = pastaEntrada;
  string nomeArquivoEntrada = pastaEntradaAux + string("Geral.csv");
  ifstream arquivoEntrada(nomeArquivoEntrada);
  int i = 0;
  if (arquivoEntrada.is_open()) {
    arquivoEntrada.ignore(1024, '\n');
    for (; i < QUANTIDADE_PARAMETROS_GERAIS * 2; i++) {
      arquivoEntrada >> retorno[i];
      arquivoEntrada.get();
      i++;
      arquivoEntrada >> retorno[i];
      arquivoEntrada.get();
      arquivoEntrada.ignore(1024, '\n');
    }
    arquivoEntrada.close();
  } else {
    cerr << "Arquivo: " << nomeArquivoEntrada << " nao foi aberto!" << endl;
    exit(1);
  }
  for (int q = 0; q < quantQuadras; q++) {
    for (int k = 0; k < quantLotes[q]; k++) {
      pastaEntradaAux = pastaEntrada;
      nomeArquivoEntrada = pastaEntradaAux + string("Quadra_") + to_string(q) +
                           SEPARADOR + string("Lote_") + to_string(k) +
                           string(".csv");
      arquivoEntrada.open(nomeArquivoEntrada);
      if (arquivoEntrada.is_open()) {
        arquivoEntrada.ignore(1024, '\n');
        for (int j = 0; j < QUANTIDADE_PARAMETROS_LOTE; j++) {
          arquivoEntrada >> retorno[i];
          arquivoEntrada.get();
          i++;
          arquivoEntrada >> retorno[i];
          i++;
          arquivoEntrada.ignore(1024, '\n');
        }
        arquivoEntrada.close();
      } else {
        cerr << "Arquivo: " << nomeArquivoEntrada << " nao foi aberto!" << endl;
        exit(1);
      }
    }
  }
  return make_tuple(quantParametros * 2, retorno);
}

int *calcularIndexParametros(const int *quantLotes, int quantQuadras) {
  int *retorno = new int[quantQuadras];
  retorno[0] = QUANTIDADE_PARAMETROS_GERAIS * 2;
  for (int i = 1; i < quantQuadras; ++i) {
    retorno[i] =
        retorno[i - 1] + (QUANTIDADE_PARAMETROS_LOTE * 2 * quantLotes[i - 1]);
  }
  return retorno;
}
}

#endif
