#include <SDL3/SDL.h>
#include "./dep/logger.cpp"
#include "./dep/mainApp.cpp"

int main(int argc, char* argv[]){

    MainApp app;

    if (!app.isInitialized()){
        return -1;
    }

    // TODO: check for file name in argv when running the program

    app.mainLoop();

    return 0;
}
