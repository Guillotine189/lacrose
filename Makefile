
.PHONY: reinstall_sdl fresh rebuild

reinstall_sdl:
	@echo "Removing old SDL build if it exists"
	@rm -rf ./src/dep/sdl/SDL

	@echo "Downloading SDL3"
	@git clone https://github.com/libsdl-org/SDL.git ./src/dep/sdl/SDL

	@echo "Generating Makefile for SDL3"
	@cmake -S ./src/dep/sdl/SDL -B ./src/dep/sdl/SDL/build

	@echo "Building SDL3"
	@cmake --build ./src/dep/sdl/SDL/build --parallel 4
	@echo "SDL3 reinstalled"


rebuild:
	@echo "Building and linking program"
	@g++ ./src/main.cpp -o lacrose \
		-L./src/dep/sdl/SDL/build \
		-lSDL3

	@echo "Build finished"


fresh: reinstall_sdl
	@$(MAKE) rebuild