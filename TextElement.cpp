#include "TextElement.h"
#include "Application.h"

TextElement::TextElement(int xP, int yP, std::string text,
                         std::string font, int fSize, SDL_Color& color)
    : m_text(text), m_font(font), m_color(color), m_fsize(fSize)
{
    m_position.x = xP;
    m_position.y = yP;

    // Load font here
    m_ttfFont = TTF_OpenFont(font.c_str(), fSize);
    setText(text);
}

TextElement::~TextElement(){}

void TextElement::setText(std::string text)
{
    SDL_Surface* surface = TTF_RenderText_Blended(m_ttfFont, text.c_str(), m_color);
    m_texture = SDL_CreateTextureFromSurface(App::glb_renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_position.w, &m_position.h);
}

// void setFont - later add this func

void TextElement::render()
{
    SDL_RenderCopy(App::glb_renderer, m_texture, nullptr, &m_position);
}