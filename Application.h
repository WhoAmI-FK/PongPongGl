
#pragma once

#include <SDL.h>


class App
{
public:
    App();
    virtual ~App();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool isAppRunning();
    void reset();

	static SDL_Renderer * glb_renderer;
	static SDL_Event      glb_event;
    static bool           glb_isRunning;
    static SDL_Rect       glb_camera;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupNet,
        groupColliders,
        groupBall,
        groupUI,
        groupProjectiles
    };
private:
    // int cnt;
    SDL_Window* m_window;

    // SCORE LOGIC
    int m_LSCORE;
    int m_RSCORE;

};
