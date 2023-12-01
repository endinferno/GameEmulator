#include "Memory6502.hpp"
#include "Logger.hpp"
#include "NesReader.hpp"

Memory6502::Memory6502(std::shared_ptr<NesReader>& nesReader)
    : internalRam_(INTERNAL_RAM_SIZE, 0)
    , mapper_(nesReader)
{}

void Memory6502::Reset()
{
    std::fill(internalRam_.begin(), internalRam_.end(), 0);
    ppuReg_.Reset();
}

uint8_t Memory6502::Read(const uint16_t& addr) const
{
    DEBUG("Read addr: 0x{:0>4X}\n", addr);
    if (addr < INTERNAL_RAM_RANGE) {
        return internalRam_[addr & (INTERNAL_RAM_SIZE - 1)];
    }
    else if (addr < PPU_REG_RANGE) {
        return ppuReg_.Read(addr);
    }
    else if (addr < APU_REG_RANGE) {
        // TODO: Implement APU
    }
    else if (addr < PRG_RAM_RANGE) {
        // TODO: Implement PRG RAM
    }
    else {
        return mapper_.Read(addr);
    }
    return 0;
}

void Memory6502::Write(const uint16_t& addr, const uint8_t val)
{
    DEBUG("Write addr: 0x{:0>4X} val: 0x{:0>2X}\n", addr, val);
    if (addr < INTERNAL_RAM_RANGE) {
        internalRam_[addr & (INTERNAL_RAM_SIZE - 1)] = val;
    }
    else if (addr < PPU_REG_RANGE) {
        ppuReg_.Write(addr, val);
    }
}

std::string Memory6502::ToString() const
{
    return ppuReg_.ToString();
}