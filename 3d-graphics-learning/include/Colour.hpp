#pragma once

// ====================
#include <cstdint>
// ====================

struct Colour32 {
  // ===============================
  Colour32(uint32_t colour = 0xFFFFFFFF)
      : m_colour{colour} {}

  // ===============================
  Colour32(uint8_t A, uint8_t R, uint8_t G, uint8_t B)
      : m_colour{(std::uint32_t{A} << 24) | (std::uint32_t{R} << 16) | (std::uint32_t{G} << 8) | std::uint32_t{B}} {}

  // ===============================
  std::uint8_t A() const {
    return static_cast<std::uint8_t>((m_colour >> 24) & 0xFFu);
  }

  // ===============================
  std::uint8_t R() const {
    return static_cast<std::uint8_t>((m_colour >> 16) & 0xFFu);
  }

  // ===============================
  std::uint8_t G() const {
    return static_cast<std::uint8_t>((m_colour >> 8) & 0xFFu);
  }

  // ===============================
  std::uint8_t B() const {
    return static_cast<std::uint8_t>(m_colour & 0xFFu);
  }
  // ===============================
  uint32_t m_colour;
};
