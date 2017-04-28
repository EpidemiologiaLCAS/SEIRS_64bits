#ifndef __MACROS__
#define __MACROS__

#ifdef __linux__

#define COMANDO_CRIAR_PASTA std::string("mkdir -p ")
#define COMANDO_EXCLUIR_PASTA std::string("rm -rf ")
#define SEPARADOR std::string("/")

#else

#define COMANDO_CRIAR_PASTA std::string("md ")
#define COMANDO_EXCLUIR_PASTA std::string("rd /s /q ")
#define SEPARADOR std::string("\\")

#endif

#define SUSCETIVEL 0
#define EXPOSTO 1
#define INFECTADO 2
#define RECUPERADO 3

#define FEMININO 0
#define MASCULINO 1

#define QUANT_IDADES 4

#define CRIANCA 3
#define JOVEM 2
#define ADULTO 1
#define IDOSO 0

#define COLUNAS_SAIDAS_QUANTIDADES 33
#define VEC(i, j, num_colunas) (((i) * (num_colunas)) + (j))

#define RUA 0

#define DIST(x1, y1, x2, y2)                                                   \
  (double)(sqrt(pow((x1) - (x2), 2.0) + pow((y1) - (y2), 2.0)))

#ifdef __CONVENCIONAL__

#define TIPO_AGENTE int

#define ATRIBUTOS_AGENTE 15

// Gets
#define GET_Q(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 0])
#define GET_L(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 1])
#define GET_R(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 2])
#define GET_T(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 3])
#define GET_F(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 4])
#define GET_A(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 5])
#define GET_S(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 6])
#define GET_I(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 7])
#define GET_E(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 8])
#define GET_U(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 9])
#define GET_H(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 10])
#define GET_C(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 11])
#define GET_M(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 12])
#define GET_X(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 13])
#define GET_Y(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 14])

// Sets
#define SET_Q(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 0] = (novo))
#define SET_L(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 1] = (novo))
#define SET_R(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 2] = (novo))
#define SET_T(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 3] = (novo))
#define SET_F(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 4] = (novo))
#define SET_A(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 5] = (novo))
#define SET_S(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 6] = (novo))
#define SET_I(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 7] = (novo))
#define SET_E(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 8] = (novo))
#define SET_U(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 9] = (novo))
#define SET_H(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 10] = (novo))
#define SET_C(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 11] = (novo))
#define SET_M(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 12] = (novo))
#define SET_X(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 13] = (novo))
#define SET_Y(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 14] = (novo))

#endif

#ifdef __BITSTRING__

#define TIPO_AGENTE unsigned

#define ATRIBUTOS_AGENTE 4

/*
 Q = Quadra                                       (10 bits, 1024 valores)
 L = Lote                                         (8 bits, 256 valores)
 R = Rota                                         (3 bits, 8 valores)
 T = Trajeto                                      (9 bits, 512 valores)
 F = Flag de movimentação                         (1 bit, 2 valores)
 A = Fração Assintomático                         (1 bit, 2 valores)

 S = Sexo                                         (1 bit, 2 valores)
 I = Idade                                        (3 bits, 8 valores)
 E = Estado                                       (3 bits, 8 valores)
 U = Sorotipo Atual                               (3 bits, 8 valores)
 H = Sorotipos contraídos                         (5 bits, Fixo)
 C = Contador de transições de estados (Ciclo)    (9 bits, 512 valores)
 M = Contador de movimentação                     (8 bits, 256 valores)

 X = Latitude                                     (32 bits)
 
 Y = Longitude                                    (32 bits)
*/

// Macros bitstring

// Tamanho em bits dos campos:
#define T_Q 10
#define T_L 8
#define T_R 3
#define T_T 9
#define T_F 1
#define T_A 1

#define T_S 1
#define T_I 3
#define T_E 3
#define T_U 3
#define T_H 5
#define T_C 9
#define T_M 8

#define T_X 32

#define T_Y 32

// Número de bits anteriores a cada campo:
#define A_Q 22
#define A_L 14
#define A_R 11
#define A_T 2
#define A_F 1
#define A_A 0

#define A_S 31
#define A_I 28
#define A_E 25
#define A_U 22
#define A_H 17
#define A_C 8
#define A_M 0

#define A_X 0

#define A_Y 0

// Máscaras

#define MA_Q (TIPO_AGENTE)4290772992U
#define MA_L (TIPO_AGENTE)4177920U
#define MA_R (TIPO_AGENTE)14336U
#define MA_T (TIPO_AGENTE)2044U
#define MA_F (TIPO_AGENTE)2U
#define MA_A (TIPO_AGENTE)1U

#define MA_S (TIPO_AGENTE)2147483648U
#define MA_I (TIPO_AGENTE)1879048192U
#define MA_E (TIPO_AGENTE)234881024U
#define MA_U (TIPO_AGENTE)29360128U
#define MA_H (TIPO_AGENTE)4063232U
#define MA_C (TIPO_AGENTE)130816U
#define MA_M (TIPO_AGENTE)255U

