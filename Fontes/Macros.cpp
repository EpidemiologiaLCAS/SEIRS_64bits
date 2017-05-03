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

#define LOCAL 0
#define ALEATORIO 1
#define LIVRE 2
#define TRAJETO 3

#define COLUNAS_SAIDAS_QUANTIDADES 33
#define VEC(i, j, num_colunas) (((i) * (num_colunas)) + (j))

#define RUA 0

#define DIST(x1, y1, x2, y2)                                                   \
  (double)(sqrt(pow((x1) - (x2), 2.0) + pow((y1) - (y2), 2.0)))

#ifdef __CONV__

#define TIPO_AGENTE int

#define ATRIBUTOS_AGENTE 16

// Gets

#define GET(i, d) (agentes[(i)*ATRIBUTOS_AGENTE + d])

#define GET_Q(i) (int)(GET(i, 0))
#define GET_L(i) (int)(GET(i, 1))
#define GET_R(i) (int)(GET(i, 2))
#define GET_T(i) (int)(GET(i, 3))
#define GET_F(i) (int)(GET(i, 4))
#define GET_A(i) (int)(GET(i, 5))
#define GET_S(i) (int)(GET(i, 6))
#define GET_I(i) (int)(GET(i, 7))
#define GET_E(i) (int)(GET(i, 8))
#define GET_U(i) (int)(GET(i, 9))
#define GET_H(i) (int)(GET(i, 10))
#define GET_C(i) (int)(GET(i, 11))
#define GET_M(i) (int)(GET(i, 12))
#define GET_K(i) (int)(GET(i, 13))
#define GET_X(i) (int)(GET(i, 14))
#define GET_Y(i) (int)(GET(i, 15))

// Sets

#define SET(i, d, novo) (agentes[(i)*ATRIBUTOS_AGENTE + d] = (novo))

#define SET_Q(i, novo) (SET(i, 0, novo))
#define SET_L(i, novo) (SET(i, 1, novo))
#define SET_R(i, novo) (SET(i, 2, novo))
#define SET_T(i, novo) (SET(i, 3, novo))
#define SET_F(i, novo) (SET(i, 4, novo))
#define SET_A(i, novo) (SET(i, 5, novo))
#define SET_S(i, novo) (SET(i, 6, novo))
#define SET_I(i, novo) (SET(i, 7, novo))
#define SET_E(i, novo) (SET(i, 8, novo))
#define SET_U(i, novo) (SET(i, 9, novo))
#define SET_H(i, novo) (SET(i, 10, novo))
#define SET_C(i, novo) (SET(i, 11, novo))
#define SET_M(i, novo) (SET(i, 12, novo))
#define SET_K(i, novo) (SET(i, 13, novo))
#define SET_X(i, novo) (SET(i, 14, novo))
#define SET_Y(i, novo) (SET(i, 15, novo))

#endif

#ifdef __BITS__

#define TIPO_AGENTE unsigned

#define ATRIBUTOS_AGENTE 4

/*
 Q = Quadra                                       (8 bits, 256 valores)
 L = Lote                                         (7 bits, 128 valores)
 R = Rota                                         (3 bits, 8 valores)
 T = Trajeto                                      (12 bits, 4096 valores)
 F = Flag de movimentação                         (1 bit, 2 valores)
 A = Fração Assintomático                         (1 bit, 2 valores)

 S = Sexo                                         (1 bit, 2 valores)
 I = Idade                                        (3 bits, 8 valores)
 E = Estado                                       (3 bits, 8 valores)
 U = Sorotipo Atual                               (3 bits, 8 valores)
 H = Sorotipos contraídos                         (5 bits, Fixo)
 C = Contador de transições de estados (Ciclo)    (8 bits, 256 valores)
 M = Contador de movimentação                     (7 bits, 128 valores)
 K = Tipo de movimentação                         (2 bits, 4 valores)

 X = Latitude                                     (32 bits)
 
 Y = Longitude                                    (32 bits)
*/

// Macros bitstring

// Tamanho em bits dos campos:
#define T_Q 8
#define T_L 7
#define T_R 3
#define T_T 12
#define T_F 1
#define T_A 1

#define T_S 1
#define T_I 3
#define T_E 3
#define T_U 3
#define T_H 5
#define T_C 8
#define T_M 7
#define T_K 2

#define T_X 32

#define T_Y 32

// Número de bits anteriores a cada campo:
#define A_Q 24
#define A_L 17
#define A_R 14
#define A_T 2
#define A_F 1
#define A_A 0

#define A_S 31
#define A_I 28
#define A_E 25
#define A_U 22
#define A_H 17
#define A_C 9
#define A_M 2
#define A_K 0

#define A_X 0

#define A_Y 0

// Máscaras

