//
// Created by Pavel Prokofyev on 2019-01-03.
//

#ifndef __USBGEN_EXTENSIONS_CONFIGURATION__
#define __USBGEN_EXTENSIONS_CONFIGURATION__

namespace usb {

namespace configuration {

struct bMaxPower_mA : public bMaxPower {
  constexpr bMaxPower_mA(uint8_t mA) : bMaxPower(mA / 2) {}
};

} // namespace configuration

namespace detail {
template <typename... AggregatesT>
struct composite_init<ConfigurationComposite<AggregatesT...>> {
  constexpr void apply(ConfigurationComposite<AggregatesT...> &Object) {
    Object.wTotalLength = sizeof(ConfigurationComposite<AggregatesT...>);
  }
};

} // namespace detail
} // namespace usb

#endif //__USBGEN_EXTENSIONS_CONFIGURATION__
