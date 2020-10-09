#ifndef INC_3D_NESTS_SPLITMIX64_H
#define INC_3D_NESTS_SPLITMIX64_H


class SplitMix64 {
    uint64_t x;

public:
    /// Seeds x using Intel's Digital Random Number Generator (DRNG)
	SplitMix64 ( );

    uint64_t next ( );
};

#endif //INC_3D_NESTS_SPLITMIX64_H

