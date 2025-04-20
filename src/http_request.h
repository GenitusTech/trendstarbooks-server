#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#define BUFFER_SIZE 4096

// START STRUCTURE: REQUEST
struct SRequest
{
  char *method;
  char *path;
  char *protocol;
  char *headers;
  char *body;
  // unsigned int header_count;
};
typedef struct SRequest HttpRequest;
// END STRUCTURE: REQUEST

// START ENUM: METHOD
#define METHOD_ENUM(VARIANT)                                                                                           \
  VARIANT(GET, 1)                                                                                                      \
  VARIANT(POST, 2)                                                                                                     \
  VARIANT(PUT, 3)                                                                                                      \
  VARIANT(DELETE, 4)                                                                                                   \
  VARIANT(OPTIONS, 5)                                                                                                  \
  VARIANT(HEAD, 6)                                                                                                     \
  VARIANT(TRACE, 7)
#define METHOD_ENUM_VARIANT(NAME, VALUE) NAME = (VALUE),
enum EMethod
{
  METHOD_ENUM(METHOD_ENUM_VARIANT)
};
typedef enum EMethod Method;

#define METHOD_ENUM_STRING(NAME, ...)                                                                                  \
  case NAME:                                                                                                           \
    return #NAME;
#define METHOD_ENUM_FROM_STRING(NAME, ...)                                                                             \
  if (ft_strcmp(str, #NAME) == 0)                                                                                         \
    return NAME;

// END ENUM: METHOD

Method sanitize_method(const char *str, ...);
HttpRequest *get_request(const char *raw_content);
void free_request(HttpRequest *req);

#endif // HTTP_REQUEST_H_
