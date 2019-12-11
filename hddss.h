#ifndef HDDSS_H
#define HDDSS_H

#include <stdint.h>

/* | Offset   | Description     | Size (bytes) | Data                                       | */
/* | 000->013 | serial number   | 20           | <spaces>NW58T5A25NHP                       | */
/* | 014->01B | FW version      | 8            | 0093002C                                   | */
/* | 01C->043 | model number    | 40           | FUJITSU MHV2020BH<spaces>                  | */
/* | 044->057 | ?               | 20           | 0x3b0fd73f8277fe41c6f6a25dfc172c177ad4f8d6 | */
/* | 058->05B | total LBAs (LE) | 4            | 0x02542980 LBAs x 512 bytes/LBA = 20GB     | */
/* | 05C->15B | encrypted stuff | 256          |                                            | */
/* | 15C->201 | null            | 166          | 0x00 x 166                                 | */
/* | 202->203 | ?               | 2            | 0x0ac2                                     | */
/* | 204->e00 | MS logo (PNG)   | 3068         |                                            | */

struct __attribute((__packed__)) HddSsHeader {
    uint8_t serial[20];
    uint8_t fw_ver[8];
    uint8_t model[40];
    uint8_t unknown[20];
    uint8_t total_lba[4];
    uint8_t encrypted[256];
    uint8_t null[166];
    uint8_t unknown2[2];
    uint8_t logo[3068];
};

#endif
