#include <chrono>   // std::chrono::system_clock
#include <climits>  // INT_MAX
#include <fstream>  // std::ifstream, std::ofstream
#include <iostream> // std::cout, std::cerr
#include <random> // std::default_random_engine, std::uniform_real_distribution
#include <tuple> // std::tuple, std::make_tuple, std::tie

#ifdef __GPU__

#include <curand.h>
#include <curand_kernel.h>

#endif

#ifdef __CPU__

#include <omp.h> // omp_set_num_threads, omp_get_max_threads, #pragma omp

#endif

#include "Macros.cpp"
#include "MonteCarlo.cpp"

int main(int argc, char **argv) {

#ifdef __CPU__

  if (argc == 2) {
    omp_set_num_threads(atoi(argv[1]));
  } else {
    omp_set_num_threads(omp_get_max_threads());
  }
  
#endif

#ifdef __GPU__

  if (argc == 2) {
    cudaSetDevice(atoi(argv[1]));
  }
  
#endif

  std::string pastaEntrada, pastaSaida;
  system((COMANDO_EXCLUIR_PASTA + std::string("Saidas")).c_str());
  for (int idMonteCarlo = 0; idMonteCarlo < 1; idMonteCarlo++) {
    pastaSaida = std::string("Saidas") + SEPARADOR +
                 std::string("MonteCarlo_") + std::to_string(idMonteCarlo) +
                 SEPARADOR;
    pastaEntrada = std::string("Entradas") + SEPARADOR +
                   std::string("MonteCarlo_") + std::to_string(idMonteCarlo) +
                   SEPARADOR;
    system((COMANDO_CRIAR_PASTA + pastaSaida).c_str());
    MonteCarlo::iniciarSimulacao(idMonteCarlo, pastaEntrada, pastaSaida);
  }
  return 0;
}
