prog: main.cpp
	clang++ $^ -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda --offload-arch=sm_80 -o $@

run: prog
	OMP_TARGET_OFFLOAD=MANDATORY ./prog

clean:
	rm prog

veryclean:
	rm *.cobaltlog *.error *.output .*.swp .*.swo
