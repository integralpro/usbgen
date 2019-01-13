//
// Created by Pavel Prokofyev on 2019-01-02.
//

#ifndef RADIO_V2_FW_COMPOSITE_H
#define RADIO_V2_FW_COMPOSITE_H

namespace usb {

namespace detail {

template <typename T> struct composite_init { constexpr void apply(T &){}; };

template <typename T> constexpr void apply(T &) {}

template <typename T, typename ModT, typename... ModsT>
constexpr void apply(T &Object, const ModT &Mod, const ModsT &... Mods) {
  Mod.apply(Object);
  apply(Object, Mods...);
}

template <typename T, typename... ModsT, size_t... I>
constexpr void apply_tuple(T &Object, const std::tuple<ModsT &&...> &Mods,
                           std::index_sequence<I...>) {
  apply(Object, std::get<I>(Mods)...);
}

template <typename T, typename... ModsT>
constexpr void apply(T &Object, const std::tuple<ModsT &&...> &Mods) {
  apply_tuple(Object, Mods,
              std::make_index_sequence<std::tuple_size<typename std::decay<decltype(Mods)>::type>{}>{});
}

template <typename... Ts> struct CompositeLayer;

template <typename T, typename... Rs> struct CompositeLayer<T, Rs...> {
  T current;
  CompositeLayer<Rs...> rest;

  constexpr CompositeLayer(T &&Current, Rs &&...Rest) : current(std::move(Current)), rest(std::move(Rest)...) {}
  CompositeLayer(const CompositeLayer &) = delete;
  CompositeLayer(CompositeLayer &&) = default;

  template <size_t I, typename = std::enable_if_t<I == 0>>
  constexpr const T &sub() const {
    return current;
  }

  template <size_t I, typename = std::enable_if_t<(I != 0)>>
  constexpr const auto &sub() const {
    return rest.template sub<I - 1>();
  }
};

template <typename T> struct CompositeLayer<T> {
  T current;

  constexpr CompositeLayer(T &&Current) : current(std::move(Current)) {}
  CompositeLayer(const CompositeLayer &) = delete;
  CompositeLayer(CompositeLayer &&) = default;

  template <size_t I, typename = std::enable_if_t<I == 0>>
  constexpr const T &sub() const {
    return current;
  }

  template <size_t I, typename = std::enable_if_t<(I != 0)>>
  constexpr const auto &sub() const {
    static_assert(I == 0, "No such sub-descriptor");
    return current;
  }
};

template <typename BaseT, typename... AggregatesT>
struct CompositeDescriptor : public BaseT {
  CompositeLayer<AggregatesT...> aggregates;

  constexpr CompositeDescriptor(AggregatesT &&... Aggs)
      : aggregates(std::move(Aggs)...) {}

  constexpr CompositeDescriptor(CompositeDescriptor &&Obj) = default;
  constexpr CompositeDescriptor(const CompositeDescriptor &) = delete;

  template <size_t Index> constexpr const auto &sub() const {
    return aggregates.template sub<Index>();
  }
};

template <typename BaseT> struct CompositeDescriptor<BaseT> : public BaseT {
  constexpr CompositeDescriptor() {}
};

template <template <typename> class Predicate> constexpr auto filter() {
  return std::make_tuple();
}

template <template <typename> class Predicate> constexpr auto filter_not() {
  return std::make_tuple();
}

template <template <typename> class Predicate, typename T, typename... Ts,
          typename std::enable_if<Predicate<T>::value, int>::type = 0>
constexpr auto filter(T &&Type, Ts &&... Rest) {
  return std::tuple_cat(std::forward_as_tuple(std::move(Type)), filter<Predicate>(Rest...));
}

template <template <typename> class Predicate, typename T, typename... Ts,
          typename std::enable_if<!Predicate<T>::value, int>::type = 0>
constexpr auto filter(T &&Type, Ts &&... Rest) {
  return filter<Predicate>(Rest...);
}

template <template <typename> class Predicate, typename T, typename... Ts,
          typename std::enable_if<!Predicate<T>::value, int>::type = 0>
constexpr auto filter_not(T &&Type, Ts &&... Rest) {
  return std::tuple_cat(std::forward_as_tuple(std::move(Type)), filter_not<Predicate>(Rest...));
}

template <template <typename> class Predicate, typename T, typename... Ts,
          typename std::enable_if<Predicate<T>::value, int>::type = 0>
constexpr auto filter_not(T &&Type, Ts &&... Rest) {
  return filter_not<Predicate>(Rest...);
}

template <template <typename...> class T, typename... AggregatesT, size_t... I>
constexpr auto composite_impl(const std::tuple<AggregatesT &&...> &Aggs,
                              std::index_sequence<I...>) {
  return T<AggregatesT...>(std::move(std::get<I>(Aggs))...);
}

template <template <typename...> class T, typename... ChildrenT>
constexpr auto composite(ChildrenT &&... Children) {
  auto aggregates = filter_not<IsApplicatorTy>(Children...);

  auto object = std::move(composite_impl<T>(
      aggregates,
      std::make_index_sequence<std::tuple_size<decltype(aggregates)>{}>{}));

  auto applicators = filter<IsApplicatorTy>(Children...);
  apply(object, applicators);

  return object;
}

} // namespace detail

#define DEFINE_COMPOSITE(NAME)                                                 \
  template <typename... AggregatesT>                                           \
  struct NAME##Composite                                                       \
      : public detail::CompositeDescriptor<NAME##Descriptor, AggregatesT...> { \
    using BaseTy =                                                             \
        detail::CompositeDescriptor<NAME##Descriptor, AggregatesT...>;         \
                                                                               \
    constexpr NAME##Composite(AggregatesT &&... Aggs)                          \
        : BaseTy(std::move(Aggs)...) {                                         \
      detail::composite_init<NAME##Composite>().apply(*this);                  \
    }                                                                          \
  };

#define DEFINE_MAKE_COMPOSITE(NAME, NAME1)                                     \
  template <typename... AggregateT>                                            \
  constexpr auto make_##NAME1(AggregateT &&... Aggs) {                         \
    return detail::composite<NAME##Composite>(std::move(Aggs)...);             \
  }

} // namespace usb

#endif // RADIO_V2_FW_COMPOSITE_H
