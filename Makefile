default: cmake clear make clear run

cmake:
	cmake -B./build
clear:
	clear
make:
	cd build && make
run:
	./build/engine