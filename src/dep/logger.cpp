#include <SDL3/SDL.h>

void Log(const char* type, const char* detail, const char* action){
	SDL_Log("[%s]: [%s] [%s]", type, detail, action);
}
