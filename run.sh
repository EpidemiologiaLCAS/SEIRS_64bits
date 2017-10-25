 #!/bin/sh

#echo "TITAN"
#echo "GPU_CONV_TITAN" && echo
#make GPU_CONV && /usr/bin/time -f "%e" ./SEIRS "Saidas_GPU_CONV_TITAN" 0
#echo

echo "GPU_BIT_TITAN" && echo
make GPU_BIT && /usr/bin/time -f "%e" ./SEIRS "Saidas_GPU_BIT_TITAN" 0
echo

#echo "K20"
#echo "GPU_CONV_K20" && echo
#make GPU_CONV && /usr/bin/time -f "%e" ./SEIRS "Saidas_GPU_CONV_K20" 1
#echo

#echo "GPU_BIT_K20" && echo
#make GPU_BIT && /usr/bin/time -f "%e" ./SEIRS "Saidas_GPU_BIT_K20" 1
#echo

#echo "CPU"
#echo "CPU_CONV" && echo
#make CPU_CONV && /usr/bin/time -f "%e" ./SEIRS "Saidas_CPU_CONV"
#echo

#echo "CPU_BIT" && echo
#make CPU_BIT && /usr/bin/time -f "%e" ./SEIRS "Saidas_CPU_BIT"
#echo
