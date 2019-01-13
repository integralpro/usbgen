//
// Created by Pavel Prokofyev on 2019-01-03.
//

#ifndef RADIO_V2_FW_ISO_DATA_ENDPOINT_H
#define RADIO_V2_FW_ISO_DATA_ENDPOINT_H

#include "Composite.h"
#include "Descriptor.h"

namespace usb {
namespace audio {

struct IsochronousDataEndpointDescriptor : public EndpointDescriptor {
  using BaseTy = EndpointDescriptor;

  // Reset to 0.
  uint8_t bRefresh = {0};

  // The address of the endpoint used to communicate synchronization information
  // if required by this endpoint. Reset to zero if no synchronization pipe is
  // used.
  uint8_t bSynchAddress = {0};

  constexpr IsochronousDataEndpointDescriptor()
      : BaseTy(sizeof(IsochronousDataEndpointDescriptor)) {
    static_assert(sizeof(IsochronousDataEndpointDescriptor) == 9,
                  "unexpected descriptor size");
  }
};

template <typename... AggregatesT>
struct IsochronousDataEndpointComposite
    : public detail::CompositeDescriptor<IsochronousDataEndpointDescriptor,
                                         AggregatesT...> {
  using BaseTy = detail::CompositeDescriptor<IsochronousDataEndpointDescriptor,
                                             AggregatesT...>;

  constexpr IsochronousDataEndpointComposite(AggregatesT &&... Aggs)
      : BaseTy(Aggs...) {}
};

template <typename... AggregateT>
static constexpr auto make_iso_data_endpoint(AggregateT &&... Aggs) {
  return detail::composite<IsochronousDataEndpointComposite>(std::move(Aggs)...);
}

namespace iso_data_endpoint {

APPLICATOR(bRefresh, uint8_t, bRefresh)
APPLICATOR(bSynchAddress, uint8_t, bSynchAddress)

} // namespace iso_data_endpoint

} // namespace audio
} // namespace usb

#endif // RADIO_V2_FW_CONTROLHEADER_H
