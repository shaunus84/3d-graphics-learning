#pragma once

// ====================
#include <algorithm>
#include <vector>

#include "Colour.hpp"
// ====================

class ColourBuffer {
 public:
  // =============================================================================================

  ColourBuffer() = default;

  // =============================================================================================

  ColourBuffer(int width, int height, Colour32 clearColour)
      : m_buffer(static_cast<std::size_t>(width) * static_cast<std::size_t>(height), clearColour)
      , m_width{width}
      , m_height{height}
      , m_clearColour{clearColour} {}

  // =============================================================================================

  void SetPixel(int x, int y, Colour32 colour) {
    if (x > 0 && x < m_width && y > 0 && y < m_height) {
      m_buffer[(m_width * y) + x] = colour;
    }
  }

  // =============================================================================================

  Colour32 GetPixel(int x, int y) const {
    if (x > 0 && x < m_width && y > 0 && y < m_height) {
      return m_buffer[(m_width * y) + x];
    }
    return {};
  }

  // =============================================================================================

  const Colour32* Data() const {
    return m_buffer.data();
  }

  // =============================================================================================

  int Pitch() const {
    return m_width * sizeof(Colour32);
  }

  // =============================================================================================

  int Width() const {
    return m_width;
  }

  // =============================================================================================

  int Height() const {
    return m_height;
  }

  // =============================================================================================

  void SetClearColour(Colour32 clearColour) {
    m_clearColour = clearColour;
  }

  // =============================================================================================

  void Clear() {
    std::fill(m_buffer.begin(), m_buffer.end(), m_clearColour);
  }

  // =============================================================================================

  void Resize(int width, int height) {
    m_width = width;
    m_height = height;
    m_buffer.assign(static_cast<std::size_t>(width) * static_cast<std::size_t>(height), m_clearColour);
  }

  // =============================================================================================

 private:
  std::vector<Colour32> m_buffer;
  int m_width{0};
  int m_height{0};
  Colour32 m_clearColour{0};
};
