//
// Created by Pavel Prokofyev on 2019-01-12.
//

#ifndef __USBGEN_DESCRIPTORS_MSC_TYPES__
#define __USBGEN_DESCRIPTORS_MSC_TYPES__

namespace usb {
namespace msc {

enum InterfaceSubclass : uint8_t {
  Undefined = 0x00,
  RBC = 0x01,
  MMC5 = 0x02,

  UFI = 0x04,
  SCSI = 0x06,
  LSDFS = 0x07,
  IEEE1667 = 0x08,

  VendorSubclass = 0xff
};

enum InterfaceProtocol : uint8_t {
  // Control/Bulk/Interrupt Transport (with command completion interrupt)
  CBI_CI = 0x00,

  // Control/Bulk/Interrupt Transport (with no command completion interrupt)
  CBI_NOCI = 0x01,

  // USB Mass Storage Class Bulk-Only (BBB) Transport
  BBB = 0x50,

  UAS = 0x62,

  VendorProtocol = 0xff
};

}
}

#endif //__USBGEN_DESCRIPTORS_MSC_TYPES__
