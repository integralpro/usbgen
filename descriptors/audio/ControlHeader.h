//
// Created by Pavel Prokofyev on 2019-01-03.
//

#ifndef RADIO_V2_FW_CONTROLHEADER_H
#define RADIO_V2_FW_CONTROLHEADER_H

#include "Composite.h"
#include "Descriptor.h"

namespace usb {
namespace audio {

template <size_t N> struct ControlHeaderDescriptor : public DescriptorBase {
  using BaseTy = DescriptorBase;

  uint8_t bDescriptorSubtype = {Header};
  uint16_t bcdADC = {0x0100};
  uint16_t wTotalLength = {0};
  uint8_t bInCollection = {N};
  std::array<uint8_t, N> baInterfaceNr = {0};

  constexpr ControlHeaderDescriptor()
      : BaseTy(sizeof(ControlHeaderDescriptor), AudioInterface) {
    static_assert(sizeof(ControlHeaderDescriptor) == 8 + N,
                  "unexpected descriptor size");
  }
};

template <size_t N, typename... AggregatesT>
struct ControlHeaderComposite
    : public detail::CompositeDescriptor<ControlHeaderDescriptor<N>,
                                         AggregatesT...> {
  using BaseTy =
      detail::CompositeDescriptor<ControlHeaderDescriptor<N>, AggregatesT...>;

  constexpr ControlHeaderComposite(AggregatesT &&... Aggs)
      : BaseTy(std::move(Aggs)...) {
    BaseTy::wTotalLength = sizeof(ControlHeaderComposite);
  }
};

template <size_t N> struct AudioControlHelper {
  template <typename... AggregateT>
  using type = ControlHeaderComposite<N, AggregateT...>;
};

template <size_t N, typename... AggregateT>
static constexpr auto make_control_header(AggregateT &&... Aggs) {
  return detail::composite<AudioControlHelper<N>::template type>(std::move(Aggs)...);
}

namespace header {

APPLICATOR(bcdADC, uint16_t, bcdADC)

template <uint8_t... Vals> struct baInterfaceNr : detail::ApplicatorBase {
  constexpr baInterfaceNr() {}

  template <typename T> constexpr void apply(T &Object) const {
    Object.baInterfaceNr = {Vals...};
  }
};

} // namespace header

} // namespace audio
} // namespace usb

#endif // RADIO_V2_FW_CONTROLHEADER_H
