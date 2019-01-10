//
// Created by Pavel Prokofyev on 2019-01-03.
//

#ifndef __USBGEN_AUDIO_FORMAT_TYPE_I__
#define __USBGEN_AUDIO_FORMAT_TYPE_I__

#include "Composite.h"
#include "Descriptor.h"

namespace usb {
namespace audio {

struct uint24_t : public std::array<uint8_t, 3> {
  template <typename T>
  constexpr uint24_t(T Val)
      : std::array<uint8_t, 3>{static_cast<uint8_t>(Val & 0xff),
                               static_cast<uint8_t>((Val >> 8) & 0xff),
                               static_cast<uint8_t>((Val >> 16) & 0xff)} {}

  constexpr uint24_t() : std::array<uint8_t, 3>{0} {}
};

template <size_t N> struct N__ { constexpr static size_t value = N; };

template <> struct N__<0> { constexpr static size_t value = 2; };

template <size_t N> struct FormatTypeIDescriptor : public DescriptorBase {
  using BaseTy = DescriptorBase;

  uint8_t bDescriptorSubtype = {FormatType};
  uint8_t bFormatType = {FormatTypeI};
  uint8_t bNrChannels = {0};
  uint8_t bSubframeSize = {1};
  uint8_t bBitResolution = {0};
  uint8_t bSamFreqType = {N};
  std::array<uint24_t, N__<N>::value> tSamFreq = {0};

  constexpr FormatTypeIDescriptor()
      : BaseTy(sizeof(FormatTypeIDescriptor), AudioInterface) {
    static_assert(sizeof(FormatTypeIDescriptor) == 8 + N__<N>::value * 3,
                  "unexpected descriptor size");
  }
};

template <size_t N, typename... AggregatesT>
struct FormatTypeIComposite
    : public detail::CompositeDescriptor<FormatTypeIDescriptor<N>,
                                         AggregatesT...> {
  using BaseTy =
      detail::CompositeDescriptor<FormatTypeIDescriptor<N>, AggregatesT...>;

  constexpr FormatTypeIComposite(AggregatesT &&... Aggs)
      : BaseTy(Aggs...) {}
};

template <size_t N> struct FormatTypeIHelper {
  template <typename... AggregateT>
  using type = FormatTypeIComposite<N, AggregateT...>;
};

template <size_t N, typename... AggregateT>
static constexpr auto make_format_type_i(AggregateT &&... Aggs) {
  return detail::composite<FormatTypeIHelper<N>::template type>(std::move(Aggs)...);
}

namespace format_type_i {

APPLICATOR(bNrChannels, uint8_t, bNrChannels)
APPLICATOR(bSubframeSize, uint8_t, bSubframeSize)
APPLICATOR(bBitResolution, uint8_t, bBitResolution)

template <uint32_t... Vals> struct tSamFreq : detail::ApplicatorBase {
  constexpr tSamFreq() {}

  template <typename T> constexpr void apply(T &Object) const {
    Object.tSamFreq = {Vals...};
  }
};

} // namespace format_type_i

} // namespace audio
} // namespace usb

#endif //__USBGEN_AUDIO_FORMAT_TYPE_I__
