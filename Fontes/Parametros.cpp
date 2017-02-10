#ifndef PARAMETROS_H
#define PARAMETROS_H

#define QUANTIDADE_PARAMETROS_GERAIS 2
#define QUANTIDADE_PARAMETROS_LOTE 8
#define PARAMETRO(idLote, idQuadra)                                            \
  indexParametros[idQuadra] + idLote *QUANTIDADE_PARAMETROS_LOTE * 2
#define ENTRE_FAIXA(min, max, percentual) min + (max - min) * percentual

#define QUANTIDADE_SIMULACOES (int)(parametros[0])
#define NUMERO_CICLOS_SIMULACAO (int)(parametros[2])
#define QUANTIDADE_HUMANOS_SUSCETIVEIS(idLote, idQuadra)                       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 0])
#define QUANTIDADE_HUMANOS_EXPOSTOS(idLote, idQuadra)                          \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 2])
#define QUANTIDADE_HUMANOS_INFECTADOS(idLote, idQuadra)                        \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 4])
#define QUANTIDADE_HUMANOS_RECUPERADOS(idLote, idQuadra)                       \
  (int)(parametros[PARAMETRO(idLote, idQuadra) + 6])
#define TAXA_INFECCAO(idLote, idQuadra, percentual)                            \
  (double)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 8],            \
                       parametros[PARAMETRO(idLote, idQuadra) + 9],            \
                       percentual))
#define PERIODO_EXPOSTO(idLote, idQuadra, percentual)                          \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 10],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 11], percentual))
#define PERIODO_INFECTADO(idLote, idQuadra, percentual)                        \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 12],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 13], percentual))
#define PERIODO_RECUPERADO(idLote, idQuadra, percentual)                       \
  (int)(ENTRE_FAIXA(parametros[PARAMETRO(idLote, idQuadra) + 14],              \
                    parametros[PARAMETRO(idLote, idQuadra) + 15], percentual))

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
