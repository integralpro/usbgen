//
// Created by Pavel Prokofyev on 2019-01-05.
//

#ifndef __USBGEN_DESCRIPTORS_AUDIO_TYPES__
#define __USBGEN_DESCRIPTORS_AUDIO_TYPES__

namespace usb {
namespace audio {

enum : uint8_t {
  Undefined = 0x00
};

enum ControlInterfaceSubtype : uint8_t {
  Header = 0x01,
  InputTerminal = 0x02,
  OutputTerminal = 0x03,
  MixerUnit = 0x04,
  SelectorUnit = 0x05,
  FeatureUnit = 0x06,
  ProcessingUnit = 0x07,
  ExtensionUnit = 0x08
};

enum StreamingInterfaceSubtype : uint8_t {
  ASGeneral = 0x01,
  FormatType = 0x02,
  FormatSpecific = 0x03,
};

enum StreamingEndpointSubtype : uint8_t {
  EPGeneral = 0x01,
};

enum InputTerminalType : uint16_t {
  // Input Terminal, undefined Type.
  InputUndefined = 0x0200,

  // A generic microphone that does not fit under any of the other
  // classifications.
  TerminalMicrophone = 0x0201,

  // A microphone normally placed on the desktop or integrated into the monitor.
  TerminalDesktopMicrophone = 0x0202,

  // A head-mounted or clip-on microphone.
  TerminalPersonalMicrophone = 0x0203,

  // A microphone designed to pick up voice from more than one speaker at
  // relatively long ranges.
  TerminalOmniDirectionalMicrophone = 0x0204,

  // An array of microphones designed for directional processing using
  // host-based signal processing algorithms.
  TerminalMicrophoneArray = 0x0205,

  // An array of microphones with an embedded signal processor.
  TerminalProcessingMicrophoneArray = 0x0206
};

enum ChannelConfig : uint16_t {
  LeftFront = (1UL << 0),
  RightFront = (1UL << 1),
  CenterFront = (1UL << 2),
  LowFrequencyEnhancement = (1UL << 3),
  LeftSurround = (1UL << 4),
  RightSurround = (1UL << 5),
  LeftCenter = (1UL << 6),
  RightCenter = (1UL << 7),
  Surround = (1UL << 8),
  SideLeft = (1UL << 9),
  SideRight = (1UL << 10),
  Top = (1UL << 11)
};

enum FeatureUnitControls : uint16_t {
  Mute = (1UL << 0),
  Volume = (1UL << 1),
  Bass = (1UL << 2),
  Mid = (1UL << 3),
  Treble = (1UL << 4),
  GraphicEqualizer = (1UL << 5),
  AutomaticGain = (1UL << 6),
  Delay = (1UL << 7),
  BassBoost = (1UL << 8),
  Loudness = (1UL << 9)
};

enum InterfaceSubclass : uint8_t {
  SubclassAudioControl = 0x01,
  SubclassAudioStreaming = 0x02,
  SubclassMidiStreaming = 0x03
};

enum InterfaceProtocol : uint8_t { ProtocolUndefined = 0x00 };

enum DescriptorType : uint8_t {
  AudioDescriptorUndefined = 0x20,
  AudioDevice = 0x21,
  AudioConfiguration = 0x22,
  AudioString = 0x23,
  AudioInterface = 0x24,
  AudioEndpoint = 0x25,
};

enum DataFormatType : uint8_t {
  FormatTypeI = 0x01,
  FormatTypeII = 0x02,
  FormatTypeIII = 0x03
};

enum DataFormatTypeI : uint16_t {
  TypeIUndefined = 0x0000,
  PCM = 0x0001,
  PCM8 = 0x0002,
  IEEE_FLOAT = 0x0003,
  ALAW = 0x0004,
  MULAW = 0x0005,
};

} // namespace audio
} // namespace usb

#endif //__USBGEN_DESCRIPTORS_AUDIO_TYPES__
