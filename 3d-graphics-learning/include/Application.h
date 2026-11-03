#pragma once

// ==========================
#include <memory>
#include <string>
#include <string_view>

#include "SoftwareRenderer.h"
// ==========================

// ===================================================
// InitResult
//
// Simple results type to handle SDL initialisation.
// Holds result as a bool and error message text.
// ===================================================
struct InitResult {
  bool succeeded;
  std::string error;

  explicit operator bool() const {
    return succeeded;
  }
};

// ==================================================
// Application
//
// Initialises SDL and Software renderer,
// contains game loop.
// ==================================================
class Application {
 public:
  Application(std::string_view windowTitle);
  ~Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  InitResult Initialise();
  void Run();

 private:
  void ProcessInput();
  void Update();
  void Render();

 private:
  struct Impl;
  std::unique_ptr<Impl> m_pImpl{nullptr};
  std::unique_ptr<SoftwareRenderer> m_pSoftwareRenderer{nullptr};
  std::string m_windowTitle;
};
