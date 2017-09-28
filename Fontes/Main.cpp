#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <tuple>

#if defined(__GPU__)

#include <curand.h>
#include <curand_kernel.h>

#endif

#if defined(__CPU__)

#include <omp.h>

#endif

using namespace std;

#include "Macros.cpp"
#include "MonteCarlo.cpp"

int main(int argc, char **argv) {

#if defined(__CPU__)

  if (argc == 2) {
    omp_set_num_threads(atoi(argv[1]));
  } else {
    omp_set_num_threads(omp_get_max_threads());
  }

#endif

#if defined(__GPU__)

  if (argc == 2) {
    cudaSetDevice(atoi(argv[1]));
  } else {
    cudaSetDevice(0);
  }

#endif

  string pastaEntrada, pastaSaida;
  system((COMANDO_EXCLUIR_PASTA + string("Saidas")).c_str());
  for (int idMonteCarlo = 0; idMonteCarlo < 1; idMonteCarlo++) {
    pastaSaida = string("Saidas") + SEPARADOR + string("MonteCarlo_") +
                 to_string(idMonteCarlo) + SEPARADOR;
    pastaEntrada = string("Entradas") + SEPARADOR + string("MonteCarlo_") +
                   to_string(idMonteCarlo) + SEPARADOR;
    system((COMANDO_CRIAR_PASTA + pastaSaida).c_str());
    MonteCarlo::iniciarSimulacao(idMonteCarlo, pastaEntrada, pastaSaida);
  }
  return 0;
}
