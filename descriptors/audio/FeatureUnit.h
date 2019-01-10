//
// Created by Pavel Prokofyev on 2019-01-03.
//

#ifndef __USBGEN_AUDIO_FEATURE_UNIT__
#define __USBGEN_AUDIO_FEATURE_UNIT__

#include "Composite.h"
#include "Descriptor.h"

namespace usb {
namespace audio {

template <typename T, size_t N>
struct FeatureUnitDescriptor : public DescriptorBase {
  using BaseTy = DescriptorBase;

  uint8_t bDescriptorSubtype = {FeatureUnit};
  uint8_t bUnitID = {0};
  uint8_t bSourceID = {0};
  uint8_t bControlSize = {sizeof(T)};
  std::array<T, N + 1> bmaControls = {0};
  uint8_t iFeature = {0};

  constexpr FeatureUnitDescriptor()
      : BaseTy(sizeof(FeatureUnitDescriptor), AudioInterface) {
    static_assert(sizeof(FeatureUnitDescriptor) == (7 + (N + 1) * sizeof(T)),
                  "unexpected descriptor size");
  }
};

template <typename T, size_t N, typename... AggregatesT>
struct FeatureUnitComposite
    : public detail::CompositeDescriptor<FeatureUnitDescriptor<T, N>,
                                         AggregatesT...> {
  using BaseTy =
      detail::CompositeDescriptor<FeatureUnitDescriptor<T, N>, AggregatesT...>;

  constexpr FeatureUnitComposite(AggregatesT &&... Aggs)
      : BaseTy(std::move(Aggs)...) {}
};

template <typename T, size_t N> struct FeatureUnitHelper {
  template <typename... AggregateT>
  using type = FeatureUnitComposite<T, N, AggregateT...>;
};

template <typename T, size_t N, typename... AggregateT>
static constexpr auto make_feature_unit(AggregateT &&... Aggs) {
  return detail::composite<FeatureUnitHelper<T, N>::template type>(std::move(Aggs)...);
}

namespace feature_unit {
APPLICATOR(bUnitID, uint8_t, bUnitID)
APPLICATOR(bSourceID, uint8_t, bSourceID)
APPLICATOR(iFeature, uint8_t, iFeature)

template <size_t... Vals> struct bmaControls : detail::ApplicatorBase {
  constexpr bmaControls() {}

  template <typename T> constexpr void apply(T &Object) const {
    Object.bmaControls = {Vals...};
  }
};

} // namespace feature_unit

} // namespace audio
} // namespace usb

#endif //__USBGEN_AUDIO_FEATURE_UNIT__
