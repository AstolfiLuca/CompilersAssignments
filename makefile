help:
	@echo "Specifica un target esplicito per eseguire operazioni sul progetto:"
	@echo "  make configure_env  - Configura l'ambiente"
	@echo "  make clang          - Compila un file cpp in llvm"
	@echo "  make cmake          - Genera la libreria ed esegue il make per un assignment"
	@echo "  make optimize       - Esegui l'ottimizzazione con opt, specificando i passi"
	@echo "    - Esempio: make optimize assignment=assignment1 test=file p=ai,sr"
	@echo "  make clean_builds   - Rimuove i file generati"

configure_env:
	export PATH=/usr/lib/llvm-19/bin:$$PATH
	export LD_LIBRARY_PATH=/usr/lib/llvm-19/lib:$$LD_LIBRARY_PATH
	export LLVM_DIR=/usr/lib/llvm-19

clang:
	clang -O$(flag) -emit-llvm -S $(assignment)/test/cpp/$(test).cpp -o $(assignment)/test/ll/$(test).ll

cmake:
	cd $(assignment)/ && \
	mkdir -p build && \
	cd build && \
	cmake -DLT_LLVM_INSTALL_DIR=$$LLVM_DIR ../ && \
	make && \
	cd ../test && \
	mkdir -p ll_optimized
	
optimize:
	cd $(assignment)/test && \
	opt -load-pass-plugin ../build/libLocalOpt.so -p $(p) ll/$(test).ll -o bc/$(test).optimized.bc && \
	llvm-dis bc/$(test).optimized.bc -o ll_optimized/$(test).optimized.ll

clean_builds:
	find . -type d -name "build" -exec rm -rf {} +


.PHONY: help configure_env cmake optimize clang clean_builds
