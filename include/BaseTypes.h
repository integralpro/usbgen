//
// Created by Pavel Prokofyev on 2019-01-02.
//

#ifndef __USBGEN_BASE_TYPES__
#define __USBGEN_BASE_TYPES__

namespace usb {

namespace detail {

struct ApplicatorBase {};

template <typename T> using IsApplicatorTy = std::is_base_of<ApplicatorBase, typename std::decay<T>::type>;

} // namespace detail

} // namespace usb

#endif //__USBGEN_BASE_TYPES__
