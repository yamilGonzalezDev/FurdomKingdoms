#pragma once

inline constexpr float PPM = 30.f;

inline constexpr float toPixels(float meters) { return meters * PPM; }
inline constexpr float toMeters(float pixels) { return pixels / PPM; }
