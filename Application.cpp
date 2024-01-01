#include "Application.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "KeyboardController.h"
#include "Renderable.h"
#include "TextElement.h"
#include "BallController.h"
#include <random>
//#define PARALLELEXEC - TODO check how to execute some functions in a separate thread

#ifdef PARALLELEXEC
#include <thread>
#endif // PARALLELEXEC

// DEBUG
#include <iostream>

SDL_Renderer* App::glb_renderer = nullptr;
SDL_Event App::glb_event;

SDL_Rect App::glb_camera = {0, 0, 800, 640};

bool App::glb_isRunning = false;


GameObjectMgr mgr;

auto& player(mgr.addGObj());
auto& player2(mgr.addGObj());
auto& rTracker(mgr.addGObj());
auto& lTracker(mgr.addGObj());
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
    m_RSCORE = m_LSCORE = 0;

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

    if(TTF_Init() == -1)
    {
        std::cout << "ERROR: TTF NOT INITALIZED" << std::endl; // Change to some debugging technique
    }

    player.addComponent<TransformComponent>(L_INIT_POS, 100.0f, 100, 20, 4);
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

    SDL_Color white = {255, 255, 255, 255};

    lTracker.addComponent<TextElement>(250, 50, "0", "pixfont.ttf", 125, white);
    lTracker.addComponent<ScoreTracker>();
    lTracker.addGroup(groupUI);

    rTracker.addComponent<TextElement>(700, 50, "0", "pixfont.ttf", 125, white);
    rTracker.addComponent<ScoreTracker>();
    rTracker.addGroup(groupUI);
}

auto& players(mgr.getGroup(App::groupPlayers));
auto& net(mgr.getGroup(App::groupNet));
auto& balls(mgr.getGroup(App::groupBall));
auto& UI(mgr.getGroup(App::groupUI));
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


    if(ball.getComponent<TransformComponent>().m_position.x < 0)
    {
        m_RSCORE++;
        rTracker.getComponent<ScoreTracker>()
                .updateScore(m_RSCORE);
        std::cout << m_RSCORE << std::endl;
        // logic for winning
        // else reset:
        reset();
    }else if(ball.getComponent<TransformComponent>().m_position.x > SCREEN_WIDTH)
    {
        m_LSCORE++;
        lTracker.getComponent<ScoreTracker>()
                .updateScore(m_LSCORE);
        std::cout << m_LSCORE << std::endl;
        reset();
    }
}

static std::random_device rd;

static std::mt19937 gen(rd());
int generateRandomValue() {


    std::uniform_int_distribution<int> distribution(0, 1);

    return (distribution(gen) == 0) ? -1 : 1;
}
// SPECIFICALLY FOR Y COORDINATE TEMP SOL
int generateRandomValueY() {


    std::uniform_int_distribution<int> distribution(-1, 1);

    return (distribution(gen));
}


void App::reset()
{
    // inital central position set
    ball.getComponent<TransformComponent>().m_position.x = static_cast<float>(SCREEN_WIDTH/2);
    ball.getComponent<TransformComponent>().m_position.y = static_cast<float>(SCREEN_HEIGHT/2);

    // Random direction toss
    ball.getComponent<TransformComponent>().m_velocity.x =    ball.getComponent<TransformComponent>().m_velocity.x * generateRandomValue();
    ball.getComponent<TransformComponent>().m_velocity.y =    ball.getComponent<TransformComponent>().m_velocity.y * generateRandomValueY();
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

    for(auto& ui: UI)
    {
        ui->render();
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
