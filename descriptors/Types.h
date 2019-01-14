//
// Created by Pavel Prokofyev on 2019-01-05.
//

#ifndef RADIO_V2_FW_TYPES_H
#define RADIO_V2_FW_TYPES_H

namespace usb {

enum DescriptorType : uint8_t {
  Device = 0x01,
  Configuration = 0x02,
  String = 0x03,
  Interface = 0x04,
  Endpoint = 0x05,
  DeviceQualifier = 0x06,
};

enum DescriptorClass : uint8_t {
  InterfaceDefined = 0x00,
  Audio = 0x01,
  CDC = 0x02,
  HID = 0x03,

  Physical = 0x05,
  Image = 0x06,
  Printer = 0x07,
  MSC = 0x08,
  Hub = 0x09,
  CDCData = 0x0a,
  SmartCard = 0x0b,
  ContentSecurity = 0x0d,
  Video = 0x0e,
  PersonalHealthcare = 0x0f,
  AudioVideo = 0x10,
  Billboard = 0x11,
  USBCBridge = 0x12,
  Diagnostic = 0xdc,
  Wireless = 0xe0,
  Miscellaneous = 0xef,
  ApplicationSpecific = 0xfe,
  VendorSpecific = 0xff
};

} // namespace usb

#endif // RADIO_V2_FW_TYPES_H
