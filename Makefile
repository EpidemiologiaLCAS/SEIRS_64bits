GPU_CC=nvcc
CPU_CC=g++
MOV=-D__TRAJETO__
GPU_FLAGS=-std=c++11 -D_MWAITXINTRIN_H_INCLUDED -x cu
CPU_FLAGS=-std=c++11 -fopenmp -Wall
FILE=Fontes/Main.cpp
EXE=SEIRS

GPU_CONV:
	$(GPU_CC) $(GPU_FLAGS) -D__GPU__ -D__CONVENCIONAL__ $(MOV) $(FILE) -o $(EXE)
	
GPU_BIT:
	$(GPU_CC) $(GPU_FLAGS) -D__GPU__ -D__BITSTRING__    $(MOV) $(FILE) -o $(EXE)

CPU_CONV:
	$(CPU_CC) $(CPU_FLAGS) -D__CPU__ -D__CONVENCIONAL__ $(MOV) $(FILE) -o $(EXE)

CPU_BIT:
	$(CPU_CC) $(CPU_FLAGS) -D__CPU__ -D__BITSTRING__    $(MOV) $(FILE) -o $(EXE)

clear:
	rm $(EXE)
