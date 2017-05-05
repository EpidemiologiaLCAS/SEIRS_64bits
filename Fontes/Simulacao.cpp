#ifndef __SIMULACAO__
#define __SIMULACAO__

#ifdef __GPU__

__global__ void initCurand(curandState *seeds, const int *rands,
                           int maxThreads) {
  int i = threadIdx.x + blockIdx.x * blockDim.x;
  if (i < maxThreads) {
    curand_init(rands[i], i, 0, &seeds[i]);
  }
}

#define CABECALHO_MOVIMENTACAO int id = blockIdx.x * blockDim.x + threadIdx.x; \
                               if (id < quantAgentes)
#define CABECALHO_CONTATO int id = blockIdx.x * blockDim.x + threadIdx.x; \
                          if (id < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4)
#define CABECALHO_TRANSICAO int id = blockIdx.x * blockDim.x + threadIdx.x; \
                            if (id < quantAgentes)

#define CABECALHO_SAIDA_ESPACIAL int id = blockIdx.x * blockDim.x + threadIdx.x; \
                                 if (id < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4)
#define CABECALHO_SAIDAS_QUANTIDADES int id = blockIdx.x * blockDim.x + threadIdx.x; \
                                     if (id < quantAgentes)
                                     
#define ATOMIC_ADD_TOTAL(ciclo, d, e) atomicAdd(&saidaQuantidadeTotal[VEC(ciclo, d + e, COLUNAS_SAIDAS_QUANTIDADES)], 1)
                   
#define ATOMIC_ADD_QUADRAS(ciclo, d, e) atomicAdd(&saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(id)] + VEC(ciclo, d + e, COLUNAS_SAIDAS_QUANTIDADES)], 1)
                      
#define MARCADOR_GLOBAL __global__
#define MARCADOR_DEVICE __device__

#endif

#ifdef __CPU__

#define CABECALHO_MOVIMENTACAO _Pragma("omp parallel for") \
                               for (int id = 0; id < quantAgentes; ++id)
#define CABECALHO_CONTATO _Pragma("omp parallel for") \
                          for (int id = 0; id < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4; id++)
#define CABECALHO_TRANSICAO _Pragma("omp parallel for") \
                            for (int id = 0; id < quantAgentes; id++)
                            
#define CABECALHO_SAIDA_ESPACIAL _Pragma("omp parallel for") \
                                 for (int id = 0; id < indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4; id++)
#define CABECALHO_SAIDAS_QUANTIDADES _Pragma("omp parallel for") \
                                     for (int id = 0; id < quantAgentes; id++)
                                     
#define ATOMIC_ADD_TOTAL(ciclo, d, e) _Pragma("omp atomic") \
                                      saidaQuantidadeTotal[VEC(ciclo, d + e, COLUNAS_SAIDAS_QUANTIDADES)]++
                   
#define ATOMIC_ADD_QUADRAS(ciclo, d, e) _Pragma("omp atomic") \
                                        saidaQuantidadeQuadras[indexSaidaQuantidadeQuadras[GET_Q(id)] + VEC(ciclo, d + e, COLUNAS_SAIDAS_QUANTIDADES)]++

#define MARCADOR_GLOBAL
#define MARCADOR_DEVICE

#endif