#define MA_Q (TIPO_AGENTE)4278190080U
#define MA_L (TIPO_AGENTE)16646144U
#define MA_R (TIPO_AGENTE)114688U
#define MA_T (TIPO_AGENTE)16380U
#define MA_F (TIPO_AGENTE)2U
#define MA_A (TIPO_AGENTE)1U

#define MA_S (TIPO_AGENTE)2147483648U
#define MA_I (TIPO_AGENTE)1879048192U
#define MA_E (TIPO_AGENTE)234881024U
#define MA_U (TIPO_AGENTE)29360128U
#define MA_H (TIPO_AGENTE)4063232U
#define MA_C (TIPO_AGENTE)130560U
#define MA_M (TIPO_AGENTE)508U
#define MA_K (TIPO_AGENTE)3U

#define MA_X (TIPO_AGENTE)4294967295U

#define MA_Y (TIPO_AGENTE)4294967295U


#define NM_Q (TIPO_AGENTE)16777215U
#define NM_L (TIPO_AGENTE)4278321151U
#define NM_R (TIPO_AGENTE)4294852607U
#define NM_T (TIPO_AGENTE)4294950915U
#define NM_F (TIPO_AGENTE)4294967293U
#define NM_A (TIPO_AGENTE)4294967294U

#define NM_S (TIPO_AGENTE)2147483647U
#define NM_I (TIPO_AGENTE)2415919103U
#define NM_E (TIPO_AGENTE)4060086271U
#define NM_U (TIPO_AGENTE)4265607167U
#define NM_H (TIPO_AGENTE)4290904063U
#define NM_C (TIPO_AGENTE)4294836735U
#define NM_M (TIPO_AGENTE)4294966787U
#define NM_K (TIPO_AGENTE)4294967292U

#define NM_X (TIPO_AGENTE)0U

#define NM_Y (TIPO_AGENTE)0U

// Gets

#define GET(i, d, ma, a) ((agentes[(i)*ATRIBUTOS_AGENTE + d] & ma) >> a)

#define GET_Q(i) (int)(GET(i, 0, MA_Q, A_Q))
#define GET_L(i) (int)(GET(i, 0, MA_L, A_L))
#define GET_R(i) (int)(GET(i, 0, MA_R, A_R))
#define GET_T(i) (int)(GET(i, 0, MA_T, A_T))
#define GET_F(i) (int)(GET(i, 0, MA_F, A_F))
#define GET_A(i) (int)(GET(i, 0, MA_A, A_A))

#define GET_S(i) (int)(GET(i, 1, MA_S, A_S))
#define GET_I(i) (int)(GET(i, 1, MA_I, A_I))
#define GET_E(i) (int)(GET(i, 1, MA_E, A_E))
#define GET_U(i) (int)(GET(i, 1, MA_U, A_U))
#define GET_H(i) (int)(GET(i, 1, MA_H, A_H))
#define GET_C(i) (int)(GET(i, 1, MA_C, A_C))
#define GET_M(i) (int)(GET(i, 1, MA_M, A_M))
#define GET_K(i) (int)(GET(i, 1, MA_K, A_K))

#define GET_X(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 2])

#define GET_Y(i) (int)(agentes[(i)*ATRIBUTOS_AGENTE + 3])

// Sets

#define SET(i, d, novo, nm, a) (agentes[(i)*ATRIBUTOS_AGENTE + d] = ((agentes[(i)*ATRIBUTOS_AGENTE + d] & nm) | (((TIPO_AGENTE)(novo)) << a)))

#define SET_Q(i, novo) (SET(i, 0, novo, NM_Q, A_Q))
#define SET_L(i, novo) (SET(i, 0, novo, NM_L, A_L))
#define SET_R(i, novo) (SET(i, 0, novo, NM_R, A_R))
#define SET_T(i, novo) (SET(i, 0, novo, NM_T, A_T))
#define SET_F(i, novo) (SET(i, 0, novo, NM_F, A_F))
#define SET_A(i, novo) (SET(i, 0, novo, NM_A, A_A))

#define SET_S(i, novo) (SET(i, 1, novo, NM_S, A_S))
#define SET_I(i, novo) (SET(i, 1, novo, NM_I, A_I))
#define SET_E(i, novo) (SET(i, 1, novo, NM_E, A_E))
#define SET_U(i, novo) (SET(i, 1, novo, NM_U, A_U))
#define SET_H(i, novo) (SET(i, 1, novo, NM_H, A_H))
#define SET_C(i, novo) (SET(i, 1, novo, NM_C, A_C))
#define SET_M(i, novo) (SET(i, 1, novo, NM_M, A_M))
#define SET_K(i, novo) (SET(i, 1, novo, NM_K, A_K))

#define SET_X(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 2] = ((TIPO_AGENTE)(novo)))
  
#define SET_Y(i, novo) (agentes[(i)*ATRIBUTOS_AGENTE + 3] = ((TIPO_AGENTE)(novo)))

#endif

#endif
