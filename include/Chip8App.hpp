#pragma once

#include <cstdint>
#include <string>

#include "Chip8Emulator.hpp"
#include "Chip8Window.hpp"

class Chip8App
{
public:
    Chip8App(const std::string& appName, uint8_t winWidth, uint8_t winHeight);

    bool LoadRom(const std::string& romPath);
    void Run();

    ~Chip8App() = default;

private:
    constexpr static int ROM_CONTENT_SIZE = 4096;
    Chip8Emulator emulator_;
    Chip8Window window_;
};
