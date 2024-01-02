
#pragma once

#include <SDL.h>
#include <stack>
#include <memory>

class State {
public:
    virtual void update(){};
    virtual void render(){};
    virtual ~State(){};
};

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

	static SDL_Renderer *                     glb_renderer;
	static SDL_Event                          glb_event;
    static bool                               glb_isRunning;
    static SDL_Rect                           glb_camera;
    static std::stack<std::unique_ptr<State>> glb_states;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupNet,
        groupColliders,
        groupBall,
        groupUI,
        groupMenuUI,
        groupMenuController,
        groupProjectiles
    };
    int m_LSCORE;
    int m_RSCORE;
private:
    // int cnt;
    SDL_Window* m_window;

    // SCORE LOGIC


};

class MainGameState : public State
{
public:
    MainGameState(App* app);
    App* m_appPtr;
    void update() override;
    void render() override;
};

class MenuGameState : public State
{
public:
    MenuGameState(App* app);
    App* m_appPtr;
    void update() override;
    void render() override;
};
