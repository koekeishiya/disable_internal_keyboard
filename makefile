all:
	rm -rf ./bin
	mkdir -p ./bin
	clang ./src/main.c -o ./bin/main -framework IOKit -framework CoreFoundation
