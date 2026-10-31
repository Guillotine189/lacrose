#include <string>

class MainApp{

private:

    bool m_running;
    bool m_initialized;

    int m_screen_height;
    int m_screen_width;

    std::string m_main_window_title;

    SDL_Window* m_main_window;
    SDL_Renderer* m_renderer;

    Uint64 m_fps;
    Uint64 m_target_frame_time;

public:

    MainApp(){
        
        m_initialized = false;
        m_running = true;

        m_main_window = nullptr;
        m_renderer = nullptr;
        m_screen_height = 640;
        m_screen_width = 720;
        m_main_window_title = "lacrose";

        m_fps = 200;
        m_target_frame_time = int(1000/m_fps);

        if ( !this->init() ){
            Log("Error", "Initializing SDL library", "Exiting");
            return;
        }

        if ( !this->createWindowAndRenderer() ){
            Log("Error", "Creating window", "Exiting");
            return;
        }   

        m_initialized = true;
    }



    ~MainApp(){

        if (m_renderer != nullptr){
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }

        if (m_main_window != nullptr){
            SDL_DestroyWindow(m_main_window);
            m_main_window = nullptr;
        }

        if (m_initialized){
            SDL_Quit();
        }
    }

    inline bool isInitialized() const {
        return m_initialized;
    }

    bool init() const {
        if ( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) )
        {
            return false;
        }
        return true;
    }

    bool createWindowAndRenderer(){
        if ( !SDL_CreateWindowAndRenderer(m_main_window_title.c_str(), m_screen_width, m_screen_height, 
                            SDL_WINDOW_RESIZABLE, &m_main_window, &m_renderer) )
        {
            return false;
        }

        return true;
    }

    void updateMainWindowTitle(const std::string& new_title){
        m_main_window_title = new_title;
        SDL_SetWindowTitle(m_main_window, m_main_window_title.c_str());
    }

    void changeFps(int fps){
        SDL_Log("Changing fps to: %d", fps);
        m_fps = fps;
        m_target_frame_time = int(1000/m_fps);
    }

    void mainLoop();
    void handleEvent();
    void render();

    void handleKeyDownEvent(SDL_Event&);

};


void MainApp :: handleKeyDownEvent(SDL_Event& event)
{

    std::string key_name;

    switch (event.key.mod){

        case SDL_KMOD_LCTRL:
            if (event.key.key != SDLK_LCTRL) {
                key_name += "LCTRL+";
            }
            break;

        case SDL_KMOD_RCTRL:
            if (event.key.key != SDLK_RCTRL) {
                key_name += "RCTRL+";
            }
            break;
    }

    key_name += SDL_GetKeyName(event.key.key);
    SDL_Log("A Key was pressed: %s", key_name.c_str());
    this->updateMainWindowTitle(key_name);
    this->changeFps(event.key.key);
}



void MainApp :: handleEvent(){
    SDL_Event event;

    // while ( SDL_WaitEvent(&event) ){
    while ( SDL_PollEvent(&event) ){

        switch (event.type){
            
            case SDL_EVENT_QUIT:
                m_running = false;
                break;

            case SDL_EVENT_KEY_DOWN:
                handleKeyDownEvent(event);
                break;
        }  // which event
    } // while loop
}

void MainApp :: render(){
    SDL_RenderPresent(m_renderer);
}


void MainApp :: mainLoop(){
    Uint64 startTick;
    Uint64 frame_time;
    Uint64 currentTick;
    Uint64 lastTickFps = SDL_GetTicks();
    
    int fps = 0;

    while (this->m_running) {

        startTick = SDL_GetTicks();

        handleEvent();
        render();

        currentTick = SDL_GetTicks();
        frame_time = currentTick - startTick;

        fps++;

        if ( currentTick - lastTickFps >= 1000){
            SDL_Log("FPS: %d", fps);
            lastTickFps = currentTick;
            fps = 0;
        }


        if (frame_time <= m_target_frame_time){
            // SDL_Log("Frame time: %d, Delaying for %d", frame_time, m_target_frame_time - frame_time);
            SDL_Delay(m_target_frame_time - frame_time);
        }

    } 


}

