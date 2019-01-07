//
// Created by Pavel Prokofyev on 2019-01-05.
//

#define DESCRIPTOR_BEGIN(NAME, NAME1, SIZE, KIND)                              \
  DESCRIPTOR_DEFINE(NAME, NAME1, SIZE, KIND)
#define FIELD(TYPE, NAME, VALUE) TYPE NAME = {VALUE};
#define FIELD_HIDDEN(TYPE, NAME, VALUE) FIELD(TYPE, NAME, VALUE)
#define DESCRIPTOR_END()                                                       \
  }                                                                            \
  ;
