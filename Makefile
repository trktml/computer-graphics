MAKEFLAGS += --silent


default: cmake clear make copy_to_main_dir clear


cmake:
	cmake -B./build
clear:
	clear
make:
	cd build && make
copy_to_main_dir:
	rm -rf ./engine && cp ./build/engine ./engine


clean:
	rm -rf build outputs