namespace Agentes {

void inicializarAgente(TIPO_AGENTE *agentes, int id, int e, int x, int y, int l,
                       int q, int s, int i, int t, int k) {
  SET_Q(id, q);
  SET_L(id, l);
  SET_R(id, 0);
  SET_T(id, t);
  SET_F(id, 1);
  // SET_A
  
  SET_S(id, s);
  SET_I(id, i);
  SET_E(id, e);
  // SET_U
  // SET_H
  SET_C(id, 0);
  SET_M(id, 0);
  SET_K(id, k);
  
  SET_X(id, x);
  
  SET_Y(id, y);  
}

void inserirAgentes(int quantAgentes, TIPO_AGENTE *agentes,
                    const double *parametros,
                    const int *quantLotes, int quantQuadras,
                    const int *indexQuadras, const int *indexPosicoes,
                    const int *posicoes, const int *indexRotas,
                    const int *rotas, const int *indexTrajetos,
                    const int *trajetos, const int *indexTrajetosFaixaEtaria, 
                    int quantidade, int estado, int sexo,
                    int idade, int *i, int k) {
  int posicoesLote, p, x, y, l, q, t;
  
  std::default_random_engine
  gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  
  for (int j = 0; j < quantidade; ++j) {      
    t = ENTRE_FAIXA(indexTrajetosFaixaEtaria[3 - idade], indexTrajetosFaixaEtaria[(3 - idade) + 1], dis(gen));

    l = rotas[indexRotas[trajetos[indexTrajetos[t]]] + 0];
    q = rotas[indexRotas[trajetos[indexTrajetos[t]]] + 1];
    posicoesLote = (indexPosicoes[indexQuadras[2 * q] + l + 1] -
                    indexPosicoes[indexQuadras[2 * q] + l]) / 4;
    p = ENTRE_FAIXA(0, posicoesLote, dis(gen));
    x = posicoes[indexPosicoes[indexQuadras[q * 2] + l] + p * 4 + 0];
    y = posicoes[indexPosicoes[indexQuadras[q * 2] + l] + p * 4 + 1];
    inicializarAgente(agentes, *i, estado, x, y, l, q, sexo, idade, t, k);
    (*i)++;
  }
}

TIPO_AGENTE *criarAgentes(int quantAgentes, const double *parametros,
                          const int *quantLotes,
                          int quantQuadras, const int *indexQuadras,
                          const int *indexPosicoes, const int *posicoes,
                          const int *indexRotas, const int *rotas,
                          const int *indexTrajetos, const int *trajetos, 
                          const int *indexTrajetosFaixaEtaria) {
  int i = 0;
  TIPO_AGENTE *agentes = new TIPO_AGENTE[quantAgentes * ATRIBUTOS_AGENTE];
  
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_LOCAL, SUSCETIVEL,
                 MASCULINO, CRIANCA, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_LOCAL, EXPOSTO,
                 MASCULINO, CRIANCA, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_LOCAL, INFECTADO,
                 MASCULINO, CRIANCA, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_LOCAL, RECUPERADO,
                 MASCULINO, CRIANCA, &i, LOCAL);
  
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_ALEATORIO, SUSCETIVEL,
                 MASCULINO, CRIANCA, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_ALEATORIO, EXPOSTO,
                 MASCULINO, CRIANCA, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_ALEATORIO, INFECTADO,
                 MASCULINO, CRIANCA, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_ALEATORIO, RECUPERADO,
                 MASCULINO, CRIANCA, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_LIVRE, SUSCETIVEL,
                 MASCULINO, CRIANCA, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_LIVRE, EXPOSTO,
                 MASCULINO, CRIANCA, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_LIVRE, INFECTADO,
                 MASCULINO, CRIANCA, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_LIVRE, RECUPERADO,
                 MASCULINO, CRIANCA, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_TRAJETO, SUSCETIVEL,
                 MASCULINO, CRIANCA, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_TRAJETO, EXPOSTO,
                 MASCULINO, CRIANCA, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_TRAJETO, INFECTADO,
                 MASCULINO, CRIANCA, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_TRAJETO, RECUPERADO,
                 MASCULINO, CRIANCA, &i, TRAJETO);
                 

  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_LOCAL, SUSCETIVEL,
                 MASCULINO, JOVEM, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_LOCAL, EXPOSTO,
                 MASCULINO, JOVEM, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_LOCAL, INFECTADO,
                 MASCULINO, JOVEM, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_LOCAL, RECUPERADO,
                 MASCULINO, JOVEM, &i, LOCAL);
            
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_ALEATORIO, SUSCETIVEL,
                 MASCULINO, JOVEM, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_ALEATORIO, EXPOSTO,
                 MASCULINO, JOVEM, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_ALEATORIO, INFECTADO,
                 MASCULINO, JOVEM, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_ALEATORIO, RECUPERADO,
                 MASCULINO, JOVEM, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_LIVRE, SUSCETIVEL,
                 MASCULINO, JOVEM, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_LIVRE, EXPOSTO,
                 MASCULINO, JOVEM, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_LIVRE, INFECTADO,
                 MASCULINO, JOVEM, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_LIVRE, RECUPERADO,
                 MASCULINO, JOVEM, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_TRAJETO, SUSCETIVEL,
                 MASCULINO, JOVEM, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_TRAJETO, EXPOSTO,
                 MASCULINO, JOVEM, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_TRAJETO, INFECTADO,
                 MASCULINO, JOVEM, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_TRAJETO, RECUPERADO,
                 MASCULINO, JOVEM, &i, TRAJETO);
                 
  
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_LOCAL, SUSCETIVEL,
                 MASCULINO, ADULTO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_LOCAL, EXPOSTO,
                 MASCULINO, ADULTO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_LOCAL, INFECTADO,
                 MASCULINO, ADULTO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_LOCAL, RECUPERADO,
                 MASCULINO, ADULTO, &i, LOCAL);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_ALEATORIO, SUSCETIVEL,
                 MASCULINO, ADULTO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_ALEATORIO, EXPOSTO,
                 MASCULINO, ADULTO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_ALEATORIO, INFECTADO,
                 MASCULINO, ADULTO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_ALEATORIO, RECUPERADO,
                 MASCULINO, ADULTO, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_LIVRE, SUSCETIVEL,
                 MASCULINO, ADULTO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_LIVRE, EXPOSTO,
                 MASCULINO, ADULTO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_LIVRE, INFECTADO,
                 MASCULINO, ADULTO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_LIVRE, RECUPERADO,
                 MASCULINO, ADULTO, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_TRAJETO, SUSCETIVEL,
                 MASCULINO, ADULTO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_TRAJETO, EXPOSTO,
                 MASCULINO, ADULTO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_TRAJETO, INFECTADO,
                 MASCULINO, ADULTO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_TRAJETO, RECUPERADO,
                 MASCULINO, ADULTO, &i, TRAJETO);
                 

  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_LOCAL, SUSCETIVEL,
                 MASCULINO, IDOSO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_LOCAL, EXPOSTO,
                 MASCULINO, IDOSO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_LOCAL, INFECTADO,
                 MASCULINO, IDOSO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_LOCAL, RECUPERADO,
                 MASCULINO, IDOSO, &i, LOCAL);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_ALEATORIO, SUSCETIVEL,
                 MASCULINO, IDOSO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_ALEATORIO, EXPOSTO,
                 MASCULINO, IDOSO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_ALEATORIO, INFECTADO,
                 MASCULINO, IDOSO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_ALEATORIO, RECUPERADO,
                 MASCULINO, IDOSO, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_LIVRE, SUSCETIVEL,
                 MASCULINO, IDOSO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_LIVRE, EXPOSTO,
                 MASCULINO, IDOSO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_LIVRE, INFECTADO,
                 MASCULINO, IDOSO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_LIVRE, RECUPERADO,
                 MASCULINO, IDOSO, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_TRAJETO, SUSCETIVEL,
                 MASCULINO, IDOSO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_TRAJETO, EXPOSTO,
                 MASCULINO, IDOSO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_TRAJETO, INFECTADO,
                 MASCULINO, IDOSO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_TRAJETO, RECUPERADO,
                 MASCULINO, IDOSO, &i, TRAJETO);
  
  

  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_LOCAL, SUSCETIVEL,
                 FEMININO, CRIANCA, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_LOCAL, EXPOSTO,
                 FEMININO, CRIANCA, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_LOCAL, INFECTADO,
                 FEMININO, CRIANCA, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_LOCAL, RECUPERADO,
                 FEMININO, CRIANCA, &i, LOCAL);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_ALEATORIO, SUSCETIVEL,
                 FEMININO, CRIANCA, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_ALEATORIO, EXPOSTO,
                 FEMININO, CRIANCA, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_ALEATORIO, INFECTADO,
                 FEMININO, CRIANCA, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_ALEATORIO, RECUPERADO,
                 FEMININO, CRIANCA, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_LIVRE, SUSCETIVEL,
                 FEMININO, CRIANCA, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_LIVRE, EXPOSTO,
                 FEMININO, CRIANCA, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_LIVRE, INFECTADO,
                 FEMININO, CRIANCA, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_LIVRE, RECUPERADO,
                 FEMININO, CRIANCA, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_TRAJETO, SUSCETIVEL,
                 FEMININO, CRIANCA, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_TRAJETO, EXPOSTO,
                 FEMININO, CRIANCA, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_TRAJETO, INFECTADO,
                 FEMININO, CRIANCA, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_TRAJETO, RECUPERADO,
                 FEMININO, CRIANCA, &i, TRAJETO);
                 
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_LOCAL, SUSCETIVEL,
                 FEMININO, JOVEM, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_LOCAL, EXPOSTO, FEMININO,
                 JOVEM, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_LOCAL, INFECTADO,
                 FEMININO, JOVEM, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_LOCAL, RECUPERADO,
                 FEMININO, JOVEM, &i, LOCAL);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_ALEATORIO, SUSCETIVEL,
                 FEMININO, JOVEM, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_ALEATORIO, EXPOSTO, FEMININO,
                 JOVEM, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_ALEATORIO, INFECTADO,
                 FEMININO, JOVEM, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_ALEATORIO, RECUPERADO,
                 FEMININO, JOVEM, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_LIVRE, SUSCETIVEL,
                 FEMININO, JOVEM, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_LIVRE, EXPOSTO, FEMININO,
                 JOVEM, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_LIVRE, INFECTADO,
                 FEMININO, JOVEM, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_LIVRE, RECUPERADO,
                 FEMININO, JOVEM, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_TRAJETO, SUSCETIVEL,
                 FEMININO, JOVEM, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_TRAJETO, EXPOSTO, FEMININO,
                 JOVEM, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_TRAJETO, INFECTADO,
                 FEMININO, JOVEM, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_TRAJETO, RECUPERADO,
                 FEMININO, JOVEM, &i, TRAJETO);
                 
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_LOCAL, SUSCETIVEL,
                 FEMININO, ADULTO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_LOCAL, EXPOSTO, FEMININO,
                 ADULTO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_LOCAL, INFECTADO,
                 FEMININO, ADULTO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_LOCAL, RECUPERADO,
                 FEMININO, ADULTO, &i, LOCAL);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_ALEATORIO, SUSCETIVEL,
                 FEMININO, ADULTO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_ALEATORIO, EXPOSTO, FEMININO,
                 ADULTO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_ALEATORIO, INFECTADO,
                 FEMININO, ADULTO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_ALEATORIO, RECUPERADO,
                 FEMININO, ADULTO, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_LIVRE, SUSCETIVEL,
                 FEMININO, ADULTO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_LIVRE, EXPOSTO, FEMININO,
                 ADULTO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_LIVRE, INFECTADO,
                 FEMININO, ADULTO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_LIVRE, RECUPERADO,
                 FEMININO, ADULTO, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_TRAJETO, SUSCETIVEL,
                 FEMININO, ADULTO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_TRAJETO, EXPOSTO, FEMININO,
                 ADULTO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_TRAJETO, INFECTADO,
                 FEMININO, ADULTO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_TRAJETO, RECUPERADO,
                 FEMININO, ADULTO, &i, TRAJETO);
                 
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_LOCAL, SUSCETIVEL,
                 FEMININO, IDOSO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_LOCAL, EXPOSTO, FEMININO,
                 IDOSO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_LOCAL, INFECTADO,
                 FEMININO, IDOSO, &i, LOCAL);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_LOCAL, RECUPERADO,
                 FEMININO, IDOSO, &i, LOCAL);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_ALEATORIO, SUSCETIVEL,
                 FEMININO, IDOSO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_ALEATORIO, EXPOSTO, FEMININO,
                 IDOSO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_ALEATORIO, INFECTADO,
                 FEMININO, IDOSO, &i, ALEATORIO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_ALEATORIO, RECUPERADO,
                 FEMININO, IDOSO, &i, ALEATORIO);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_LIVRE, SUSCETIVEL,
                 FEMININO, IDOSO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_LIVRE, EXPOSTO, FEMININO,
                 IDOSO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_LIVRE, INFECTADO,
                 FEMININO, IDOSO, &i, LIVRE);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_LIVRE, RECUPERADO,
                 FEMININO, IDOSO, &i, LIVRE);
                 
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_TRAJETO, SUSCETIVEL,
                 FEMININO, IDOSO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_TRAJETO, EXPOSTO, FEMININO,
                 IDOSO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_TRAJETO, INFECTADO,
                 FEMININO, IDOSO, &i, TRAJETO);
  inserirAgentes(quantAgentes, agentes, parametros, quantLotes,
                 quantQuadras, indexQuadras, indexPosicoes, posicoes,
                 indexRotas, rotas, indexTrajetos, trajetos, indexTrajetosFaixaEtaria, 
                 QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_TRAJETO, RECUPERADO,
                 FEMININO, IDOSO, &i, TRAJETO);
                 
  return agentes;
}

