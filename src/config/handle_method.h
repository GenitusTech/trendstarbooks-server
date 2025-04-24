#ifndef HANDLE_METHOD_H_
#define HANDLE_METHOD_H_

#include "libft.h"

#define METHOD_ENUM(VARIANT)                                                   \
  VARIANT(GET, 1)                                                              \
  VARIANT(POST, 2)                                                             \
  VARIANT(PUT, 3)                                                              \
  VARIANT(PATCH, 4)                                                            \
  VARIANT(DELETE, 5)                                                           \
  VARIANT(OPTIONS, 6)                                                          \
  VARIANT(HEAD, 7)                                                             \
  VARIANT(TRACE, 8)

#define METHOD_ENUM_FROM_STRING(NAME, ...)                                     \
  if (ft_strcmp(str, #NAME) == 0)                                              \
    return NAME;

#define METHOD_ENUM_STRING(NAME, ...)                                          \
  case NAME:                                                                   \
    return #NAME;

#define METHOD_ENUM_VARIANT(NAME, VALUE) NAME = (VALUE),
enum EMethod
{
  METHOD_ENUM(METHOD_ENUM_VARIANT)
};

typedef enum EMethod Method;

Method string_to_method(const char *str, ...);
char *method_to_string(Method method);

#endif // HANDLE_METHOD_H_
