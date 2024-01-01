#pragma once

#include "GameObject.h"

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>


// Another solution is to inherit Renderable class and move
// everything to RendererComponent logic, but for now
// I will just separate text and geometry, later
// if needed can be moved to RendererComponent

class TextElement : public Component
{
public:
    TextElement(int xP, int yP, std::string text,
                std::string font, int fSize, SDL_Color& color);
    ~TextElement();

    void setText(std::string text);
    void render() override;

private:
    SDL_Rect m_position;
    std::string m_text;
    std::string m_font;
    SDL_Color m_color;
    SDL_Texture* m_texture;
    TTF_Font* m_ttfFont;
    int m_fsize;
};
// Simple dull solution, but works :)
class ScoreTracker : public Component
{
public:
    void updateScore(int score)
    {
        this->m_gObjPtr->getComponent<TextElement>().setText(std::to_string(score));
    }
    //TextElement* m_te;
};
