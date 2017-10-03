 #!/bin/sh

echo "GPU_CONV" && echo
make GPU_CONV && /usr/bin/time -f "%e" ./SEIRS "Saidas_GPU_CONV"
echo

echo "GPU_BIT" && echo
make GPU_BIT && /usr/bin/time -f "%e" ./SEIRS "Saidas_GPU_BIT"
echo

echo "CPU_CONV" && echo
make CPU_CONV && /usr/bin/time -f "%e" ./SEIRS "Saidas_CPU_CONV"
echo

echo "CPU_BIT" && echo
make CPU_BIT && /usr/bin/time -f "%e" ./SEIRS "Saidas_CPU_BIT"
echo
