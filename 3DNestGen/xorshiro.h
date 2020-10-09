#ifndef INC_3D_NESTS_XORSHIRO_H
#define INC_3D_NESTS_XORSHIRO_H

#include "splitmix64.h"

class Xorshiro {
    uint64_t s[2]{};

    inline uint64_t rotl(uint64_t x, int k);

public:
    Xorshiro ( ) {
        SplitMix64 split;
        s[0] = split.next();
        s[1] = split.next();
    }// end Xorshiro ( )

    uint64_t next();
    void jump();
};

#endif //INC_3D_NESTS_XORSHIRO_H
