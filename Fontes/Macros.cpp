#ifndef MACROS_H
#define MACROS_H

#ifdef __linux__
#define COMANDO_CRIAR_PASTA string("mkdir -p ")
#define COMANDO_EXCLUIR_PASTA string("rm -rf ")
#define SEPARADOR string("/")
#else
#define COMANDO_CRIAR_PASTA string("md ")
#define COMANDO_EXCLUIR_PASTA string("rd /s /q ")
#define SEPARADOR string("\\")
#endif

#define SUSCETIVEL 0
#define EXPOSTO 1
#define INFECTADO 2
#define RECUPERADO 3

#define FEMININO 0
#define MASCULINO 1

#define CRIANCA 3
#define JOVEM 2
#define ADULTO 1
#define IDOSO 0

#define COLUNAS_SAIDAS_QUANTIDADES 34
#define VEC(i, j, num_colunas) (((i) * (num_colunas)) + (j))

#ifdef __CONVENCIONAL__

#define TIPO_AGENTE int

#define ATRIBUTOS_AGENTE 8

// Gets
#define GET_Q(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 0])
#define GET_S(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 1])
#define GET_I(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 2])
#define GET_L(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 3])
#define GET_X(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 4])
#define GET_Y(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 5])
#define GET_C(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 6])
#define GET_E(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 7])

// Sets
#define SET_Q(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 0] = (novo))
#define SET_S(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 1] = (novo))
#define SET_I(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 2] = (novo))
#define SET_L(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 3] = (novo))
#define SET_X(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 4] = (novo))
#define SET_Y(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 5] = (novo))
#define SET_C(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 6] = (novo))
#define SET_E(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 7] = (novo))

#endif

#ifdef __BITSTRING__

#define UINT8 uint8_t
#define UINT32 uint32_t

struct Agente {
  UINT8 t1;
  UINT32 t2, t3;
};

#define TIPO_AGENTE Agente

#define ATRIBUTOS_AGENTE 1

// Macros bitstring

// Tamanho em bits dos campos:
#define T_Q 7  // MAX = 128 valores             Q: 9 bits
#define T_S 1  // MAX = 2 valores               S: 1 bit
#define T_I 2  // MAX = 4 valores              FE: 3 bits 
#define T_L 11 // MAX = 2048 valores            L: 13 bits
#define T_X 19 // MAX = 524288 valores          X: 19 bits
#define T_Y 24 // MAX = 16777216 valores        Y: 23 bits
#define T_C 6  // MAX = 64 valores              C: 8 bits
#define T_E 2  // MAX = 4 valores              SD: 3 bits 

// Número de bits anteriores a cada campo:
#define A_Q 1
#define A_S 0
#define A_I 30
#define A_L 19
#define A_X 0
#define A_Y 8
#define A_C 2
#define A_E 0

// Máscaras

#define MA_Q (UINT8)254U
#define MA_S (UINT8)1U
#define MA_I (UINT32)3221225472U
#define MA_L (UINT32)1073217536U
#define MA_X (UINT32)524287U
#define MA_Y (UINT32)4294967040U
#define MA_C (UINT32)252U
#define MA_E (UINT32)3U

#define NM_Q (UINT8)4294967041U
#define NM_S (UINT8)4294967294U
#define NM_I (UINT32)1073741823U
#define NM_L (UINT32)3221749759U
#define NM_X (UINT32)4294443008U
#define NM_Y (UINT32)255U
#define NM_C (UINT32)4294967043U
#define NM_E (UINT32)4294967292U

// Gets
#define GET_Q(i) (int)((agentes[i].t1 & MA_Q) >> A_Q)
#define GET_S(i) (int)((agentes[i].t1 & MA_S) >> A_S)
#define GET_I(i) (int)((agentes[i].t2 & MA_I) >> A_I)
#define GET_L(i) (int)((agentes[i].t2 & MA_L) >> A_L)
#define GET_X(i) (int)((agentes[i].t2 & MA_X) >> A_X)
#define GET_Y(i) (int)((agentes[i].t3 & MA_Y) >> A_Y)
#define GET_C(i) (int)((agentes[i].t3 & MA_C) >> A_C)
#define GET_E(i) (int)((agentes[i].t3 & MA_E) >> A_E)

// Sets
#define SET_Q(i, novo)                                                         \
  (agentes[i].t1 = ((agentes[i].t1 & NM_Q) | (((UINT8)novo) << A_Q)))
#define SET_S(i, novo)                                                         \
  (agentes[i].t1 = ((agentes[i].t1 & NM_S) | (((UINT8)novo) << A_S)))
#define SET_I(i, novo)                                                         \
  (agentes[i].t2 = ((agentes[i].t2 & NM_I) | (((UINT32)novo) << A_I)))
#define SET_L(i, novo)                                                         \
  (agentes[i].t2 = ((agentes[i].t2 & NM_L) | (((UINT32)novo) << A_L)))
#define SET_X(i, novo)                                                         \
  (agentes[i].t2 = ((agentes[i].t2 & NM_X) | (((UINT32)novo) << A_X)))
#define SET_Y(i, novo)                                                         \
  (agentes[i].t3 = ((agentes[i].t3 & NM_Y) | (((UINT32)novo) << A_Y)))
#define SET_C(i, novo)                                                         \
  (agentes[i].t3 = ((agentes[i].t3 & NM_C) | (((UINT32)novo) << A_C)))
#define SET_E(i, novo)                                                         \
  (agentes[i].t3 = ((agentes[i].t3 & NM_E) | (((UINT32)novo) << A_E)))

#endif

#endif
