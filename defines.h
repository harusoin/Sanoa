#ifndef DEFINES_H
#define DEFINES_H
#include "libmtp.h"

enum DeviceType{
    DEVICETYPE_NULL,
    DEVICETYPE_STANDARD,
    DEVICETYPE_MTP,
};
typedef struct MTP_STORAGE_ID_struct
{
    uint32_t busno;
    uint8_t devno;
}MTP_STORAGE_ID_t;

#endif // DEFINES_H
