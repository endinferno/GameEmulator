#include "CPU6502.hpp"
#include "Chip8App.hpp"
#include "Logger.hpp"
#include "NesReader.hpp"

void PrintUsage()
{
    INFO("Usage: GameEmulator <type> <rom>");
}

void RunEmulator(const std::string& emulatorType, const std::string& romPath)
{
    DEBUG("Emulator Type: \"{}\" Rom Path: \"{}\"", emulatorType, romPath);
    if (emulatorType == "nes") {
        auto nesReader = std::make_shared<NesReader>(romPath);
        CPU6502 cpu(nesReader);
        INFO("{}", nesReader->ToString());
        INFO("{}", cpu.ToString());
        cpu.Run();
    }
    else if (emulatorType == "chip8") {
        Chip8App app("CHIP8 Emulator", 64, 32);
        app.LoadRom(romPath);
        app.Run();
    }
    else {
        ERROR("Unknown emulator type: {}", emulatorType);
    }
}

int main(int argc, char* argv[])
{
    if (argc == 3) {
        RunEmulator(argv[1], argv[2]);
    }
    else {
        PrintUsage();
    }
    return 0;
}
