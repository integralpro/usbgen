//
// Created by Pavel Prokofyev on 2019-01-07.
//

#ifndef __USBGEN_DESCRIPTORS_STRING__
#define __USBGEN_DESCRIPTORS_STRING__

namespace usb {

namespace detail {

template<typename T, std::size_t N, std::size_t ... Is>
constexpr std::array<T, N - 1> to_array(const T (&a)[N], std::index_sequence<Is...>) {
  return {{a[Is]...}};
}

template<typename T, std::size_t N>
constexpr std::array<T, N - 1> to_array(const T (&a)[N]) {
  return to_array(a, std::make_index_sequence<N - 1>());
}

}

template<size_t N>
struct StringDescriptor : public DescriptorBase {
  using BaseTy = DescriptorBase;
  std::array<char16_t, N> wString;

  constexpr StringDescriptor(const char16_t (&Str)[N + 1])
      : BaseTy(sizeof(StringDescriptor), String), wString(detail::to_array<char16_t>(Str)) {
    static_assert(sizeof(StringDescriptor) == (2 + N * 2), "unexpected descriptor size");
  }
};

template<>
struct StringDescriptor<0> : public DescriptorBase {
  using BaseTy = DescriptorBase;

  constexpr StringDescriptor(const char16_t (&Str)[1])
      : BaseTy(sizeof(StringDescriptor), String) {
    static_assert(sizeof(StringDescriptor) == 2, "unexpected descriptor size");
  }
};

template<size_t N>
constexpr auto make_string(const char16_t (&Str)[N]) {
  return StringDescriptor<N - 1>(Str);
}

template<size_t N>
constexpr auto make_lang_ids(const char16_t (&Str)[N]) {
  return StringDescriptor<N>(Str);
}

constexpr auto make_lang_ids(char16_t LangID) {
  return StringDescriptor<1>({LangID});
}

}

#endif //__USBGEN_DESCRIPTORS_STRING__
