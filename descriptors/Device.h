//
// Created by Pavel Prokofyev on 2019-01-03.
//

#ifndef __USBGEN_EXTENSIONS_DEVICE__
#define __USBGEN_EXTENSIONS_DEVICE__

namespace usb {

namespace detail {
template <typename... AggregatesT>
struct composite_init<DeviceComposite<AggregatesT...>> {
  constexpr void apply(DeviceComposite<AggregatesT...> &Object) {
    Object.bNumConfigurations = sizeof...(AggregatesT);
  }
};

} // namespace detail
} // namespace usb

#endif //__USBGEN_EXTENSIONS_DEVICE__
