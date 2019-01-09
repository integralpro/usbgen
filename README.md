# USB Descriptor Generator

```cpp
extern "C" constexpr auto USBDeviceDesc = make_device(
    device::idVendor(1155),
    device::idProduct(22336),
    device::bMaxPacketSize(64),
    device::iSerialNumber(1),
    make_configuration(
        configuration::bConfigurationValue(1),
        configuration::bNumInterfaces(2),
        configuration::bMaxPower(100),
        configuration::bmAttributes(0x80),
        make_interface(
            interface::bInterfaceNumber(0),
            interface::bAlternateSetting(0),
            interface::bNumEndpoints(0),
            interface::bInterfaceClass(Audio),
            interface::bInterfaceSubClass(SubclassAudioControl),
            interface::bInterfaceProtocol(ProtocolUndefined),
            make_control_header<1>(
                header::bcdADC(0x0100),
                header::baInterfaceNr<1>(),
                make_input_terminal(
                    input_terminal::bTerminalID(1),
                    input_terminal::wTerminalType(TerminalMicrophone),
                    input_terminal::bAssocTerminal(0),
                    input_terminal::bNrChannels(2),
                    input_terminal::wChannelConfig(LeftFront | RightFront)
                    ),
                make_feature_unit<uint16_t, 2>(
                    feature_unit::bUnitID(2),
                    output_terminal::bSourceID(1),
                    feature_unit::bmaControls<Mute | Volume, 0, 0>()
                    ),
                make_output_terminal(
                    output_terminal::bTerminalID(3),
                    output_terminal::bSourceID(2),
                    output_terminal::wTerminalType(0x0101)
                    )
                )
        ),
        make_interface(
            interface::bInterfaceNumber(1),
            interface::bAlternateSetting(0),
            interface::bNumEndpoints(0),
            interface::bInterfaceClass(Audio),
            interface::bInterfaceSubClass(SubclassAudioStreaming),
            interface::bInterfaceProtocol(ProtocolUndefined)
        ),
        make_interface(
            interface::bInterfaceNumber(1),
            interface::bAlternateSetting(1),
            interface::bNumEndpoints(1),
            interface::bInterfaceClass(Audio),
            interface::bInterfaceSubClass(SubclassAudioStreaming),
            interface::bInterfaceProtocol(ProtocolUndefined)
        ),
        make_streaming_interface(
            streaming_interface::bTerminalLink(3),
            streaming_interface::wFormatTag(PCM)
            ),
        make_format_type_i<1>(
            format_type_i::bNrChannels(2),
            format_type_i::bSubframeSize(2),
            format_type_i::bBitResolution(16),
            format_type_i::tSamFreq<48000>()
            ),
        make_iso_data_endpoint(
            endpoint::bEndpointAddress(0x81),
            endpoint::wMaxPacketSize((48000 * 2 * 2) / 1000),
            endpoint::bmAttributes(0x05),
            endpoint::bInterval(1)
        ),
        make_as_iso_data_endpoint()
    ));
```