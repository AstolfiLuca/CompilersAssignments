help:
	@echo "Specifica un target esplicito per eseguire operazioni sul progetto:"
	@echo "  make configure_env    - Configura l'ambiente"
	@echo "  make runtest          - Esegui un test dato l'assignment e l'opt"
	@echo "  make clean_builds     - Rimuove i file generati"

configure_env:
	export PATH=/usr/lib/llvm-19/bin:$$PATH
	export LD_LIBRARY_PATH=/usr/lib/llvm-19/lib:$$LD_LIBRARY_PATH
	export LLVM_DIR=/usr/lib/llvm-19

runtest:
	cd $(assignment)/$(opt) && \
	mkdir -p build && \
	cd build && \
	cmake -DLT_LLVM_INSTALL_DIR=$$LLVM_DIR ../ && \
	make && \
	cd ../test && \
	mkdir -p optimized && \
	opt -load-pass-plugin ../build/libLocalOpt.so -p local-opt $(test).ll -o optimized/$(test).optimized.bc && \
	llvm-dis optimized/$(test).optimized.bc -o optimized/$(test).optimized.ll

clean_builds:
	find . -type d -name "build" -exec rm -rf {} +

# Inutilizzata normalmente
compile_clang:
	clang -O$(flag) -emit-llvm -S $(assignment)/$(opt)/test/$(test).cpp -o $(assignment)/$(opt)/test/$(test).ll

.PHONY: help configure_env runtest clean_builds compile_clang
