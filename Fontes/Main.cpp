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

#if defined(__GPU__)

void escolherMelhorGPU() {
  int deviceCount = 0;
  cudaGetDeviceCount(&deviceCount);
  int device = 0;
  double clock = 0.0, highestClock = 0.0;
  cudaDeviceProp deviceProp;
  for (int dev = 0; dev < deviceCount; ++dev) {
    cudaGetDeviceProperties(&deviceProp, dev);
    clock = deviceProp.clockRate * 1e-3f;
    if (clock > highestClock) {
      highestClock = clock;
      device = dev;
    }
  }
  cudaSetDevice(device);
  cudaGetDeviceProperties(&deviceProp, device);
  cout << "Usando device " << device << " - " << deviceProp.name << endl;  
}

#endif

int main(int argc, char **argv) {

#if defined(__CPU__)

  if (argc == 3) {
    omp_set_num_threads(atoi(argv[2]));
  } else {
    omp_set_num_threads(omp_get_max_threads());
  }

#endif

#if defined(__GPU__)

  if (argc == 3) {
    cudaSetDevice(atoi(argv[2]));
  } else {
    cudaSetDevice(0);
  }
  
  escolherMelhorGPU();

#endif

  string pastaRaiz;
  if (argc > 1) {
    pastaRaiz = string(argv[1]);
  } else {
    cout << "Informe a pasta de saida!" << endl;
  }

  string pastaEntrada, pastaSaida;
  system((COMANDO_EXCLUIR_PASTA + pastaRaiz).c_str());
  for (int idMonteCarlo = 0; idMonteCarlo < 1; idMonteCarlo++) {
    cout << idMonteCarlo << endl;
    pastaSaida = pastaRaiz + SEPARADOR + string("MonteCarlo_") +
                 to_string(idMonteCarlo) + SEPARADOR;
    pastaEntrada = string("Entradas") + SEPARADOR + string("MonteCarlo_") +
                   to_string(idMonteCarlo) + SEPARADOR;
    system((COMANDO_CRIAR_PASTA + pastaSaida).c_str());
    MonteCarlo::iniciarSimulacao(idMonteCarlo, pastaEntrada, pastaSaida,
                                 pastaRaiz);
  }
  return 0;
}