int contarTotalAgentes(const int *quantLotes, int quantQuadras,
                       const double *parametros) {
  int quantAgentes = 0;
  quantAgentes += QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_MASCULINO_TRAJETO +
                  
                  

                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_MASCULINO_TRAJETO +
                  
                  

                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_MASCULINO_TRAJETO +
                  
                  

                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_MASCULINO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_MASCULINO_TRAJETO +
                  
                  
                  
                  
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_CRIANCA_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_CRIANCA_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_CRIANCA_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_CRIANCA_FEMININO_TRAJETO +
                  
                  
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_JOVEM_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_JOVEM_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_JOVEM_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_JOVEM_FEMININO_TRAJETO +
                  
                  
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_ADULTO_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_ADULTO_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_ADULTO_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_ADULTO_FEMININO_TRAJETO +
                  
                  
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_LOCAL +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_LOCAL +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_ALEATORIO +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_ALEATORIO +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_LIVRE +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_LIVRE +
                  
                  QUANTIDADE_AGENTES_SUSCETIVEIS_IDOSO_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_EXPOSTOS_IDOSO_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_INFECTADOS_IDOSO_FEMININO_TRAJETO +
                  QUANTIDADE_AGENTES_RECUPERADOS_IDOSO_FEMININO_TRAJETO;
  
  return quantAgentes;
}
}

namespace SaidasSimulacao {

void salvarSaidaEspacial(std::string pastaSaida, const int *saidaEspacial, const int *posicoes,
                         int quantLinhasSaidaEspacial,
                         int quantColunasSaidaEspacial) {
  int k = 0;
  std::string nomeArquivoSaida = pastaSaida + std::string("Espacial_Geo.csv");
  std::ofstream arquivoSaida(nomeArquivoSaida);
  if (arquivoSaida.is_open()) {
    for (int i = 0; i < quantLinhasSaidaEspacial; ++i) {
      arquivoSaida << posicoes[k + 0]  << ";" <<  posicoes[k + 1] << ";";
      k += 4;
      for (int j = 0; j < quantColunasSaidaEspacial; ++j) {
        arquivoSaida << saidaEspacial[VEC(i, j, quantColunasSaidaEspacial)]
                     << ";";
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

MARCADOR_GLOBAL void gerarSaidaQuantidadeTotal(const TIPO_AGENTE *agentes, int quantAgentes,
                               int *saidaQuantidadeTotal, int ciclo) {
CABECALHO_SAIDAS_QUANTIDADES {
    if (GET_S(id) == MASCULINO) {
      switch (GET_I(id)) {
      case CRIANCA: {
        ATOMIC_ADD_TOTAL(ciclo, 0, GET_E(id));
      } break;
      case JOVEM: {
        ATOMIC_ADD_TOTAL(ciclo, 4, GET_E(id));
      } break;
      case ADULTO: {
        ATOMIC_ADD_TOTAL(ciclo, 8, GET_E(id));
      } break;
      case IDOSO: {
        ATOMIC_ADD_TOTAL(ciclo, 12, GET_E(id));
      } break;
      }
    } else {
      switch (GET_I(id)) {
      case CRIANCA: {
        ATOMIC_ADD_TOTAL(ciclo, 16, GET_E(id));
      } break;
      case JOVEM: {
        ATOMIC_ADD_TOTAL(ciclo, 20, GET_E(id));
      } break;
      case ADULTO: {
        ATOMIC_ADD_TOTAL(ciclo, 24, GET_E(id));
      } break;
      case IDOSO: {
        ATOMIC_ADD_TOTAL(ciclo, 28, GET_E(id));
      } break;
      }
    }
    ATOMIC_ADD_TOTAL(ciclo, 32, 0);
  }
}

MARCADOR_GLOBAL void gerarSaidaQuantidadeQuadras(const TIPO_AGENTE *agentes, int quantAgentes,
                                 const int *indexSaidaQuantidadeQuadras,
                                 int *saidaQuantidadeQuadras, int ciclo) {
CABECALHO_SAIDAS_QUANTIDADES {
    if (GET_S(id) == MASCULINO) {
      switch (GET_I(id)) {
      case CRIANCA: {
        ATOMIC_ADD_QUADRAS(ciclo, 0, GET_E(id));
      } break;
      case JOVEM: {
        ATOMIC_ADD_QUADRAS(ciclo, 4, GET_E(id));
      } break;
      case ADULTO: {
        ATOMIC_ADD_QUADRAS(ciclo, 8, GET_E(id));
      } break;
      case IDOSO: {
        ATOMIC_ADD_QUADRAS(ciclo, 12, GET_E(id));
      } break;
      }
    } else {
      switch (GET_I(id)) {
      case CRIANCA: {
        ATOMIC_ADD_QUADRAS(ciclo, 16, GET_E(id));
      } break;
      case JOVEM: {
        ATOMIC_ADD_QUADRAS(ciclo, 20, GET_E(id));
      } break;
      case ADULTO: {
        ATOMIC_ADD_QUADRAS(ciclo, 24, GET_E(id));
      } break;
      case IDOSO: {
        ATOMIC_ADD_QUADRAS(ciclo, 28, GET_E(id));
      } break;
      }
    }
    ATOMIC_ADD_QUADRAS(ciclo, 32, 0);
  }
}

MARCADOR_GLOBAL void gerarSaidaEspacial(const TIPO_AGENTE *agentes, int quantAgentes,
                        int *saidaEspacial, int ciclo, int quantQuadras,
                        int ciclos, const int *indexQuadras,
                        const int *indexPosicoes, const int *posicoes) {
CABECALHO_SAIDA_ESPACIAL {
    int x = posicoes[id * 4 + 0];
    int y = posicoes[id * 4 + 1];
    int l = posicoes[id * 4 + 2];
    int q = posicoes[id * 4 + 3];
    int e;
    for (int i = 0; i < quantAgentes; ++i) {
      if (GET_Q(i) == q && GET_L(i) == l && GET_X(i) == x && GET_Y(i) == y) {
        e = 2000;
        e += GET_E(i) + 1;
        e += (GET_I(i) + 1) * 10;
        if (e > saidaEspacial[VEC(id, ciclo, ciclos)]) {
          saidaEspacial[VEC(id, ciclo, ciclos)] = e;
        }
      }
    }
  }
}
}

namespace Simulacao {

MARCADOR_DEVICE void movimentacaoLocal(int id, void *seeds, TIPO_AGENTE *agentes, int quantAgentes,
                  const int *indexQuadras, const int *indexVizinhancas,
                  const int *vizinhancas, const double *parametros,
                  const int *indexFronteiras,
                  const int *fronteiras, const int *indexEsquinas,
                  const int *esquinas, const int *indexCentrosEsquinas,
                  const int *centrosEsquinas, int quantRotas,
                  const int *indexRotas, const int *rotas,
                  const int *indexPosicoes, const int *posicoes,
                  int quantTrajetos, const int *indexTrajetos,
                  const int *trajetos, const int *indexPeriodos,
                  const int *periodos) {
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
    // Conta quantas posições de vizinhança o agente possui
    int quantidade = 0;
    for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
         i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
      if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y && 
          vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
        quantidade++;
      }
    }
    // Se o agente possuir posições de vizinhanças
    if (quantidade > 0) {
      int indice = (int)(randomizarPercentual() * quantidade);
      int k = 0;
      for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
           i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
           i += 6) {
        if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
            vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
          if (k == indice) {
            x = vizinhancas[i + 2];
            y = vizinhancas[i + 3];
            l = vizinhancas[i + 4];
            q = vizinhancas[i + 5];
            SET_X(id, x);
            SET_Y(id, y);
            SET_L(id, l);
            SET_Q(id, q);
            break;
          }
          k++;
        }
      }
    }
  }
}

MARCADOR_DEVICE void movimentacaoAleatoria(int id, void *seeds, TIPO_AGENTE *agentes, int quantAgentes,
                  const int *indexQuadras, const int *indexVizinhancas,
                  const int *vizinhancas, const double *parametros,
                  const int *indexFronteiras,
                  const int *fronteiras, const int *indexEsquinas,
                  const int *esquinas, const int *indexCentrosEsquinas,
                  const int *centrosEsquinas, int quantRotas,
                  const int *indexRotas, const int *rotas,
                  const int *indexPosicoes, const int *posicoes,
                  int quantTrajetos, const int *indexTrajetos,
                  const int *trajetos, const int *indexPeriodos,
                  const int *periodos) {
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
    // Conta quantas posições de vizinhança o agente possui
    int quantidade = 0;
    for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
         i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
      if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
        quantidade++;
      }
    }
    // Se o agente possuir posições de vizinhanças
    if (quantidade > 0) {
      int indice = (int)(randomizarPercentual() * quantidade);
      int k = 0;
      for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
           i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
           i += 6) {
        if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
          if (k == indice) {
            x = vizinhancas[i + 2];
            y = vizinhancas[i + 3];
            l = vizinhancas[i + 4];
            q = vizinhancas[i + 5];
            SET_X(id, x);
            SET_Y(id, y);
            SET_L(id, l);
            SET_Q(id, q);
            break;
          }
          k++;
        }
      }
    }
  }
}

