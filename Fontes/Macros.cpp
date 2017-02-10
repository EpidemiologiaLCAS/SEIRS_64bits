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

#define COLUNAS_SAIDAS_QUANTIDADES 6
#define VEC(i, j, num_colunas) (((i) * (num_colunas)) + (j))

#ifdef __CONVENCIONAL__

#define TIPO_AGENTE int

#define ATRIBUTOS_AGENTE 6

// Gets
#define GET_Q(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 0])
#define GET_L(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 1])
#define GET_X(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 2])
#define GET_Y(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 3])
#define GET_C(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 4])
#define GET_E(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 5])

// Sets
#define SET_Q(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 0] = (novo))
#define SET_L(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 1] = (novo))
#define SET_X(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 2] = (novo))
#define SET_Y(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 3] = (novo))
#define SET_C(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 4] = (novo))
#define SET_E(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 5] = (novo))

#endif

#ifdef __BITSTRING__

#define TIPO_AGENTE uint64_t

#define ATRIBUTOS_AGENTE 1

// Macros bitstring

// Tamanho em bits dos campos:
#define T_Q 8  // MAX = 256 valores
#define T_L 5  // MAX = 32 valores
#define T_X 19 // MAX = 524288 valores
#define T_Y 24 // MAX = 16777216 valores
#define T_C 6  // MAX = 64 valores
#define T_E 2  // MAX = 4 valores

// Número de bits anteriores a cada campo:
#define A_Q 56
#define A_L 51
#define A_X 32
#define A_Y 8
#define A_C 2
#define A_E 0

// Máscaras

#define MA_Q (TIPO_AGENTE)18374686479671623680U
#define MA_L (TIPO_AGENTE)69805794224242688U
#define MA_X (TIPO_AGENTE)2251795518717952U
#define MA_Y (TIPO_AGENTE)4294967040U
#define MA_C (TIPO_AGENTE)252U
#define MA_E (TIPO_AGENTE)3U

#define NM_Q (TIPO_AGENTE)72057594037927935U
#define NM_L (TIPO_AGENTE)18376938279485308927U
#define NM_X (TIPO_AGENTE)18444492278190833663U
#define NM_Y (TIPO_AGENTE)18446744069414584575U
#define NM_C (TIPO_AGENTE)18446744073709551363U
#define NM_E (TIPO_AGENTE)18446744073709551612U

// Gets
#define GET_Q(i) (int)((agentes[i] & MA_Q) >> A_Q)
#define GET_L(i) (int)((agentes[i] & MA_L) >> A_L)
#define GET_X(i) (int)((agentes[i] & MA_X) >> A_X)
#define GET_Y(i) (int)((agentes[i] & MA_Y) >> A_Y)
#define GET_C(i) (int)((agentes[i] & MA_C) >> A_C)
#define GET_E(i) (int)((agentes[i] & MA_E) >> A_E)

// Sets
#define SET_Q(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_Q) | (((TIPO_AGENTE)novo) << A_Q)))
#define SET_L(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_L) | (((TIPO_AGENTE)novo) << A_L)))
#define SET_X(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_X) | (((TIPO_AGENTE)novo) << A_X)))
#define SET_Y(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_Y) | (((TIPO_AGENTE)novo) << A_Y)))
#define SET_C(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_C) | (((TIPO_AGENTE)novo) << A_C)))
#define SET_E(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_E) | (((TIPO_AGENTE)novo) << A_E)))

#endif

#endif
