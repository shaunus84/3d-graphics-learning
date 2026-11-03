#include "Application.h"

// ==============================================
// PIMPL Idiom
// Don't expose SDL in public application header
// ==============================================
#include <SDL2/SDL.h>

namespace {

InitResult FAIL(const char* message) {
  return {false, std::string{message} + ": " + SDL_GetError()};
}

InitResult SUCCESS(const char* message) {
  return {true, std::string{message}};
}

}  // namespace

struct Application::Impl {
  SDL_Window* window{nullptr};
  bool running{false};
  bool sdl_initialised{false};

  ~Impl() {
    if (window != nullptr) {
      SDL_DestroyWindow(window);
    }

    if (sdl_initialised) {
      SDL_Quit();
    }
  }
};

// ===============================================

Application::Application(std::string_view windowTitle)
    : m_pImpl{std::make_unique<Impl>()}
    , m_windowTitle{windowTitle} {}

// ===============================================

Application::~Application() = default;

// ==============================================

InitResult Application::Initialise() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    return FAIL("Could not initialise SDL");
  }

  m_pImpl->sdl_initialised = true;

  // Determine monitor and display size

  if (SDL_GetNumVideoDisplays() < 1) {
    return FAIL("No suitable displays found");
  }

  SDL_Rect displayRect{};
  if (SDL_GetDisplayUsableBounds(0, &displayRect) != 0) {
    return FAIL("Failed to get display bounds");
  }

  // Create window

  m_pImpl->window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED_DISPLAY(0), SDL_WINDOWPOS_CENTERED_DISPLAY(0), displayRect.w, displayRect.h, 0);

  if (m_pImpl->window == nullptr) {
    return FAIL("Could not create window");
  }

  // Create renderer
  m_pSoftwareRenderer = std::make_unique<SoftwareRenderer>(0xFF000000);
  if (!m_pSoftwareRenderer->Initialise(m_pImpl->window)) {
    return FAIL("Failed to create SoftwareRenderer");
  }

  m_pImpl->running = true;
  return SUCCESS("Initialised Application");
}

// ==============================================

void Application::ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        m_pImpl->running = false;
        break;
    }
  }
}

// ==============================================

void Application::Update() {}

// ==============================================

void Application::Render() {
  m_pSoftwareRenderer->Render();
}

// ==============================================

void Application::Run() {
  while (m_pImpl->running) {
    ProcessInput();
    Update();
    Render();
  }
}