MARCADOR_DEVICE void movimentacaoLivre(int id, void *seeds, TIPO_AGENTE *agentes, int quantAgentes,
                  const int *indexQuadras, const int *indexVizinhancas,
                  const int *vizinhancas, const double *parametros,
                  const int *indexFronteiras,
                  const int *fronteiras, const int *indexEsquinas,
                  const int *esquinas, const int *indexCentrosEsquinas,
                  const int *centrosEsquinas, int quantRotas,
                  const int *indexRotas, const int *rotas,
                  const int *indexPosicoes, const int *posicoes,
                  int quantTrajetos, const int *indexTrajetos,
                  const int *trajetos, const int *indexPeriodos,
                  const int *periodos) {
  int q = GET_Q(id);
  int l = GET_L(id);
  int x = GET_X(id);
  int y = GET_Y(id);
  int m = GET_M(id);
  
  /*
  // PARAR O AGENTE APÓS UMA VOLTA
  if (m == -1) {
    continue;
  }
  */
  
  int r = GET_R(id);
  int t = GET_T(id);
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
    // Conta quantas posições de vizinhança o agente possui
    int quantidade = 0;
    for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
         i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
      if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
        quantidade++;
      }
    }
    // Se o agente possuir posições de vizinhanças
    if (quantidade > 0) {
      int l_origem = rotas[indexRotas[trajetos[indexTrajetos[t]] + r] + 0];
      int q_origem = rotas[indexRotas[trajetos[indexTrajetos[t]] + r] + 1];
      int l_destino =
          rotas[indexRotas[trajetos[indexTrajetos[t]] + r + 1] - 2];
      int q_destino =
          rotas[indexRotas[trajetos[indexTrajetos[t]] + r + 1] - 1];
      int x_destino;
      int y_destino;
      for (int i = indexFronteiras[indexQuadras[2 * q_destino] + l_destino];
           i < indexFronteiras[indexQuadras[2 * q_destino] + l_destino + 1]; 
           i += 3) {
          x_destino = fronteiras[i + 0];
          y_destino = fronteiras[i + 1];
          break;
      }
      // O AGENTE ESTÁ NA QUADRA E NO LOTE DE ORIGEM
      if (q == q_origem && l == l_origem) {
        if (GET_F(id) == 1) {
          SET_M(id, periodos[indexPeriodos[t] + r]);
          SET_F(id, 0);
        }
        m = GET_M(id);
        if (m > 0) {
          int quantidade = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
              quantidade++;
            }
          }
          int indice = (int)(randomizarPercentual() * quantidade);
          int k = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
              if (k == indice) {
                x = vizinhancas[i + 2];
                y = vizinhancas[i + 3];
                l = vizinhancas[i + 4];
                q = vizinhancas[i + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                SET_M(id, m - 1);
                break;
              }
              k++;
            }
          }
        } else {
          // Conta quantas posições vizinhas pertencem à próxima rua da rota
          int pontosRuas = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 5] == RUA) {
              pontosRuas++;
            }
          }
          // Se a vizinhança do agente tem uma posição vizinha que pertence a
          // uma rua
          // (O agente está na fronteira do lote)
          // Move o agente para esta posição
          if (pontosRuas > 0) {
            for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                 i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
              if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                 vizinhancas[i + 5] == RUA) {
                x = vizinhancas[i + 2];
                y = vizinhancas[i + 3];
                l = vizinhancas[i + 4];
                q = vizinhancas[i + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                SET_F(id, 0);
                break;
              }
            }
          } else {
            // Se a vizinhança do agente não tem uma posição vizinha que
            // pertence a uma rua
            // (O agente está no interior do lote)
            // Encontra na lista de pontos de fronteira um ponto
            // que pertença a uma rua
            int indMenorFront = 0;
            for (int i = indexFronteiras[indexQuadras[2 * q] + l];
                 i < indexFronteiras[indexQuadras[2 * q] + l + 1]; i += 3) {
                indMenorFront = i;
                break;
            }
            // Encontra na vizinhança do agente o ponto mais próximo
            // ao ponto de fronteira
            // e que pertença ao mesmo lote atual do agente
            int indMenorViz = 0;
            double distMenorViz = INT_MAX;
            for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                 i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
              if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                  vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
                double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                   fronteiras[indMenorFront + 0],
                                   fronteiras[indMenorFront + 1]);
                if (dist < distMenorViz) {
                  distMenorViz = dist;
                  indMenorViz = i;
                }
              }
            }
            // Move o agente
            x = vizinhancas[indMenorViz + 2];
            y = vizinhancas[indMenorViz + 3];
            l = vizinhancas[indMenorViz + 4];
            q = vizinhancas[indMenorViz + 5];
            SET_X(id, x);
            SET_Y(id, y);
            SET_L(id, l);
            SET_Q(id, q);
          }
        }
      } else {
        // O AGENTE ESTÁ NA RUA
        if (q == RUA) {
          // Conta quantas posições vizinhas pertencem à quadra e lote destino
          int pontosLoteDestino = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 4] == l_destino &&
                vizinhancas[i + 5] == q_destino) {
              pontosLoteDestino++;
            }
          }
          // Se a vizinhança do agente tem uma posição vizinha com o lote
          // destino
          // Move para esta posição
          if (pontosLoteDestino > 0) {
            for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                 i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
              if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                  vizinhancas[i + 4] == l_destino &&
                  vizinhancas[i + 5] == q_destino) {
                x = vizinhancas[i + 2];
                y = vizinhancas[i + 3];
                l = vizinhancas[i + 4];
                q = vizinhancas[i + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                break;
              }
            }
          } else {              
            // Se a vizinhança do agente não tem uma posição vizinha com o
            // lote destino
            // Se contador de movimentação do agente é maior que zero
            if (m > 0) {
              // Encontra na vizinhança do agente o ponto de rua mais próximo
              // ao destino
              // e que pertença a mesma rua do agente
              int indMenorViz = 0;
              double distMenorViz = INT_MAX;
              for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                   i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                   i += 6) {
                if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                    vizinhancas[i + 4] == l && vizinhancas[i + 5] == RUA) {
                  double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                     x_destino, y_destino);
                  if (dist < distMenorViz) {
                    distMenorViz = dist;
                    indMenorViz = i;
                  }
                }
              }
              // Move o agente
              x = vizinhancas[indMenorViz + 2];
              y = vizinhancas[indMenorViz + 3];
              l = vizinhancas[indMenorViz + 4];
              q = vizinhancas[indMenorViz + 5];
              SET_X(id, x);
              SET_Y(id, y);
              SET_L(id, l);
              SET_Q(id, q);
              // Decrementa o contador de movimentação do agente
              SET_M(id, m - 1);
            } else {
              if (GET_F(id) == 0) {
                // Se a flag é igual a false
                // Procura na vizinhança do agente uma posição de rua que
                // diminua sua distância ao destino
                int indMenorViz = -1;
                double distMenorViz = DIST(x, y, x_destino, y_destino);
                for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                     i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                     i += 6) {
                  if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                      vizinhancas[i + 5] == RUA) {
                    double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                       x_destino, y_destino);
                    if (dist < distMenorViz) {
                      distMenorViz = dist;
                      indMenorViz = i;
                    }
                  }
                }
                // Se não houver
                if (indMenorViz == -1) {
                  // seta flag = true
                  SET_F(id, 1);
                  // Encontra na lista de pontos de esquina o ponto com menor
                  // distância ao destino
                  int indMenorEsq = 0;
                  double distMenorEsq = INT_MAX;
                  for (int i = indexEsquinas[l]; i < indexEsquinas[l + 1];
                       i += 3) {
                    double dist = DIST(esquinas[i + 0], esquinas[i + 1],
                                       x_destino, y_destino);
                    if (dist < distMenorEsq) {
                      distMenorEsq = dist;
                      indMenorEsq = i;
                    }
                  }
                  // Encontra na vizinhança do agente o ponto que diminua sua
                  // distância ao ponto de esquina
                  int indMenorViz = -1;
                  double distMenorViz = DIST(x, y, esquinas[indMenorEsq + 0],
                                             esquinas[indMenorEsq + 1]);
                  for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                       i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                       i += 6) {
                    if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                        vizinhancas[i + 5] == RUA) {
                      double dist =
                          DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                               esquinas[indMenorEsq + 0],
                               esquinas[indMenorEsq + 1]);
                      if (dist < distMenorViz) {
                        distMenorViz = dist;
                        indMenorViz = i;
                      }
                    }
                  }
                  if (indMenorViz != -1) {
                    // Move o agente
                    x = vizinhancas[indMenorViz + 2];
                    y = vizinhancas[indMenorViz + 3];
                    l = vizinhancas[indMenorViz + 4];
                    q = vizinhancas[indMenorViz + 5];
                    SET_X(id, x);
                    SET_Y(id, y);
                    SET_L(id, l);
                    SET_Q(id, q);
                  }
                } else {
                  // Encontra na vizinhança do agente o ponto de rua que
                  // diminua sua distância ao destino
                  int indMenorViz = -1;
                  double distMenorViz = DIST(x, y, x_destino, y_destino);
                  for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                       i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                       i += 6) {
                    if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                        vizinhancas[i + 5] == RUA) {
                      double dist =
                          DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                               x_destino, y_destino);
                      if (dist < distMenorViz) {
                        distMenorViz = dist;
                        indMenorViz = i;
                      }
                    }
                  }
                  if (indMenorViz != -1) {
                    // Move o agente
                    x = vizinhancas[indMenorViz + 2];
                    y = vizinhancas[indMenorViz + 3];
                    l = vizinhancas[indMenorViz + 4];
                    q = vizinhancas[indMenorViz + 5];
                    SET_X(id, x);
                    SET_Y(id, y);
                    SET_L(id, l);
                    SET_Q(id, q);
                  }
                }
              } else {
                // Encontra na lista de pontos de esquina o ponto com menor
                // distância ao destino
                int indMenorEsq = 0;
                double distMenorEsq = INT_MAX;
                for (int i = indexEsquinas[l]; i < indexEsquinas[l + 1];
                     i += 3) {
                  double dist = DIST(esquinas[i + 0], esquinas[i + 1],
                                     x_destino, y_destino);
                  if (dist < distMenorEsq) {
                    distMenorEsq = dist;
                    indMenorEsq = i;
                  }
                }
                // Encontra na vizinhança do agente o ponto mais próximo ao
                // ponto de esquina
                int indMenorViz = 0;
                double distMenorViz = INT_MAX;
                for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                     i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                     i += 6) {
                  if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                      vizinhancas[i + 5] == RUA) {
                    double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                       esquinas[indMenorEsq + 0],
                                       esquinas[indMenorEsq + 1]);
                    if (dist < distMenorViz) {
                      distMenorViz = dist;
                      indMenorViz = i;
                    }
                  }
                }
                // Se esta posição pertence a outra rua
                if (vizinhancas[indMenorViz + 4] != l) {
                  // seta flag = false
                  SET_F(id, 0);
                  // seta contador de movimentação = 5
                  SET_M(id, 5);
                }
                // Move o agente
                x = vizinhancas[indMenorViz + 2];
                y = vizinhancas[indMenorViz + 3];
                l = vizinhancas[indMenorViz + 4];
                q = vizinhancas[indMenorViz + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
              }
            }
          }
        } else {
          // O AGENTE ESTÁ NA QUADRA E NO LOTE DE DESTINO
          if (q == q_destino && l == l_destino) {
            if (GET_F(id) == 0) {
              SET_M(id, periodos[indexPeriodos[t] + r + 1]);
              SET_F(id, 1);
            }
            m = GET_M(id);
            if (m > 0) {
              int quantidade = 0;
              for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                   i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                   i += 6) {
                if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                    vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
                  quantidade++;
                }
              }
              int indice = (int)(randomizarPercentual() * quantidade);
              int k = 0;
              for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                   i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                   i += 6) {
                if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                    vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
                  if (k == indice) {
                    x = vizinhancas[i + 2];
                    y = vizinhancas[i + 3];
                    l = vizinhancas[i + 4];
                    q = vizinhancas[i + 5];
                    SET_X(id, x);
                    SET_Y(id, y);
                    SET_L(id, l);
                    SET_Q(id, q);
                    SET_M(id, m - 1);
                    break;
                  }
                  k++;
                }
              }
            } else {
              SET_M(id, 0);
              SET_F(id, 0);
              // Se o agente não está percorrendo a última rota do trajeto
              if (r + 1 != (indexTrajetos[t + 1] - indexTrajetos[t])) {
                SET_R(id, r + 1);
              } else {
                // Se o agente está percorrendo a última rota do trajeto
                SET_R(id, 0);
                SET_F(id, 1);
                
                /*
                // PARAR O AGENTE APÓS UMA VOLTA
                SET_M(id, -1);
                */
                
              }
            }
          }
        }
      }
    }
  }
}

