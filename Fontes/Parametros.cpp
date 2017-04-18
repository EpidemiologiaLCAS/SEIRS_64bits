#ifndef PARAMETROS_H
#define PARAMETROS_H

#define QUANTIDADE_PARAMETROS_GERAIS 54
#define ENTRE_FAIXA(min, max, percentual)                                      \
  ((min) + ((max) - (min)) * (percentual))

#define QUANTIDADE_SIMULACOES (int)(parametros[0])
#define NUMERO_CICLOS_SIMULACAO (int)(parametros[2])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO (int)(parametros[4])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO (int)(parametros[6])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO (int)(parametros[8])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO (int)(parametros[10])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO (int)(parametros[12])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO (int)(parametros[14])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO (int)(parametros[16])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO (int)(parametros[18])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO (int)(parametros[20])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO (int)(parametros[22])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO (int)(parametros[24])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO (int)(parametros[26])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO (int)(parametros[28])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO (int)(parametros[30])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO (int)(parametros[32])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO (int)(parametros[34])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO (int)(parametros[36])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO (int)(parametros[38])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO (int)(parametros[40])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO (int)(parametros[42])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO (int)(parametros[44])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO (int)(parametros[46])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO (int)(parametros[48])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO (int)(parametros[50])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO (int)(parametros[52])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO (int)(parametros[54])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO (int)(parametros[56])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO (int)(parametros[58])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO (int)(parametros[60])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO (int)(parametros[62])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO (int)(parametros[64])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO (int)(parametros[66])

#define TAXA_INFECCAO_CRIANCA(percentual)                                      \
  (double)(ENTRE_FAIXA(parametros[68], parametros[69], percentual))
#define PERIODO_EXPOSTO_CRIANCA(percentual)                                    \
  (int)(ENTRE_FAIXA(parametros[70], parametros[71], percentual))
#define PERIODO_INFECTADO_CRIANCA(percentual)                                  \
  (int)(ENTRE_FAIXA(parametros[72], parametros[73], percentual))
#define PERIODO_RECUPERADO_CRIANCA(percentual)                                 \
  (int)(ENTRE_FAIXA(parametros[74], parametros[75], percentual))

#define TAXA_INFECCAO_JOVEM(percentual)                                        \
  (double)(ENTRE_FAIXA(parametros[76], parametros[77], percentual))
#define PERIODO_EXPOSTO_JOVEM(percentual)                                      \
  (int)(ENTRE_FAIXA(parametros[78], parametros[79], percentual))
#define PERIODO_INFECTADO_JOVEM(percentual)                                    \
  (int)(ENTRE_FAIXA(parametros[80], parametros[81], percentual))
#define PERIODO_RECUPERADO_JOVEM(percentual)                                   \
  (int)(ENTRE_FAIXA(parametros[82], parametros[83], percentual))

#define TAXA_INFECCAO_ADULTO(percentual)                                       \
  (double)(ENTRE_FAIXA(parametros[84], parametros[85], percentual))
#define PERIODO_EXPOSTO_ADULTO(percentual)                                     \
  (int)(ENTRE_FAIXA(parametros[86], parametros[87], percentual))
#define PERIODO_INFECTADO_ADULTO(percentual)                                   \
  (int)(ENTRE_FAIXA(parametros[88], parametros[89], percentual))
#define PERIODO_RECUPERADO_ADULTO(percentual)                                  \
  (int)(ENTRE_FAIXA(parametros[90], parametros[91], percentual))

#define TAXA_INFECCAO_IDOSO(percentual)                                        \
  (double)(ENTRE_FAIXA(parametros[92], parametros[93], percentual))
#define PERIODO_EXPOSTO_IDOSO(percentual)                                      \
  (int)(ENTRE_FAIXA(parametros[94], parametros[95], percentual))
#define PERIODO_INFECTADO_IDOSO(percentual)                                    \
  (int)(ENTRE_FAIXA(parametros[96], parametros[97], percentual))
#define PERIODO_RECUPERADO_IDOSO(percentual)                                   \
  (int)(ENTRE_FAIXA(parametros[98], parametros[99], percentual))

#define TAXA_MOBILIDADE_CRIANCA(percentual)                                    \
  (double)(ENTRE_FAIXA(parametros[100], parametros[101], percentual))
#define TAXA_MOBILIDADE_JOVEM(percentual)                                      \
  (double)(ENTRE_FAIXA(parametros[102], parametros[103], percentual))
#define TAXA_MOBILIDADE_ADULTO(percentual)                                     \
  (double)(ENTRE_FAIXA(parametros[104], parametros[105], percentual))
#define TAXA_MOBILIDADE_IDOSO(percentual)                                      \
  (double)(ENTRE_FAIXA(parametros[106], parametros[107], percentual))

