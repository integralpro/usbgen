//
// Created by Pavel Prokofyev on 2019-01-02.
//

#ifndef __USBGEN__
#define __USBGEN__

#ifndef AMALGAMATION
#include "Std.h"
#endif // AMALGAMATION

#pragma pack(push, 1)

#include "BaseTypes.h"
#include "Composite.h"
#include "Descriptor.h"

#include "descriptors/Descriptors.h"
#include "descriptors/audio/Descriptors.h"
#include "descriptors/msc/Descriptors.h"

#pragma pack(pop)

#endif //__USBGEN__
