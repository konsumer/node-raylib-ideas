export default function generateC(version, api) {
  const functionBodyOut = []
  const functionDefOut = []

  functionBodyOut.push(`// Function to test bindings
napi_value RaylibSayHello(napi_env env, napi_callback_info info) {
  // Get the name argument (with default "World")
  const char* name = get_string_arg(env, info);

  // Create result string
  char result[1024];
  snprintf(result, sizeof(result), "Hello, %s!", name == NULL ?  "World" : name);

  // Return the result
  return return_string(env, result);
}`)

  functionDefOut.push(`NAPI_CALL(env, napi_create_function(env, "SayHello", NAPI_AUTO_LENGTH, RaylibSayHello, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SayHello", fn));
  `)

  const out = [
  `// Raylib for nodejs ${version}

#include <node_api.h>
#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define NAPI_CALL(env, call)                                                   \
  do {                                                                         \
    napi_status status = (call);                                               \
    if (status != napi_ok) {                                                   \
      const napi_extended_error_info *error_info = NULL;                       \
      napi_get_last_error_info((env), &error_info);                            \
      const char *err_message = error_info->error_message;                     \
      napi_throw_error((env), NULL, err_message);                              \
      return NULL;                                                             \
    }                                                                          \
  } while (0)

// Helper to get string argument with default value
const char* get_string_arg(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  static char str_buf[1024];  // Note: Static for return safety

  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

  // Return default if no args or not a string
  if (argc < 1) {
    return NULL;
  }

  napi_valuetype value_type;
  NAPI_CALL(env, napi_typeof(env, args[0], &value_type));
  if (value_type != napi_string) {
    return NULL;
  }

  size_t str_len;
  NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], str_buf, sizeof(str_buf), &str_len));

  return str_buf;
}

// Helper to return string to JavaScript
napi_value return_string(napi_env env, const char* str) {
  napi_value return_value;
  NAPI_CALL(env, napi_create_string_utf8(env, str, strlen(str), &return_value));
  return return_value;
}


${functionBodyOut.join('\n')}

static napi_value Init(napi_env env, napi_value exports) {
  napi_value fn;

  ${functionDefOut.join('\n')}

  return exports;
}
NAPI_MODULE(raylib, Init)

  `
  ]
  return out.join('\n')
}
