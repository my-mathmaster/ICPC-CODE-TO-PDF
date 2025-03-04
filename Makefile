SRCS=$(shell find src/) $(shell find tex/)

main.pdf: $(SRCS) Makefile scl.yaml
	mkdir -p build/
	python3 format.py > scl.yaml	
	python3 gen2.py > build/code.tex
	cp tex/* build/
	- cd build && xelatex -interaction=nonstopmode main.tex
	- cd build && xelatex -interaction=nonstopmode main.tex
	mv build/main.pdf ./

.PHONY: clean check
check:
	true # code valid check

clean:
	rm -rf build/
	rm main.pdf
