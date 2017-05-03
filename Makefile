GPU_CC=nvcc
CPU_CC=g++

GPU_FLAGS=-std=c++11 -D_MWAITXINTRIN_H_INCLUDED -x cu
CPU_FLAGS=-std=c++11 -fopenmp -Wall

FILE=Fontes/Main.cpp

EXE=SEIRS

GPU_CONV:
	$(GPU_CC) $(GPU_FLAGS) -D__GPU__ -D__CONV__ $(FILE) -o $(EXE)
	
GPU_BITS:
	$(GPU_CC) $(GPU_FLAGS) -D__GPU__ -D__BITS__ $(FILE) -o $(EXE)

CPU_CONV:
	$(CPU_CC) $(CPU_FLAGS) -D__CPU__ -D__CONV__ $(FILE) -o $(EXE)

CPU_BITS:
	$(CPU_CC) $(CPU_FLAGS) -D__CPU__ -D__BITS__ $(FILE) -o $(EXE)

clear:
	rm $(EXE)
