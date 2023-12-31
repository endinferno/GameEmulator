#pragma once

#include <cstdint>

#include "CPU6502Register.hpp"
#include "Memory6502.hpp"
#include "NesOpcode.hpp"
#include "NesReader.hpp"
#include "PStatusReg6502.hpp"

using std::uint8_t;
using std::uint16_t;

class CPU6502
{
public:
    CPU6502(std::shared_ptr<NesReader>& nesReader);

    void Reset();
    void Run();

    std::string ToString() const;

    ~CPU6502() = default;

private:
    Opcode6502 ReadOpcode();
    Opcode6502 DecodeOpcode(uint8_t opcode) const;
    void InputOpcode(const Opcode6502& opcode);
    void IncreasePC(uint16_t offset);
    void Reset(uint16_t startAddr);

private:
    constexpr static uint16_t RESET_VECTOR_ADDR = 0xFFFC;

    std::shared_ptr<PStatusReg6502> pStatus_;
    std::shared_ptr<Memory6502> memory_;
    uint16_t pc_ = 0;
    uint8_t sp_ = 0;
    CPU6502Register accumReg_;
    CPU6502Register xReg_;
    CPU6502Register yReg_;
};
