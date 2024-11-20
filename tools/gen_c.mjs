/*
Here is an example of a struct:

// Return Color object to JavaScript
static napi_value return_color(napi_env env, Color color) {
  napi_value obj, r_val, g_val, b_val, a_val;
  NAPI_CALL(env, napi_create_object(env, &obj));
  NAPI_CALL(env, napi_create_uint32(env, color.r, &r_val));
  NAPI_CALL(env, napi_create_uint32(env, color.g, &g_val));
  NAPI_CALL(env, napi_create_uint32(env, color.b, &b_val));
  NAPI_CALL(env, napi_create_uint32(env, color.a, &a_val));
  NAPI_CALL(env, napi_set_named_property(env, obj, "r", r_val));
  NAPI_CALL(env, napi_set_named_property(env, obj, "g", g_val));
  NAPI_CALL(env, napi_set_named_property(env, obj, "b", b_val));
  NAPI_CALL(env, napi_set_named_property(env, obj, "a", a_val));
  return obj;
}



// get a single Color argument
static Color get_color_arg(napi_value* args, int argNum, napi_env env, napi_callback_info info) {
  Color color = {0, 0, 0, 255};  // Default to black with full alpha

  if (args == NULL) return color;

  // Check if the argument is an object
  napi_valuetype valuetype;
  napi_status status = napi_typeof(env, args[argNum], &valuetype);
  if (status != napi_ok || valuetype != napi_object) {
    return color;
  }

  // Get r value
  napi_value r_value;
  if (napi_get_named_property(env, args[argNum], "r", &r_value) == napi_ok) {
    uint32_t r;
    if (napi_get_value_uint32(env, r_value, &r) == napi_ok) {
      color.r = (unsigned char)r;
    }
  }

  // Get g value
  napi_value g_value;
  if (napi_get_named_property(env, args[argNum], "g", &g_value) == napi_ok) {
    uint32_t g;
    if (napi_get_value_uint32(env, g_value, &g) == napi_ok) {
      color.g = (unsigned char)g;
    }
  }

  // Get b value
  napi_value b_value;
  if (napi_get_named_property(env, args[argNum], "b", &b_value) == napi_ok) {
    uint32_t b;
    if (napi_get_value_uint32(env, b_value, &b) == napi_ok) {
      color.b = (unsigned char)b;
    }
  }

  // Get a value
  napi_value a_value;
  if (napi_get_named_property(env, args[argNum], "a", &a_value) == napi_ok) {
    uint32_t a;
    if (napi_get_value_uint32(env, a_value, &a) == napi_ok) {
      color.a = (unsigned char)a;
    }
  }

  return color;
}



*/

import { readFile  } from 'node:fs/promises'

const typeNames = JSON.parse(await readFile('tools/typeNames.json', 'utf8'))

export default function generateC(version, api) {
  const functionBodyOut = []
  const functionDefOut = []

  functionBodyOut.push(`// Function to test bindings
napi_value NodeRaylibSayHello(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  char* name = get_string_arg(args, 0, env, info);
  free(args);

  char result[127] = {};
  snprintf(result, sizeof(result), "Hello, %s!", name == NULL ? "World" : name);

  return return_string(env, result);
}`)

  functionDefOut.push(`NAPI_CALL(env, napi_create_function(env, "SayHello", NAPI_AUTO_LENGTH, NodeRaylibSayHello, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SayHello", fn));
  `)


  for (const f of api.functions) {
    if (f.name === 'TraceLog') {
      continue
    }
    functionDefOut.push(`  NAPI_CALL(env, napi_create_function(env, "${f.name}", NAPI_AUTO_LENGTH, NodeRaylib${f.name}, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "${f.name}", fn));
    `)
    functionBodyOut.push(`\n// ${f.description}`)
    functionBodyOut.push(`napi_value NodeRaylib${f.name}(napi_env env, napi_callback_info info) {`)

    if (f?.returnType && f.returnType !== 'void') {
      functionBodyOut.push(`  ${f.returnType} ret;`)
    }

    const params = f.params || []
    if (params.length) {
      functionBodyOut.push(`  napi_value* args = get_args(env, info, ${params.length});`)
      let i=0
      for (const { type, name } of params) {
         functionBodyOut.push(`  ${type} ${name} = get_${typeNames[type]}_arg(args, ${i++}, env, info)`)
      }
    }
    if (!f?.returnType || f.returnType === 'void') {
      functionBodyOut.push(`  ${f.name}(${params.map(p => p.name).join(', ')});`)
      functionBodyOut.push(`  return n_undefined;`)
    } else {
      functionBodyOut.push(`  ret=${f.name}(${params.map(p => p.name).join(', ')});`)
      functionBodyOut.push(`  return return_${typeNames[f.returnType]}(ret);`)
    }
    functionBodyOut.push(`}`)
  }


  const out = [
    `// Raylib for nodejs ${version}

#include <node_api.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAPI_CALL(env, call)                               \\
  do {                                                     \\
    napi_status status = (call);                           \\
    if (status != napi_ok) {                               \\
      const napi_extended_error_info* error_info = NULL;   \\
      napi_get_last_error_info((env), &error_info);        \\
      const char* err_message = error_info->error_message; \\
      napi_throw_error((env), NULL, err_message);          \\
      return NULL;                                         \\
    }                                                      \\
  } while (0)

static napi_value n_undefined;
static napi_value n_true;
static napi_value n_false;

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

// Get a single int argument
static int get_int_arg(napi_value* args, int argNum, napi_env env, napi_callback_info info) {
  if (args == NULL) return 0;  // Return 0 as default error value

  napi_valuetype valuetype;
  napi_status status = napi_typeof(env, args[argNum], &valuetype);
  if (status != napi_ok || valuetype != napi_number) {
    // napi_throw_type_error(env, NULL, "Number expected");
    return 0;
  }

  int value;
  status = napi_get_value_int32(env, args[argNum], &value);
  if (status != napi_ok) {
    // napi_throw_error(env, NULL, "Failed to get integer");
    return 0;
  }

  return value;
}

// Return string to JavaScript
static napi_value return_string(napi_env env, const char* str) {
  napi_value return_value;
  NAPI_CALL(env, napi_create_string_utf8(env, str, strlen(str), &return_value));
  return return_value;
}



${functionBodyOut.join('\n')}

static napi_value Init(napi_env env, napi_value exports) {
  // not sure if there are already better imports for this
  napi_get_undefined(env, &n_undefined);
  napi_get_boolean(env, true, &n_true);
  napi_get_boolean(env, false, &n_false);

  napi_value fn;

  ${functionDefOut.join('\n')}

  return exports;
}
NAPI_MODULE(raylib, Init)

  `
  ]
  return out.join('\n')
}
