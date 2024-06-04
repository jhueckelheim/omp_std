prog: main.cpp
	clang++ $^ -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda --offload-arch=sm_80 -o $@

run: prog
	OMP_TARGET_OFFLOAD=MANDATORY ./prog

clean:
	rm *.cobaltlog *.error *.output prog

# run notes:
# qsub -I -n 1 -q gpu_a100 -t 10
# module load llvm/master-nightly cuda/12.3.0 
