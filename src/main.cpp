#include <SDL3/SDL.h>
#include "./dep/logger.cpp"



class SDLApp{

public:
    SDL_Window* g_main_window;
    SDL_Renderer* g_renderer;
    bool running;
    int m_screen_height;
    int m_screen_width;

    SDLApp(){
        
        this->g_main_window = nullptr;
        this->g_renderer = nullptr;
        this->running = true;
        m_screen_height = 640;
        m_screen_width = 720;

        if ( !this->init() ){
            Log("Error", "Initializing SDL library", "Exiting");
            return;
        }

        if ( !this->createWindowAndRenderer() ){
            Log("Error", "Creating window", "Exiting");
            this->~SDLApp();
            return;
        }

        return;
    }



    ~SDLApp(){
        SDL_Quit();
    }



    bool init(){
        if ( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) )
        {
            return false;
        }
        return true;
    }

    bool createWindowAndRenderer(){
        if ( !SDL_CreateWindowAndRenderer("Test window", this->m_screen_width, this->m_screen_height, 
                            SDL_WINDOW_RESIZABLE, &this->g_main_window, &this->g_renderer) )
        {
            return false;
        }

        return true;
    }

    void mainLoop();


};


void SDLApp :: mainLoop(){



    bool running = true;

    while (running) {

        SDL_Event event;

        while ( SDL_PollEvent(&event) ){

            switch (event.type){
                
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    SDL_Log("A Key was pressed: %d", event.key.key);
                    break;
            }


        } // END OF poll event

    // here starts the actual logic for loop
    SDL_RenderPresent(g_renderer);

    } // END OF main loop


}



int main(){

    SDLApp app;

    app.mainLoop();

    return 0;
}