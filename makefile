help:
	@echo "Specifica un target esplicito per eseguire operazioni sul progetto:"
	@echo "  make configure_env  - Configura l'ambiente"
	@echo "  make clang          - Compila un file cpp in llvm"
	@echo "  make cmake          - Genera la libreria ed esegue il make per un assignment"
	@echo "  make optimize       - Esegui l'ottimizzazione con opt, specificando i passi"
	@echo "    - Esempio: make optimize assignment=1 test=file p=ai,sr,mi"
	@echo "  make clean_builds   - Rimuove i file generati"

configure_env:
	export PATH=/usr/lib/llvm-19/bin:$$PATH
	export LD_LIBRARY_PATH=/usr/lib/llvm-19/lib:$$LD_LIBRARY_PATH
	export LLVM_DIR=/usr/lib/llvm-19

clang:
	cd assignment$(assignment)/test && \
	clang -O$(flag) -emit-llvm -Xclang -disable-O0-optnone -S cpp/$(test).cpp -o bc/$(test)_mem.bc && \
	opt -p mem2reg bc/$(test)_mem.bc -o bc/$(test).bc && \
	llvm-dis bc/$(test).bc -o ll/$(test).ll && \
	rm bc/$(test)_mem.bc

cmake:
	cd assignment$(assignment)/ && \
	mkdir -p build && \
	cd build && \
	cmake -DLT_LLVM_INSTALL_DIR=$$LLVM_DIR ../ && \
	make && \
	cd ../test && \
	mkdir -p ll_optimized

# Create the test (.ll) from the .cpp (passing through the bytecode .bc), given a specific flag. 
# Note: it removes the load/store instructions
clang:
	cd assignment$(assignment)/test && \
	clang -O$(flag) -emit-llvm -Xclang -disable-O0-optnone -S cpp/$(test).cpp -o bc/$(test)_mem.bc && \
	opt -passes=mem2reg bc/$(test)_mem.bc -o bc/$(test).bc && \
	llvm-dis bc/$(test).bc -o ll/$(test).ll && \
	rm bc/$(test)_mem.bc

# Create the test (.ll) optimization (.optimized.ll) 
optimize:
	cd assignment$(assignment)/test && \
	opt -load-pass-plugin ../build/libLocalOpt.so -p $(p),dce ll/$(test).ll -o bc/$(test).optimized.bc && \
	llvm-dis bc/$(test).optimized.bc -o ll_optimized/$(test).optimized.ll

clean_builds:
	find . -type d -name "build" -exec rm -rf {} +


.PHONY: help configure_env cmake optimize clang clean_builds
