#include "Application.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RendererComponent.h"

SDL_Renderer* App::glb_renderer = nullptr;
SDL_Event App::glb_event;

SDL_Rect App::glb_camera = {0, 0, 800, 640};

bool App::glb_isRunning = false;


GameObjectMgr mgr;

auto& player(mgr.addGObj());

App::App()
{
}

App::~App()
{
}

void App::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        glb_renderer = SDL_CreateRenderer(m_window, -1, 0);
        if(glb_renderer){
            SDL_SetRenderDrawColor(glb_renderer, 0, 0, 0, 255);
        }
        glb_isRunning = true;
    }

    player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);
    player.addComponent<RendererComponent>();
    player.addGroup(groupPlayers);
}

auto& players(mgr.getGroup(App::groupPlayers));

void App::handleEvents()
{
    SDL_PollEvent(&glb_event);

	switch (glb_event.type)
	{
	case SDL_QUIT :
		glb_isRunning = false;
		break;
	default:
		break;
	}
}

void App::update()
{

}

void App::render()
{
    SDL_RenderClear(glb_renderer);

    // Rendering here
    for (auto& p : players)
	{
		p->render();
	}

    SDL_RenderPresent(glb_renderer);
}

void App::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(glb_renderer);
    SDL_Quit();
}

bool App::isAppRunning(){
    return glb_isRunning;
}
