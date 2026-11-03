#include "SoftwareRenderer.h"

#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>

struct SoftwareRenderer::Impl {
  SDL_Renderer* renderer{nullptr};
  SDL_Texture* bufferTexture{nullptr};

  ~Impl() {
    if (bufferTexture != nullptr) {
      SDL_DestroyTexture(bufferTexture);
    }

    if (renderer != nullptr) {
      SDL_DestroyRenderer(renderer);
    }
  }
};

SoftwareRenderer::SoftwareRenderer(Colour32 clearColour)
    : m_pImpl{std::make_unique<Impl>()}
    , m_clearColour{clearColour} {}

SoftwareRenderer::~SoftwareRenderer() = default;

bool SoftwareRenderer::Initialise(SDL_Window* pWindow) {
  m_pImpl->renderer = SDL_CreateRenderer(pWindow, -1, 0);

  if (m_pImpl->renderer == nullptr) {
    return false;
  }

  // Get renderer size

  int renderW = 0, renderH = 0;
  if (SDL_GetRendererOutputSize(m_pImpl->renderer, &renderW, &renderH) != 0) {
    return false;
  }

  // Resize buffer

  m_buffer.SetClearColour(m_clearColour);
  m_buffer.Resize(renderW, renderH);

  // Create the colour buffer texture

  m_pImpl->bufferTexture = SDL_CreateTexture(m_pImpl->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, renderW, renderH);

  if (m_pImpl->bufferTexture == nullptr) {
    return false;
  }

  return true;
}

void SoftwareRenderer::Render() {
  SDL_SetRenderDrawColor(m_pImpl->renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_pImpl->renderer);

  SDL_UpdateTexture(m_pImpl->bufferTexture, nullptr, m_buffer.Data(), m_buffer.Pitch());
  SDL_RenderCopy(m_pImpl->renderer, m_pImpl->bufferTexture, nullptr, nullptr);
  ClearBuffer();

  SDL_RenderPresent(m_pImpl->renderer);
}

void SoftwareRenderer::ClearBuffer() {
  m_buffer.Clear();
}
