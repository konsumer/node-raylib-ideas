export default function generateC(version, api) {
  const functionBodyOut = []
  const functionDefOut = []

  functionBodyOut.push(`// Function to test bindings
static napi_value RaylibSayHello(napi_env env, napi_callback_info info) {
  napi_value args[1] = get_args(env, info, 1);
  char* name = get_string_arg(args[0], env);

  char response_cstr[1024];
  snprintf(response_cstr, sizeof(response_cstr), "Hello %s!", name != NULL ? name : "World");

  napi_status status;
  napi_value response;
  
  status = napi_create_string_utf8(env, response_cstr, strlen(response_cstr), &response);
  assert(status == napi_ok);
  return response;
}`)

  functionDefOut.push(`napi_property_descriptor desc = NAPI_METHOD("SayHello", RaylibSayHello);
  status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  `)

  const out = [
  `// Raylib for nodejs.
// Generated at ${new Date().toISOString()}
// for Raylib ${version}

#include <assert.h>
#include <node_api.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

// get the args
napi_value* get_args(napi_env env, napi_callback_info info, size_t argc) {
  napi_value* argv = malloc(sizeof(napi_value) * argc);
  napi_status status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  return argv;
}

// get a string function argument as a char*
char* get_string_arg(napi_value arg, napi_env env) {
  napi_valuetype* result;
  if (napi_typeof(env, arg, result) != napi_string) {
    napi_throw_type_error(env, NULL, "Expected a string argument.");
    return NULL;
  }
  size_t str_len;
  napi_get_value_string_utf8(env, arg, NULL, 0, &str_len);
  char str_value[str_len + 1];
  napi_get_value_string_utf8(env, arg, str_value, str_len + 1, NULL);
  return str_value;
}


${functionBodyOut.join('\n')}

#define NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  
  ${functionDefOut.join('\n')}

  return exports;
}
NAPI_MODULE(raylib, Init)

  `
  ]
  return out.join('\n')
}