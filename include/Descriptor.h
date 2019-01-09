//
// Created by Pavel Prokofyev on 2019-01-02.
//

#ifndef __USBGEN__DESCRIPTOR_IMPL__
#define __USBGEN__DESCRIPTOR_IMPL__

namespace usb {

struct DescriptorBase {
  uint8_t bLength;
  uint8_t bDescriptorType;

  constexpr DescriptorBase(uint8_t bLength, uint8_t bDescriptorType)
      : bLength(bLength), bDescriptorType(bDescriptorType) {}

  constexpr uint8_t *getPointer() const { return const_cast<uint8_t *>(&bLength); }
};

#define APPLICATOR(NAME, TYPE, PROP)                                           \
  struct NAME : detail::ApplicatorBase {                                       \
    TYPE v_##PROP;                                                             \
    constexpr NAME(TYPE v_##PROP) : v_##PROP(v_##PROP) {}                      \
    template <typename T> constexpr void apply(T &Object) const {              \
      Object.PROP = v_##PROP;                                                  \
    }                                                                          \
  };

#define DESCRIPTOR_DEFINE(NAME, NAME1, SIZE, KIND)                             \
  struct NAME##Descriptor : public DescriptorBase {                            \
    using BaseTy = DescriptorBase;                                             \
    constexpr NAME##Descriptor() : BaseTy(sizeof(NAME##Descriptor), KIND) {    \
      static_assert(sizeof(NAME##Descriptor) == SIZE,                          \
                    "unexpected descriptor size");                             \
    }

} // namespace usb

#endif //__USBGEN__DESCRIPTOR_IMPL__
