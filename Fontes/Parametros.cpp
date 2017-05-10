#ifndef __PARAMETROS__
#define __PARAMETROS__

#define QUANTIDADE_PARAMETROS_GERAIS 150
#define ENTRE_FAIXA(min, max, percentual)                                      \
  ((min) + ((max) - (min)) * (percentual))

#define QUANTIDADE_SIMULACOES (int)(parametros[0])
#define NUMERO_CICLOS_SIMULACAO (int)(parametros[2])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_LOCAL                 \
  (int)(parametros[4])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_LOCAL (int)(parametros[6])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_LOCAL                  \
  (int)(parametros[8])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_LOCAL                 \
  (int)(parametros[10])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_ALEATORIO             \
  (int)(parametros[12])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_ALEATORIO                \
  (int)(parametros[14])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_ALEATORIO              \
  (int)(parametros[16])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_ALEATORIO             \
  (int)(parametros[18])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_LIVRE                 \
  (int)(parametros[20])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_LIVRE                    \
  (int)(parametros[22])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_LIVRE                  \
  (int)(parametros[24])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_LIVRE                 \
  (int)(parametros[26])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_TRAJETO               \
  (int)(parametros[28])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_TRAJETO                  \
  (int)(parametros[30])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_TRAJETO                \
  (int)(parametros[32])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_TRAJETO               \
  (int)(parametros[34])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_LOCAL                   \
  (int)(parametros[36])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_LOCAL (int)(parametros[38])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_LOCAL                    \
  (int)(parametros[40])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_LOCAL                   \
  (int)(parametros[42])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_ALEATORIO               \
  (int)(parametros[44])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_ALEATORIO                  \
  (int)(parametros[46])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_ALEATORIO                \
  (int)(parametros[48])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_ALEATORIO               \
  (int)(parametros[50])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_LIVRE                   \
  (int)(parametros[52])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_LIVRE (int)(parametros[54])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_LIVRE                    \
  (int)(parametros[56])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_LIVRE                   \
  (int)(parametros[58])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_TRAJETO                 \
  (int)(parametros[60])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_TRAJETO                    \
  (int)(parametros[62])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_TRAJETO                  \
  (int)(parametros[64])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_TRAJETO                 \
  (int)(parametros[66])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_LOCAL                  \
  (int)(parametros[68])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_LOCAL (int)(parametros[70])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_LOCAL                   \
  (int)(parametros[72])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_LOCAL                  \
  (int)(parametros[74])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_ALEATORIO              \
  (int)(parametros[76])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_ALEATORIO                 \
  (int)(parametros[78])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_ALEATORIO               \
  (int)(parametros[80])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_ALEATORIO              \
  (int)(parametros[82])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_LIVRE                  \
  (int)(parametros[84])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_LIVRE (int)(parametros[86])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_LIVRE                   \
  (int)(parametros[88])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_LIVRE                  \
  (int)(parametros[90])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_TRAJETO                \
  (int)(parametros[92])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_TRAJETO                   \
  (int)(parametros[94])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_TRAJETO                 \
  (int)(parametros[96])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_TRAJETO                \
  (int)(parametros[98])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_LOCAL                   \
  (int)(parametros[100])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_LOCAL (int)(parametros[102])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_LOCAL                    \
  (int)(parametros[104])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_LOCAL                   \
  (int)(parametros[106])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_ALEATORIO               \
  (int)(parametros[108])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_ALEATORIO                  \
  (int)(parametros[110])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_ALEATORIO                \
  (int)(parametros[112])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_ALEATORIO               \
  (int)(parametros[114])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_LIVRE                   \
  (int)(parametros[116])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_LIVRE (int)(parametros[118])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_LIVRE                    \
  (int)(parametros[120])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_LIVRE                   \
  (int)(parametros[122])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_TRAJETO                 \
  (int)(parametros[124])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_TRAJETO                    \
  (int)(parametros[126])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_TRAJETO                  \
  (int)(parametros[128])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_TRAJETO                 \
  (int)(parametros[130])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_LOCAL                  \
  (int)(parametros[132])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_LOCAL                     \
  (int)(parametros[134])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_LOCAL                   \
  (int)(parametros[136])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_LOCAL                  \
  (int)(parametros[138])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_ALEATORIO              \
  (int)(parametros[140])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_ALEATORIO                 \
  (int)(parametros[142])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_ALEATORIO               \
  (int)(parametros[144])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_ALEATORIO              \
  (int)(parametros[146])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_LIVRE                  \
  (int)(parametros[148])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_LIVRE                     \
  (int)(parametros[150])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_LIVRE                   \
  (int)(parametros[152])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_LIVRE                  \
  (int)(parametros[154])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_TRAJETO                \
  (int)(parametros[156])
#define QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_TRAJETO                   \
  (int)(parametros[158])
#define QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_TRAJETO                 \
  (int)(parametros[160])
