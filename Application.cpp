#include "Application.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "KeyboardController.h"
#include "Renderable.h"
#include "BallController.h"
//#define PARALLELEXEC - TODO check how to execute some functions in a separate thread

#ifdef PARALLELEXEC
#include <thread>
#endif // PARALLELEXEC

SDL_Renderer* App::glb_renderer = nullptr;
SDL_Event App::glb_event;

SDL_Rect App::glb_camera = {0, 0, 800, 640};

bool App::glb_isRunning = false;


GameObjectMgr mgr;

auto& player(mgr.addGObj());
auto& player2(mgr.addGObj());
auto& ball(mgr.addGObj());

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

    player.addComponent<TransformComponent>(50.0f, 100.0f, 100, 20, 4);
    player.addComponent<RendererComponent>()
                .addRenderable<RenderableRec>();
    player.addComponent<KeyboardController>(SDLK_w, SDLK_s);
    player.addGroup(groupPlayers);


    player2.addComponent<TransformComponent>(950.0f, 100.0f, 100, 20, 4);
    player2.addComponent<RendererComponent>();
    player2.getComponent<RendererComponent>()
            .addRenderable<RenderableRec>();
    player2.addComponent<KeyboardController>(SDLK_UP, SDLK_DOWN);
    player2.addGroup(groupPlayers);

    for(int i = 0;i<9;i++)
    {
        auto& netObj(mgr.addGObj());
        netObj.addComponent<TransformComponent>(static_cast<float>((SCREEN_WIDTH/2 - NET_WIDTH/2)),static_cast<float>(i * (NET_HEIGHT + NET_SPACE)),
                                                NET_HEIGHT,
                                                NET_WIDTH,
                                                1);
        netObj.addComponent<RendererComponent>()
                    .addRenderable<RenderableRec>();
        netObj.addGroup(groupNet);
    }

    ball.addComponent<TransformComponent>(static_cast<float>((SCREEN_WIDTH/2)),
                                          static_cast<float>(SCREEN_HEIGHT/2),
                                          RADIUS);
    ball.addComponent<RendererComponent>();
    ball.getComponent<RendererComponent>()
        .addRenderable<RenderableCircle>();
    ball.addComponent<BallController>(&player, &player2); // FIX
    ball.addGroup(groupBall);

}

auto& players(mgr.getGroup(App::groupPlayers));
auto& net(mgr.getGroup(App::groupNet));
auto& balls(mgr.getGroup(App::groupBall));

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
    mgr.update();
}

void App::render()
{
    SDL_RenderClear(glb_renderer);

    // Rendering here
    for (auto& p : players)
	{
		p->render();
	}

	for(auto& n : net)
    {
        n->render();
    }

    for(auto& b : balls)
    {
        b->render();
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
