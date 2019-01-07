//
// Created by Pavel Prokofyev on 2019-01-05.
//

#define DESCRIPTOR_BEGIN(NAME, NAME1, SIZE, KIND)                              \
  DEFINE_COMPOSITE(NAME)                                                       \
  DEFINE_MAKE_COMPOSITE(NAME, NAME1)

#define DESCRIPTOR_END()

#define FIELD(TYPE, NAME, VALUE)
#define FIELD_HIDDEN(TYPE, NAME, VALUE)