MARCADOR_DEVICE void movimentacaoTrajeto(int id, void *seeds, TIPO_AGENTE *agentes, int quantAgentes,
                  const int *indexQuadras, const int *indexVizinhancas,
                  const int *vizinhancas, const double *parametros,
                  const int *indexFronteiras,
                  const int *fronteiras, const int *indexEsquinas,
                  const int *esquinas, const int *indexCentrosEsquinas,
                  const int *centrosEsquinas, int quantRotas,
                  const int *indexRotas, const int *rotas,
                  const int *indexPosicoes, const int *posicoes,
                  int quantTrajetos, const int *indexTrajetos,
                  const int *trajetos, const int *indexPeriodos,
                  const int *periodos) {
  int q = GET_Q(id);
  int l = GET_L(id);
  int x = GET_X(id);
  int y = GET_Y(id);
  int m = GET_M(id);
  
  /*
  // PARAR O AGENTE APÓS UMA VOLTA
  if (m == -1) {
    continue;
  }
  */
  
  int r = GET_R(id);
  int t = GET_T(id);
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
    // Conta quantas posições de vizinhança o agente possui
    int quantidade = 0;
    for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
         i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
      if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
        quantidade++;
      }
    }
    // Se o agente possuir posições de vizinhanças
    if (quantidade > 0) {
      int l_origem = rotas[indexRotas[trajetos[indexTrajetos[t]] + r] + 0];
      int q_origem = rotas[indexRotas[trajetos[indexTrajetos[t]] + r] + 1];
      int l_destino =
          rotas[indexRotas[trajetos[indexTrajetos[t]] + r + 1] - 2];
      int q_destino =
          rotas[indexRotas[trajetos[indexTrajetos[t]] + r + 1] - 1];
      int x_destino;
      int y_destino;
      for (int i = indexFronteiras[indexQuadras[2 * q_destino] + l_destino];
           i < indexFronteiras[indexQuadras[2 * q_destino] + l_destino + 1]; 
           i += 3) {
         if (fronteiras[i + 2] == l) {
            x_destino = fronteiras[i + 0];
            y_destino = fronteiras[i + 1];
            break;
        }
      }
      int prox_rua = rotas[indexRotas[trajetos[indexTrajetos[t]] + r] + 2];
      
      // O AGENTE ESTÁ NA QUADRA E NO LOTE DE ORIGEM
      if (q == q_origem && l == l_origem) {
        if (GET_F(id) == 1) {
          SET_M(id, periodos[indexPeriodos[t] + r]);
          SET_F(id, 0);
        }
        m = GET_M(id);
        if (m > 0) {
          int quantidade = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
              quantidade++;
            }
          }
          int indice = (int)(randomizarPercentual() * quantidade);
          int k = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
              if (k == indice) {
                x = vizinhancas[i + 2];
                y = vizinhancas[i + 3];
                l = vizinhancas[i + 4];
                q = vizinhancas[i + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                SET_M(id, m - 1);
                break;
              }
              k++;
            }
          }
        } else {
          // Conta quantas posições vizinhas pertencem à próxima rua da rota
          int pontosRuas = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 4] == prox_rua && vizinhancas[i + 5] == RUA) {
              pontosRuas++;
            }
          }
          // Se a vizinhança do agente tem uma posição vizinha que pertence a
          // proxima rua da rota
          // (O agente está na fronteira do lote)
          // Move o agente para esta posição
          if (pontosRuas > 0) {
            for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                 i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
              if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                  vizinhancas[i + 4] == prox_rua && vizinhancas[i + 5] == RUA) {
                x = vizinhancas[i + 2];
                y = vizinhancas[i + 3];
                l = vizinhancas[i + 4];
                q = vizinhancas[i + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                SET_F(id, 0);
                break;
              }
            }
          } else {
            // Se a vizinhança do agente não tem uma posição vizinha que
            // pertence a uma rua
            // (O agente está no interior do lote)
            // Encontra na lista de pontos de fronteira um ponto
            // que pertença a próxima rua da rota
            int indMenorFront = 0;
            for (int i = indexFronteiras[indexQuadras[2 * q] + l];
                 i < indexFronteiras[indexQuadras[2 * q] + l + 1]; i += 3) {
               if (fronteiras[i + 2] == prox_rua) {
                  indMenorFront = i;
                  break;
              }
            }
            // Encontra na vizinhança do agente o ponto mais próximo
            // ao ponto de fronteira
            // e que pertença ao mesmo lote atual do agente
            int indMenorViz = 0;
            double distMenorViz = INT_MAX;
            for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                 i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
              if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                  vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
                double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                   fronteiras[indMenorFront + 0],
                                   fronteiras[indMenorFront + 1]);
                if (dist < distMenorViz) {
                  distMenorViz = dist;
                  indMenorViz = i;
                }
              }
            }
            // Move o agente
            x = vizinhancas[indMenorViz + 2];
            y = vizinhancas[indMenorViz + 3];
            l = vizinhancas[indMenorViz + 4];
            q = vizinhancas[indMenorViz + 5];
            SET_X(id, x);
            SET_Y(id, y);
            SET_L(id, l);
            SET_Q(id, q);
          }
        }
      } else {
        // O AGENTE ESTÁ NA RUA
        if (q == RUA) {
          // Conta quantas posições vizinhas pertencem à quadra e lote destino
          int pontosLoteDestino = 0;
          for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
               i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
            if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                vizinhancas[i + 4] == l_destino &&
                vizinhancas[i + 5] == q_destino) {
              pontosLoteDestino++;
            }
          }
          // Se a vizinhança do agente tem uma posição vizinha com o lote
          // destino
          // Move para esta posição
          if (pontosLoteDestino > 0) {
            for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                 i < indexVizinhancas[indexQuadras[2 * q] + l + 1]; i += 6) {
              if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                  vizinhancas[i + 4] == l_destino &&
                  vizinhancas[i + 5] == q_destino) {
                x = vizinhancas[i + 2];
                y = vizinhancas[i + 3];
                l = vizinhancas[i + 4];
                q = vizinhancas[i + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                break;
              }
            }
          } else {
            // Se o agente está na última rua da rota atual
            if (m + 1 == ((indexRotas[trajetos[indexTrajetos[t]] + r + 1] -
                           indexRotas[trajetos[indexTrajetos[t]] + r]) -
                          4)) {
              // Encontra na vizinhança do agente um ponto que diminua sua
              // distância ao
              // ponto de destino e que pertença ao seu lote atual
              int indMenorViz = -1;
              double distMenorViz = DIST(x, y, x_destino, y_destino);
              for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                   i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                   i += 6) {
                if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                    vizinhancas[i + 4] == l && vizinhancas[i + 5] == RUA) {
                  double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                     x_destino, y_destino);
                  if (dist < distMenorViz) {
                    distMenorViz = dist;
                    indMenorViz = i;
                  }
                }
              }
              if (indMenorViz != -1) {
                // Move o agente
                x = vizinhancas[indMenorViz + 2];
                y = vizinhancas[indMenorViz + 3];
                l = vizinhancas[indMenorViz + 4];
                q = vizinhancas[indMenorViz + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
              } else {
                
                // O agente está na posição de mínimo local
                // Armazena a posição de mínimo local
                int x_min = x;
                int y_min = y;
                // Procura na vizinhança do agente o ponto com menor distância
                // ao ponto destino
                int indMenorViz = 0;
                double distMenorViz = INT_MAX;
                for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                     i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                     i += 6) {
                  if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                      vizinhancas[i + 4] == l && vizinhancas[i + 5] == RUA) {
                    double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                       x_destino, y_destino);
                    if (dist < distMenorViz) {
                      distMenorViz = dist;
                      indMenorViz = i;
                    }
                  }
                }
                // Move o agente
                x = vizinhancas[indMenorViz + 2];
                y = vizinhancas[indMenorViz + 3];
                l = vizinhancas[indMenorViz + 4];
                q = vizinhancas[indMenorViz + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                // Procura na vizinhança do agente o ponto com menor distância
                // ao ponto destino
                // removendo o ponto de mínimo local
                indMenorViz = 0;
                distMenorViz = INT_MAX;
                for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                     i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                     i += 6) {
                  if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                      vizinhancas[i + 2] != x_min &&
                      vizinhancas[i + 3] != y_min &&
                      vizinhancas[i + 4] == l && vizinhancas[i + 5] == RUA) {
                    double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                       x_destino, y_destino);
                    if (dist < distMenorViz) {
                      distMenorViz = dist;
                      indMenorViz = i;
                    }
                  }
                }
                // Move o agente
                x = vizinhancas[indMenorViz + 2];
                y = vizinhancas[indMenorViz + 3];
                l = vizinhancas[indMenorViz + 4];
                q = vizinhancas[indMenorViz + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);                  
              }
            } else {
              // Procura um ponto central de esquina que pertença a próxima
              // rua da rota atual
              int pontoCentral = -1;
              for (int i = indexCentrosEsquinas[l];
                   i < indexCentrosEsquinas[l + 1]; i += 3) {
                if (centrosEsquinas[i + 2] ==
                    rotas[indexRotas[trajetos[indexTrajetos[t]] + r] + 2 + m +
                          1]) {
                  pontoCentral = i;
                  break;
                }
              }              
              // Encontra na vizinhança do agente o ponto mais próximo ao
              // ponto central da esquina que pertença a próxima rua do
              // trajeto
              int indMenorViz = 0;
              double distMenorViz = INT_MAX;
              for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                   i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                   i += 6) {
                if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                    vizinhancas[i + 4] ==
                        rotas[indexRotas[trajetos[indexTrajetos[t]] + r] + 2 +
                              m + 1] &&
                    vizinhancas[i + 5] == RUA) {
                  double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                     centrosEsquinas[pontoCentral + 0],
                                     centrosEsquinas[pontoCentral + 1]);
                  if (dist < distMenorViz) {
                    distMenorViz = dist;
                    indMenorViz = i;
                  }
                }
              }
              // Se a distância entre a posição do agente e a posição próxima
              // ao centro da esquina
              // for menor que 2
              if (distMenorViz < 2) {
                // Move o agente
                x = vizinhancas[indMenorViz + 2];
                y = vizinhancas[indMenorViz + 3];
                l = vizinhancas[indMenorViz + 4];
                q = vizinhancas[indMenorViz + 5];
                SET_X(id, x);
                SET_Y(id, y);
                SET_L(id, l);
                SET_Q(id, q);
                // incrementa o contador de movimentação
                SET_M(id, m + 1);
              } else {
                // Encontra na vizinhança do agente o ponto mais próximo ao
                // ponto central da esquina que pertença a mesma rua do agente
                int indMenorViz = -1;
                double distMenorViz = DIST(x, y, centrosEsquinas[pontoCentral + 0], centrosEsquinas[pontoCentral + 1]);
                for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                     i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                     i += 6) {
                  if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                      vizinhancas[i + 4] == l && vizinhancas[i + 5] == RUA) {
                    double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                       centrosEsquinas[pontoCentral + 0], centrosEsquinas[pontoCentral + 1]);
                    if (dist < distMenorViz) {
                      distMenorViz = dist;
                      indMenorViz = i;
                    }
                  }
                }
                if (indMenorViz != -1) {
                  // Move o agente
                  x = vizinhancas[indMenorViz + 2];
                  y = vizinhancas[indMenorViz + 3];
                  l = vizinhancas[indMenorViz + 4];
                  q = vizinhancas[indMenorViz + 5];
                  SET_X(id, x);
                  SET_Y(id, y);
                  SET_L(id, l);
                  SET_Q(id, q);
                } else {
                  // O agente está na posição de mínimo local
                  // Armazena a posição de mínimo local
                  int x_min = x;
                  int y_min = y;
                  // Procura na vizinhança do agente o ponto com menor distância
                  // ao ponto central da esquina que pertença a mesma rua do agente
                  int indMenorViz = 0;
                  double distMenorViz = INT_MAX;
                  for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                       i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                       i += 6) {
                    if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                        vizinhancas[i + 4] == l && vizinhancas[i + 5] == RUA) {
                      double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                         centrosEsquinas[pontoCentral + 0], centrosEsquinas[pontoCentral + 1]);
                      if (dist < distMenorViz) {
                        distMenorViz = dist;
                        indMenorViz = i;
                      }
                    }
                  }
                  // Move o agente
                  x = vizinhancas[indMenorViz + 2];
                  y = vizinhancas[indMenorViz + 3];
                  l = vizinhancas[indMenorViz + 4];
                  q = vizinhancas[indMenorViz + 5];
                  SET_X(id, x);
                  SET_Y(id, y);
                  SET_L(id, l);
                  SET_Q(id, q);
                  // Conta quantas posições de vizinhança o agente possui
                  int quantidade = 0;
                  for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                       i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                       i += 6) {
                    if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y) {
                      quantidade++;
                    }
                  }
                  // Procura na vizinhança do agente o ponto com menor distância
                  // ao ponto central da esquina que pertença a mesma rua do agente
                  // removendo o ponto de mínimo local
                  indMenorViz = 0;
                  distMenorViz = INT_MAX;
                  for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                       i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                       i += 6) {
                    if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                        vizinhancas[i + 2] != x_min &&
                        vizinhancas[i + 3] != y_min &&
                        vizinhancas[i + 4] == l && vizinhancas[i + 5] == RUA) {
                      double dist = DIST(vizinhancas[i + 2], vizinhancas[i + 3],
                                         centrosEsquinas[pontoCentral + 0], centrosEsquinas[pontoCentral + 1]);
                      if (dist < distMenorViz) {
                        distMenorViz = dist;
                        indMenorViz = i;
                      }
                    }
                  }
                  // Move o agente
                  x = vizinhancas[indMenorViz + 2];
                  y = vizinhancas[indMenorViz + 3];
                  l = vizinhancas[indMenorViz + 4];
                  q = vizinhancas[indMenorViz + 5];
                  SET_X(id, x);
                  SET_Y(id, y);
                  SET_L(id, l);
                  SET_Q(id, q);
                }                  
              }
            }
          }
        } else {
          // O AGENTE ESTÁ NA QUADRA E NO LOTE DE DESTINO
          if (q == q_destino && l == l_destino) {
            if (GET_F(id) == 0) {
              SET_M(id, periodos[indexPeriodos[t] + r + 1]);
              SET_F(id, 1);
            }
            m = GET_M(id);
            if (m > 0) {
              int quantidade = 0;
              for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                   i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                   i += 6) {
                if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                    vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
                  quantidade++;
                }
              }
              int indice = (int)(randomizarPercentual() * quantidade);
              int k = 0;
              for (int i = indexVizinhancas[indexQuadras[2 * q] + l];
                   i < indexVizinhancas[indexQuadras[2 * q] + l + 1];
                   i += 6) {
                if (vizinhancas[i + 0] == x && vizinhancas[i + 1] == y &&
                    vizinhancas[i + 4] == l && vizinhancas[i + 5] == q) {
                  if (k == indice) {
                    x = vizinhancas[i + 2];
                    y = vizinhancas[i + 3];
                    l = vizinhancas[i + 4];
                    q = vizinhancas[i + 5];
                    SET_X(id, x);
                    SET_Y(id, y);
                    SET_L(id, l);
                    SET_Q(id, q);
                    SET_M(id, m - 1);
                    break;
                  }
                  k++;
                }
              }
            } else {
              SET_M(id, 0);
              SET_F(id, 0);
              // Se o agente não está percorrendo a última rota do trajeto
              if (r + 1 != (indexTrajetos[t + 1] - indexTrajetos[t])) {
                SET_R(id, r + 1);
              } else {
                // Se o agente está percorrendo a última rota do trajeto
                SET_R(id, 0);
                SET_F(id, 1);
                
                /*
                // PARAR O AGENTE APÓS UMA VOLTA
                SET_M(id, -1);
                */
                
              }
            }
          }
        }
      }
    }
  }
}

