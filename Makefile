MAKEFLAGS += --silent


default: cmake clear make clear run


cmake:
	cmake -B./build
clear:
	clear
make:
	cd build && make
run:
	./build/engine


clean:
	rm -rf build outputs