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

#define RUA 0

#define Q_ORIGEM 3
#define L_ORIGEM 3
#define X_ORIGEM 251466
#define Y_ORIGEM 7237700

#define Q_DESTINO 13
#define L_DESTINO 8
#define X_DESTINO 251266
#define Y_DESTINO 7237116

#define ABS(x) (x < 0 ? (-1 * x) : x)
#define DIST(x1, y1, x2, y2) (double)(sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0)))

#ifdef __CONVENCIONAL__

#define TIPO_AGENTE int

#define ATRIBUTOS_AGENTE 10

// Gets
#define GET_Q(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 0])
#define GET_S(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 1])
#define GET_I(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 2])
#define GET_L(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 3])
#define GET_X(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 4])
#define GET_Y(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 5])
#define GET_C(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 6])
#define GET_E(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 7])
#define GET_M(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 8])
#define GET_F(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 9])

// Sets
#define SET_Q(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 0] = (novo))
#define SET_S(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 1] = (novo))
#define SET_I(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 2] = (novo))
#define SET_L(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 3] = (novo))
#define SET_X(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 4] = (novo))
#define SET_Y(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 5] = (novo))
#define SET_C(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 6] = (novo))
#define SET_E(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 7] = (novo))
#define SET_M(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 8] = (novo))
#define SET_F(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 9] = (novo))

#endif

#ifdef __BITSTRING__

#define TIPO_AGENTE uint64_t

#define ATRIBUTOS_AGENTE 1

// Macros bitstring

// Tamanho em bits dos campos:
#define T_Q 5  // MAX = 32 valores
#define T_S 1  // MAX = 2 valores
#define T_I 2  // MAX = 4 valores
#define T_L 5  // MAX = 32 valores
#define T_X 19 // MAX = 524288 valores
#define T_Y 24 // MAX = 16777216 valores
#define T_C 6  // MAX = 64 valores
#define T_E 2  // MAX = 4 valores

// Número de bits anteriores a cada campo:
#define A_Q 59
#define A_S 58
#define A_I 56
#define A_L 51
#define A_X 32
#define A_Y 8
#define A_C 2
#define A_E 0

// Máscaras

#define MA_Q (TIPO_AGENTE)17870283321406128128U
#define MA_S (TIPO_AGENTE)288230376151711744U
#define MA_I (TIPO_AGENTE)216172782113783808U
#define MA_L (TIPO_AGENTE)69805794224242688U
#define MA_X (TIPO_AGENTE)2251795518717952U
#define MA_Y (TIPO_AGENTE)4294967040U
#define MA_C (TIPO_AGENTE)252U
#define MA_E (TIPO_AGENTE)3U

#define NM_Q (TIPO_AGENTE)576460752303423487U
#define NM_S (TIPO_AGENTE)18158513697557839871U
#define NM_I (TIPO_AGENTE)18230571291595767807U
#define NM_L (TIPO_AGENTE)18376938279485308927U
#define NM_X (TIPO_AGENTE)18444492278190833663U
#define NM_Y (TIPO_AGENTE)18446744069414584575U
#define NM_C (TIPO_AGENTE)18446744073709551363U
#define NM_E (TIPO_AGENTE)18446744073709551612U

// Gets
#define GET_Q(i) (int)((agentes[i] & MA_Q) >> A_Q)
#define GET_S(i) (int)((agentes[i] & MA_S) >> A_S)
#define GET_I(i) (int)((agentes[i] & MA_I) >> A_I)
#define GET_L(i) (int)((agentes[i] & MA_L) >> A_L)
#define GET_X(i) (int)((agentes[i] & MA_X) >> A_X)
#define GET_Y(i) (int)((agentes[i] & MA_Y) >> A_Y)
#define GET_C(i) (int)((agentes[i] & MA_C) >> A_C)
#define GET_E(i) (int)((agentes[i] & MA_E) >> A_E)

// Sets
#define SET_Q(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_Q) | (((TIPO_AGENTE)novo) << A_Q)))
#define SET_S(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_S) | (((TIPO_AGENTE)novo) << A_S)))
#define SET_I(i, novo)                                                         \
  (agentes[i] = ((agentes[i] & NM_I) | (((TIPO_AGENTE)novo) << A_I)))
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