MARCADOR_GLOBAL void movimentacao(void *seeds, TIPO_AGENTE *agentes, int quantAgentes,
                  const int *indexQuadras, const int *indexVizinhancas,
                  const int *vizinhancas, const double *parametros,
                  const int *indexFronteiras,
                  const int *fronteiras, const int *indexEsquinas,
                  const int *esquinas, const int *indexCentrosEsquinas,
                  const int *centrosEsquinas, int quantRotas,
                  const int *indexRotas, const int *rotas,
                  const int *indexPosicoes, const int *posicoes,
                  int quantTrajetos, const int *indexTrajetos,
                  const int *trajetos, const int *indexPeriodos,
                  const int *periodos) {
CABECALHO_MOVIMENTACAO {
    switch (GET_K(id)) {
    case LOCAL:
      movimentacaoLocal(id, seeds, agentes, quantAgentes, indexQuadras, indexVizinhancas,
                  vizinhancas, parametros, indexFronteiras, fronteiras, indexEsquinas,
                  esquinas, indexCentrosEsquinas, centrosEsquinas, quantRotas,
                  indexRotas, rotas, indexPosicoes, posicoes,
                  quantTrajetos, indexTrajetos, trajetos, indexPeriodos, periodos);
      break;
    case ALEATORIO:
      movimentacaoAleatoria(id, seeds, agentes, quantAgentes, indexQuadras, indexVizinhancas,
                  vizinhancas, parametros, indexFronteiras, fronteiras, indexEsquinas,
                  esquinas, indexCentrosEsquinas, centrosEsquinas, quantRotas,
                  indexRotas, rotas, indexPosicoes, posicoes,
                  quantTrajetos, indexTrajetos, trajetos, indexPeriodos, periodos);
      break;
    case LIVRE:
      movimentacaoLivre(id, seeds, agentes, quantAgentes, indexQuadras, indexVizinhancas,
                  vizinhancas, parametros, indexFronteiras, fronteiras, indexEsquinas,
                  esquinas, indexCentrosEsquinas, centrosEsquinas, quantRotas,
                  indexRotas, rotas, indexPosicoes, posicoes,
                  quantTrajetos, indexTrajetos, trajetos, indexPeriodos, periodos);
      break;
    case TRAJETO:
      movimentacaoTrajeto(id, seeds, agentes, quantAgentes, indexQuadras, indexVizinhancas,
                  vizinhancas, parametros, indexFronteiras, fronteiras, indexEsquinas,
                  esquinas, indexCentrosEsquinas, centrosEsquinas, quantRotas,
                  indexRotas, rotas, indexPosicoes, posicoes,
                  quantTrajetos, indexTrajetos, trajetos, indexPeriodos, periodos);
      break;
    }
  }
}