#define QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_TRAJETO                \
  (int)(parametros[162])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_LOCAL                    \
  (int)(parametros[164])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_LOCAL (int)(parametros[166])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_LOCAL                     \
  (int)(parametros[168])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_LOCAL                    \
  (int)(parametros[170])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_ALEATORIO                \
  (int)(parametros[172])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_ALEATORIO                   \
  (int)(parametros[174])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_ALEATORIO                 \
  (int)(parametros[176])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_ALEATORIO                \
  (int)(parametros[178])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_LIVRE                    \
  (int)(parametros[180])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_LIVRE (int)(parametros[182])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_LIVRE                     \
  (int)(parametros[184])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_LIVRE                    \
  (int)(parametros[186])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_TRAJETO                  \
  (int)(parametros[188])
#define QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_TRAJETO                     \
  (int)(parametros[190])
#define QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_TRAJETO                   \
  (int)(parametros[192])
#define QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_TRAJETO                  \
  (int)(parametros[194])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_LOCAL                   \
  (int)(parametros[196])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_LOCAL (int)(parametros[198])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_LOCAL                    \
  (int)(parametros[200])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_LOCAL                   \
  (int)(parametros[202])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_ALEATORIO               \
  (int)(parametros[204])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_ALEATORIO                  \
  (int)(parametros[206])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_ALEATORIO                \
  (int)(parametros[208])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_ALEATORIO               \
  (int)(parametros[210])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_LIVRE                   \
  (int)(parametros[212])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_LIVRE (int)(parametros[214])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_LIVRE                    \
  (int)(parametros[216])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_LIVRE                   \
  (int)(parametros[218])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_TRAJETO                 \
  (int)(parametros[220])
#define QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_TRAJETO                    \
  (int)(parametros[222])
#define QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_TRAJETO                  \
  (int)(parametros[224])
#define QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_TRAJETO                 \
  (int)(parametros[226])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_LOCAL                    \
  (int)(parametros[228])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_LOCAL (int)(parametros[230])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_LOCAL                     \
  (int)(parametros[232])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_LOCAL                    \
  (int)(parametros[234])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_ALEATORIO                \
  (int)(parametros[236])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_ALEATORIO                   \
  (int)(parametros[238])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_ALEATORIO                 \
  (int)(parametros[240])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_ALEATORIO                \
  (int)(parametros[242])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_LIVRE                    \
  (int)(parametros[244])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_LIVRE (int)(parametros[246])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_LIVRE                     \
  (int)(parametros[248])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_LIVRE                    \
  (int)(parametros[250])

#define QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_TRAJETO                  \
  (int)(parametros[252])
#define QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_TRAJETO                     \
  (int)(parametros[254])
#define QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_TRAJETO                   \
  (int)(parametros[256])
#define QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_TRAJETO                  \
  (int)(parametros[258])

#define TAXA_INFECCAO_CRIANCA(percentual)                                      \
  (double)(ENTRE_FAIXA(parametros[260], parametros[261], (percentual)))
#define PERIODO_EXPOSTO_CRIANCA(percentual)                                    \
  (int)(ENTRE_FAIXA(parametros[262], parametros[263], (percentual)))
#define PERIODO_INFECTADO_CRIANCA(percentual)                                  \
  (int)(ENTRE_FAIXA(parametros[264], parametros[265], (percentual)))
#define PERIODO_RECUPERADO_CRIANCA(percentual)                                 \
  (int)(ENTRE_FAIXA(parametros[266], parametros[267], (percentual)))

#define TAXA_INFECCAO_JOVEM(percentual)                                        \
  (double)(ENTRE_FAIXA(parametros[268], parametros[269], (percentual)))
#define PERIODO_EXPOSTO_JOVEM(percentual)                                      \
  (int)(ENTRE_FAIXA(parametros[270], parametros[271], (percentual)))
#define PERIODO_INFECTADO_JOVEM(percentual)                                    \
  (int)(ENTRE_FAIXA(parametros[272], parametros[273], (percentual)))
#define PERIODO_RECUPERADO_JOVEM(percentual)                                   \
  (int)(ENTRE_FAIXA(parametros[274], parametros[275], (percentual)))

#define TAXA_INFECCAO_ADULTO(percentual)                                       \
  (double)(ENTRE_FAIXA(parametros[276], parametros[277], (percentual)))
#define PERIODO_EXPOSTO_ADULTO(percentual)                                     \
  (int)(ENTRE_FAIXA(parametros[278], parametros[279], (percentual)))
#define PERIODO_INFECTADO_ADULTO(percentual)                                   \
  (int)(ENTRE_FAIXA(parametros[280], parametros[281], (percentual)))
#define PERIODO_RECUPERADO_ADULTO(percentual)                                  \
  (int)(ENTRE_FAIXA(parametros[282], parametros[283], (percentual)))