default_random_engine
    gen(chrono::system_clock::now().time_since_epoch().count());
uniform_real_distribution<double> dis(0.0, 1.0);

double randomizarPercentual() { return dis(gen); }

namespace Parametros {

tuple<int, int *, int *, int *, int *, int *, int *, int *, int *, int *, int *,
      int *, int *, int, int *, int *, int, int *, int *>
lerVetores() {
  int quantQuadras, *quantLotes, *indexQuadras;
  int *indexVizinhancas, *vizinhancas;
  int *indexPosicoes, *posicoes;
  int *indexFronteiras, *fronteiras;
  int *indexEsquinas, *esquinas;
  int *indexCentrosEsquinas, *centrosEsquinas;
  int quantRotas, *indexRotas, *rotas;
  int quantTrajetos, *indexTrajetos, *trajetos;
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
    indexFronteiras = new int[indexQuadras[quantQuadras * 2 - 1] + 1];
    for (int i = 0; i < indexQuadras[quantQuadras * 2 - 1] + 1; ++i) {
      arquivoEntrada >> indexFronteiras[i];
      arquivoEntrada.get();
    }
    fronteiras = new int[indexFronteiras[indexQuadras[quantQuadras * 2 - 1]]];
    for (int i = 0; i < indexFronteiras[indexQuadras[quantQuadras * 2 - 1]];
         ++i) {
      arquivoEntrada >> fronteiras[i];
      arquivoEntrada.get();
    }
    indexEsquinas = new int[quantLotes[0] + 1];
    for (int i = 0; i < quantLotes[0] + 1; ++i) {
      arquivoEntrada >> indexEsquinas[i];
      arquivoEntrada.get();
    }
    esquinas = new int[indexEsquinas[quantLotes[0]]];
    for (int i = 0; i < indexEsquinas[quantLotes[0]]; ++i) {
      arquivoEntrada >> esquinas[i];
      arquivoEntrada.get();
    }
    indexCentrosEsquinas = new int[quantLotes[0] + 1];
    for (int i = 0; i < quantLotes[0] + 1; ++i) {
      arquivoEntrada >> indexCentrosEsquinas[i];
      arquivoEntrada.get();
    }
    centrosEsquinas = new int[indexCentrosEsquinas[quantLotes[0]]];
    for (int i = 0; i < indexCentrosEsquinas[quantLotes[0]]; ++i) {
      arquivoEntrada >> centrosEsquinas[i];
      arquivoEntrada.get();
    }
    arquivoEntrada >> quantRotas;
    arquivoEntrada.get();
    indexRotas = new int[quantRotas + 1];
    for (int i = 0; i < quantRotas + 1; ++i) {
      arquivoEntrada >> indexRotas[i];
      arquivoEntrada.get();
    }
    rotas = new int[indexRotas[quantRotas]];
    for (int i = 0; i < indexRotas[quantRotas]; ++i) {
      arquivoEntrada >> rotas[i];
      arquivoEntrada.get();
    }
    
    arquivoEntrada >> quantTrajetos;
    arquivoEntrada.get();
    indexTrajetos = new int[quantTrajetos + 1];
    for (int i = 0; i < quantTrajetos + 1; ++i) {
      arquivoEntrada >> indexTrajetos[i];
      arquivoEntrada.get();
    }
    trajetos = new int[indexTrajetos[quantTrajetos]];
    for (int i = 0; i < indexTrajetos[quantTrajetos]; ++i) {
      arquivoEntrada >> trajetos[i];
      arquivoEntrada.get();
    }
    arquivoEntrada.close();
  } else {
    cerr << "Arquivo: " << nomeArquivoEntrada << " nao foi aberto!" << endl;
    exit(1);
  }
  return make_tuple(quantQuadras, quantLotes, indexQuadras, indexVizinhancas,
                    vizinhancas, indexPosicoes, posicoes, indexFronteiras,
                    fronteiras, indexEsquinas, esquinas, indexCentrosEsquinas,
                    centrosEsquinas, quantRotas, indexRotas, rotas, 
                    quantTrajetos, indexTrajetos, trajetos);
}

tuple<int, double *> lerParametros(string pastaEntrada, const int *quantLotes,
                                   int quantQuadras) {
  int quantParametros = QUANTIDADE_PARAMETROS_GERAIS;
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
  return make_tuple(quantParametros * 2, retorno);
}

int *calcularIndexParametros(const int *quantLotes, int quantQuadras) {
  int *retorno = new int[quantQuadras];
  retorno[0] = QUANTIDADE_PARAMETROS_GERAIS * 2;
  return retorno;
}
}

#endif