MARCADOR_GLOBAL void contato(void *seeds, TIPO_AGENTE *agentes, int quantAgentes, const int *quantLotes,
             int quantQuadras, const double *parametros,
             const int *indexQuadras,
             const int *indexPosicoes, const int *posicoes) {
CABECALHO_CONTATO {
    int x = posicoes[id * 4 + 0];
    int y = posicoes[id * 4 + 1];
    int l = posicoes[id * 4 + 2];
    int q = posicoes[id * 4 + 3];
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

MARCADOR_GLOBAL void transicao(void *seeds, TIPO_AGENTE *agentes, int quantAgentes, const double *parametros) {
CABECALHO_TRANSICAO {
    int c = GET_C(id);
    switch (GET_E(id)) {
    case EXPOSTO: {
      double periodo;
      switch (GET_I(id)) {
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
        SET_E(id, INFECTADO);
        SET_C(id, 0);
      } else {
        SET_C(id, c + 1);
      }
    } break;
    case INFECTADO: {
      double periodo;
      switch (GET_I(id)) {
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
        SET_E(id, RECUPERADO);
        SET_C(id, 0);
      } else {
        SET_C(id, c + 1);
      }
    } break;
    case RECUPERADO: {
      double periodo;
      switch (GET_I(id)) {
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
        SET_E(id, SUSCETIVEL);
        SET_C(id, 0);
      } else {
        SET_C(id, c + 1);
      }
    } break;
    }
  }
}

void iniciarSimulacao(
    int idSimulacao, const double *parametros, int sizeParametros,
    std::string pastaSaida,
    int *saidaQuantidadeTotal, const int *quantLotes, int quantQuadras,
    const int *indexQuadras, const int *indexVizinhancas,
    const int *vizinhancas, const int *indexPosicoes, const int *posicoes,
    const int *indexFronteiras, const int *fronteiras, const int *indexEsquinas,
    const int *esquinas, const int *indexCentrosEsquinas,
    const int *centrosEsquinas, const int *indexSaidaQuantidadeQuadras,
    int *saidaQuantidadeQuadras, int quantRotas, const int *indexRotas,
    const int *rotas, int quantTrajetos, const int *indexTrajetos,
    const int *trajetos, const int *indexPeriodos, const int *periodos, 
    const int *indexTrajetosFaixaEtaria) {
  int ciclos = NUMERO_CICLOS_SIMULACAO + 1;

  int quantLinhasSaidaEspacial =
      indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4;
  int *saidaEspacial = new int[quantLinhasSaidaEspacial * ciclos]();

  int quantAgentes = Agentes::contarTotalAgentes(quantLotes, quantQuadras,
                                                 parametros);
  TIPO_AGENTE *agentes = Agentes::criarAgentes(
      quantAgentes, parametros, quantLotes, quantQuadras,
      indexQuadras, indexPosicoes, posicoes, indexRotas, rotas, indexTrajetos,
      trajetos, indexTrajetosFaixaEtaria);

  if (idSimulacao == 0) {
    int totMem = (quantAgentes * ATRIBUTOS_AGENTE * sizeof(TIPO_AGENTE));
    totMem += (ciclos * COLUNAS_SAIDAS_QUANTIDADES * sizeof(int));
    totMem += (sizeParametros * sizeof(double));
    totMem +=
        (indexVizinhancas[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int));
    totMem += indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int);
    totMem += indexFronteiras[indexQuadras[quantQuadras * 2 - 1]] * sizeof(int);
    totMem += indexEsquinas[quantLotes[0]] * sizeof(int);
    totMem += indexCentrosEsquinas[quantLotes[0]] * sizeof(int);
    totMem += indexRotas[quantRotas] * sizeof(int);
    totMem += indexTrajetos[quantTrajetos] * sizeof(int);
    totMem += indexPeriodos[quantTrajetos] * sizeof(int);
    std::cout << totMem << std::endl;
  }

#ifdef __GPU__

  TIPO_AGENTE *agentesDev;
  int *saidaQuantidadeTotalDev;
  int *indexSaidaQuantidadeQuadrasDev;
  int *saidaQuantidadeQuadrasDev;
  int *saidaEspacialDev;
  int *quantLotesDev;
  double *parametrosDev;
  int *indexQuadrasDev;
  int *indexVizinhancasDev;
  int *vizinhancasDev;
  int *indexPosicoesDev;
  int *posicoesDev;
  int *indexFronteirasDev;
  int *fronteirasDev;
  int *indexEsquinasDev;
  int *esquinasDev;
  int *indexCentrosEsquinasDev;
  int *centrosEsquinasDev;
  int *indexRotasDev;
  int *rotasDev;
  int *indexTrajetosDev;
  int *trajetosDev;
  int *indexPeriodosDev;
  int *periodosDev;

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
  cudaMalloc((void **)&indexEsquinasDev, (quantLotes[0] + 1) * sizeof(int));
  cudaMalloc((void **)&esquinasDev, indexEsquinas[quantLotes[0]] * sizeof(int));
  cudaMalloc((void **)&indexCentrosEsquinasDev,
             (quantLotes[0] + 1) * sizeof(int));
  cudaMalloc((void **)&centrosEsquinasDev,
             indexCentrosEsquinas[quantLotes[0]] * sizeof(int));
  cudaMalloc((void **)&indexRotasDev, (quantRotas + 1) * sizeof(int));
  cudaMalloc((void **)&rotasDev, indexRotas[quantRotas] * sizeof(int));
  cudaMalloc((void **)&indexTrajetosDev, (quantTrajetos + 1) * sizeof(int));
  cudaMalloc((void **)&trajetosDev, indexTrajetos[quantTrajetos] * sizeof(int));
  cudaMalloc((void **)&indexPeriodosDev, (quantTrajetos + 1) * sizeof(int));
  cudaMalloc((void **)&periodosDev, indexPeriodos[quantTrajetos] * sizeof(int));

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
  cudaMemcpy(indexEsquinasDev, indexEsquinas, (quantLotes[0] + 1) * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(esquinasDev, esquinas, indexEsquinas[quantLotes[0]] * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexCentrosEsquinasDev, indexCentrosEsquinas,
             (quantLotes[0] + 1) * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(centrosEsquinasDev, centrosEsquinas,
             indexCentrosEsquinas[quantLotes[0]] * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexRotasDev, indexRotas, (quantRotas + 1) * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(rotasDev, rotas, indexRotas[quantRotas] * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexTrajetosDev, indexTrajetos, (quantTrajetos + 1) * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(trajetosDev, trajetos, indexTrajetos[quantTrajetos] * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(indexPeriodosDev, indexPeriodos, (quantTrajetos + 1) * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(periodosDev, periodos, indexTrajetos[quantTrajetos] * sizeof(int),
             cudaMemcpyHostToDevice);

  int numThreads = 1024;
  int f1 = (int)((quantAgentes / numThreads) + 1);
  int f2 = (int)((indexPosicoes[indexQuadras[quantQuadras * 2 - 1]] / 4 /
                  numThreads) +
                 1);
  int f = (f1 > f2) ? f1 : f2;
  int maxThreads = f * numThreads;

  std::default_random_engine
  gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dis(0.0, 1.0);

  curandState *seeds;
  cudaMalloc((void **)&seeds, maxThreads * sizeof(curandState));
  int *rands = new int[maxThreads];
  int *randsDev;
  cudaMalloc((void **)&randsDev, maxThreads * sizeof(int));
  for (int i = 0; i < maxThreads; ++i) {
    rands[i] = (int)ENTRE_FAIXA(0, 100000, dis(gen));
  }
  cudaMemcpy(randsDev, rands, maxThreads * sizeof(int), cudaMemcpyHostToDevice);
  initCurand<<<f, numThreads>>>(seeds, randsDev, maxThreads);
  delete[](rands);
  cudaFree(randsDev);

#endif

#ifdef __GPU__

  SaidasSimulacao::gerarSaidaQuantidadeTotal<<<f1, numThreads>>>(
      agentesDev, quantAgentes, saidaQuantidadeTotalDev, 0);

  SaidasSimulacao::gerarSaidaQuantidadeQuadras<<<f1, numThreads>>>(
      agentesDev, quantAgentes, indexSaidaQuantidadeQuadrasDev,
      saidaQuantidadeQuadrasDev, 0);

  SaidasSimulacao::gerarSaidaEspacial<<<f2, numThreads>>>(
      agentesDev, quantAgentes, saidaEspacialDev, 0, quantQuadras, ciclos,
      indexQuadrasDev, indexPosicoesDev, posicoesDev);

  for (int ciclo = 1; ciclo < ciclos; ++ciclo) {
        
    movimentacao<<<f1, numThreads>>>(seeds, 
        agentesDev, quantAgentes, indexQuadrasDev,
        indexVizinhancasDev, vizinhancasDev, parametrosDev,
        indexFronteirasDev, fronteirasDev, indexEsquinasDev, esquinasDev,
        indexCentrosEsquinasDev, centrosEsquinasDev, quantRotas, indexRotasDev,
        rotasDev, indexPosicoesDev, posicoesDev, quantTrajetos,
        indexTrajetosDev, trajetosDev, indexPeriodosDev, periodosDev);

    contato<<<f2, numThreads>>>(seeds, agentesDev, quantAgentes,
                                quantLotesDev, quantQuadras, parametrosDev,
                                indexQuadrasDev,
                                indexPosicoesDev, posicoesDev);

    transicao<<<f1, numThreads>>>(seeds, agentesDev, quantAgentes,
                                  parametrosDev);

    SaidasSimulacao::gerarSaidaQuantidadeTotal<<<f1, numThreads>>>(
        agentesDev, quantAgentes, saidaQuantidadeTotalDev, ciclo);

    SaidasSimulacao::gerarSaidaQuantidadeQuadras<<<f1, numThreads>>>(
        agentesDev, quantAgentes, indexSaidaQuantidadeQuadrasDev,
        saidaQuantidadeQuadrasDev, ciclo);

    SaidasSimulacao::gerarSaidaEspacial<<<f2, numThreads>>>(
        agentesDev, quantAgentes, saidaEspacialDev, ciclo, quantQuadras, ciclos,
        indexQuadrasDev, indexPosicoesDev, posicoesDev);
  }

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
    
    std::cout << ciclo << std::endl;
    
    movimentacao(NULL, agentes, quantAgentes, indexQuadras, indexVizinhancas,
                 vizinhancas, parametros, indexFronteiras,
                 fronteiras, indexEsquinas, esquinas, indexCentrosEsquinas,
                 centrosEsquinas, quantRotas, indexRotas, rotas, indexPosicoes,
                 posicoes, quantTrajetos, indexTrajetos, trajetos,
                 indexPeriodos, periodos);
    contato(NULL, agentes, quantAgentes, quantLotes, quantQuadras, parametros,
            indexQuadras, indexPosicoes, posicoes);
    transicao(NULL, agentes, quantAgentes, parametros);

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

#ifdef __GPU__

  cudaMemcpy(saidaQuantidadeTotal, saidaQuantidadeTotalDev,
             ciclos * COLUNAS_SAIDAS_QUANTIDADES * sizeof(int),
             cudaMemcpyDeviceToHost);
  cudaMemcpy(saidaQuantidadeQuadras, saidaQuantidadeQuadrasDev,
             indexSaidaQuantidadeQuadras[quantQuadras] * sizeof(int),
             cudaMemcpyDeviceToHost);
  cudaMemcpy(saidaEspacial, saidaEspacialDev,
             quantLinhasSaidaEspacial * ciclos * sizeof(int),
             cudaMemcpyDeviceToHost);

  cudaFree(seeds);
  cudaFree(agentesDev);
  cudaFree(saidaQuantidadeTotalDev);
  cudaFree(indexSaidaQuantidadeQuadrasDev);
  cudaFree(saidaQuantidadeQuadrasDev);
  cudaFree(saidaEspacialDev);
  cudaFree(quantLotesDev);
  cudaFree(parametrosDev);
  cudaFree(indexQuadrasDev);
  cudaFree(indexVizinhancasDev);
  cudaFree(vizinhancasDev);
  cudaFree(indexPosicoesDev);
  cudaFree(posicoesDev);
  cudaFree(indexFronteirasDev);
  cudaFree(fronteirasDev);
  cudaFree(indexEsquinasDev);
  cudaFree(esquinasDev);
  cudaFree(indexCentrosEsquinasDev);
  cudaFree(centrosEsquinasDev);
  cudaFree(indexRotasDev);
  cudaFree(rotasDev);
  cudaFree(indexTrajetosDev);
  cudaFree(trajetosDev);
  cudaFree(indexPeriodosDev);
  cudaFree(periodosDev);

#endif

  system((COMANDO_CRIAR_PASTA + pastaSaida).c_str());
  SaidasSimulacao::salvarSaidaEspacial(pastaSaida, saidaEspacial, posicoes,
                                       quantLinhasSaidaEspacial, ciclos);

  delete[](saidaEspacial);
  delete[](agentes);
}
}

#endif