#define TAXA_INFECCAO_IDOSO(percentual)                                        \
  (double)(ENTRE_FAIXA(parametros[284], parametros[285], (percentual)))
#define PERIODO_EXPOSTO_IDOSO(percentual)                                      \
  (int)(ENTRE_FAIXA(parametros[286], parametros[287], (percentual)))
#define PERIODO_INFECTADO_IDOSO(percentual)                                    \
  (int)(ENTRE_FAIXA(parametros[288], parametros[289], (percentual)))
#define PERIODO_RECUPERADO_IDOSO(percentual)                                   \
  (int)(ENTRE_FAIXA(parametros[290], parametros[291], (percentual)))

#define TAXA_MOBILIDADE_CRIANCA(percentual)                                    \
  (double)(ENTRE_FAIXA(parametros[292], parametros[293], (percentual)))
#define TAXA_MOBILIDADE_JOVEM(percentual)                                      \
  (double)(ENTRE_FAIXA(parametros[294], parametros[295], (percentual)))
#define TAXA_MOBILIDADE_ADULTO(percentual)                                     \
  (double)(ENTRE_FAIXA(parametros[296], parametros[297], (percentual)))
#define TAXA_MOBILIDADE_IDOSO(percentual)                                      \
  (double)(ENTRE_FAIXA(parametros[298], parametros[299], (percentual)))

#ifdef __CPU__

std::default_random_engine
    gen(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<double> dis(0.0, 1.0);

double randomizarPercentual() { return dis(gen); }

#endif

#ifdef __GPU__

#define randomizarPercentual()                                                 \
  curand_uniform_double(((curandState *)seeds) + id)

#endif

namespace Parametros {

std::tuple<int, int *, int *, int *, int *, int *, int *, int *, int *, int *,
           int *, int *, int *, int, int *, int *, int, int *, int *, int *,
           int *, int *>
lerVetores() {
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

  std::string nomeArquivoEntrada =
      std::string("Entradas") + SEPARADOR + std::string("Vetores.csv");
  std::ifstream arquivoEntrada(nomeArquivoEntrada);
  if (arquivoEntrada.is_open()) {
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
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

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
    indexPeriodos = new int[quantTrajetos + 1];
    for (int i = 0; i < quantTrajetos + 1; ++i) {
      arquivoEntrada >> indexPeriodos[i];
      arquivoEntrada.get();
    }
    periodos = new int[indexPeriodos[quantTrajetos]];
    for (int i = 0; i < indexPeriodos[quantTrajetos]; ++i) {
      arquivoEntrada >> periodos[i];
      arquivoEntrada.get();
    }

    arquivoEntrada.ignore(1024, '\n');
    arquivoEntrada.ignore(1024, '\n');
    indexTrajetosFaixaEtaria = new int[QUANT_IDADES + 1];
    for (int i = 0; i < QUANT_IDADES + 1; ++i) {
      arquivoEntrada >> indexTrajetosFaixaEtaria[i];
      arquivoEntrada.get();
    }

    arquivoEntrada.close();
  } else {
    std::cerr << "Arquivo: " << nomeArquivoEntrada << " nao foi aberto!"
              << std::endl;
    exit(1);
  }
  return std::make_tuple(
      quantQuadras, quantLotes, indexQuadras, indexVizinhancas, vizinhancas,
      indexPosicoes, posicoes, indexFronteiras, fronteiras, indexEsquinas,
      esquinas, indexCentrosEsquinas, centrosEsquinas, quantRotas, indexRotas,
      rotas, quantTrajetos, indexTrajetos, trajetos, indexPeriodos, periodos,
      indexTrajetosFaixaEtaria);
}

std::tuple<int, double *> lerParametros(std::string pastaEntrada,
                                        const int *quantLotes,
                                        int quantQuadras) {
  int quantParametros = QUANTIDADE_PARAMETROS_GERAIS;
  double *retorno = new double[quantParametros * 2];
  std::string pastaEntradaAux = pastaEntrada;
  std::string nomeArquivoEntrada = pastaEntradaAux + std::string("Geral.csv");
  std::ifstream arquivoEntrada(nomeArquivoEntrada);
  int i = 0;
  if (arquivoEntrada.is_open()) {
    arquivoEntrada.ignore(1024, '\n');
    for (; i < QUANTIDADE_PARAMETROS_GERAIS * 2;) {
      arquivoEntrada >> retorno[i++];
      arquivoEntrada.get();
      arquivoEntrada >> retorno[i++];
      arquivoEntrada.get();
      arquivoEntrada.ignore(1024, '\n');
    }
    arquivoEntrada.close();
  } else {
    std::cerr << "Arquivo: " << nomeArquivoEntrada << " nao foi aberto!"
              << std::endl;
    exit(1);
  }
  return std::make_tuple(quantParametros * 2, retorno);
}
}

#endif
