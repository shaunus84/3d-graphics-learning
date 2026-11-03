#pragma once

#include <memory>

#include "ColourBuffer.hpp"

struct SDL_Window;

class SoftwareRenderer {
 public:
  SoftwareRenderer(Colour32 clearColour);
  ~SoftwareRenderer();

  SoftwareRenderer(const SoftwareRenderer&) = delete;
  SoftwareRenderer& operator=(const SoftwareRenderer&) = delete;

  bool Initialise(SDL_Window* pWindow);
  void Render();

 private:
  void ClearBuffer();

 private:
  struct Impl;
  std::unique_ptr<Impl> m_pImpl{nullptr};
  Colour32 m_clearColour;
  ColourBuffer m_buffer;
};