#define MA_X (TIPO_AGENTE)4294967295U

#define MA_Y (TIPO_AGENTE)4294967295U


#define NM_Q (TIPO_AGENTE)4194303U
#define NM_L (TIPO_AGENTE)4290789375U
#define NM_R (TIPO_AGENTE)4294952959U
#define NM_T (TIPO_AGENTE)4294965251U
#define NM_F (TIPO_AGENTE)4294967293U
#define NM_A (TIPO_AGENTE)4294967294U

#define NM_S (TIPO_AGENTE)2147483647U
#define NM_I (TIPO_AGENTE)2415919103U
#define NM_E (TIPO_AGENTE)4060086271U
#define NM_U (TIPO_AGENTE)4265607167U
#define NM_H (TIPO_AGENTE)4290904063U
#define NM_C (TIPO_AGENTE)4294836479U
#define NM_M (TIPO_AGENTE)4294967040U

#define NM_X (TIPO_AGENTE)0U

#define NM_Y (TIPO_AGENTE)0U

// Gets
#define GET_Q(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 0] & MA_Q) >> A_Q)
#define GET_L(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 0] & MA_L) >> A_L)
#define GET_R(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 0] & MA_R) >> A_R)
#define GET_T(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 0] & MA_T) >> A_T)
#define GET_F(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 0] & MA_F) >> A_F)
#define GET_A(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 0] & MA_A) >> A_A)

#define GET_S(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 1] & MA_S) >> A_S)
#define GET_I(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 1] & MA_I) >> A_I)
#define GET_E(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 1] & MA_E) >> A_E)
#define GET_U(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 1] & MA_U) >> A_U)
#define GET_H(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 1] & MA_H) >> A_H)
#define GET_C(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 1] & MA_C) >> A_C)
#define GET_M(i) (int)((agentes[(i)*ATRIBUTOS_AGENTE + 1] & MA_M) >> A_M)

#define GET_X(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 2])

#define GET_Y(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 3])

// Sets
#define SET_Q(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 0] = ((agentes[(i)*ATRIBUTOS_AGENTE + 0] & NM_Q) | (((TIPO_AGENTE)(novo)) << A_Q)))
#define SET_L(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 0] = ((agentes[(i)*ATRIBUTOS_AGENTE + 0] & NM_L) | (((TIPO_AGENTE)(novo)) << A_L)))
#define SET_R(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 0] = ((agentes[(i)*ATRIBUTOS_AGENTE + 0] & NM_R) | (((TIPO_AGENTE)(novo)) << A_R)))
#define SET_T(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 0] = ((agentes[(i)*ATRIBUTOS_AGENTE + 0] & NM_T) | (((TIPO_AGENTE)(novo)) << A_T)))
#define SET_F(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 0] = ((agentes[(i)*ATRIBUTOS_AGENTE + 0] & NM_F) | (((TIPO_AGENTE)(novo)) << A_F)))
#define SET_A(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 0] = ((agentes[(i)*ATRIBUTOS_AGENTE + 0] & NM_A) | (((TIPO_AGENTE)(novo)) << A_A)))

#define SET_S(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 1] = ((agentes[(i)*ATRIBUTOS_AGENTE + 1] & NM_S) | (((TIPO_AGENTE)(novo)) << A_S)))
#define SET_I(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 1] = ((agentes[(i)*ATRIBUTOS_AGENTE + 1] & NM_I) | (((TIPO_AGENTE)(novo)) << A_I)))
#define SET_E(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 1] = ((agentes[(i)*ATRIBUTOS_AGENTE + 1] & NM_E) | (((TIPO_AGENTE)(novo)) << A_E)))
#define SET_U(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 1] = ((agentes[(i)*ATRIBUTOS_AGENTE + 1] & NM_U) | (((TIPO_AGENTE)(novo)) << A_U)))
#define SET_H(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 1] = ((agentes[(i)*ATRIBUTOS_AGENTE + 1] & NM_H) | (((TIPO_AGENTE)(novo)) << A_H)))
#define SET_C(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 1] = ((agentes[(i)*ATRIBUTOS_AGENTE + 1] & NM_C) | (((TIPO_AGENTE)(novo)) << A_C)))
#define SET_M(i, novo)                                                         \
  (agentes[(i)*ATRIBUTOS_AGENTE + 1] = ((agentes[(i)*ATRIBUTOS_AGENTE + 1] & NM_M) | (((TIPO_AGENTE)(novo)) << A_M)))

#define SET_X(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 2] = ((TIPO_AGENTE)(novo)))
  
#define SET_Y(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 3] = ((TIPO_AGENTE)(novo)))

#endif

#endif
