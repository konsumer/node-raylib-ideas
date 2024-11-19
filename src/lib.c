// Raylib for nodejs 5.5.0

#include <node_api.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAPI_CALL(env, call)                               \
  do {                                                     \
    napi_status status = (call);                           \
    if (status != napi_ok) {                               \
      const napi_extended_error_info* error_info = NULL;   \
      napi_get_last_error_info((env), &error_info);        \
      const char* err_message = error_info->error_message; \
      napi_throw_error((env), NULL, err_message);          \
      return NULL;                                         \
    }                                                      \
  } while (0)

// Get the arguments for a function-call
static napi_value* get_args(napi_env env, napi_callback_info info, size_t expected_args) {
  size_t argc = expected_args;
  napi_value* args = (napi_value*)malloc(sizeof(napi_value) * expected_args);
  napi_status status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  if (status != napi_ok) {
    free(args);
    napi_throw_error(env, NULL, "Failed to parse arguments");
    return NULL;
  }
  return args;
}

// Get a single string argument
static char* get_string_arg(napi_value* args, int argNum, napi_env env, napi_callback_info info) {
  if (args == NULL) return NULL;
  napi_valuetype valuetype;
  napi_status status = napi_typeof(env, args[argNum], &valuetype);
  if (status != napi_ok || valuetype != napi_string) {
    // napi_throw_type_error(env, NULL, "String expected");
    return NULL;
  }
  char* str = (char*)malloc(1024);  // Or whatever reasonable size you expect
  size_t result;
  status = napi_get_value_string_utf8(env, args[argNum], str, 1024, &result);
  if (status != napi_ok) {
    free(str);
    // napi_throw_error(env, NULL, "Failed to get string");
    return NULL;
  }
  return str;
}

// Return string to JavaScript
napi_value return_string(napi_env env, const char* str) {
  napi_value return_value;
  NAPI_CALL(env, napi_create_string_utf8(env, str, strlen(str), &return_value));
  return return_value;
}

// Function to test bindings
napi_value RaylibSayHello(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  char* name = get_string_arg(args, 0, env, info);
  free(args);

  char result[127] = {};
  snprintf(result, sizeof(result), "Hello, %s!", name == NULL ? "World" : name);

  return return_string(env, result);
}

static napi_value Init(napi_env env, napi_value exports) {
  napi_value fn;

  NAPI_CALL(env, napi_create_function(env, "SayHello", NAPI_AUTO_LENGTH, RaylibSayHello, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SayHello", fn));
  

  return exports;
}
NAPI_MODULE(raylib, Init)

  