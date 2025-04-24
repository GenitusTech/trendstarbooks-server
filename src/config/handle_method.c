#include "handle_method.h"

Method string_to_method(const char *str, ...)
{
  METHOD_ENUM(METHOD_ENUM_FROM_STRING)
  return (0);
}

char *method_to_string(Method method)
{
  switch (method)
  {
    METHOD_ENUM(METHOD_ENUM_STRING)
    default:
      break;
  }
  return (0);
}
