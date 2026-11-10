#ifndef RP_UTILITY_RANDOM_H
#define RP_UTILITY_RANDOM_H
#include <Pack/types_pack.h>

/**
 * @brief LCG random number generator
 */
class RPUtlRandom {
public:
    /**
     * @brief Seeds the generator using the system clock
     */
    static void initialize();

    /**
     * @brief Generates a random unsigned 32-bit integer
     *
     * Resort: out of line (weak copy at 0x8025C9B0, getU32__11RPUtlRandomFv); callers
     * `bl` it. The body is calc() below.
     */
    static u32 getU32();

    /**
     * @brief Generates a random unsigned 32-bit integer in the range [0, max)
     *
     * @param max Upper bound (exclusive)
     */
    static u32 getU32(u32 max) {
        return max * getF32();
    }

    /**
     * @brief Generates a random floating point value in the range [0, 1)
     */
    static f32 getF32() {
        // Limited to u16 bounds, converted to a percentage (+1 makes the upper
        // bound exclusive!). Single expression: named locals change FPR
        // allocation in RPSysKokeshi::LoadResource and Bowling callers.
        return static_cast<f32>(
                   static_cast<u16>(RANDF_MAX & (getU32() >> RANDF_SHIFT))) /
               static_cast<f32>(RANDF_MAX + 1);
    }

private:
    /**
     * @brief Advances the generator state
     *
     * Resort (getU32 copy at 0x8025C9B0): an LCG combined with a shift
     * register, multiplier as an immediate. Wii Sports used the LCG alone
     * (sSeed * MULT + 1).
     */
    static u32 calc() {
        sSeed = sSeed * MULT + 12345;

        if (sUnk806F4E3C & 1) {
            sUnk806F4E3C ^= 0x11020;
        }
        sUnk806F4E3C >>= 1;

        return sSeed ^ sUnk806F4E3C;
    }

private:
    //! Seed multiplier
    static const u32 MULT = 0x41C64E6D;

    //! Integer limit for random floating point generation
    static const u32 RANDF_MAX;
    //! Bit shift amount for random floating point generation
    static const u32 RANDF_SHIFT;

    //! Global generator seed (Resort: 0x806F4E38)
    static u32 sSeed;
    //! Resort: shift-register state (0x806F4E3C), name unknown
    static u32 sUnk806F4E3C;
};

#endif
