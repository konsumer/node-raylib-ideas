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

// Function to test bindings
napi_value NodeRaylibSayHello(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  char* name = get_string_arg(args, 0, env, info);
  free(args);

  char result[127] = {};
  snprintf(result, sizeof(result), "Hello, %s!", name == NULL ? "World" : name);

  return return_string(env, result);
}

// Initialize window and OpenGL context
napi_value NodeRaylibInitWindow(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  const char * title = get_string_arg(args, 2, env, info)
  free(args);
  InitWindow(width, height, title);
  return n_undefined;
}

// Close window and unload OpenGL context
napi_value NodeRaylibCloseWindow(napi_env env, napi_callback_info info) {
  CloseWindow();
  return n_undefined;
}

// Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
napi_value NodeRaylibWindowShouldClose(napi_env env, napi_callback_info info) {
  bool ret;
  ret=WindowShouldClose();
  return return_bool(ret);
}

// Check if window has been initialized successfully
napi_value NodeRaylibIsWindowReady(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsWindowReady();
  return return_bool(ret);
}

// Check if window is currently fullscreen
napi_value NodeRaylibIsWindowFullscreen(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsWindowFullscreen();
  return return_bool(ret);
}

// Check if window is currently hidden
napi_value NodeRaylibIsWindowHidden(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsWindowHidden();
  return return_bool(ret);
}

// Check if window is currently minimized
napi_value NodeRaylibIsWindowMinimized(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsWindowMinimized();
  return return_bool(ret);
}

// Check if window is currently maximized
napi_value NodeRaylibIsWindowMaximized(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsWindowMaximized();
  return return_bool(ret);
}

// Check if window is currently focused
napi_value NodeRaylibIsWindowFocused(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsWindowFocused();
  return return_bool(ret);
}

// Check if window has been resized last frame
napi_value NodeRaylibIsWindowResized(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsWindowResized();
  return return_bool(ret);
}

// Check if one specific window flag is enabled
napi_value NodeRaylibIsWindowState(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  unsigned int flag = get_uint_arg(args, 0, env, info)
  free(args);
  ret=IsWindowState(flag);
  return return_bool(ret);
}

// Set window configuration state using flags
napi_value NodeRaylibSetWindowState(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  unsigned int flags = get_uint_arg(args, 0, env, info)
  free(args);
  SetWindowState(flags);
  return n_undefined;
}

// Clear window configuration state flags
napi_value NodeRaylibClearWindowState(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  unsigned int flags = get_uint_arg(args, 0, env, info)
  free(args);
  ClearWindowState(flags);
  return n_undefined;
}

// Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
napi_value NodeRaylibToggleFullscreen(napi_env env, napi_callback_info info) {
  ToggleFullscreen();
  return n_undefined;
}

// Toggle window state: borderless windowed, resizes window to match monitor resolution
napi_value NodeRaylibToggleBorderlessWindowed(napi_env env, napi_callback_info info) {
  ToggleBorderlessWindowed();
  return n_undefined;
}

// Set window state: maximized, if resizable
napi_value NodeRaylibMaximizeWindow(napi_env env, napi_callback_info info) {
  MaximizeWindow();
  return n_undefined;
}

// Set window state: minimized, if resizable
napi_value NodeRaylibMinimizeWindow(napi_env env, napi_callback_info info) {
  MinimizeWindow();
  return n_undefined;
}

// Set window state: not minimized/maximized
napi_value NodeRaylibRestoreWindow(napi_env env, napi_callback_info info) {
  RestoreWindow();
  return n_undefined;
}

// Set icon for window (single image, RGBA 32bit)
napi_value NodeRaylibSetWindowIcon(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image image = get_Image_arg(args, 0, env, info)
  free(args);
  SetWindowIcon(image);
  return n_undefined;
}

// Set icon for window (multiple images, RGBA 32bit)
napi_value NodeRaylibSetWindowIcons(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * images = get_Image_pointer_arg(args, 0, env, info)
  int count = get_int_arg(args, 1, env, info)
  free(args);
  SetWindowIcons(images, count);
  return n_undefined;
}

// Set title for window
napi_value NodeRaylibSetWindowTitle(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  const char * title = get_string_arg(args, 0, env, info)
  free(args);
  SetWindowTitle(title);
  return n_undefined;
}

// Set window position on screen
napi_value NodeRaylibSetWindowPosition(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int x = get_int_arg(args, 0, env, info)
  int y = get_int_arg(args, 1, env, info)
  free(args);
  SetWindowPosition(x, y);
  return n_undefined;
}

// Set monitor for the current window
napi_value NodeRaylibSetWindowMonitor(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  SetWindowMonitor(monitor);
  return n_undefined;
}

// Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
napi_value NodeRaylibSetWindowMinSize(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  free(args);
  SetWindowMinSize(width, height);
  return n_undefined;
}

// Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
napi_value NodeRaylibSetWindowMaxSize(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  free(args);
  SetWindowMaxSize(width, height);
  return n_undefined;
}

// Set window dimensions
napi_value NodeRaylibSetWindowSize(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  free(args);
  SetWindowSize(width, height);
  return n_undefined;
}

// Set window opacity [0.0f..1.0f]
napi_value NodeRaylibSetWindowOpacity(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  float opacity = get_float_arg(args, 0, env, info)
  free(args);
  SetWindowOpacity(opacity);
  return n_undefined;
}

// Set window focused
napi_value NodeRaylibSetWindowFocused(napi_env env, napi_callback_info info) {
  SetWindowFocused();
  return n_undefined;
}

// Get native window handle
napi_value NodeRaylibGetWindowHandle(napi_env env, napi_callback_info info) {
  void * ret;
  ret=GetWindowHandle();
  return return_undefined(ret);
}

// Get current screen width
napi_value NodeRaylibGetScreenWidth(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetScreenWidth();
  return return_int(ret);
}

// Get current screen height
napi_value NodeRaylibGetScreenHeight(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetScreenHeight();
  return return_int(ret);
}

// Get current render width (it considers HiDPI)
napi_value NodeRaylibGetRenderWidth(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetRenderWidth();
  return return_int(ret);
}

// Get current render height (it considers HiDPI)
napi_value NodeRaylibGetRenderHeight(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetRenderHeight();
  return return_int(ret);
}

// Get number of connected monitors
napi_value NodeRaylibGetMonitorCount(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetMonitorCount();
  return return_int(ret);
}

// Get current monitor where window is placed
napi_value NodeRaylibGetCurrentMonitor(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetCurrentMonitor();
  return return_int(ret);
}

// Get specified monitor position
napi_value NodeRaylibGetMonitorPosition(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetMonitorPosition(monitor);
  return return_Vector2(ret);
}

// Get specified monitor width (current video mode used by monitor)
napi_value NodeRaylibGetMonitorWidth(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetMonitorWidth(monitor);
  return return_int(ret);
}

// Get specified monitor height (current video mode used by monitor)
napi_value NodeRaylibGetMonitorHeight(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetMonitorHeight(monitor);
  return return_int(ret);
}

// Get specified monitor physical width in millimetres
napi_value NodeRaylibGetMonitorPhysicalWidth(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetMonitorPhysicalWidth(monitor);
  return return_int(ret);
}

// Get specified monitor physical height in millimetres
napi_value NodeRaylibGetMonitorPhysicalHeight(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetMonitorPhysicalHeight(monitor);
  return return_int(ret);
}

// Get specified monitor refresh rate
napi_value NodeRaylibGetMonitorRefreshRate(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetMonitorRefreshRate(monitor);
  return return_int(ret);
}

// Get window position XY on monitor
napi_value NodeRaylibGetWindowPosition(napi_env env, napi_callback_info info) {
  Vector2 ret;
  ret=GetWindowPosition();
  return return_Vector2(ret);
}

// Get window scale DPI factor
napi_value NodeRaylibGetWindowScaleDPI(napi_env env, napi_callback_info info) {
  Vector2 ret;
  ret=GetWindowScaleDPI();
  return return_Vector2(ret);
}

// Get the human-readable, UTF-8 encoded name of the specified monitor
napi_value NodeRaylibGetMonitorName(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  int monitor = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetMonitorName(monitor);
  return return_string(ret);
}

// Set clipboard text content
napi_value NodeRaylibSetClipboardText(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  SetClipboardText(text);
  return n_undefined;
}

// Get clipboard text content
napi_value NodeRaylibGetClipboardText(napi_env env, napi_callback_info info) {
  const char * ret;
  ret=GetClipboardText();
  return return_string(ret);
}

// Get clipboard image content
napi_value NodeRaylibGetClipboardImage(napi_env env, napi_callback_info info) {
  Image ret;
  ret=GetClipboardImage();
  return return_Image(ret);
}

// Enable waiting for events on EndDrawing(), no automatic event polling
napi_value NodeRaylibEnableEventWaiting(napi_env env, napi_callback_info info) {
  EnableEventWaiting();
  return n_undefined;
}

// Disable waiting for events on EndDrawing(), automatic events polling
napi_value NodeRaylibDisableEventWaiting(napi_env env, napi_callback_info info) {
  DisableEventWaiting();
  return n_undefined;
}

// Shows cursor
napi_value NodeRaylibShowCursor(napi_env env, napi_callback_info info) {
  ShowCursor();
  return n_undefined;
}

// Hides cursor
napi_value NodeRaylibHideCursor(napi_env env, napi_callback_info info) {
  HideCursor();
  return n_undefined;
}

// Check if cursor is not visible
napi_value NodeRaylibIsCursorHidden(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsCursorHidden();
  return return_bool(ret);
}

// Enables cursor (unlock cursor)
napi_value NodeRaylibEnableCursor(napi_env env, napi_callback_info info) {
  EnableCursor();
  return n_undefined;
}

// Disables cursor (lock cursor)
napi_value NodeRaylibDisableCursor(napi_env env, napi_callback_info info) {
  DisableCursor();
  return n_undefined;
}

// Check if cursor is on the screen
napi_value NodeRaylibIsCursorOnScreen(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsCursorOnScreen();
  return return_bool(ret);
}

// Set background color (framebuffer clear color)
napi_value NodeRaylibClearBackground(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Color color = get_Color_arg(args, 0, env, info)
  free(args);
  ClearBackground(color);
  return n_undefined;
}

// Setup canvas (framebuffer) to start drawing
napi_value NodeRaylibBeginDrawing(napi_env env, napi_callback_info info) {
  BeginDrawing();
  return n_undefined;
}

// End canvas drawing and swap buffers (double buffering)
napi_value NodeRaylibEndDrawing(napi_env env, napi_callback_info info) {
  EndDrawing();
  return n_undefined;
}

// Begin 2D mode with custom camera (2D)
napi_value NodeRaylibBeginMode2D(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Camera2D camera = get_Camera2D_arg(args, 0, env, info)
  free(args);
  BeginMode2D(camera);
  return n_undefined;
}

// Ends 2D mode with custom camera
napi_value NodeRaylibEndMode2D(napi_env env, napi_callback_info info) {
  EndMode2D();
  return n_undefined;
}

// Begin 3D mode with custom camera (3D)
napi_value NodeRaylibBeginMode3D(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Camera3D camera = get_Camera3D_arg(args, 0, env, info)
  free(args);
  BeginMode3D(camera);
  return n_undefined;
}

// Ends 3D mode and returns to default 2D orthographic mode
napi_value NodeRaylibEndMode3D(napi_env env, napi_callback_info info) {
  EndMode3D();
  return n_undefined;
}

// Begin drawing to render texture
napi_value NodeRaylibBeginTextureMode(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  RenderTexture2D target = get_RenderTexture2D_arg(args, 0, env, info)
  free(args);
  BeginTextureMode(target);
  return n_undefined;
}

// Ends drawing to render texture
napi_value NodeRaylibEndTextureMode(napi_env env, napi_callback_info info) {
  EndTextureMode();
  return n_undefined;
}

// Begin custom shader drawing
napi_value NodeRaylibBeginShaderMode(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Shader shader = get_Shader_arg(args, 0, env, info)
  free(args);
  BeginShaderMode(shader);
  return n_undefined;
}

// End custom shader drawing (use default shader)
napi_value NodeRaylibEndShaderMode(napi_env env, napi_callback_info info) {
  EndShaderMode();
  return n_undefined;
}

// Begin blending mode (alpha, additive, multiplied, subtract, custom)
napi_value NodeRaylibBeginBlendMode(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int mode = get_int_arg(args, 0, env, info)
  free(args);
  BeginBlendMode(mode);
  return n_undefined;
}

// End blending mode (reset to default: alpha blending)
napi_value NodeRaylibEndBlendMode(napi_env env, napi_callback_info info) {
  EndBlendMode();
  return n_undefined;
}

// Begin scissor mode (define screen area for following drawing)
napi_value NodeRaylibBeginScissorMode(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  int x = get_int_arg(args, 0, env, info)
  int y = get_int_arg(args, 1, env, info)
  int width = get_int_arg(args, 2, env, info)
  int height = get_int_arg(args, 3, env, info)
  free(args);
  BeginScissorMode(x, y, width, height);
  return n_undefined;
}

// End scissor mode
napi_value NodeRaylibEndScissorMode(napi_env env, napi_callback_info info) {
  EndScissorMode();
  return n_undefined;
}

// Begin stereo rendering (requires VR simulator)
napi_value NodeRaylibBeginVrStereoMode(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  VrStereoConfig config = get_VrStereoConfig_arg(args, 0, env, info)
  free(args);
  BeginVrStereoMode(config);
  return n_undefined;
}

// End stereo rendering (requires VR simulator)
napi_value NodeRaylibEndVrStereoMode(napi_env env, napi_callback_info info) {
  EndVrStereoMode();
  return n_undefined;
}

// Load VR stereo config for VR simulator device parameters
napi_value NodeRaylibLoadVrStereoConfig(napi_env env, napi_callback_info info) {
  VrStereoConfig ret;
  napi_value* args = get_args(env, info, 1);
  VrDeviceInfo device = get_VrDeviceInfo_arg(args, 0, env, info)
  free(args);
  ret=LoadVrStereoConfig(device);
  return return_VrStereoConfig(ret);
}

// Unload VR stereo config
napi_value NodeRaylibUnloadVrStereoConfig(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  VrStereoConfig config = get_VrStereoConfig_arg(args, 0, env, info)
  free(args);
  UnloadVrStereoConfig(config);
  return n_undefined;
}

// Load shader from files and bind default locations
napi_value NodeRaylibLoadShader(napi_env env, napi_callback_info info) {
  Shader ret;
  napi_value* args = get_args(env, info, 2);
  const char * vsFileName = get_string_arg(args, 0, env, info)
  const char * fsFileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=LoadShader(vsFileName, fsFileName);
  return return_Shader(ret);
}

// Load shader from code strings and bind default locations
napi_value NodeRaylibLoadShaderFromMemory(napi_env env, napi_callback_info info) {
  Shader ret;
  napi_value* args = get_args(env, info, 2);
  const char * vsCode = get_string_arg(args, 0, env, info)
  const char * fsCode = get_string_arg(args, 1, env, info)
  free(args);
  ret=LoadShaderFromMemory(vsCode, fsCode);
  return return_Shader(ret);
}

// Check if a shader is valid (loaded on GPU)
napi_value NodeRaylibIsShaderValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Shader shader = get_Shader_arg(args, 0, env, info)
  free(args);
  ret=IsShaderValid(shader);
  return return_bool(ret);
}

// Get shader uniform location
napi_value NodeRaylibGetShaderLocation(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  Shader shader = get_Shader_arg(args, 0, env, info)
  const char * uniformName = get_string_arg(args, 1, env, info)
  free(args);
  ret=GetShaderLocation(shader, uniformName);
  return return_int(ret);
}

// Get shader attribute location
napi_value NodeRaylibGetShaderLocationAttrib(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  Shader shader = get_Shader_arg(args, 0, env, info)
  const char * attribName = get_string_arg(args, 1, env, info)
  free(args);
  ret=GetShaderLocationAttrib(shader, attribName);
  return return_int(ret);
}

// Set shader uniform value
napi_value NodeRaylibSetShaderValue(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Shader shader = get_Shader_arg(args, 0, env, info)
  int locIndex = get_int_arg(args, 1, env, info)
  const void * value = get_undefined_arg(args, 2, env, info)
  int uniformType = get_int_arg(args, 3, env, info)
  free(args);
  SetShaderValue(shader, locIndex, value, uniformType);
  return n_undefined;
}

// Set shader uniform value vector
napi_value NodeRaylibSetShaderValueV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Shader shader = get_Shader_arg(args, 0, env, info)
  int locIndex = get_int_arg(args, 1, env, info)
  const void * value = get_undefined_arg(args, 2, env, info)
  int uniformType = get_int_arg(args, 3, env, info)
  int count = get_int_arg(args, 4, env, info)
  free(args);
  SetShaderValueV(shader, locIndex, value, uniformType, count);
  return n_undefined;
}

// Set shader uniform value (matrix 4x4)
napi_value NodeRaylibSetShaderValueMatrix(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Shader shader = get_Shader_arg(args, 0, env, info)
  int locIndex = get_int_arg(args, 1, env, info)
  Matrix mat = get_Matrix_arg(args, 2, env, info)
  free(args);
  SetShaderValueMatrix(shader, locIndex, mat);
  return n_undefined;
}

// Set shader uniform value for texture (sampler2d)
napi_value NodeRaylibSetShaderValueTexture(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Shader shader = get_Shader_arg(args, 0, env, info)
  int locIndex = get_int_arg(args, 1, env, info)
  Texture2D texture = get_Texture2D_arg(args, 2, env, info)
  free(args);
  SetShaderValueTexture(shader, locIndex, texture);
  return n_undefined;
}

// Unload shader from GPU memory (VRAM)
napi_value NodeRaylibUnloadShader(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Shader shader = get_Shader_arg(args, 0, env, info)
  free(args);
  UnloadShader(shader);
  return n_undefined;
}

// Get a ray trace from screen position (i.e mouse)
napi_value NodeRaylibGetScreenToWorldRay(napi_env env, napi_callback_info info) {
  Ray ret;
  napi_value* args = get_args(env, info, 2);
  Vector2 position = get_Vector2_arg(args, 0, env, info)
  Camera camera = get_Camera_arg(args, 1, env, info)
  free(args);
  ret=GetScreenToWorldRay(position, camera);
  return return_Ray(ret);
}

// Get a ray trace from screen position (i.e mouse) in a viewport
napi_value NodeRaylibGetScreenToWorldRayEx(napi_env env, napi_callback_info info) {
  Ray ret;
  napi_value* args = get_args(env, info, 4);
  Vector2 position = get_Vector2_arg(args, 0, env, info)
  Camera camera = get_Camera_arg(args, 1, env, info)
  int width = get_int_arg(args, 2, env, info)
  int height = get_int_arg(args, 3, env, info)
  free(args);
  ret=GetScreenToWorldRayEx(position, camera, width, height);
  return return_Ray(ret);
}

// Get the screen space position for a 3d world space position
napi_value NodeRaylibGetWorldToScreen(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 2);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  Camera camera = get_Camera_arg(args, 1, env, info)
  free(args);
  ret=GetWorldToScreen(position, camera);
  return return_Vector2(ret);
}

// Get size position for a 3d world space position
napi_value NodeRaylibGetWorldToScreenEx(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 4);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  Camera camera = get_Camera_arg(args, 1, env, info)
  int width = get_int_arg(args, 2, env, info)
  int height = get_int_arg(args, 3, env, info)
  free(args);
  ret=GetWorldToScreenEx(position, camera, width, height);
  return return_Vector2(ret);
}

// Get the screen space position for a 2d camera world space position
napi_value NodeRaylibGetWorldToScreen2D(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 2);
  Vector2 position = get_Vector2_arg(args, 0, env, info)
  Camera2D camera = get_Camera2D_arg(args, 1, env, info)
  free(args);
  ret=GetWorldToScreen2D(position, camera);
  return return_Vector2(ret);
}

// Get the world space position for a 2d camera screen space position
napi_value NodeRaylibGetScreenToWorld2D(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 2);
  Vector2 position = get_Vector2_arg(args, 0, env, info)
  Camera2D camera = get_Camera2D_arg(args, 1, env, info)
  free(args);
  ret=GetScreenToWorld2D(position, camera);
  return return_Vector2(ret);
}

// Get camera transform matrix (view matrix)
napi_value NodeRaylibGetCameraMatrix(napi_env env, napi_callback_info info) {
  Matrix ret;
  napi_value* args = get_args(env, info, 1);
  Camera camera = get_Camera_arg(args, 0, env, info)
  free(args);
  ret=GetCameraMatrix(camera);
  return return_Matrix(ret);
}

// Get camera 2d transform matrix
napi_value NodeRaylibGetCameraMatrix2D(napi_env env, napi_callback_info info) {
  Matrix ret;
  napi_value* args = get_args(env, info, 1);
  Camera2D camera = get_Camera2D_arg(args, 0, env, info)
  free(args);
  ret=GetCameraMatrix2D(camera);
  return return_Matrix(ret);
}

// Set target FPS (maximum)
napi_value NodeRaylibSetTargetFPS(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int fps = get_int_arg(args, 0, env, info)
  free(args);
  SetTargetFPS(fps);
  return n_undefined;
}

// Get time in seconds for last frame drawn (delta time)
napi_value NodeRaylibGetFrameTime(napi_env env, napi_callback_info info) {
  float ret;
  ret=GetFrameTime();
  return return_float(ret);
}

// Get elapsed time in seconds since InitWindow()
napi_value NodeRaylibGetTime(napi_env env, napi_callback_info info) {
  double ret;
  ret=GetTime();
  return return_double(ret);
}

// Get current FPS
napi_value NodeRaylibGetFPS(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetFPS();
  return return_int(ret);
}

// Swap back buffer with front buffer (screen drawing)
napi_value NodeRaylibSwapScreenBuffer(napi_env env, napi_callback_info info) {
  SwapScreenBuffer();
  return n_undefined;
}

// Register all input events
napi_value NodeRaylibPollInputEvents(napi_env env, napi_callback_info info) {
  PollInputEvents();
  return n_undefined;
}

// Wait for some time (halt program execution)
napi_value NodeRaylibWaitTime(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  double seconds = get_double_arg(args, 0, env, info)
  free(args);
  WaitTime(seconds);
  return n_undefined;
}

// Set the seed for the random number generator
napi_value NodeRaylibSetRandomSeed(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  unsigned int seed = get_uint_arg(args, 0, env, info)
  free(args);
  SetRandomSeed(seed);
  return n_undefined;
}

// Get a random value between min and max (both included)
napi_value NodeRaylibGetRandomValue(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  int min = get_int_arg(args, 0, env, info)
  int max = get_int_arg(args, 1, env, info)
  free(args);
  ret=GetRandomValue(min, max);
  return return_int(ret);
}

// Load random values sequence, no values repeated
napi_value NodeRaylibLoadRandomSequence(napi_env env, napi_callback_info info) {
  int * ret;
  napi_value* args = get_args(env, info, 3);
  unsigned int count = get_uint_arg(args, 0, env, info)
  int min = get_int_arg(args, 1, env, info)
  int max = get_int_arg(args, 2, env, info)
  free(args);
  ret=LoadRandomSequence(count, min, max);
  return return_int_pointer(ret);
}

// Unload random values sequence
napi_value NodeRaylibUnloadRandomSequence(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int * sequence = get_int_pointer_arg(args, 0, env, info)
  free(args);
  UnloadRandomSequence(sequence);
  return n_undefined;
}

// Takes a screenshot of current screen (filename extension defines format)
napi_value NodeRaylibTakeScreenshot(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  TakeScreenshot(fileName);
  return n_undefined;
}

// Setup init configuration flags (view FLAGS)
napi_value NodeRaylibSetConfigFlags(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  unsigned int flags = get_uint_arg(args, 0, env, info)
  free(args);
  SetConfigFlags(flags);
  return n_undefined;
}

// Open URL with default system browser (if available)
napi_value NodeRaylibOpenURL(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  const char * url = get_string_arg(args, 0, env, info)
  free(args);
  OpenURL(url);
  return n_undefined;
}

// Set the current threshold (minimum) log level
napi_value NodeRaylibSetTraceLogLevel(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int logLevel = get_int_arg(args, 0, env, info)
  free(args);
  SetTraceLogLevel(logLevel);
  return n_undefined;
}

// Internal memory allocator
napi_value NodeRaylibMemAlloc(napi_env env, napi_callback_info info) {
  void * ret;
  napi_value* args = get_args(env, info, 1);
  unsigned int size = get_uint_arg(args, 0, env, info)
  free(args);
  ret=MemAlloc(size);
  return return_undefined(ret);
}

// Internal memory reallocator
napi_value NodeRaylibMemRealloc(napi_env env, napi_callback_info info) {
  void * ret;
  napi_value* args = get_args(env, info, 2);
  void * ptr = get_undefined_arg(args, 0, env, info)
  unsigned int size = get_uint_arg(args, 1, env, info)
  free(args);
  ret=MemRealloc(ptr, size);
  return return_undefined(ret);
}

// Internal memory free
napi_value NodeRaylibMemFree(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  void * ptr = get_undefined_arg(args, 0, env, info)
  free(args);
  MemFree(ptr);
  return n_undefined;
}

// Set custom trace log
napi_value NodeRaylibSetTraceLogCallback(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  TraceLogCallback callback = get_undefined_arg(args, 0, env, info)
  free(args);
  SetTraceLogCallback(callback);
  return n_undefined;
}

// Set custom file binary data loader
napi_value NodeRaylibSetLoadFileDataCallback(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  LoadFileDataCallback callback = get_undefined_arg(args, 0, env, info)
  free(args);
  SetLoadFileDataCallback(callback);
  return n_undefined;
}

// Set custom file binary data saver
napi_value NodeRaylibSetSaveFileDataCallback(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  SaveFileDataCallback callback = get_undefined_arg(args, 0, env, info)
  free(args);
  SetSaveFileDataCallback(callback);
  return n_undefined;
}

// Set custom file text data loader
napi_value NodeRaylibSetLoadFileTextCallback(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  LoadFileTextCallback callback = get_undefined_arg(args, 0, env, info)
  free(args);
  SetLoadFileTextCallback(callback);
  return n_undefined;
}

// Set custom file text data saver
napi_value NodeRaylibSetSaveFileTextCallback(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  SaveFileTextCallback callback = get_undefined_arg(args, 0, env, info)
  free(args);
  SetSaveFileTextCallback(callback);
  return n_undefined;
}

// Load file data as byte array (read)
napi_value NodeRaylibLoadFileData(napi_env env, napi_callback_info info) {
  unsigned char * ret;
  napi_value* args = get_args(env, info, 2);
  const char * fileName = get_string_arg(args, 0, env, info)
  int * dataSize = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=LoadFileData(fileName, dataSize);
  return return_uchar_pointer(ret);
}

// Unload file data allocated by LoadFileData()
napi_value NodeRaylibUnloadFileData(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  free(args);
  UnloadFileData(data);
  return n_undefined;
}

// Save data to file from byte array (write), returns true on success
napi_value NodeRaylibSaveFileData(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 3);
  const char * fileName = get_string_arg(args, 0, env, info)
  void * data = get_undefined_arg(args, 1, env, info)
  int dataSize = get_int_arg(args, 2, env, info)
  free(args);
  ret=SaveFileData(fileName, data, dataSize);
  return return_bool(ret);
}

// Export data to code (.h), returns true on success
napi_value NodeRaylibExportDataAsCode(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 3);
  const unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  int dataSize = get_int_arg(args, 1, env, info)
  const char * fileName = get_string_arg(args, 2, env, info)
  free(args);
  ret=ExportDataAsCode(data, dataSize, fileName);
  return return_bool(ret);
}

// Load text data from file (read), returns a '\0' terminated string
napi_value NodeRaylibLoadFileText(napi_env env, napi_callback_info info) {
  char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadFileText(fileName);
  return return_string(ret);
}

// Unload file text data allocated by LoadFileText()
napi_value NodeRaylibUnloadFileText(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  char * text = get_string_arg(args, 0, env, info)
  free(args);
  UnloadFileText(text);
  return n_undefined;
}

// Save text data to file (write), string must be '\0' terminated, returns true on success
napi_value NodeRaylibSaveFileText(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  const char * fileName = get_string_arg(args, 0, env, info)
  char * text = get_string_arg(args, 1, env, info)
  free(args);
  ret=SaveFileText(fileName, text);
  return return_bool(ret);
}

// Check if file exists
napi_value NodeRaylibFileExists(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=FileExists(fileName);
  return return_bool(ret);
}

// Check if a directory path exists
napi_value NodeRaylibDirectoryExists(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  const char * dirPath = get_string_arg(args, 0, env, info)
  free(args);
  ret=DirectoryExists(dirPath);
  return return_bool(ret);
}

// Check file extension (including point: .png, .wav)
napi_value NodeRaylibIsFileExtension(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  const char * fileName = get_string_arg(args, 0, env, info)
  const char * ext = get_string_arg(args, 1, env, info)
  free(args);
  ret=IsFileExtension(fileName, ext);
  return return_bool(ret);
}

// Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
napi_value NodeRaylibGetFileLength(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetFileLength(fileName);
  return return_int(ret);
}

// Get pointer to extension for a filename string (includes dot: '.png')
napi_value NodeRaylibGetFileExtension(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetFileExtension(fileName);
  return return_string(ret);
}

// Get pointer to filename for a path string
napi_value NodeRaylibGetFileName(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * filePath = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetFileName(filePath);
  return return_string(ret);
}

// Get filename string without extension (uses static string)
napi_value NodeRaylibGetFileNameWithoutExt(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * filePath = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetFileNameWithoutExt(filePath);
  return return_string(ret);
}

// Get full path for a given fileName with path (uses static string)
napi_value NodeRaylibGetDirectoryPath(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * filePath = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetDirectoryPath(filePath);
  return return_string(ret);
}

// Get previous directory path for a given path (uses static string)
napi_value NodeRaylibGetPrevDirectoryPath(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * dirPath = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetPrevDirectoryPath(dirPath);
  return return_string(ret);
}

// Get current working directory (uses static string)
napi_value NodeRaylibGetWorkingDirectory(napi_env env, napi_callback_info info) {
  const char * ret;
  ret=GetWorkingDirectory();
  return return_string(ret);
}

// Get the directory of the running application (uses static string)
napi_value NodeRaylibGetApplicationDirectory(napi_env env, napi_callback_info info) {
  const char * ret;
  ret=GetApplicationDirectory();
  return return_string(ret);
}

// Create directories (including full path requested), returns 0 on success
napi_value NodeRaylibMakeDirectory(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  const char * dirPath = get_string_arg(args, 0, env, info)
  free(args);
  ret=MakeDirectory(dirPath);
  return return_int(ret);
}

// Change working directory, return true on success
napi_value NodeRaylibChangeDirectory(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  const char * dir = get_string_arg(args, 0, env, info)
  free(args);
  ret=ChangeDirectory(dir);
  return return_bool(ret);
}

// Check if a given path is a file or a directory
napi_value NodeRaylibIsPathFile(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  const char * path = get_string_arg(args, 0, env, info)
  free(args);
  ret=IsPathFile(path);
  return return_bool(ret);
}

// Check if fileName is valid for the platform/OS
napi_value NodeRaylibIsFileNameValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=IsFileNameValid(fileName);
  return return_bool(ret);
}

// Load directory filepaths
napi_value NodeRaylibLoadDirectoryFiles(napi_env env, napi_callback_info info) {
  FilePathList ret;
  napi_value* args = get_args(env, info, 1);
  const char * dirPath = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadDirectoryFiles(dirPath);
  return return_FilePathList(ret);
}

// Load directory filepaths with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result
napi_value NodeRaylibLoadDirectoryFilesEx(napi_env env, napi_callback_info info) {
  FilePathList ret;
  napi_value* args = get_args(env, info, 3);
  const char * basePath = get_string_arg(args, 0, env, info)
  const char * filter = get_string_arg(args, 1, env, info)
  bool scanSubdirs = get_bool_arg(args, 2, env, info)
  free(args);
  ret=LoadDirectoryFilesEx(basePath, filter, scanSubdirs);
  return return_FilePathList(ret);
}

// Unload filepaths
napi_value NodeRaylibUnloadDirectoryFiles(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  FilePathList files = get_FilePathList_arg(args, 0, env, info)
  free(args);
  UnloadDirectoryFiles(files);
  return n_undefined;
}

// Check if a file has been dropped into window
napi_value NodeRaylibIsFileDropped(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsFileDropped();
  return return_bool(ret);
}

// Load dropped filepaths
napi_value NodeRaylibLoadDroppedFiles(napi_env env, napi_callback_info info) {
  FilePathList ret;
  ret=LoadDroppedFiles();
  return return_FilePathList(ret);
}

// Unload dropped filepaths
napi_value NodeRaylibUnloadDroppedFiles(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  FilePathList files = get_FilePathList_arg(args, 0, env, info)
  free(args);
  UnloadDroppedFiles(files);
  return n_undefined;
}

// Get file modification time (last write time)
napi_value NodeRaylibGetFileModTime(napi_env env, napi_callback_info info) {
  long ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetFileModTime(fileName);
  return return_long(ret);
}

// Compress data (DEFLATE algorithm), memory must be MemFree()
napi_value NodeRaylibCompressData(napi_env env, napi_callback_info info) {
  unsigned char * ret;
  napi_value* args = get_args(env, info, 3);
  const unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  int dataSize = get_int_arg(args, 1, env, info)
  int * compDataSize = get_int_pointer_arg(args, 2, env, info)
  free(args);
  ret=CompressData(data, dataSize, compDataSize);
  return return_uchar_pointer(ret);
}

// Decompress data (DEFLATE algorithm), memory must be MemFree()
napi_value NodeRaylibDecompressData(napi_env env, napi_callback_info info) {
  unsigned char * ret;
  napi_value* args = get_args(env, info, 3);
  const unsigned char * compData = get_uchar_pointer_arg(args, 0, env, info)
  int compDataSize = get_int_arg(args, 1, env, info)
  int * dataSize = get_int_pointer_arg(args, 2, env, info)
  free(args);
  ret=DecompressData(compData, compDataSize, dataSize);
  return return_uchar_pointer(ret);
}

// Encode data to Base64 string, memory must be MemFree()
napi_value NodeRaylibEncodeDataBase64(napi_env env, napi_callback_info info) {
  char * ret;
  napi_value* args = get_args(env, info, 3);
  const unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  int dataSize = get_int_arg(args, 1, env, info)
  int * outputSize = get_int_pointer_arg(args, 2, env, info)
  free(args);
  ret=EncodeDataBase64(data, dataSize, outputSize);
  return return_string(ret);
}

// Decode Base64 string data, memory must be MemFree()
napi_value NodeRaylibDecodeDataBase64(napi_env env, napi_callback_info info) {
  unsigned char * ret;
  napi_value* args = get_args(env, info, 2);
  const unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  int * outputSize = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=DecodeDataBase64(data, outputSize);
  return return_uchar_pointer(ret);
}

// Compute CRC32 hash code
napi_value NodeRaylibComputeCRC32(napi_env env, napi_callback_info info) {
  unsigned int ret;
  napi_value* args = get_args(env, info, 2);
  unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  int dataSize = get_int_arg(args, 1, env, info)
  free(args);
  ret=ComputeCRC32(data, dataSize);
  return return_uint(ret);
}

// Compute MD5 hash code, returns static int[4] (16 bytes)
napi_value NodeRaylibComputeMD5(napi_env env, napi_callback_info info) {
  unsigned int * ret;
  napi_value* args = get_args(env, info, 2);
  unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  int dataSize = get_int_arg(args, 1, env, info)
  free(args);
  ret=ComputeMD5(data, dataSize);
  return return_uint_pointer(ret);
}

// Compute SHA1 hash code, returns static int[5] (20 bytes)
napi_value NodeRaylibComputeSHA1(napi_env env, napi_callback_info info) {
  unsigned int * ret;
  napi_value* args = get_args(env, info, 2);
  unsigned char * data = get_uchar_pointer_arg(args, 0, env, info)
  int dataSize = get_int_arg(args, 1, env, info)
  free(args);
  ret=ComputeSHA1(data, dataSize);
  return return_uint_pointer(ret);
}

// Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
napi_value NodeRaylibLoadAutomationEventList(napi_env env, napi_callback_info info) {
  AutomationEventList ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadAutomationEventList(fileName);
  return return_AutomationEventList(ret);
}

// Unload automation events list from file
napi_value NodeRaylibUnloadAutomationEventList(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AutomationEventList list = get_AutomationEventList_arg(args, 0, env, info)
  free(args);
  UnloadAutomationEventList(list);
  return n_undefined;
}

// Export automation events list as text file
napi_value NodeRaylibExportAutomationEventList(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  AutomationEventList list = get_AutomationEventList_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportAutomationEventList(list, fileName);
  return return_bool(ret);
}

// Set automation event list to record to
napi_value NodeRaylibSetAutomationEventList(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AutomationEventList * list = get_AutomationEventList_pointer_arg(args, 0, env, info)
  free(args);
  SetAutomationEventList(list);
  return n_undefined;
}

// Set automation event internal base frame to start recording
napi_value NodeRaylibSetAutomationEventBaseFrame(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int frame = get_int_arg(args, 0, env, info)
  free(args);
  SetAutomationEventBaseFrame(frame);
  return n_undefined;
}

// Start recording automation events (AutomationEventList must be set)
napi_value NodeRaylibStartAutomationEventRecording(napi_env env, napi_callback_info info) {
  StartAutomationEventRecording();
  return n_undefined;
}

// Stop recording automation events
napi_value NodeRaylibStopAutomationEventRecording(napi_env env, napi_callback_info info) {
  StopAutomationEventRecording();
  return n_undefined;
}

// Play a recorded automation event
napi_value NodeRaylibPlayAutomationEvent(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AutomationEvent event = get_AutomationEvent_arg(args, 0, env, info)
  free(args);
  PlayAutomationEvent(event);
  return n_undefined;
}

// Check if a key has been pressed once
napi_value NodeRaylibIsKeyPressed(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int key = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsKeyPressed(key);
  return return_bool(ret);
}

// Check if a key has been pressed again
napi_value NodeRaylibIsKeyPressedRepeat(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int key = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsKeyPressedRepeat(key);
  return return_bool(ret);
}

// Check if a key is being pressed
napi_value NodeRaylibIsKeyDown(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int key = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsKeyDown(key);
  return return_bool(ret);
}

// Check if a key has been released once
napi_value NodeRaylibIsKeyReleased(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int key = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsKeyReleased(key);
  return return_bool(ret);
}

// Check if a key is NOT being pressed
napi_value NodeRaylibIsKeyUp(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int key = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsKeyUp(key);
  return return_bool(ret);
}

// Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
napi_value NodeRaylibGetKeyPressed(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetKeyPressed();
  return return_int(ret);
}

// Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
napi_value NodeRaylibGetCharPressed(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetCharPressed();
  return return_int(ret);
}

// Set a custom key to exit program (default is ESC)
napi_value NodeRaylibSetExitKey(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int key = get_int_arg(args, 0, env, info)
  free(args);
  SetExitKey(key);
  return n_undefined;
}

// Check if a gamepad is available
napi_value NodeRaylibIsGamepadAvailable(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int gamepad = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsGamepadAvailable(gamepad);
  return return_bool(ret);
}

// Get gamepad internal name id
napi_value NodeRaylibGetGamepadName(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  int gamepad = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetGamepadName(gamepad);
  return return_string(ret);
}

// Check if a gamepad button has been pressed once
napi_value NodeRaylibIsGamepadButtonPressed(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  int gamepad = get_int_arg(args, 0, env, info)
  int button = get_int_arg(args, 1, env, info)
  free(args);
  ret=IsGamepadButtonPressed(gamepad, button);
  return return_bool(ret);
}

// Check if a gamepad button is being pressed
napi_value NodeRaylibIsGamepadButtonDown(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  int gamepad = get_int_arg(args, 0, env, info)
  int button = get_int_arg(args, 1, env, info)
  free(args);
  ret=IsGamepadButtonDown(gamepad, button);
  return return_bool(ret);
}

// Check if a gamepad button has been released once
napi_value NodeRaylibIsGamepadButtonReleased(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  int gamepad = get_int_arg(args, 0, env, info)
  int button = get_int_arg(args, 1, env, info)
  free(args);
  ret=IsGamepadButtonReleased(gamepad, button);
  return return_bool(ret);
}

// Check if a gamepad button is NOT being pressed
napi_value NodeRaylibIsGamepadButtonUp(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  int gamepad = get_int_arg(args, 0, env, info)
  int button = get_int_arg(args, 1, env, info)
  free(args);
  ret=IsGamepadButtonUp(gamepad, button);
  return return_bool(ret);
}

// Get the last gamepad button pressed
napi_value NodeRaylibGetGamepadButtonPressed(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetGamepadButtonPressed();
  return return_int(ret);
}

// Get gamepad axis count for a gamepad
napi_value NodeRaylibGetGamepadAxisCount(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  int gamepad = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetGamepadAxisCount(gamepad);
  return return_int(ret);
}

// Get axis movement value for a gamepad axis
napi_value NodeRaylibGetGamepadAxisMovement(napi_env env, napi_callback_info info) {
  float ret;
  napi_value* args = get_args(env, info, 2);
  int gamepad = get_int_arg(args, 0, env, info)
  int axis = get_int_arg(args, 1, env, info)
  free(args);
  ret=GetGamepadAxisMovement(gamepad, axis);
  return return_float(ret);
}

// Set internal gamepad mappings (SDL_GameControllerDB)
napi_value NodeRaylibSetGamepadMappings(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  const char * mappings = get_string_arg(args, 0, env, info)
  free(args);
  ret=SetGamepadMappings(mappings);
  return return_int(ret);
}

// Set gamepad vibration for both motors (duration in seconds)
napi_value NodeRaylibSetGamepadVibration(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  int gamepad = get_int_arg(args, 0, env, info)
  float leftMotor = get_float_arg(args, 1, env, info)
  float rightMotor = get_float_arg(args, 2, env, info)
  float duration = get_float_arg(args, 3, env, info)
  free(args);
  SetGamepadVibration(gamepad, leftMotor, rightMotor, duration);
  return n_undefined;
}

// Check if a mouse button has been pressed once
napi_value NodeRaylibIsMouseButtonPressed(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int button = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsMouseButtonPressed(button);
  return return_bool(ret);
}

// Check if a mouse button is being pressed
napi_value NodeRaylibIsMouseButtonDown(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int button = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsMouseButtonDown(button);
  return return_bool(ret);
}

// Check if a mouse button has been released once
napi_value NodeRaylibIsMouseButtonReleased(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int button = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsMouseButtonReleased(button);
  return return_bool(ret);
}

// Check if a mouse button is NOT being pressed
napi_value NodeRaylibIsMouseButtonUp(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  int button = get_int_arg(args, 0, env, info)
  free(args);
  ret=IsMouseButtonUp(button);
  return return_bool(ret);
}

// Get mouse position X
napi_value NodeRaylibGetMouseX(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetMouseX();
  return return_int(ret);
}

// Get mouse position Y
napi_value NodeRaylibGetMouseY(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetMouseY();
  return return_int(ret);
}

// Get mouse position XY
napi_value NodeRaylibGetMousePosition(napi_env env, napi_callback_info info) {
  Vector2 ret;
  ret=GetMousePosition();
  return return_Vector2(ret);
}

// Get mouse delta between frames
napi_value NodeRaylibGetMouseDelta(napi_env env, napi_callback_info info) {
  Vector2 ret;
  ret=GetMouseDelta();
  return return_Vector2(ret);
}

// Set mouse position XY
napi_value NodeRaylibSetMousePosition(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int x = get_int_arg(args, 0, env, info)
  int y = get_int_arg(args, 1, env, info)
  free(args);
  SetMousePosition(x, y);
  return n_undefined;
}

// Set mouse offset
napi_value NodeRaylibSetMouseOffset(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int offsetX = get_int_arg(args, 0, env, info)
  int offsetY = get_int_arg(args, 1, env, info)
  free(args);
  SetMouseOffset(offsetX, offsetY);
  return n_undefined;
}

// Set mouse scaling
napi_value NodeRaylibSetMouseScale(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  float scaleX = get_float_arg(args, 0, env, info)
  float scaleY = get_float_arg(args, 1, env, info)
  free(args);
  SetMouseScale(scaleX, scaleY);
  return n_undefined;
}

// Get mouse wheel movement for X or Y, whichever is larger
napi_value NodeRaylibGetMouseWheelMove(napi_env env, napi_callback_info info) {
  float ret;
  ret=GetMouseWheelMove();
  return return_float(ret);
}

// Get mouse wheel movement for both X and Y
napi_value NodeRaylibGetMouseWheelMoveV(napi_env env, napi_callback_info info) {
  Vector2 ret;
  ret=GetMouseWheelMoveV();
  return return_Vector2(ret);
}

// Set mouse cursor
napi_value NodeRaylibSetMouseCursor(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int cursor = get_int_arg(args, 0, env, info)
  free(args);
  SetMouseCursor(cursor);
  return n_undefined;
}

// Get touch position X for touch point 0 (relative to screen size)
napi_value NodeRaylibGetTouchX(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetTouchX();
  return return_int(ret);
}

// Get touch position Y for touch point 0 (relative to screen size)
napi_value NodeRaylibGetTouchY(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetTouchY();
  return return_int(ret);
}

// Get touch position XY for a touch point index (relative to screen size)
napi_value NodeRaylibGetTouchPosition(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 1);
  int index = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetTouchPosition(index);
  return return_Vector2(ret);
}

// Get touch point identifier for given index
napi_value NodeRaylibGetTouchPointId(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  int index = get_int_arg(args, 0, env, info)
  free(args);
  ret=GetTouchPointId(index);
  return return_int(ret);
}

// Get number of touch points
napi_value NodeRaylibGetTouchPointCount(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetTouchPointCount();
  return return_int(ret);
}

// Enable a set of gestures using flags
napi_value NodeRaylibSetGesturesEnabled(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  unsigned int flags = get_uint_arg(args, 0, env, info)
  free(args);
  SetGesturesEnabled(flags);
  return n_undefined;
}

// Check if a gesture have been detected
napi_value NodeRaylibIsGestureDetected(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  unsigned int gesture = get_uint_arg(args, 0, env, info)
  free(args);
  ret=IsGestureDetected(gesture);
  return return_bool(ret);
}

// Get latest detected gesture
napi_value NodeRaylibGetGestureDetected(napi_env env, napi_callback_info info) {
  int ret;
  ret=GetGestureDetected();
  return return_int(ret);
}

// Get gesture hold time in seconds
napi_value NodeRaylibGetGestureHoldDuration(napi_env env, napi_callback_info info) {
  float ret;
  ret=GetGestureHoldDuration();
  return return_float(ret);
}

// Get gesture drag vector
napi_value NodeRaylibGetGestureDragVector(napi_env env, napi_callback_info info) {
  Vector2 ret;
  ret=GetGestureDragVector();
  return return_Vector2(ret);
}

// Get gesture drag angle
napi_value NodeRaylibGetGestureDragAngle(napi_env env, napi_callback_info info) {
  float ret;
  ret=GetGestureDragAngle();
  return return_float(ret);
}

// Get gesture pinch delta
napi_value NodeRaylibGetGesturePinchVector(napi_env env, napi_callback_info info) {
  Vector2 ret;
  ret=GetGesturePinchVector();
  return return_Vector2(ret);
}

// Get gesture pinch angle
napi_value NodeRaylibGetGesturePinchAngle(napi_env env, napi_callback_info info) {
  float ret;
  ret=GetGesturePinchAngle();
  return return_float(ret);
}

// Update camera position for selected mode
napi_value NodeRaylibUpdateCamera(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Camera * camera = get_Camera_pointer_arg(args, 0, env, info)
  int mode = get_int_arg(args, 1, env, info)
  free(args);
  UpdateCamera(camera, mode);
  return n_undefined;
}

// Update camera movement/rotation
napi_value NodeRaylibUpdateCameraPro(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Camera * camera = get_Camera_pointer_arg(args, 0, env, info)
  Vector3 movement = get_Vector3_arg(args, 1, env, info)
  Vector3 rotation = get_Vector3_arg(args, 2, env, info)
  float zoom = get_float_arg(args, 3, env, info)
  free(args);
  UpdateCameraPro(camera, movement, rotation, zoom);
  return n_undefined;
}

// Set texture and rectangle to be used on shapes drawing
napi_value NodeRaylibSetShapesTexture(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  Rectangle source = get_Rectangle_arg(args, 1, env, info)
  free(args);
  SetShapesTexture(texture, source);
  return n_undefined;
}

// Get texture that is used for shapes drawing
napi_value NodeRaylibGetShapesTexture(napi_env env, napi_callback_info info) {
  Texture2D ret;
  ret=GetShapesTexture();
  return return_Texture2D(ret);
}

// Get texture source rectangle that is used for shapes drawing
napi_value NodeRaylibGetShapesTextureRectangle(napi_env env, napi_callback_info info) {
  Rectangle ret;
  ret=GetShapesTextureRectangle();
  return return_Rectangle(ret);
}

// Draw a pixel using geometry [Can be slow, use with care]
napi_value NodeRaylibDrawPixel(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  int posX = get_int_arg(args, 0, env, info)
  int posY = get_int_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawPixel(posX, posY, color);
  return n_undefined;
}

// Draw a pixel using geometry (Vector version) [Can be slow, use with care]
napi_value NodeRaylibDrawPixelV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Vector2 position = get_Vector2_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  free(args);
  DrawPixelV(position, color);
  return n_undefined;
}

// Draw a line
napi_value NodeRaylibDrawLine(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  int startPosX = get_int_arg(args, 0, env, info)
  int startPosY = get_int_arg(args, 1, env, info)
  int endPosX = get_int_arg(args, 2, env, info)
  int endPosY = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawLine(startPosX, startPosY, endPosX, endPosY, color);
  return n_undefined;
}

// Draw a line (using gl lines)
napi_value NodeRaylibDrawLineV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector2 startPos = get_Vector2_arg(args, 0, env, info)
  Vector2 endPos = get_Vector2_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawLineV(startPos, endPos, color);
  return n_undefined;
}

// Draw a line (using triangles/quads)
napi_value NodeRaylibDrawLineEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Vector2 startPos = get_Vector2_arg(args, 0, env, info)
  Vector2 endPos = get_Vector2_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawLineEx(startPos, endPos, thick, color);
  return n_undefined;
}

// Draw lines sequence (using gl lines)
napi_value NodeRaylibDrawLineStrip(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawLineStrip(points, pointCount, color);
  return n_undefined;
}

// Draw line segment cubic-bezier in-out interpolation
napi_value NodeRaylibDrawLineBezier(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Vector2 startPos = get_Vector2_arg(args, 0, env, info)
  Vector2 endPos = get_Vector2_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawLineBezier(startPos, endPos, thick, color);
  return n_undefined;
}

// Draw a color-filled circle
napi_value NodeRaylibDrawCircle(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  int centerX = get_int_arg(args, 0, env, info)
  int centerY = get_int_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawCircle(centerX, centerY, radius, color);
  return n_undefined;
}

// Draw a piece of a circle
napi_value NodeRaylibDrawCircleSector(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  float startAngle = get_float_arg(args, 2, env, info)
  float endAngle = get_float_arg(args, 3, env, info)
  int segments = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
  return n_undefined;
}

// Draw circle sector outline
napi_value NodeRaylibDrawCircleSectorLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  float startAngle = get_float_arg(args, 2, env, info)
  float endAngle = get_float_arg(args, 3, env, info)
  int segments = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
  return n_undefined;
}

// Draw a gradient-filled circle
napi_value NodeRaylibDrawCircleGradient(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  int centerX = get_int_arg(args, 0, env, info)
  int centerY = get_int_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  Color inner = get_Color_arg(args, 3, env, info)
  Color outer = get_Color_arg(args, 4, env, info)
  free(args);
  DrawCircleGradient(centerX, centerY, radius, inner, outer);
  return n_undefined;
}

// Draw a color-filled circle (Vector version)
napi_value NodeRaylibDrawCircleV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawCircleV(center, radius, color);
  return n_undefined;
}

// Draw circle outline
napi_value NodeRaylibDrawCircleLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  int centerX = get_int_arg(args, 0, env, info)
  int centerY = get_int_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawCircleLines(centerX, centerY, radius, color);
  return n_undefined;
}

// Draw circle outline (Vector version)
napi_value NodeRaylibDrawCircleLinesV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawCircleLinesV(center, radius, color);
  return n_undefined;
}

// Draw ellipse
napi_value NodeRaylibDrawEllipse(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  int centerX = get_int_arg(args, 0, env, info)
  int centerY = get_int_arg(args, 1, env, info)
  float radiusH = get_float_arg(args, 2, env, info)
  float radiusV = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawEllipse(centerX, centerY, radiusH, radiusV, color);
  return n_undefined;
}

// Draw ellipse outline
napi_value NodeRaylibDrawEllipseLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  int centerX = get_int_arg(args, 0, env, info)
  int centerY = get_int_arg(args, 1, env, info)
  float radiusH = get_float_arg(args, 2, env, info)
  float radiusV = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
  return n_undefined;
}

// Draw ring
napi_value NodeRaylibDrawRing(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 7);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float innerRadius = get_float_arg(args, 1, env, info)
  float outerRadius = get_float_arg(args, 2, env, info)
  float startAngle = get_float_arg(args, 3, env, info)
  float endAngle = get_float_arg(args, 4, env, info)
  int segments = get_int_arg(args, 5, env, info)
  Color color = get_Color_arg(args, 6, env, info)
  free(args);
  DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
  return n_undefined;
}

// Draw ring outline
napi_value NodeRaylibDrawRingLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 7);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float innerRadius = get_float_arg(args, 1, env, info)
  float outerRadius = get_float_arg(args, 2, env, info)
  float startAngle = get_float_arg(args, 3, env, info)
  float endAngle = get_float_arg(args, 4, env, info)
  int segments = get_int_arg(args, 5, env, info)
  Color color = get_Color_arg(args, 6, env, info)
  free(args);
  DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
  return n_undefined;
}

// Draw a color-filled rectangle
napi_value NodeRaylibDrawRectangle(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  int posX = get_int_arg(args, 0, env, info)
  int posY = get_int_arg(args, 1, env, info)
  int width = get_int_arg(args, 2, env, info)
  int height = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawRectangle(posX, posY, width, height, color);
  return n_undefined;
}

// Draw a color-filled rectangle (Vector version)
napi_value NodeRaylibDrawRectangleV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector2 position = get_Vector2_arg(args, 0, env, info)
  Vector2 size = get_Vector2_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawRectangleV(position, size, color);
  return n_undefined;
}

// Draw a color-filled rectangle
napi_value NodeRaylibDrawRectangleRec(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Rectangle rec = get_Rectangle_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  free(args);
  DrawRectangleRec(rec, color);
  return n_undefined;
}

// Draw a color-filled rectangle with pro parameters
napi_value NodeRaylibDrawRectanglePro(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Rectangle rec = get_Rectangle_arg(args, 0, env, info)
  Vector2 origin = get_Vector2_arg(args, 1, env, info)
  float rotation = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawRectanglePro(rec, origin, rotation, color);
  return n_undefined;
}

// Draw a vertical-gradient-filled rectangle
napi_value NodeRaylibDrawRectangleGradientV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  int posX = get_int_arg(args, 0, env, info)
  int posY = get_int_arg(args, 1, env, info)
  int width = get_int_arg(args, 2, env, info)
  int height = get_int_arg(args, 3, env, info)
  Color top = get_Color_arg(args, 4, env, info)
  Color bottom = get_Color_arg(args, 5, env, info)
  free(args);
  DrawRectangleGradientV(posX, posY, width, height, top, bottom);
  return n_undefined;
}

// Draw a horizontal-gradient-filled rectangle
napi_value NodeRaylibDrawRectangleGradientH(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  int posX = get_int_arg(args, 0, env, info)
  int posY = get_int_arg(args, 1, env, info)
  int width = get_int_arg(args, 2, env, info)
  int height = get_int_arg(args, 3, env, info)
  Color left = get_Color_arg(args, 4, env, info)
  Color right = get_Color_arg(args, 5, env, info)
  free(args);
  DrawRectangleGradientH(posX, posY, width, height, left, right);
  return n_undefined;
}

// Draw a gradient-filled rectangle with custom vertex colors
napi_value NodeRaylibDrawRectangleGradientEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Rectangle rec = get_Rectangle_arg(args, 0, env, info)
  Color topLeft = get_Color_arg(args, 1, env, info)
  Color bottomLeft = get_Color_arg(args, 2, env, info)
  Color topRight = get_Color_arg(args, 3, env, info)
  Color bottomRight = get_Color_arg(args, 4, env, info)
  free(args);
  DrawRectangleGradientEx(rec, topLeft, bottomLeft, topRight, bottomRight);
  return n_undefined;
}

// Draw rectangle outline
napi_value NodeRaylibDrawRectangleLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  int posX = get_int_arg(args, 0, env, info)
  int posY = get_int_arg(args, 1, env, info)
  int width = get_int_arg(args, 2, env, info)
  int height = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawRectangleLines(posX, posY, width, height, color);
  return n_undefined;
}

// Draw rectangle outline with extended parameters
napi_value NodeRaylibDrawRectangleLinesEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Rectangle rec = get_Rectangle_arg(args, 0, env, info)
  float lineThick = get_float_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawRectangleLinesEx(rec, lineThick, color);
  return n_undefined;
}

// Draw rectangle with rounded edges
napi_value NodeRaylibDrawRectangleRounded(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Rectangle rec = get_Rectangle_arg(args, 0, env, info)
  float roundness = get_float_arg(args, 1, env, info)
  int segments = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawRectangleRounded(rec, roundness, segments, color);
  return n_undefined;
}

// Draw rectangle lines with rounded edges
napi_value NodeRaylibDrawRectangleRoundedLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Rectangle rec = get_Rectangle_arg(args, 0, env, info)
  float roundness = get_float_arg(args, 1, env, info)
  int segments = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawRectangleRoundedLines(rec, roundness, segments, color);
  return n_undefined;
}

// Draw rectangle with rounded edges outline
napi_value NodeRaylibDrawRectangleRoundedLinesEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Rectangle rec = get_Rectangle_arg(args, 0, env, info)
  float roundness = get_float_arg(args, 1, env, info)
  int segments = get_int_arg(args, 2, env, info)
  float lineThick = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawRectangleRoundedLinesEx(rec, roundness, segments, lineThick, color);
  return n_undefined;
}

// Draw a color-filled triangle (vertex in counter-clockwise order!)
napi_value NodeRaylibDrawTriangle(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Vector2 v1 = get_Vector2_arg(args, 0, env, info)
  Vector2 v2 = get_Vector2_arg(args, 1, env, info)
  Vector2 v3 = get_Vector2_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawTriangle(v1, v2, v3, color);
  return n_undefined;
}

// Draw triangle outline (vertex in counter-clockwise order!)
napi_value NodeRaylibDrawTriangleLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Vector2 v1 = get_Vector2_arg(args, 0, env, info)
  Vector2 v2 = get_Vector2_arg(args, 1, env, info)
  Vector2 v3 = get_Vector2_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawTriangleLines(v1, v2, v3, color);
  return n_undefined;
}

// Draw a triangle fan defined by points (first vertex is the center)
napi_value NodeRaylibDrawTriangleFan(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawTriangleFan(points, pointCount, color);
  return n_undefined;
}

// Draw a triangle strip defined by points
napi_value NodeRaylibDrawTriangleStrip(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawTriangleStrip(points, pointCount, color);
  return n_undefined;
}

// Draw a regular polygon (Vector version)
napi_value NodeRaylibDrawPoly(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  int sides = get_int_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  float rotation = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawPoly(center, sides, radius, rotation, color);
  return n_undefined;
}

// Draw a polygon outline of n sides
napi_value NodeRaylibDrawPolyLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  int sides = get_int_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  float rotation = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawPolyLines(center, sides, radius, rotation, color);
  return n_undefined;
}

// Draw a polygon outline of n sides with extended parameters
napi_value NodeRaylibDrawPolyLinesEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  int sides = get_int_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  float rotation = get_float_arg(args, 3, env, info)
  float lineThick = get_float_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
  return n_undefined;
}

// Draw spline: Linear, minimum 2 points
napi_value NodeRaylibDrawSplineLinear(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawSplineLinear(points, pointCount, thick, color);
  return n_undefined;
}

// Draw spline: B-Spline, minimum 4 points
napi_value NodeRaylibDrawSplineBasis(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawSplineBasis(points, pointCount, thick, color);
  return n_undefined;
}

// Draw spline: Catmull-Rom, minimum 4 points
napi_value NodeRaylibDrawSplineCatmullRom(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawSplineCatmullRom(points, pointCount, thick, color);
  return n_undefined;
}

// Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
napi_value NodeRaylibDrawSplineBezierQuadratic(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawSplineBezierQuadratic(points, pointCount, thick, color);
  return n_undefined;
}

// Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
napi_value NodeRaylibDrawSplineBezierCubic(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  const Vector2 * points = get_Vector2_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawSplineBezierCubic(points, pointCount, thick, color);
  return n_undefined;
}

// Draw spline segment: Linear, 2 points
napi_value NodeRaylibDrawSplineSegmentLinear(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 p2 = get_Vector2_arg(args, 1, env, info)
  float thick = get_float_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawSplineSegmentLinear(p1, p2, thick, color);
  return n_undefined;
}

// Draw spline segment: B-Spline, 4 points
napi_value NodeRaylibDrawSplineSegmentBasis(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 p2 = get_Vector2_arg(args, 1, env, info)
  Vector2 p3 = get_Vector2_arg(args, 2, env, info)
  Vector2 p4 = get_Vector2_arg(args, 3, env, info)
  float thick = get_float_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
  return n_undefined;
}

// Draw spline segment: Catmull-Rom, 4 points
napi_value NodeRaylibDrawSplineSegmentCatmullRom(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 p2 = get_Vector2_arg(args, 1, env, info)
  Vector2 p3 = get_Vector2_arg(args, 2, env, info)
  Vector2 p4 = get_Vector2_arg(args, 3, env, info)
  float thick = get_float_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
  return n_undefined;
}

// Draw spline segment: Quadratic Bezier, 2 points, 1 control point
napi_value NodeRaylibDrawSplineSegmentBezierQuadratic(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 c2 = get_Vector2_arg(args, 1, env, info)
  Vector2 p3 = get_Vector2_arg(args, 2, env, info)
  float thick = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color);
  return n_undefined;
}

// Draw spline segment: Cubic Bezier, 2 points, 2 control points
napi_value NodeRaylibDrawSplineSegmentBezierCubic(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 c2 = get_Vector2_arg(args, 1, env, info)
  Vector2 c3 = get_Vector2_arg(args, 2, env, info)
  Vector2 p4 = get_Vector2_arg(args, 3, env, info)
  float thick = get_float_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color);
  return n_undefined;
}

// Get (evaluate) spline point: Linear
napi_value NodeRaylibGetSplinePointLinear(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 3);
  Vector2 startPos = get_Vector2_arg(args, 0, env, info)
  Vector2 endPos = get_Vector2_arg(args, 1, env, info)
  float t = get_float_arg(args, 2, env, info)
  free(args);
  ret=GetSplinePointLinear(startPos, endPos, t);
  return return_Vector2(ret);
}

// Get (evaluate) spline point: B-Spline
napi_value NodeRaylibGetSplinePointBasis(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 5);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 p2 = get_Vector2_arg(args, 1, env, info)
  Vector2 p3 = get_Vector2_arg(args, 2, env, info)
  Vector2 p4 = get_Vector2_arg(args, 3, env, info)
  float t = get_float_arg(args, 4, env, info)
  free(args);
  ret=GetSplinePointBasis(p1, p2, p3, p4, t);
  return return_Vector2(ret);
}

// Get (evaluate) spline point: Catmull-Rom
napi_value NodeRaylibGetSplinePointCatmullRom(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 5);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 p2 = get_Vector2_arg(args, 1, env, info)
  Vector2 p3 = get_Vector2_arg(args, 2, env, info)
  Vector2 p4 = get_Vector2_arg(args, 3, env, info)
  float t = get_float_arg(args, 4, env, info)
  free(args);
  ret=GetSplinePointCatmullRom(p1, p2, p3, p4, t);
  return return_Vector2(ret);
}

// Get (evaluate) spline point: Quadratic Bezier
napi_value NodeRaylibGetSplinePointBezierQuad(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 4);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 c2 = get_Vector2_arg(args, 1, env, info)
  Vector2 p3 = get_Vector2_arg(args, 2, env, info)
  float t = get_float_arg(args, 3, env, info)
  free(args);
  ret=GetSplinePointBezierQuad(p1, c2, p3, t);
  return return_Vector2(ret);
}

// Get (evaluate) spline point: Cubic Bezier
napi_value NodeRaylibGetSplinePointBezierCubic(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 5);
  Vector2 p1 = get_Vector2_arg(args, 0, env, info)
  Vector2 c2 = get_Vector2_arg(args, 1, env, info)
  Vector2 c3 = get_Vector2_arg(args, 2, env, info)
  Vector2 p4 = get_Vector2_arg(args, 3, env, info)
  float t = get_float_arg(args, 4, env, info)
  free(args);
  ret=GetSplinePointBezierCubic(p1, c2, c3, p4, t);
  return return_Vector2(ret);
}

// Check collision between two rectangles
napi_value NodeRaylibCheckCollisionRecs(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Rectangle rec1 = get_Rectangle_arg(args, 0, env, info)
  Rectangle rec2 = get_Rectangle_arg(args, 1, env, info)
  free(args);
  ret=CheckCollisionRecs(rec1, rec2);
  return return_bool(ret);
}

// Check collision between two circles
napi_value NodeRaylibCheckCollisionCircles(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 4);
  Vector2 center1 = get_Vector2_arg(args, 0, env, info)
  float radius1 = get_float_arg(args, 1, env, info)
  Vector2 center2 = get_Vector2_arg(args, 2, env, info)
  float radius2 = get_float_arg(args, 3, env, info)
  free(args);
  ret=CheckCollisionCircles(center1, radius1, center2, radius2);
  return return_bool(ret);
}

// Check collision between circle and rectangle
napi_value NodeRaylibCheckCollisionCircleRec(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 3);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  Rectangle rec = get_Rectangle_arg(args, 2, env, info)
  free(args);
  ret=CheckCollisionCircleRec(center, radius, rec);
  return return_bool(ret);
}

// Check if circle collides with a line created betweeen two points [p1] and [p2]
napi_value NodeRaylibCheckCollisionCircleLine(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 4);
  Vector2 center = get_Vector2_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  Vector2 p1 = get_Vector2_arg(args, 2, env, info)
  Vector2 p2 = get_Vector2_arg(args, 3, env, info)
  free(args);
  ret=CheckCollisionCircleLine(center, radius, p1, p2);
  return return_bool(ret);
}

// Check if point is inside rectangle
napi_value NodeRaylibCheckCollisionPointRec(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Vector2 point = get_Vector2_arg(args, 0, env, info)
  Rectangle rec = get_Rectangle_arg(args, 1, env, info)
  free(args);
  ret=CheckCollisionPointRec(point, rec);
  return return_bool(ret);
}

// Check if point is inside circle
napi_value NodeRaylibCheckCollisionPointCircle(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 3);
  Vector2 point = get_Vector2_arg(args, 0, env, info)
  Vector2 center = get_Vector2_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  free(args);
  ret=CheckCollisionPointCircle(point, center, radius);
  return return_bool(ret);
}

// Check if point is inside a triangle
napi_value NodeRaylibCheckCollisionPointTriangle(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 4);
  Vector2 point = get_Vector2_arg(args, 0, env, info)
  Vector2 p1 = get_Vector2_arg(args, 1, env, info)
  Vector2 p2 = get_Vector2_arg(args, 2, env, info)
  Vector2 p3 = get_Vector2_arg(args, 3, env, info)
  free(args);
  ret=CheckCollisionPointTriangle(point, p1, p2, p3);
  return return_bool(ret);
}

// Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
napi_value NodeRaylibCheckCollisionPointLine(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 4);
  Vector2 point = get_Vector2_arg(args, 0, env, info)
  Vector2 p1 = get_Vector2_arg(args, 1, env, info)
  Vector2 p2 = get_Vector2_arg(args, 2, env, info)
  int threshold = get_int_arg(args, 3, env, info)
  free(args);
  ret=CheckCollisionPointLine(point, p1, p2, threshold);
  return return_bool(ret);
}

// Check if point is within a polygon described by array of vertices
napi_value NodeRaylibCheckCollisionPointPoly(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 3);
  Vector2 point = get_Vector2_arg(args, 0, env, info)
  const Vector2 * points = get_Vector2_pointer_arg(args, 1, env, info)
  int pointCount = get_int_arg(args, 2, env, info)
  free(args);
  ret=CheckCollisionPointPoly(point, points, pointCount);
  return return_bool(ret);
}

// Check the collision between two lines defined by two points each, returns collision point by reference
napi_value NodeRaylibCheckCollisionLines(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 5);
  Vector2 startPos1 = get_Vector2_arg(args, 0, env, info)
  Vector2 endPos1 = get_Vector2_arg(args, 1, env, info)
  Vector2 startPos2 = get_Vector2_arg(args, 2, env, info)
  Vector2 endPos2 = get_Vector2_arg(args, 3, env, info)
  Vector2 * collisionPoint = get_Vector2_pointer_arg(args, 4, env, info)
  free(args);
  ret=CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, collisionPoint);
  return return_bool(ret);
}

// Get collision rectangle for two rectangles collision
napi_value NodeRaylibGetCollisionRec(napi_env env, napi_callback_info info) {
  Rectangle ret;
  napi_value* args = get_args(env, info, 2);
  Rectangle rec1 = get_Rectangle_arg(args, 0, env, info)
  Rectangle rec2 = get_Rectangle_arg(args, 1, env, info)
  free(args);
  ret=GetCollisionRec(rec1, rec2);
  return return_Rectangle(ret);
}

// Load image from file into CPU memory (RAM)
napi_value NodeRaylibLoadImage(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadImage(fileName);
  return return_Image(ret);
}

// Load image from RAW file data
napi_value NodeRaylibLoadImageRaw(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 5);
  const char * fileName = get_string_arg(args, 0, env, info)
  int width = get_int_arg(args, 1, env, info)
  int height = get_int_arg(args, 2, env, info)
  int format = get_int_arg(args, 3, env, info)
  int headerSize = get_int_arg(args, 4, env, info)
  free(args);
  ret=LoadImageRaw(fileName, width, height, format, headerSize);
  return return_Image(ret);
}

// Load image sequence from file (frames appended to image.data)
napi_value NodeRaylibLoadImageAnim(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 2);
  const char * fileName = get_string_arg(args, 0, env, info)
  int * frames = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=LoadImageAnim(fileName, frames);
  return return_Image(ret);
}

// Load image sequence from memory buffer
napi_value NodeRaylibLoadImageAnimFromMemory(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 4);
  const char * fileType = get_string_arg(args, 0, env, info)
  const unsigned char * fileData = get_uchar_pointer_arg(args, 1, env, info)
  int dataSize = get_int_arg(args, 2, env, info)
  int * frames = get_int_pointer_arg(args, 3, env, info)
  free(args);
  ret=LoadImageAnimFromMemory(fileType, fileData, dataSize, frames);
  return return_Image(ret);
}

// Load image from memory buffer, fileType refers to extension: i.e. '.png'
napi_value NodeRaylibLoadImageFromMemory(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 3);
  const char * fileType = get_string_arg(args, 0, env, info)
  const unsigned char * fileData = get_uchar_pointer_arg(args, 1, env, info)
  int dataSize = get_int_arg(args, 2, env, info)
  free(args);
  ret=LoadImageFromMemory(fileType, fileData, dataSize);
  return return_Image(ret);
}

// Load image from GPU texture data
napi_value NodeRaylibLoadImageFromTexture(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 1);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  free(args);
  ret=LoadImageFromTexture(texture);
  return return_Image(ret);
}

// Load image from screen buffer and (screenshot)
napi_value NodeRaylibLoadImageFromScreen(napi_env env, napi_callback_info info) {
  Image ret;
  ret=LoadImageFromScreen();
  return return_Image(ret);
}

// Check if an image is valid (data and parameters)
napi_value NodeRaylibIsImageValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Image image = get_Image_arg(args, 0, env, info)
  free(args);
  ret=IsImageValid(image);
  return return_bool(ret);
}

// Unload image from CPU memory (RAM)
napi_value NodeRaylibUnloadImage(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image image = get_Image_arg(args, 0, env, info)
  free(args);
  UnloadImage(image);
  return n_undefined;
}

// Export image data to file, returns true on success
napi_value NodeRaylibExportImage(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Image image = get_Image_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportImage(image, fileName);
  return return_bool(ret);
}

// Export image to memory buffer
napi_value NodeRaylibExportImageToMemory(napi_env env, napi_callback_info info) {
  unsigned char * ret;
  napi_value* args = get_args(env, info, 3);
  Image image = get_Image_arg(args, 0, env, info)
  const char * fileType = get_string_arg(args, 1, env, info)
  int * fileSize = get_int_pointer_arg(args, 2, env, info)
  free(args);
  ret=ExportImageToMemory(image, fileType, fileSize);
  return return_uchar_pointer(ret);
}

// Export image as code file defining an array of bytes, returns true on success
napi_value NodeRaylibExportImageAsCode(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Image image = get_Image_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportImageAsCode(image, fileName);
  return return_bool(ret);
}

// Generate image: plain color
napi_value NodeRaylibGenImageColor(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 3);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  ret=GenImageColor(width, height, color);
  return return_Image(ret);
}

// Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
napi_value NodeRaylibGenImageGradientLinear(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 5);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  int direction = get_int_arg(args, 2, env, info)
  Color start = get_Color_arg(args, 3, env, info)
  Color end = get_Color_arg(args, 4, env, info)
  free(args);
  ret=GenImageGradientLinear(width, height, direction, start, end);
  return return_Image(ret);
}

// Generate image: radial gradient
napi_value NodeRaylibGenImageGradientRadial(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 5);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  float density = get_float_arg(args, 2, env, info)
  Color inner = get_Color_arg(args, 3, env, info)
  Color outer = get_Color_arg(args, 4, env, info)
  free(args);
  ret=GenImageGradientRadial(width, height, density, inner, outer);
  return return_Image(ret);
}

// Generate image: square gradient
napi_value NodeRaylibGenImageGradientSquare(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 5);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  float density = get_float_arg(args, 2, env, info)
  Color inner = get_Color_arg(args, 3, env, info)
  Color outer = get_Color_arg(args, 4, env, info)
  free(args);
  ret=GenImageGradientSquare(width, height, density, inner, outer);
  return return_Image(ret);
}

// Generate image: checked
napi_value NodeRaylibGenImageChecked(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 6);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  int checksX = get_int_arg(args, 2, env, info)
  int checksY = get_int_arg(args, 3, env, info)
  Color col1 = get_Color_arg(args, 4, env, info)
  Color col2 = get_Color_arg(args, 5, env, info)
  free(args);
  ret=GenImageChecked(width, height, checksX, checksY, col1, col2);
  return return_Image(ret);
}

// Generate image: white noise
napi_value NodeRaylibGenImageWhiteNoise(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 3);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  float factor = get_float_arg(args, 2, env, info)
  free(args);
  ret=GenImageWhiteNoise(width, height, factor);
  return return_Image(ret);
}

// Generate image: perlin noise
napi_value NodeRaylibGenImagePerlinNoise(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 5);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  int offsetX = get_int_arg(args, 2, env, info)
  int offsetY = get_int_arg(args, 3, env, info)
  float scale = get_float_arg(args, 4, env, info)
  free(args);
  ret=GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
  return return_Image(ret);
}

// Generate image: cellular algorithm, bigger tileSize means bigger cells
napi_value NodeRaylibGenImageCellular(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 3);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  int tileSize = get_int_arg(args, 2, env, info)
  free(args);
  ret=GenImageCellular(width, height, tileSize);
  return return_Image(ret);
}

// Generate image: grayscale image from text data
napi_value NodeRaylibGenImageText(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 3);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  const char * text = get_string_arg(args, 2, env, info)
  free(args);
  ret=GenImageText(width, height, text);
  return return_Image(ret);
}

// Create an image duplicate (useful for transformations)
napi_value NodeRaylibImageCopy(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 1);
  Image image = get_Image_arg(args, 0, env, info)
  free(args);
  ret=ImageCopy(image);
  return return_Image(ret);
}

// Create an image from another image piece
napi_value NodeRaylibImageFromImage(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 2);
  Image image = get_Image_arg(args, 0, env, info)
  Rectangle rec = get_Rectangle_arg(args, 1, env, info)
  free(args);
  ret=ImageFromImage(image, rec);
  return return_Image(ret);
}

// Create an image from a selected channel of another image (GRAYSCALE)
napi_value NodeRaylibImageFromChannel(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 2);
  Image image = get_Image_arg(args, 0, env, info)
  int selectedChannel = get_int_arg(args, 1, env, info)
  free(args);
  ret=ImageFromChannel(image, selectedChannel);
  return return_Image(ret);
}

// Create an image from text (default font)
napi_value NodeRaylibImageText(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 3);
  const char * text = get_string_arg(args, 0, env, info)
  int fontSize = get_int_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  ret=ImageText(text, fontSize, color);
  return return_Image(ret);
}

// Create an image from text (custom sprite font)
napi_value NodeRaylibImageTextEx(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 5);
  Font font = get_Font_arg(args, 0, env, info)
  const char * text = get_string_arg(args, 1, env, info)
  float fontSize = get_float_arg(args, 2, env, info)
  float spacing = get_float_arg(args, 3, env, info)
  Color tint = get_Color_arg(args, 4, env, info)
  free(args);
  ret=ImageTextEx(font, text, fontSize, spacing, tint);
  return return_Image(ret);
}

// Convert image data to desired format
napi_value NodeRaylibImageFormat(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int newFormat = get_int_arg(args, 1, env, info)
  free(args);
  ImageFormat(image, newFormat);
  return n_undefined;
}

// Convert image to POT (power-of-two)
napi_value NodeRaylibImageToPOT(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  Color fill = get_Color_arg(args, 1, env, info)
  free(args);
  ImageToPOT(image, fill);
  return n_undefined;
}

// Crop an image to a defined rectangle
napi_value NodeRaylibImageCrop(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  Rectangle crop = get_Rectangle_arg(args, 1, env, info)
  free(args);
  ImageCrop(image, crop);
  return n_undefined;
}

// Crop image depending on alpha value
napi_value NodeRaylibImageAlphaCrop(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  float threshold = get_float_arg(args, 1, env, info)
  free(args);
  ImageAlphaCrop(image, threshold);
  return n_undefined;
}

// Clear alpha channel to desired color
napi_value NodeRaylibImageAlphaClear(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  float threshold = get_float_arg(args, 2, env, info)
  free(args);
  ImageAlphaClear(image, color, threshold);
  return n_undefined;
}

// Apply alpha mask to image
napi_value NodeRaylibImageAlphaMask(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  Image alphaMask = get_Image_arg(args, 1, env, info)
  free(args);
  ImageAlphaMask(image, alphaMask);
  return n_undefined;
}

// Premultiply alpha channel
napi_value NodeRaylibImageAlphaPremultiply(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageAlphaPremultiply(image);
  return n_undefined;
}

// Apply Gaussian blur using a box blur approximation
napi_value NodeRaylibImageBlurGaussian(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int blurSize = get_int_arg(args, 1, env, info)
  free(args);
  ImageBlurGaussian(image, blurSize);
  return n_undefined;
}

// Apply custom square convolution kernel to image
napi_value NodeRaylibImageKernelConvolution(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  const float * kernel = get_float_pointer_arg(args, 1, env, info)
  int kernelSize = get_int_arg(args, 2, env, info)
  free(args);
  ImageKernelConvolution(image, kernel, kernelSize);
  return n_undefined;
}

// Resize image (Bicubic scaling algorithm)
napi_value NodeRaylibImageResize(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int newWidth = get_int_arg(args, 1, env, info)
  int newHeight = get_int_arg(args, 2, env, info)
  free(args);
  ImageResize(image, newWidth, newHeight);
  return n_undefined;
}

// Resize image (Nearest-Neighbor scaling algorithm)
napi_value NodeRaylibImageResizeNN(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int newWidth = get_int_arg(args, 1, env, info)
  int newHeight = get_int_arg(args, 2, env, info)
  free(args);
  ImageResizeNN(image, newWidth, newHeight);
  return n_undefined;
}

// Resize canvas and fill with color
napi_value NodeRaylibImageResizeCanvas(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int newWidth = get_int_arg(args, 1, env, info)
  int newHeight = get_int_arg(args, 2, env, info)
  int offsetX = get_int_arg(args, 3, env, info)
  int offsetY = get_int_arg(args, 4, env, info)
  Color fill = get_Color_arg(args, 5, env, info)
  free(args);
  ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, fill);
  return n_undefined;
}

// Compute all mipmap levels for a provided image
napi_value NodeRaylibImageMipmaps(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageMipmaps(image);
  return n_undefined;
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
napi_value NodeRaylibImageDither(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int rBpp = get_int_arg(args, 1, env, info)
  int gBpp = get_int_arg(args, 2, env, info)
  int bBpp = get_int_arg(args, 3, env, info)
  int aBpp = get_int_arg(args, 4, env, info)
  free(args);
  ImageDither(image, rBpp, gBpp, bBpp, aBpp);
  return n_undefined;
}

// Flip image vertically
napi_value NodeRaylibImageFlipVertical(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageFlipVertical(image);
  return n_undefined;
}

// Flip image horizontally
napi_value NodeRaylibImageFlipHorizontal(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageFlipHorizontal(image);
  return n_undefined;
}

// Rotate image by input angle in degrees (-359 to 359)
napi_value NodeRaylibImageRotate(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int degrees = get_int_arg(args, 1, env, info)
  free(args);
  ImageRotate(image, degrees);
  return n_undefined;
}

// Rotate image clockwise 90deg
napi_value NodeRaylibImageRotateCW(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageRotateCW(image);
  return n_undefined;
}

// Rotate image counter-clockwise 90deg
napi_value NodeRaylibImageRotateCCW(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageRotateCCW(image);
  return n_undefined;
}

// Modify image color: tint
napi_value NodeRaylibImageColorTint(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  free(args);
  ImageColorTint(image, color);
  return n_undefined;
}

// Modify image color: invert
napi_value NodeRaylibImageColorInvert(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageColorInvert(image);
  return n_undefined;
}

// Modify image color: grayscale
napi_value NodeRaylibImageColorGrayscale(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  free(args);
  ImageColorGrayscale(image);
  return n_undefined;
}

// Modify image color: contrast (-100 to 100)
napi_value NodeRaylibImageColorContrast(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  float contrast = get_float_arg(args, 1, env, info)
  free(args);
  ImageColorContrast(image, contrast);
  return n_undefined;
}

// Modify image color: brightness (-255 to 255)
napi_value NodeRaylibImageColorBrightness(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  int brightness = get_int_arg(args, 1, env, info)
  free(args);
  ImageColorBrightness(image, brightness);
  return n_undefined;
}

// Modify image color: replace color
napi_value NodeRaylibImageColorReplace(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Image * image = get_Image_pointer_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  Color replace = get_Color_arg(args, 2, env, info)
  free(args);
  ImageColorReplace(image, color, replace);
  return n_undefined;
}

// Load color data from image as a Color array (RGBA - 32bit)
napi_value NodeRaylibLoadImageColors(napi_env env, napi_callback_info info) {
  Color * ret;
  napi_value* args = get_args(env, info, 1);
  Image image = get_Image_arg(args, 0, env, info)
  free(args);
  ret=LoadImageColors(image);
  return return_Color_pointer(ret);
}

// Load colors palette from image as a Color array (RGBA - 32bit)
napi_value NodeRaylibLoadImagePalette(napi_env env, napi_callback_info info) {
  Color * ret;
  napi_value* args = get_args(env, info, 3);
  Image image = get_Image_arg(args, 0, env, info)
  int maxPaletteSize = get_int_arg(args, 1, env, info)
  int * colorCount = get_int_pointer_arg(args, 2, env, info)
  free(args);
  ret=LoadImagePalette(image, maxPaletteSize, colorCount);
  return return_Color_pointer(ret);
}

// Unload color data loaded with LoadImageColors()
napi_value NodeRaylibUnloadImageColors(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Color * colors = get_Color_pointer_arg(args, 0, env, info)
  free(args);
  UnloadImageColors(colors);
  return n_undefined;
}

// Unload colors palette loaded with LoadImagePalette()
napi_value NodeRaylibUnloadImagePalette(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Color * colors = get_Color_pointer_arg(args, 0, env, info)
  free(args);
  UnloadImagePalette(colors);
  return n_undefined;
}

// Get image alpha border rectangle
napi_value NodeRaylibGetImageAlphaBorder(napi_env env, napi_callback_info info) {
  Rectangle ret;
  napi_value* args = get_args(env, info, 2);
  Image image = get_Image_arg(args, 0, env, info)
  float threshold = get_float_arg(args, 1, env, info)
  free(args);
  ret=GetImageAlphaBorder(image, threshold);
  return return_Rectangle(ret);
}

// Get image pixel color at (x, y) position
napi_value NodeRaylibGetImageColor(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 3);
  Image image = get_Image_arg(args, 0, env, info)
  int x = get_int_arg(args, 1, env, info)
  int y = get_int_arg(args, 2, env, info)
  free(args);
  ret=GetImageColor(image, x, y);
  return return_Color(ret);
}

// Clear image background with given color
napi_value NodeRaylibImageClearBackground(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  free(args);
  ImageClearBackground(dst, color);
  return n_undefined;
}

// Draw pixel within an image
napi_value NodeRaylibImageDrawPixel(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  int posX = get_int_arg(args, 1, env, info)
  int posY = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawPixel(dst, posX, posY, color);
  return n_undefined;
}

// Draw pixel within an image (Vector version)
napi_value NodeRaylibImageDrawPixelV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 position = get_Vector2_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  ImageDrawPixelV(dst, position, color);
  return n_undefined;
}

// Draw line within an image
napi_value NodeRaylibImageDrawLine(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  int startPosX = get_int_arg(args, 1, env, info)
  int startPosY = get_int_arg(args, 2, env, info)
  int endPosX = get_int_arg(args, 3, env, info)
  int endPosY = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, color);
  return n_undefined;
}

// Draw line within an image (Vector version)
napi_value NodeRaylibImageDrawLineV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 start = get_Vector2_arg(args, 1, env, info)
  Vector2 end = get_Vector2_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawLineV(dst, start, end, color);
  return n_undefined;
}

// Draw a line defining thickness within an image
napi_value NodeRaylibImageDrawLineEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 start = get_Vector2_arg(args, 1, env, info)
  Vector2 end = get_Vector2_arg(args, 2, env, info)
  int thick = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  ImageDrawLineEx(dst, start, end, thick, color);
  return n_undefined;
}

// Draw a filled circle within an image
napi_value NodeRaylibImageDrawCircle(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  int centerX = get_int_arg(args, 1, env, info)
  int centerY = get_int_arg(args, 2, env, info)
  int radius = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  ImageDrawCircle(dst, centerX, centerY, radius, color);
  return n_undefined;
}

// Draw a filled circle within an image (Vector version)
napi_value NodeRaylibImageDrawCircleV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 center = get_Vector2_arg(args, 1, env, info)
  int radius = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawCircleV(dst, center, radius, color);
  return n_undefined;
}

// Draw circle outline within an image
napi_value NodeRaylibImageDrawCircleLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  int centerX = get_int_arg(args, 1, env, info)
  int centerY = get_int_arg(args, 2, env, info)
  int radius = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  ImageDrawCircleLines(dst, centerX, centerY, radius, color);
  return n_undefined;
}

// Draw circle outline within an image (Vector version)
napi_value NodeRaylibImageDrawCircleLinesV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 center = get_Vector2_arg(args, 1, env, info)
  int radius = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawCircleLinesV(dst, center, radius, color);
  return n_undefined;
}

// Draw rectangle within an image
napi_value NodeRaylibImageDrawRectangle(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  int posX = get_int_arg(args, 1, env, info)
  int posY = get_int_arg(args, 2, env, info)
  int width = get_int_arg(args, 3, env, info)
  int height = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  ImageDrawRectangle(dst, posX, posY, width, height, color);
  return n_undefined;
}

// Draw rectangle within an image (Vector version)
napi_value NodeRaylibImageDrawRectangleV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 position = get_Vector2_arg(args, 1, env, info)
  Vector2 size = get_Vector2_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawRectangleV(dst, position, size, color);
  return n_undefined;
}

// Draw rectangle within an image
napi_value NodeRaylibImageDrawRectangleRec(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Rectangle rec = get_Rectangle_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  ImageDrawRectangleRec(dst, rec, color);
  return n_undefined;
}

// Draw rectangle lines within an image
napi_value NodeRaylibImageDrawRectangleLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Rectangle rec = get_Rectangle_arg(args, 1, env, info)
  int thick = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawRectangleLines(dst, rec, thick, color);
  return n_undefined;
}

// Draw triangle within an image
napi_value NodeRaylibImageDrawTriangle(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 v1 = get_Vector2_arg(args, 1, env, info)
  Vector2 v2 = get_Vector2_arg(args, 2, env, info)
  Vector2 v3 = get_Vector2_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  ImageDrawTriangle(dst, v1, v2, v3, color);
  return n_undefined;
}

// Draw triangle with interpolated colors within an image
napi_value NodeRaylibImageDrawTriangleEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 7);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 v1 = get_Vector2_arg(args, 1, env, info)
  Vector2 v2 = get_Vector2_arg(args, 2, env, info)
  Vector2 v3 = get_Vector2_arg(args, 3, env, info)
  Color c1 = get_Color_arg(args, 4, env, info)
  Color c2 = get_Color_arg(args, 5, env, info)
  Color c3 = get_Color_arg(args, 6, env, info)
  free(args);
  ImageDrawTriangleEx(dst, v1, v2, v3, c1, c2, c3);
  return n_undefined;
}

// Draw triangle outline within an image
napi_value NodeRaylibImageDrawTriangleLines(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 v1 = get_Vector2_arg(args, 1, env, info)
  Vector2 v2 = get_Vector2_arg(args, 2, env, info)
  Vector2 v3 = get_Vector2_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  ImageDrawTriangleLines(dst, v1, v2, v3, color);
  return n_undefined;
}

// Draw a triangle fan defined by points within an image (first vertex is the center)
napi_value NodeRaylibImageDrawTriangleFan(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 * points = get_Vector2_pointer_arg(args, 1, env, info)
  int pointCount = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawTriangleFan(dst, points, pointCount, color);
  return n_undefined;
}

// Draw a triangle strip defined by points within an image
napi_value NodeRaylibImageDrawTriangleStrip(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Vector2 * points = get_Vector2_pointer_arg(args, 1, env, info)
  int pointCount = get_int_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  ImageDrawTriangleStrip(dst, points, pointCount, color);
  return n_undefined;
}

// Draw a source image within a destination image (tint applied to source)
napi_value NodeRaylibImageDraw(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Image src = get_Image_arg(args, 1, env, info)
  Rectangle srcRec = get_Rectangle_arg(args, 2, env, info)
  Rectangle dstRec = get_Rectangle_arg(args, 3, env, info)
  Color tint = get_Color_arg(args, 4, env, info)
  free(args);
  ImageDraw(dst, src, srcRec, dstRec, tint);
  return n_undefined;
}

// Draw text (using default font) within an image (destination)
napi_value NodeRaylibImageDrawText(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  const char * text = get_string_arg(args, 1, env, info)
  int posX = get_int_arg(args, 2, env, info)
  int posY = get_int_arg(args, 3, env, info)
  int fontSize = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  ImageDrawText(dst, text, posX, posY, fontSize, color);
  return n_undefined;
}

// Draw text (custom sprite font) within an image (destination)
napi_value NodeRaylibImageDrawTextEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 7);
  Image * dst = get_Image_pointer_arg(args, 0, env, info)
  Font font = get_Font_arg(args, 1, env, info)
  const char * text = get_string_arg(args, 2, env, info)
  Vector2 position = get_Vector2_arg(args, 3, env, info)
  float fontSize = get_float_arg(args, 4, env, info)
  float spacing = get_float_arg(args, 5, env, info)
  Color tint = get_Color_arg(args, 6, env, info)
  free(args);
  ImageDrawTextEx(dst, font, text, position, fontSize, spacing, tint);
  return n_undefined;
}

// Load texture from file into GPU memory (VRAM)
napi_value NodeRaylibLoadTexture(napi_env env, napi_callback_info info) {
  Texture2D ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadTexture(fileName);
  return return_Texture2D(ret);
}

// Load texture from image data
napi_value NodeRaylibLoadTextureFromImage(napi_env env, napi_callback_info info) {
  Texture2D ret;
  napi_value* args = get_args(env, info, 1);
  Image image = get_Image_arg(args, 0, env, info)
  free(args);
  ret=LoadTextureFromImage(image);
  return return_Texture2D(ret);
}

// Load cubemap from image, multiple image cubemap layouts supported
napi_value NodeRaylibLoadTextureCubemap(napi_env env, napi_callback_info info) {
  TextureCubemap ret;
  napi_value* args = get_args(env, info, 2);
  Image image = get_Image_arg(args, 0, env, info)
  int layout = get_int_arg(args, 1, env, info)
  free(args);
  ret=LoadTextureCubemap(image, layout);
  return return_TextureCubemap(ret);
}

// Load texture for rendering (framebuffer)
napi_value NodeRaylibLoadRenderTexture(napi_env env, napi_callback_info info) {
  RenderTexture2D ret;
  napi_value* args = get_args(env, info, 2);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  free(args);
  ret=LoadRenderTexture(width, height);
  return return_RenderTexture2D(ret);
}

// Check if a texture is valid (loaded in GPU)
napi_value NodeRaylibIsTextureValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  free(args);
  ret=IsTextureValid(texture);
  return return_bool(ret);
}

// Unload texture from GPU memory (VRAM)
napi_value NodeRaylibUnloadTexture(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  free(args);
  UnloadTexture(texture);
  return n_undefined;
}

// Check if a render texture is valid (loaded in GPU)
napi_value NodeRaylibIsRenderTextureValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  RenderTexture2D target = get_RenderTexture2D_arg(args, 0, env, info)
  free(args);
  ret=IsRenderTextureValid(target);
  return return_bool(ret);
}

// Unload render texture from GPU memory (VRAM)
napi_value NodeRaylibUnloadRenderTexture(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  RenderTexture2D target = get_RenderTexture2D_arg(args, 0, env, info)
  free(args);
  UnloadRenderTexture(target);
  return n_undefined;
}

// Update GPU texture with new data
napi_value NodeRaylibUpdateTexture(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  const void * pixels = get_undefined_arg(args, 1, env, info)
  free(args);
  UpdateTexture(texture, pixels);
  return n_undefined;
}

// Update GPU texture rectangle with new data
napi_value NodeRaylibUpdateTextureRec(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  Rectangle rec = get_Rectangle_arg(args, 1, env, info)
  const void * pixels = get_undefined_arg(args, 2, env, info)
  free(args);
  UpdateTextureRec(texture, rec, pixels);
  return n_undefined;
}

// Generate GPU mipmaps for a texture
napi_value NodeRaylibGenTextureMipmaps(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Texture2D * texture = get_Texture2D_pointer_arg(args, 0, env, info)
  free(args);
  GenTextureMipmaps(texture);
  return n_undefined;
}

// Set texture scaling filter mode
napi_value NodeRaylibSetTextureFilter(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  int filter = get_int_arg(args, 1, env, info)
  free(args);
  SetTextureFilter(texture, filter);
  return n_undefined;
}

// Set texture wrapping mode
napi_value NodeRaylibSetTextureWrap(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  int wrap = get_int_arg(args, 1, env, info)
  free(args);
  SetTextureWrap(texture, wrap);
  return n_undefined;
}

// Draw a Texture2D
napi_value NodeRaylibDrawTexture(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  int posX = get_int_arg(args, 1, env, info)
  int posY = get_int_arg(args, 2, env, info)
  Color tint = get_Color_arg(args, 3, env, info)
  free(args);
  DrawTexture(texture, posX, posY, tint);
  return n_undefined;
}

// Draw a Texture2D with position defined as Vector2
napi_value NodeRaylibDrawTextureV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  Vector2 position = get_Vector2_arg(args, 1, env, info)
  Color tint = get_Color_arg(args, 2, env, info)
  free(args);
  DrawTextureV(texture, position, tint);
  return n_undefined;
}

// Draw a Texture2D with extended parameters
napi_value NodeRaylibDrawTextureEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  Vector2 position = get_Vector2_arg(args, 1, env, info)
  float rotation = get_float_arg(args, 2, env, info)
  float scale = get_float_arg(args, 3, env, info)
  Color tint = get_Color_arg(args, 4, env, info)
  free(args);
  DrawTextureEx(texture, position, rotation, scale, tint);
  return n_undefined;
}

// Draw a part of a texture defined by a rectangle
napi_value NodeRaylibDrawTextureRec(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  Rectangle source = get_Rectangle_arg(args, 1, env, info)
  Vector2 position = get_Vector2_arg(args, 2, env, info)
  Color tint = get_Color_arg(args, 3, env, info)
  free(args);
  DrawTextureRec(texture, source, position, tint);
  return n_undefined;
}

// Draw a part of a texture defined by a rectangle with 'pro' parameters
napi_value NodeRaylibDrawTexturePro(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  Rectangle source = get_Rectangle_arg(args, 1, env, info)
  Rectangle dest = get_Rectangle_arg(args, 2, env, info)
  Vector2 origin = get_Vector2_arg(args, 3, env, info)
  float rotation = get_float_arg(args, 4, env, info)
  Color tint = get_Color_arg(args, 5, env, info)
  free(args);
  DrawTexturePro(texture, source, dest, origin, rotation, tint);
  return n_undefined;
}

// Draws a texture (or part of it) that stretches or shrinks nicely
napi_value NodeRaylibDrawTextureNPatch(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Texture2D texture = get_Texture2D_arg(args, 0, env, info)
  NPatchInfo nPatchInfo = get_NPatchInfo_arg(args, 1, env, info)
  Rectangle dest = get_Rectangle_arg(args, 2, env, info)
  Vector2 origin = get_Vector2_arg(args, 3, env, info)
  float rotation = get_float_arg(args, 4, env, info)
  Color tint = get_Color_arg(args, 5, env, info)
  free(args);
  DrawTextureNPatch(texture, nPatchInfo, dest, origin, rotation, tint);
  return n_undefined;
}

// Check if two colors are equal
napi_value NodeRaylibColorIsEqual(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Color col1 = get_Color_arg(args, 0, env, info)
  Color col2 = get_Color_arg(args, 1, env, info)
  free(args);
  ret=ColorIsEqual(col1, col2);
  return return_bool(ret);
}

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
napi_value NodeRaylibFade(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 2);
  Color color = get_Color_arg(args, 0, env, info)
  float alpha = get_float_arg(args, 1, env, info)
  free(args);
  ret=Fade(color, alpha);
  return return_Color(ret);
}

// Get hexadecimal value for a Color (0xRRGGBBAA)
napi_value NodeRaylibColorToInt(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  Color color = get_Color_arg(args, 0, env, info)
  free(args);
  ret=ColorToInt(color);
  return return_int(ret);
}

// Get Color normalized as float [0..1]
napi_value NodeRaylibColorNormalize(napi_env env, napi_callback_info info) {
  Vector4 ret;
  napi_value* args = get_args(env, info, 1);
  Color color = get_Color_arg(args, 0, env, info)
  free(args);
  ret=ColorNormalize(color);
  return return_Vector4(ret);
}

// Get Color from normalized values [0..1]
napi_value NodeRaylibColorFromNormalized(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 1);
  Vector4 normalized = get_Vector4_arg(args, 0, env, info)
  free(args);
  ret=ColorFromNormalized(normalized);
  return return_Color(ret);
}

// Get HSV values for a Color, hue [0..360], saturation/value [0..1]
napi_value NodeRaylibColorToHSV(napi_env env, napi_callback_info info) {
  Vector3 ret;
  napi_value* args = get_args(env, info, 1);
  Color color = get_Color_arg(args, 0, env, info)
  free(args);
  ret=ColorToHSV(color);
  return return_Vector3(ret);
}

// Get a Color from HSV values, hue [0..360], saturation/value [0..1]
napi_value NodeRaylibColorFromHSV(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 3);
  float hue = get_float_arg(args, 0, env, info)
  float saturation = get_float_arg(args, 1, env, info)
  float value = get_float_arg(args, 2, env, info)
  free(args);
  ret=ColorFromHSV(hue, saturation, value);
  return return_Color(ret);
}

// Get color multiplied with another color
napi_value NodeRaylibColorTint(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 2);
  Color color = get_Color_arg(args, 0, env, info)
  Color tint = get_Color_arg(args, 1, env, info)
  free(args);
  ret=ColorTint(color, tint);
  return return_Color(ret);
}

// Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
napi_value NodeRaylibColorBrightness(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 2);
  Color color = get_Color_arg(args, 0, env, info)
  float factor = get_float_arg(args, 1, env, info)
  free(args);
  ret=ColorBrightness(color, factor);
  return return_Color(ret);
}

// Get color with contrast correction, contrast values between -1.0f and 1.0f
napi_value NodeRaylibColorContrast(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 2);
  Color color = get_Color_arg(args, 0, env, info)
  float contrast = get_float_arg(args, 1, env, info)
  free(args);
  ret=ColorContrast(color, contrast);
  return return_Color(ret);
}

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
napi_value NodeRaylibColorAlpha(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 2);
  Color color = get_Color_arg(args, 0, env, info)
  float alpha = get_float_arg(args, 1, env, info)
  free(args);
  ret=ColorAlpha(color, alpha);
  return return_Color(ret);
}

// Get src alpha-blended into dst color with tint
napi_value NodeRaylibColorAlphaBlend(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 3);
  Color dst = get_Color_arg(args, 0, env, info)
  Color src = get_Color_arg(args, 1, env, info)
  Color tint = get_Color_arg(args, 2, env, info)
  free(args);
  ret=ColorAlphaBlend(dst, src, tint);
  return return_Color(ret);
}

// Get color lerp interpolation between two colors, factor [0.0f..1.0f]
napi_value NodeRaylibColorLerp(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 3);
  Color color1 = get_Color_arg(args, 0, env, info)
  Color color2 = get_Color_arg(args, 1, env, info)
  float factor = get_float_arg(args, 2, env, info)
  free(args);
  ret=ColorLerp(color1, color2, factor);
  return return_Color(ret);
}

// Get Color structure from hexadecimal value
napi_value NodeRaylibGetColor(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 1);
  unsigned int hexValue = get_uint_arg(args, 0, env, info)
  free(args);
  ret=GetColor(hexValue);
  return return_Color(ret);
}

// Get Color from a source pixel pointer of certain format
napi_value NodeRaylibGetPixelColor(napi_env env, napi_callback_info info) {
  Color ret;
  napi_value* args = get_args(env, info, 2);
  void * srcPtr = get_undefined_arg(args, 0, env, info)
  int format = get_int_arg(args, 1, env, info)
  free(args);
  ret=GetPixelColor(srcPtr, format);
  return return_Color(ret);
}

// Set color formatted into destination pixel pointer
napi_value NodeRaylibSetPixelColor(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  void * dstPtr = get_undefined_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  int format = get_int_arg(args, 2, env, info)
  free(args);
  SetPixelColor(dstPtr, color, format);
  return n_undefined;
}

// Get pixel data size in bytes for certain format
napi_value NodeRaylibGetPixelDataSize(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 3);
  int width = get_int_arg(args, 0, env, info)
  int height = get_int_arg(args, 1, env, info)
  int format = get_int_arg(args, 2, env, info)
  free(args);
  ret=GetPixelDataSize(width, height, format);
  return return_int(ret);
}

// Get the default Font
napi_value NodeRaylibGetFontDefault(napi_env env, napi_callback_info info) {
  Font ret;
  ret=GetFontDefault();
  return return_Font(ret);
}

// Load font from file into GPU memory (VRAM)
napi_value NodeRaylibLoadFont(napi_env env, napi_callback_info info) {
  Font ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadFont(fileName);
  return return_Font(ret);
}

// Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height
napi_value NodeRaylibLoadFontEx(napi_env env, napi_callback_info info) {
  Font ret;
  napi_value* args = get_args(env, info, 4);
  const char * fileName = get_string_arg(args, 0, env, info)
  int fontSize = get_int_arg(args, 1, env, info)
  int * codepoints = get_int_pointer_arg(args, 2, env, info)
  int codepointCount = get_int_arg(args, 3, env, info)
  free(args);
  ret=LoadFontEx(fileName, fontSize, codepoints, codepointCount);
  return return_Font(ret);
}

// Load font from Image (XNA style)
napi_value NodeRaylibLoadFontFromImage(napi_env env, napi_callback_info info) {
  Font ret;
  napi_value* args = get_args(env, info, 3);
  Image image = get_Image_arg(args, 0, env, info)
  Color key = get_Color_arg(args, 1, env, info)
  int firstChar = get_int_arg(args, 2, env, info)
  free(args);
  ret=LoadFontFromImage(image, key, firstChar);
  return return_Font(ret);
}

// Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
napi_value NodeRaylibLoadFontFromMemory(napi_env env, napi_callback_info info) {
  Font ret;
  napi_value* args = get_args(env, info, 6);
  const char * fileType = get_string_arg(args, 0, env, info)
  const unsigned char * fileData = get_uchar_pointer_arg(args, 1, env, info)
  int dataSize = get_int_arg(args, 2, env, info)
  int fontSize = get_int_arg(args, 3, env, info)
  int * codepoints = get_int_pointer_arg(args, 4, env, info)
  int codepointCount = get_int_arg(args, 5, env, info)
  free(args);
  ret=LoadFontFromMemory(fileType, fileData, dataSize, fontSize, codepoints, codepointCount);
  return return_Font(ret);
}

// Check if a font is valid (font data loaded, WARNING: GPU texture not checked)
napi_value NodeRaylibIsFontValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Font font = get_Font_arg(args, 0, env, info)
  free(args);
  ret=IsFontValid(font);
  return return_bool(ret);
}

// Load font data for further use
napi_value NodeRaylibLoadFontData(napi_env env, napi_callback_info info) {
  GlyphInfo * ret;
  napi_value* args = get_args(env, info, 6);
  const unsigned char * fileData = get_uchar_pointer_arg(args, 0, env, info)
  int dataSize = get_int_arg(args, 1, env, info)
  int fontSize = get_int_arg(args, 2, env, info)
  int * codepoints = get_int_pointer_arg(args, 3, env, info)
  int codepointCount = get_int_arg(args, 4, env, info)
  int type = get_int_arg(args, 5, env, info)
  free(args);
  ret=LoadFontData(fileData, dataSize, fontSize, codepoints, codepointCount, type);
  return return_GlyphInfo_pointer(ret);
}

// Generate image font atlas using chars info
napi_value NodeRaylibGenImageFontAtlas(napi_env env, napi_callback_info info) {
  Image ret;
  napi_value* args = get_args(env, info, 6);
  const GlyphInfo * glyphs = get_GlyphInfo_pointer_arg(args, 0, env, info)
  Rectangle ** glyphRecs = get_Rectangle_pointer_arg(args, 1, env, info)
  int glyphCount = get_int_arg(args, 2, env, info)
  int fontSize = get_int_arg(args, 3, env, info)
  int padding = get_int_arg(args, 4, env, info)
  int packMethod = get_int_arg(args, 5, env, info)
  free(args);
  ret=GenImageFontAtlas(glyphs, glyphRecs, glyphCount, fontSize, padding, packMethod);
  return return_Image(ret);
}

// Unload font chars info data (RAM)
napi_value NodeRaylibUnloadFontData(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  GlyphInfo * glyphs = get_GlyphInfo_pointer_arg(args, 0, env, info)
  int glyphCount = get_int_arg(args, 1, env, info)
  free(args);
  UnloadFontData(glyphs, glyphCount);
  return n_undefined;
}

// Unload font from GPU memory (VRAM)
napi_value NodeRaylibUnloadFont(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Font font = get_Font_arg(args, 0, env, info)
  free(args);
  UnloadFont(font);
  return n_undefined;
}

// Export font as code file, returns true on success
napi_value NodeRaylibExportFontAsCode(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Font font = get_Font_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportFontAsCode(font, fileName);
  return return_bool(ret);
}

// Draw current FPS
napi_value NodeRaylibDrawFPS(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int posX = get_int_arg(args, 0, env, info)
  int posY = get_int_arg(args, 1, env, info)
  free(args);
  DrawFPS(posX, posY);
  return n_undefined;
}

// Draw text (using default font)
napi_value NodeRaylibDrawText(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  const char * text = get_string_arg(args, 0, env, info)
  int posX = get_int_arg(args, 1, env, info)
  int posY = get_int_arg(args, 2, env, info)
  int fontSize = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawText(text, posX, posY, fontSize, color);
  return n_undefined;
}

// Draw text using font and additional parameters
napi_value NodeRaylibDrawTextEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Font font = get_Font_arg(args, 0, env, info)
  const char * text = get_string_arg(args, 1, env, info)
  Vector2 position = get_Vector2_arg(args, 2, env, info)
  float fontSize = get_float_arg(args, 3, env, info)
  float spacing = get_float_arg(args, 4, env, info)
  Color tint = get_Color_arg(args, 5, env, info)
  free(args);
  DrawTextEx(font, text, position, fontSize, spacing, tint);
  return n_undefined;
}

// Draw text using Font and pro parameters (rotation)
napi_value NodeRaylibDrawTextPro(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 8);
  Font font = get_Font_arg(args, 0, env, info)
  const char * text = get_string_arg(args, 1, env, info)
  Vector2 position = get_Vector2_arg(args, 2, env, info)
  Vector2 origin = get_Vector2_arg(args, 3, env, info)
  float rotation = get_float_arg(args, 4, env, info)
  float fontSize = get_float_arg(args, 5, env, info)
  float spacing = get_float_arg(args, 6, env, info)
  Color tint = get_Color_arg(args, 7, env, info)
  free(args);
  DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, tint);
  return n_undefined;
}

// Draw one character (codepoint)
napi_value NodeRaylibDrawTextCodepoint(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Font font = get_Font_arg(args, 0, env, info)
  int codepoint = get_int_arg(args, 1, env, info)
  Vector2 position = get_Vector2_arg(args, 2, env, info)
  float fontSize = get_float_arg(args, 3, env, info)
  Color tint = get_Color_arg(args, 4, env, info)
  free(args);
  DrawTextCodepoint(font, codepoint, position, fontSize, tint);
  return n_undefined;
}

// Draw multiple character (codepoint)
napi_value NodeRaylibDrawTextCodepoints(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 7);
  Font font = get_Font_arg(args, 0, env, info)
  const int * codepoints = get_int_pointer_arg(args, 1, env, info)
  int codepointCount = get_int_arg(args, 2, env, info)
  Vector2 position = get_Vector2_arg(args, 3, env, info)
  float fontSize = get_float_arg(args, 4, env, info)
  float spacing = get_float_arg(args, 5, env, info)
  Color tint = get_Color_arg(args, 6, env, info)
  free(args);
  DrawTextCodepoints(font, codepoints, codepointCount, position, fontSize, spacing, tint);
  return n_undefined;
}

// Set vertical line spacing when drawing with line-breaks
napi_value NodeRaylibSetTextLineSpacing(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int spacing = get_int_arg(args, 0, env, info)
  free(args);
  SetTextLineSpacing(spacing);
  return n_undefined;
}

// Measure string width for default font
napi_value NodeRaylibMeasureText(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  const char * text = get_string_arg(args, 0, env, info)
  int fontSize = get_int_arg(args, 1, env, info)
  free(args);
  ret=MeasureText(text, fontSize);
  return return_int(ret);
}

// Measure string size for Font
napi_value NodeRaylibMeasureTextEx(napi_env env, napi_callback_info info) {
  Vector2 ret;
  napi_value* args = get_args(env, info, 4);
  Font font = get_Font_arg(args, 0, env, info)
  const char * text = get_string_arg(args, 1, env, info)
  float fontSize = get_float_arg(args, 2, env, info)
  float spacing = get_float_arg(args, 3, env, info)
  free(args);
  ret=MeasureTextEx(font, text, fontSize, spacing);
  return return_Vector2(ret);
}

// Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
napi_value NodeRaylibGetGlyphIndex(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  Font font = get_Font_arg(args, 0, env, info)
  int codepoint = get_int_arg(args, 1, env, info)
  free(args);
  ret=GetGlyphIndex(font, codepoint);
  return return_int(ret);
}

// Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
napi_value NodeRaylibGetGlyphInfo(napi_env env, napi_callback_info info) {
  GlyphInfo ret;
  napi_value* args = get_args(env, info, 2);
  Font font = get_Font_arg(args, 0, env, info)
  int codepoint = get_int_arg(args, 1, env, info)
  free(args);
  ret=GetGlyphInfo(font, codepoint);
  return return_GlyphInfo(ret);
}

// Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
napi_value NodeRaylibGetGlyphAtlasRec(napi_env env, napi_callback_info info) {
  Rectangle ret;
  napi_value* args = get_args(env, info, 2);
  Font font = get_Font_arg(args, 0, env, info)
  int codepoint = get_int_arg(args, 1, env, info)
  free(args);
  ret=GetGlyphAtlasRec(font, codepoint);
  return return_Rectangle(ret);
}

// Load UTF-8 text encoded from codepoints array
napi_value NodeRaylibLoadUTF8(napi_env env, napi_callback_info info) {
  char * ret;
  napi_value* args = get_args(env, info, 2);
  const int * codepoints = get_int_pointer_arg(args, 0, env, info)
  int length = get_int_arg(args, 1, env, info)
  free(args);
  ret=LoadUTF8(codepoints, length);
  return return_string(ret);
}

// Unload UTF-8 text encoded from codepoints array
napi_value NodeRaylibUnloadUTF8(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  char * text = get_string_arg(args, 0, env, info)
  free(args);
  UnloadUTF8(text);
  return n_undefined;
}

// Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
napi_value NodeRaylibLoadCodepoints(napi_env env, napi_callback_info info) {
  int * ret;
  napi_value* args = get_args(env, info, 2);
  const char * text = get_string_arg(args, 0, env, info)
  int * count = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=LoadCodepoints(text, count);
  return return_int_pointer(ret);
}

// Unload codepoints data from memory
napi_value NodeRaylibUnloadCodepoints(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int * codepoints = get_int_pointer_arg(args, 0, env, info)
  free(args);
  UnloadCodepoints(codepoints);
  return n_undefined;
}

// Get total number of codepoints in a UTF-8 encoded string
napi_value NodeRaylibGetCodepointCount(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=GetCodepointCount(text);
  return return_int(ret);
}

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
napi_value NodeRaylibGetCodepoint(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  const char * text = get_string_arg(args, 0, env, info)
  int * codepointSize = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=GetCodepoint(text, codepointSize);
  return return_int(ret);
}

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
napi_value NodeRaylibGetCodepointNext(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  const char * text = get_string_arg(args, 0, env, info)
  int * codepointSize = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=GetCodepointNext(text, codepointSize);
  return return_int(ret);
}

// Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
napi_value NodeRaylibGetCodepointPrevious(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  const char * text = get_string_arg(args, 0, env, info)
  int * codepointSize = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=GetCodepointPrevious(text, codepointSize);
  return return_int(ret);
}

// Encode one codepoint into UTF-8 byte array (array length returned as parameter)
napi_value NodeRaylibCodepointToUTF8(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 2);
  int codepoint = get_int_arg(args, 0, env, info)
  int * utf8Size = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=CodepointToUTF8(codepoint, utf8Size);
  return return_string(ret);
}

// Copy one string to another, returns bytes copied
napi_value NodeRaylibTextCopy(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  char * dst = get_string_arg(args, 0, env, info)
  const char * src = get_string_arg(args, 1, env, info)
  free(args);
  ret=TextCopy(dst, src);
  return return_int(ret);
}

// Check if two text string are equal
napi_value NodeRaylibTextIsEqual(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  const char * text1 = get_string_arg(args, 0, env, info)
  const char * text2 = get_string_arg(args, 1, env, info)
  free(args);
  ret=TextIsEqual(text1, text2);
  return return_bool(ret);
}

// Get text length, checks for '\0' ending
napi_value NodeRaylibTextLength(napi_env env, napi_callback_info info) {
  unsigned int ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextLength(text);
  return return_uint(ret);
}

// Get a piece of a text string
napi_value NodeRaylibTextSubtext(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 3);
  const char * text = get_string_arg(args, 0, env, info)
  int position = get_int_arg(args, 1, env, info)
  int length = get_int_arg(args, 2, env, info)
  free(args);
  ret=TextSubtext(text, position, length);
  return return_string(ret);
}

// Replace text string (WARNING: memory must be freed!)
napi_value NodeRaylibTextReplace(napi_env env, napi_callback_info info) {
  char * ret;
  napi_value* args = get_args(env, info, 3);
  const char * text = get_string_arg(args, 0, env, info)
  const char * replace = get_string_arg(args, 1, env, info)
  const char * by = get_string_arg(args, 2, env, info)
  free(args);
  ret=TextReplace(text, replace, by);
  return return_string(ret);
}

// Insert text in a position (WARNING: memory must be freed!)
napi_value NodeRaylibTextInsert(napi_env env, napi_callback_info info) {
  char * ret;
  napi_value* args = get_args(env, info, 3);
  const char * text = get_string_arg(args, 0, env, info)
  const char * insert = get_string_arg(args, 1, env, info)
  int position = get_int_arg(args, 2, env, info)
  free(args);
  ret=TextInsert(text, insert, position);
  return return_string(ret);
}

// Join text strings with delimiter
napi_value NodeRaylibTextJoin(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 3);
  const char ** textList = get_string_array_arg(args, 0, env, info)
  int count = get_int_arg(args, 1, env, info)
  const char * delimiter = get_string_arg(args, 2, env, info)
  free(args);
  ret=TextJoin(textList, count, delimiter);
  return return_string(ret);
}

// Split text into multiple strings
napi_value NodeRaylibTextSplit(napi_env env, napi_callback_info info) {
  const char ** ret;
  napi_value* args = get_args(env, info, 3);
  const char * text = get_string_arg(args, 0, env, info)
  char delimiter = get_char_arg(args, 1, env, info)
  int * count = get_int_pointer_arg(args, 2, env, info)
  free(args);
  ret=TextSplit(text, delimiter, count);
  return return_string_array(ret);
}

// Append text at specific position and move cursor!
napi_value NodeRaylibTextAppend(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  char * text = get_string_arg(args, 0, env, info)
  const char * append = get_string_arg(args, 1, env, info)
  int * position = get_int_pointer_arg(args, 2, env, info)
  free(args);
  TextAppend(text, append, position);
  return n_undefined;
}

// Find first text occurrence within a string
napi_value NodeRaylibTextFindIndex(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 2);
  const char * text = get_string_arg(args, 0, env, info)
  const char * find = get_string_arg(args, 1, env, info)
  free(args);
  ret=TextFindIndex(text, find);
  return return_int(ret);
}

// Get upper case version of provided string
napi_value NodeRaylibTextToUpper(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextToUpper(text);
  return return_string(ret);
}

// Get lower case version of provided string
napi_value NodeRaylibTextToLower(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextToLower(text);
  return return_string(ret);
}

// Get Pascal case notation version of provided string
napi_value NodeRaylibTextToPascal(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextToPascal(text);
  return return_string(ret);
}

// Get Snake case notation version of provided string
napi_value NodeRaylibTextToSnake(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextToSnake(text);
  return return_string(ret);
}

// Get Camel case notation version of provided string
napi_value NodeRaylibTextToCamel(napi_env env, napi_callback_info info) {
  const char * ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextToCamel(text);
  return return_string(ret);
}

// Get integer value from text (negative values not supported)
napi_value NodeRaylibTextToInteger(napi_env env, napi_callback_info info) {
  int ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextToInteger(text);
  return return_int(ret);
}

// Get float value from text (negative values not supported)
napi_value NodeRaylibTextToFloat(napi_env env, napi_callback_info info) {
  float ret;
  napi_value* args = get_args(env, info, 1);
  const char * text = get_string_arg(args, 0, env, info)
  free(args);
  ret=TextToFloat(text);
  return return_float(ret);
}

// Draw a line in 3D world space
napi_value NodeRaylibDrawLine3D(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector3 startPos = get_Vector3_arg(args, 0, env, info)
  Vector3 endPos = get_Vector3_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawLine3D(startPos, endPos, color);
  return n_undefined;
}

// Draw a point in 3D space, actually a small line
napi_value NodeRaylibDrawPoint3D(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  free(args);
  DrawPoint3D(position, color);
  return n_undefined;
}

// Draw a circle in 3D world space
napi_value NodeRaylibDrawCircle3D(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector3 center = get_Vector3_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  Vector3 rotationAxis = get_Vector3_arg(args, 2, env, info)
  float rotationAngle = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
  return n_undefined;
}

// Draw a color-filled triangle (vertex in counter-clockwise order!)
napi_value NodeRaylibDrawTriangle3D(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Vector3 v1 = get_Vector3_arg(args, 0, env, info)
  Vector3 v2 = get_Vector3_arg(args, 1, env, info)
  Vector3 v3 = get_Vector3_arg(args, 2, env, info)
  Color color = get_Color_arg(args, 3, env, info)
  free(args);
  DrawTriangle3D(v1, v2, v3, color);
  return n_undefined;
}

// Draw a triangle strip defined by points
napi_value NodeRaylibDrawTriangleStrip3D(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  const Vector3 * points = get_Vector3_pointer_arg(args, 0, env, info)
  int pointCount = get_int_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawTriangleStrip3D(points, pointCount, color);
  return n_undefined;
}

// Draw cube
napi_value NodeRaylibDrawCube(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  float width = get_float_arg(args, 1, env, info)
  float height = get_float_arg(args, 2, env, info)
  float length = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawCube(position, width, height, length, color);
  return n_undefined;
}

// Draw cube (Vector version)
napi_value NodeRaylibDrawCubeV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  Vector3 size = get_Vector3_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawCubeV(position, size, color);
  return n_undefined;
}

// Draw cube wires
napi_value NodeRaylibDrawCubeWires(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  float width = get_float_arg(args, 1, env, info)
  float height = get_float_arg(args, 2, env, info)
  float length = get_float_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawCubeWires(position, width, height, length, color);
  return n_undefined;
}

// Draw cube wires (Vector version)
napi_value NodeRaylibDrawCubeWiresV(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  Vector3 size = get_Vector3_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawCubeWiresV(position, size, color);
  return n_undefined;
}

// Draw sphere
napi_value NodeRaylibDrawSphere(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector3 centerPos = get_Vector3_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawSphere(centerPos, radius, color);
  return n_undefined;
}

// Draw sphere with extended parameters
napi_value NodeRaylibDrawSphereEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector3 centerPos = get_Vector3_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  int rings = get_int_arg(args, 2, env, info)
  int slices = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawSphereEx(centerPos, radius, rings, slices, color);
  return n_undefined;
}

// Draw sphere wires
napi_value NodeRaylibDrawSphereWires(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Vector3 centerPos = get_Vector3_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  int rings = get_int_arg(args, 2, env, info)
  int slices = get_int_arg(args, 3, env, info)
  Color color = get_Color_arg(args, 4, env, info)
  free(args);
  DrawSphereWires(centerPos, radius, rings, slices, color);
  return n_undefined;
}

// Draw a cylinder/cone
napi_value NodeRaylibDrawCylinder(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  float radiusTop = get_float_arg(args, 1, env, info)
  float radiusBottom = get_float_arg(args, 2, env, info)
  float height = get_float_arg(args, 3, env, info)
  int slices = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
  return n_undefined;
}

// Draw a cylinder with base at startPos and top at endPos
napi_value NodeRaylibDrawCylinderEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector3 startPos = get_Vector3_arg(args, 0, env, info)
  Vector3 endPos = get_Vector3_arg(args, 1, env, info)
  float startRadius = get_float_arg(args, 2, env, info)
  float endRadius = get_float_arg(args, 3, env, info)
  int sides = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
  return n_undefined;
}

// Draw a cylinder/cone wires
napi_value NodeRaylibDrawCylinderWires(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector3 position = get_Vector3_arg(args, 0, env, info)
  float radiusTop = get_float_arg(args, 1, env, info)
  float radiusBottom = get_float_arg(args, 2, env, info)
  float height = get_float_arg(args, 3, env, info)
  int slices = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
  return n_undefined;
}

// Draw a cylinder wires with base at startPos and top at endPos
napi_value NodeRaylibDrawCylinderWiresEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector3 startPos = get_Vector3_arg(args, 0, env, info)
  Vector3 endPos = get_Vector3_arg(args, 1, env, info)
  float startRadius = get_float_arg(args, 2, env, info)
  float endRadius = get_float_arg(args, 3, env, info)
  int sides = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);
  return n_undefined;
}

// Draw a capsule with the center of its sphere caps at startPos and endPos
napi_value NodeRaylibDrawCapsule(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector3 startPos = get_Vector3_arg(args, 0, env, info)
  Vector3 endPos = get_Vector3_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  int slices = get_int_arg(args, 3, env, info)
  int rings = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCapsule(startPos, endPos, radius, slices, rings, color);
  return n_undefined;
}

// Draw capsule wireframe with the center of its sphere caps at startPos and endPos
napi_value NodeRaylibDrawCapsuleWires(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Vector3 startPos = get_Vector3_arg(args, 0, env, info)
  Vector3 endPos = get_Vector3_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  int slices = get_int_arg(args, 3, env, info)
  int rings = get_int_arg(args, 4, env, info)
  Color color = get_Color_arg(args, 5, env, info)
  free(args);
  DrawCapsuleWires(startPos, endPos, radius, slices, rings, color);
  return n_undefined;
}

// Draw a plane XZ
napi_value NodeRaylibDrawPlane(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Vector3 centerPos = get_Vector3_arg(args, 0, env, info)
  Vector2 size = get_Vector2_arg(args, 1, env, info)
  Color color = get_Color_arg(args, 2, env, info)
  free(args);
  DrawPlane(centerPos, size, color);
  return n_undefined;
}

// Draw a ray line
napi_value NodeRaylibDrawRay(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Ray ray = get_Ray_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  free(args);
  DrawRay(ray, color);
  return n_undefined;
}

// Draw a grid (centered at (0, 0, 0))
napi_value NodeRaylibDrawGrid(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  int slices = get_int_arg(args, 0, env, info)
  float spacing = get_float_arg(args, 1, env, info)
  free(args);
  DrawGrid(slices, spacing);
  return n_undefined;
}

// Load model from files (meshes and materials)
napi_value NodeRaylibLoadModel(napi_env env, napi_callback_info info) {
  Model ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadModel(fileName);
  return return_Model(ret);
}

// Load model from generated mesh (default material)
napi_value NodeRaylibLoadModelFromMesh(napi_env env, napi_callback_info info) {
  Model ret;
  napi_value* args = get_args(env, info, 1);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  free(args);
  ret=LoadModelFromMesh(mesh);
  return return_Model(ret);
}

// Check if a model is valid (loaded in GPU, VAO/VBOs)
napi_value NodeRaylibIsModelValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Model model = get_Model_arg(args, 0, env, info)
  free(args);
  ret=IsModelValid(model);
  return return_bool(ret);
}

// Unload model (including meshes) from memory (RAM and/or VRAM)
napi_value NodeRaylibUnloadModel(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Model model = get_Model_arg(args, 0, env, info)
  free(args);
  UnloadModel(model);
  return n_undefined;
}

// Compute model bounding box limits (considers all meshes)
napi_value NodeRaylibGetModelBoundingBox(napi_env env, napi_callback_info info) {
  BoundingBox ret;
  napi_value* args = get_args(env, info, 1);
  Model model = get_Model_arg(args, 0, env, info)
  free(args);
  ret=GetModelBoundingBox(model);
  return return_BoundingBox(ret);
}

// Draw a model (with texture if set)
napi_value NodeRaylibDrawModel(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Model model = get_Model_arg(args, 0, env, info)
  Vector3 position = get_Vector3_arg(args, 1, env, info)
  float scale = get_float_arg(args, 2, env, info)
  Color tint = get_Color_arg(args, 3, env, info)
  free(args);
  DrawModel(model, position, scale, tint);
  return n_undefined;
}

// Draw a model with extended parameters
napi_value NodeRaylibDrawModelEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Model model = get_Model_arg(args, 0, env, info)
  Vector3 position = get_Vector3_arg(args, 1, env, info)
  Vector3 rotationAxis = get_Vector3_arg(args, 2, env, info)
  float rotationAngle = get_float_arg(args, 3, env, info)
  Vector3 scale = get_Vector3_arg(args, 4, env, info)
  Color tint = get_Color_arg(args, 5, env, info)
  free(args);
  DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
  return n_undefined;
}

// Draw a model wires (with texture if set)
napi_value NodeRaylibDrawModelWires(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Model model = get_Model_arg(args, 0, env, info)
  Vector3 position = get_Vector3_arg(args, 1, env, info)
  float scale = get_float_arg(args, 2, env, info)
  Color tint = get_Color_arg(args, 3, env, info)
  free(args);
  DrawModelWires(model, position, scale, tint);
  return n_undefined;
}

// Draw a model wires (with texture if set) with extended parameters
napi_value NodeRaylibDrawModelWiresEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Model model = get_Model_arg(args, 0, env, info)
  Vector3 position = get_Vector3_arg(args, 1, env, info)
  Vector3 rotationAxis = get_Vector3_arg(args, 2, env, info)
  float rotationAngle = get_float_arg(args, 3, env, info)
  Vector3 scale = get_Vector3_arg(args, 4, env, info)
  Color tint = get_Color_arg(args, 5, env, info)
  free(args);
  DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
  return n_undefined;
}

// Draw a model as points
napi_value NodeRaylibDrawModelPoints(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Model model = get_Model_arg(args, 0, env, info)
  Vector3 position = get_Vector3_arg(args, 1, env, info)
  float scale = get_float_arg(args, 2, env, info)
  Color tint = get_Color_arg(args, 3, env, info)
  free(args);
  DrawModelPoints(model, position, scale, tint);
  return n_undefined;
}

// Draw a model as points with extended parameters
napi_value NodeRaylibDrawModelPointsEx(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Model model = get_Model_arg(args, 0, env, info)
  Vector3 position = get_Vector3_arg(args, 1, env, info)
  Vector3 rotationAxis = get_Vector3_arg(args, 2, env, info)
  float rotationAngle = get_float_arg(args, 3, env, info)
  Vector3 scale = get_Vector3_arg(args, 4, env, info)
  Color tint = get_Color_arg(args, 5, env, info)
  free(args);
  DrawModelPointsEx(model, position, rotationAxis, rotationAngle, scale, tint);
  return n_undefined;
}

// Draw bounding box (wires)
napi_value NodeRaylibDrawBoundingBox(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  BoundingBox box = get_BoundingBox_arg(args, 0, env, info)
  Color color = get_Color_arg(args, 1, env, info)
  free(args);
  DrawBoundingBox(box, color);
  return n_undefined;
}

// Draw a billboard texture
napi_value NodeRaylibDrawBillboard(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Camera camera = get_Camera_arg(args, 0, env, info)
  Texture2D texture = get_Texture2D_arg(args, 1, env, info)
  Vector3 position = get_Vector3_arg(args, 2, env, info)
  float scale = get_float_arg(args, 3, env, info)
  Color tint = get_Color_arg(args, 4, env, info)
  free(args);
  DrawBillboard(camera, texture, position, scale, tint);
  return n_undefined;
}

// Draw a billboard texture defined by source
napi_value NodeRaylibDrawBillboardRec(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 6);
  Camera camera = get_Camera_arg(args, 0, env, info)
  Texture2D texture = get_Texture2D_arg(args, 1, env, info)
  Rectangle source = get_Rectangle_arg(args, 2, env, info)
  Vector3 position = get_Vector3_arg(args, 3, env, info)
  Vector2 size = get_Vector2_arg(args, 4, env, info)
  Color tint = get_Color_arg(args, 5, env, info)
  free(args);
  DrawBillboardRec(camera, texture, source, position, size, tint);
  return n_undefined;
}

// Draw a billboard texture defined by source and rotation
napi_value NodeRaylibDrawBillboardPro(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 9);
  Camera camera = get_Camera_arg(args, 0, env, info)
  Texture2D texture = get_Texture2D_arg(args, 1, env, info)
  Rectangle source = get_Rectangle_arg(args, 2, env, info)
  Vector3 position = get_Vector3_arg(args, 3, env, info)
  Vector3 up = get_Vector3_arg(args, 4, env, info)
  Vector2 size = get_Vector2_arg(args, 5, env, info)
  Vector2 origin = get_Vector2_arg(args, 6, env, info)
  float rotation = get_float_arg(args, 7, env, info)
  Color tint = get_Color_arg(args, 8, env, info)
  free(args);
  DrawBillboardPro(camera, texture, source, position, up, size, origin, rotation, tint);
  return n_undefined;
}

// Upload mesh vertex data in GPU and provide VAO/VBO ids
napi_value NodeRaylibUploadMesh(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Mesh * mesh = get_Mesh_pointer_arg(args, 0, env, info)
  bool dynamic = get_bool_arg(args, 1, env, info)
  free(args);
  UploadMesh(mesh, dynamic);
  return n_undefined;
}

// Update mesh vertex data in GPU for a specific buffer index
napi_value NodeRaylibUpdateMeshBuffer(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 5);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  int index = get_int_arg(args, 1, env, info)
  const void * data = get_undefined_arg(args, 2, env, info)
  int dataSize = get_int_arg(args, 3, env, info)
  int offset = get_int_arg(args, 4, env, info)
  free(args);
  UpdateMeshBuffer(mesh, index, data, dataSize, offset);
  return n_undefined;
}

// Unload mesh data from CPU and GPU
napi_value NodeRaylibUnloadMesh(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  free(args);
  UnloadMesh(mesh);
  return n_undefined;
}

// Draw a 3d mesh with material and transform
napi_value NodeRaylibDrawMesh(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  Material material = get_Material_arg(args, 1, env, info)
  Matrix transform = get_Matrix_arg(args, 2, env, info)
  free(args);
  DrawMesh(mesh, material, transform);
  return n_undefined;
}

// Draw multiple mesh instances with material and different transforms
napi_value NodeRaylibDrawMeshInstanced(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  Material material = get_Material_arg(args, 1, env, info)
  const Matrix * transforms = get_Matrix_pointer_arg(args, 2, env, info)
  int instances = get_int_arg(args, 3, env, info)
  free(args);
  DrawMeshInstanced(mesh, material, transforms, instances);
  return n_undefined;
}

// Compute mesh bounding box limits
napi_value NodeRaylibGetMeshBoundingBox(napi_env env, napi_callback_info info) {
  BoundingBox ret;
  napi_value* args = get_args(env, info, 1);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  free(args);
  ret=GetMeshBoundingBox(mesh);
  return return_BoundingBox(ret);
}

// Compute mesh tangents
napi_value NodeRaylibGenMeshTangents(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Mesh * mesh = get_Mesh_pointer_arg(args, 0, env, info)
  free(args);
  GenMeshTangents(mesh);
  return n_undefined;
}

// Export mesh data to file, returns true on success
napi_value NodeRaylibExportMesh(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportMesh(mesh, fileName);
  return return_bool(ret);
}

// Export mesh as code file (.h) defining multiple arrays of vertex attributes
napi_value NodeRaylibExportMeshAsCode(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Mesh mesh = get_Mesh_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportMeshAsCode(mesh, fileName);
  return return_bool(ret);
}

// Generate polygonal mesh
napi_value NodeRaylibGenMeshPoly(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 2);
  int sides = get_int_arg(args, 0, env, info)
  float radius = get_float_arg(args, 1, env, info)
  free(args);
  ret=GenMeshPoly(sides, radius);
  return return_Mesh(ret);
}

// Generate plane mesh (with subdivisions)
napi_value NodeRaylibGenMeshPlane(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 4);
  float width = get_float_arg(args, 0, env, info)
  float length = get_float_arg(args, 1, env, info)
  int resX = get_int_arg(args, 2, env, info)
  int resZ = get_int_arg(args, 3, env, info)
  free(args);
  ret=GenMeshPlane(width, length, resX, resZ);
  return return_Mesh(ret);
}

// Generate cuboid mesh
napi_value NodeRaylibGenMeshCube(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 3);
  float width = get_float_arg(args, 0, env, info)
  float height = get_float_arg(args, 1, env, info)
  float length = get_float_arg(args, 2, env, info)
  free(args);
  ret=GenMeshCube(width, height, length);
  return return_Mesh(ret);
}

// Generate sphere mesh (standard sphere)
napi_value NodeRaylibGenMeshSphere(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 3);
  float radius = get_float_arg(args, 0, env, info)
  int rings = get_int_arg(args, 1, env, info)
  int slices = get_int_arg(args, 2, env, info)
  free(args);
  ret=GenMeshSphere(radius, rings, slices);
  return return_Mesh(ret);
}

// Generate half-sphere mesh (no bottom cap)
napi_value NodeRaylibGenMeshHemiSphere(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 3);
  float radius = get_float_arg(args, 0, env, info)
  int rings = get_int_arg(args, 1, env, info)
  int slices = get_int_arg(args, 2, env, info)
  free(args);
  ret=GenMeshHemiSphere(radius, rings, slices);
  return return_Mesh(ret);
}

// Generate cylinder mesh
napi_value NodeRaylibGenMeshCylinder(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 3);
  float radius = get_float_arg(args, 0, env, info)
  float height = get_float_arg(args, 1, env, info)
  int slices = get_int_arg(args, 2, env, info)
  free(args);
  ret=GenMeshCylinder(radius, height, slices);
  return return_Mesh(ret);
}

// Generate cone/pyramid mesh
napi_value NodeRaylibGenMeshCone(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 3);
  float radius = get_float_arg(args, 0, env, info)
  float height = get_float_arg(args, 1, env, info)
  int slices = get_int_arg(args, 2, env, info)
  free(args);
  ret=GenMeshCone(radius, height, slices);
  return return_Mesh(ret);
}

// Generate torus mesh
napi_value NodeRaylibGenMeshTorus(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 4);
  float radius = get_float_arg(args, 0, env, info)
  float size = get_float_arg(args, 1, env, info)
  int radSeg = get_int_arg(args, 2, env, info)
  int sides = get_int_arg(args, 3, env, info)
  free(args);
  ret=GenMeshTorus(radius, size, radSeg, sides);
  return return_Mesh(ret);
}

// Generate trefoil knot mesh
napi_value NodeRaylibGenMeshKnot(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 4);
  float radius = get_float_arg(args, 0, env, info)
  float size = get_float_arg(args, 1, env, info)
  int radSeg = get_int_arg(args, 2, env, info)
  int sides = get_int_arg(args, 3, env, info)
  free(args);
  ret=GenMeshKnot(radius, size, radSeg, sides);
  return return_Mesh(ret);
}

// Generate heightmap mesh from image data
napi_value NodeRaylibGenMeshHeightmap(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 2);
  Image heightmap = get_Image_arg(args, 0, env, info)
  Vector3 size = get_Vector3_arg(args, 1, env, info)
  free(args);
  ret=GenMeshHeightmap(heightmap, size);
  return return_Mesh(ret);
}

// Generate cubes-based map mesh from image data
napi_value NodeRaylibGenMeshCubicmap(napi_env env, napi_callback_info info) {
  Mesh ret;
  napi_value* args = get_args(env, info, 2);
  Image cubicmap = get_Image_arg(args, 0, env, info)
  Vector3 cubeSize = get_Vector3_arg(args, 1, env, info)
  free(args);
  ret=GenMeshCubicmap(cubicmap, cubeSize);
  return return_Mesh(ret);
}

// Load materials from model file
napi_value NodeRaylibLoadMaterials(napi_env env, napi_callback_info info) {
  Material * ret;
  napi_value* args = get_args(env, info, 2);
  const char * fileName = get_string_arg(args, 0, env, info)
  int * materialCount = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=LoadMaterials(fileName, materialCount);
  return return_Material_pointer(ret);
}

// Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
napi_value NodeRaylibLoadMaterialDefault(napi_env env, napi_callback_info info) {
  Material ret;
  ret=LoadMaterialDefault();
  return return_Material(ret);
}

// Check if a material is valid (shader assigned, map textures loaded in GPU)
napi_value NodeRaylibIsMaterialValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Material material = get_Material_arg(args, 0, env, info)
  free(args);
  ret=IsMaterialValid(material);
  return return_bool(ret);
}

// Unload material from GPU memory (VRAM)
napi_value NodeRaylibUnloadMaterial(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Material material = get_Material_arg(args, 0, env, info)
  free(args);
  UnloadMaterial(material);
  return n_undefined;
}

// Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
napi_value NodeRaylibSetMaterialTexture(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Material * material = get_Material_pointer_arg(args, 0, env, info)
  int mapType = get_int_arg(args, 1, env, info)
  Texture2D texture = get_Texture2D_arg(args, 2, env, info)
  free(args);
  SetMaterialTexture(material, mapType, texture);
  return n_undefined;
}

// Set material for a mesh
napi_value NodeRaylibSetModelMeshMaterial(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Model * model = get_Model_pointer_arg(args, 0, env, info)
  int meshId = get_int_arg(args, 1, env, info)
  int materialId = get_int_arg(args, 2, env, info)
  free(args);
  SetModelMeshMaterial(model, meshId, materialId);
  return n_undefined;
}

// Load model animations from file
napi_value NodeRaylibLoadModelAnimations(napi_env env, napi_callback_info info) {
  ModelAnimation * ret;
  napi_value* args = get_args(env, info, 2);
  const char * fileName = get_string_arg(args, 0, env, info)
  int * animCount = get_int_pointer_arg(args, 1, env, info)
  free(args);
  ret=LoadModelAnimations(fileName, animCount);
  return return_ModelAnimation_pointer(ret);
}

// Update model animation pose (CPU)
napi_value NodeRaylibUpdateModelAnimation(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Model model = get_Model_arg(args, 0, env, info)
  ModelAnimation anim = get_ModelAnimation_arg(args, 1, env, info)
  int frame = get_int_arg(args, 2, env, info)
  free(args);
  UpdateModelAnimation(model, anim, frame);
  return n_undefined;
}

// Update model animation mesh bone matrices (GPU skinning)
napi_value NodeRaylibUpdateModelAnimationBones(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Model model = get_Model_arg(args, 0, env, info)
  ModelAnimation anim = get_ModelAnimation_arg(args, 1, env, info)
  int frame = get_int_arg(args, 2, env, info)
  free(args);
  UpdateModelAnimationBones(model, anim, frame);
  return n_undefined;
}

// Unload animation data
napi_value NodeRaylibUnloadModelAnimation(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  ModelAnimation anim = get_ModelAnimation_arg(args, 0, env, info)
  free(args);
  UnloadModelAnimation(anim);
  return n_undefined;
}

// Unload animation array data
napi_value NodeRaylibUnloadModelAnimations(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  ModelAnimation * animations = get_ModelAnimation_pointer_arg(args, 0, env, info)
  int animCount = get_int_arg(args, 1, env, info)
  free(args);
  UnloadModelAnimations(animations, animCount);
  return n_undefined;
}

// Check model animation skeleton match
napi_value NodeRaylibIsModelAnimationValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Model model = get_Model_arg(args, 0, env, info)
  ModelAnimation anim = get_ModelAnimation_arg(args, 1, env, info)
  free(args);
  ret=IsModelAnimationValid(model, anim);
  return return_bool(ret);
}

// Check collision between two spheres
napi_value NodeRaylibCheckCollisionSpheres(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 4);
  Vector3 center1 = get_Vector3_arg(args, 0, env, info)
  float radius1 = get_float_arg(args, 1, env, info)
  Vector3 center2 = get_Vector3_arg(args, 2, env, info)
  float radius2 = get_float_arg(args, 3, env, info)
  free(args);
  ret=CheckCollisionSpheres(center1, radius1, center2, radius2);
  return return_bool(ret);
}

// Check collision between two bounding boxes
napi_value NodeRaylibCheckCollisionBoxes(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  BoundingBox box1 = get_BoundingBox_arg(args, 0, env, info)
  BoundingBox box2 = get_BoundingBox_arg(args, 1, env, info)
  free(args);
  ret=CheckCollisionBoxes(box1, box2);
  return return_bool(ret);
}

// Check collision between box and sphere
napi_value NodeRaylibCheckCollisionBoxSphere(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 3);
  BoundingBox box = get_BoundingBox_arg(args, 0, env, info)
  Vector3 center = get_Vector3_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  free(args);
  ret=CheckCollisionBoxSphere(box, center, radius);
  return return_bool(ret);
}

// Get collision info between ray and sphere
napi_value NodeRaylibGetRayCollisionSphere(napi_env env, napi_callback_info info) {
  RayCollision ret;
  napi_value* args = get_args(env, info, 3);
  Ray ray = get_Ray_arg(args, 0, env, info)
  Vector3 center = get_Vector3_arg(args, 1, env, info)
  float radius = get_float_arg(args, 2, env, info)
  free(args);
  ret=GetRayCollisionSphere(ray, center, radius);
  return return_RayCollision(ret);
}

// Get collision info between ray and box
napi_value NodeRaylibGetRayCollisionBox(napi_env env, napi_callback_info info) {
  RayCollision ret;
  napi_value* args = get_args(env, info, 2);
  Ray ray = get_Ray_arg(args, 0, env, info)
  BoundingBox box = get_BoundingBox_arg(args, 1, env, info)
  free(args);
  ret=GetRayCollisionBox(ray, box);
  return return_RayCollision(ret);
}

// Get collision info between ray and mesh
napi_value NodeRaylibGetRayCollisionMesh(napi_env env, napi_callback_info info) {
  RayCollision ret;
  napi_value* args = get_args(env, info, 3);
  Ray ray = get_Ray_arg(args, 0, env, info)
  Mesh mesh = get_Mesh_arg(args, 1, env, info)
  Matrix transform = get_Matrix_arg(args, 2, env, info)
  free(args);
  ret=GetRayCollisionMesh(ray, mesh, transform);
  return return_RayCollision(ret);
}

// Get collision info between ray and triangle
napi_value NodeRaylibGetRayCollisionTriangle(napi_env env, napi_callback_info info) {
  RayCollision ret;
  napi_value* args = get_args(env, info, 4);
  Ray ray = get_Ray_arg(args, 0, env, info)
  Vector3 p1 = get_Vector3_arg(args, 1, env, info)
  Vector3 p2 = get_Vector3_arg(args, 2, env, info)
  Vector3 p3 = get_Vector3_arg(args, 3, env, info)
  free(args);
  ret=GetRayCollisionTriangle(ray, p1, p2, p3);
  return return_RayCollision(ret);
}

// Get collision info between ray and quad
napi_value NodeRaylibGetRayCollisionQuad(napi_env env, napi_callback_info info) {
  RayCollision ret;
  napi_value* args = get_args(env, info, 5);
  Ray ray = get_Ray_arg(args, 0, env, info)
  Vector3 p1 = get_Vector3_arg(args, 1, env, info)
  Vector3 p2 = get_Vector3_arg(args, 2, env, info)
  Vector3 p3 = get_Vector3_arg(args, 3, env, info)
  Vector3 p4 = get_Vector3_arg(args, 4, env, info)
  free(args);
  ret=GetRayCollisionQuad(ray, p1, p2, p3, p4);
  return return_RayCollision(ret);
}

// Initialize audio device and context
napi_value NodeRaylibInitAudioDevice(napi_env env, napi_callback_info info) {
  InitAudioDevice();
  return n_undefined;
}

// Close the audio device and context
napi_value NodeRaylibCloseAudioDevice(napi_env env, napi_callback_info info) {
  CloseAudioDevice();
  return n_undefined;
}

// Check if audio device has been initialized successfully
napi_value NodeRaylibIsAudioDeviceReady(napi_env env, napi_callback_info info) {
  bool ret;
  ret=IsAudioDeviceReady();
  return return_bool(ret);
}

// Set master volume (listener)
napi_value NodeRaylibSetMasterVolume(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  float volume = get_float_arg(args, 0, env, info)
  free(args);
  SetMasterVolume(volume);
  return n_undefined;
}

// Get master volume (listener)
napi_value NodeRaylibGetMasterVolume(napi_env env, napi_callback_info info) {
  float ret;
  ret=GetMasterVolume();
  return return_float(ret);
}

// Load wave data from file
napi_value NodeRaylibLoadWave(napi_env env, napi_callback_info info) {
  Wave ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadWave(fileName);
  return return_Wave(ret);
}

// Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
napi_value NodeRaylibLoadWaveFromMemory(napi_env env, napi_callback_info info) {
  Wave ret;
  napi_value* args = get_args(env, info, 3);
  const char * fileType = get_string_arg(args, 0, env, info)
  const unsigned char * fileData = get_uchar_pointer_arg(args, 1, env, info)
  int dataSize = get_int_arg(args, 2, env, info)
  free(args);
  ret=LoadWaveFromMemory(fileType, fileData, dataSize);
  return return_Wave(ret);
}

// Checks if wave data is valid (data loaded and parameters)
napi_value NodeRaylibIsWaveValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Wave wave = get_Wave_arg(args, 0, env, info)
  free(args);
  ret=IsWaveValid(wave);
  return return_bool(ret);
}

// Load sound from file
napi_value NodeRaylibLoadSound(napi_env env, napi_callback_info info) {
  Sound ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadSound(fileName);
  return return_Sound(ret);
}

// Load sound from wave data
napi_value NodeRaylibLoadSoundFromWave(napi_env env, napi_callback_info info) {
  Sound ret;
  napi_value* args = get_args(env, info, 1);
  Wave wave = get_Wave_arg(args, 0, env, info)
  free(args);
  ret=LoadSoundFromWave(wave);
  return return_Sound(ret);
}

// Create a new sound that shares the same sample data as the source sound, does not own the sound data
napi_value NodeRaylibLoadSoundAlias(napi_env env, napi_callback_info info) {
  Sound ret;
  napi_value* args = get_args(env, info, 1);
  Sound source = get_Sound_arg(args, 0, env, info)
  free(args);
  ret=LoadSoundAlias(source);
  return return_Sound(ret);
}

// Checks if a sound is valid (data loaded and buffers initialized)
napi_value NodeRaylibIsSoundValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Sound sound = get_Sound_arg(args, 0, env, info)
  free(args);
  ret=IsSoundValid(sound);
  return return_bool(ret);
}

// Update sound buffer with new data
napi_value NodeRaylibUpdateSound(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Sound sound = get_Sound_arg(args, 0, env, info)
  const void * data = get_undefined_arg(args, 1, env, info)
  int sampleCount = get_int_arg(args, 2, env, info)
  free(args);
  UpdateSound(sound, data, sampleCount);
  return n_undefined;
}

// Unload wave data
napi_value NodeRaylibUnloadWave(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Wave wave = get_Wave_arg(args, 0, env, info)
  free(args);
  UnloadWave(wave);
  return n_undefined;
}

// Unload sound
napi_value NodeRaylibUnloadSound(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Sound sound = get_Sound_arg(args, 0, env, info)
  free(args);
  UnloadSound(sound);
  return n_undefined;
}

// Unload a sound alias (does not deallocate sample data)
napi_value NodeRaylibUnloadSoundAlias(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Sound alias = get_Sound_arg(args, 0, env, info)
  free(args);
  UnloadSoundAlias(alias);
  return n_undefined;
}

// Export wave data to file, returns true on success
napi_value NodeRaylibExportWave(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Wave wave = get_Wave_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportWave(wave, fileName);
  return return_bool(ret);
}

// Export wave sample data to code (.h), returns true on success
napi_value NodeRaylibExportWaveAsCode(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 2);
  Wave wave = get_Wave_arg(args, 0, env, info)
  const char * fileName = get_string_arg(args, 1, env, info)
  free(args);
  ret=ExportWaveAsCode(wave, fileName);
  return return_bool(ret);
}

// Play a sound
napi_value NodeRaylibPlaySound(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Sound sound = get_Sound_arg(args, 0, env, info)
  free(args);
  PlaySound(sound);
  return n_undefined;
}

// Stop playing a sound
napi_value NodeRaylibStopSound(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Sound sound = get_Sound_arg(args, 0, env, info)
  free(args);
  StopSound(sound);
  return n_undefined;
}

// Pause a sound
napi_value NodeRaylibPauseSound(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Sound sound = get_Sound_arg(args, 0, env, info)
  free(args);
  PauseSound(sound);
  return n_undefined;
}

// Resume a paused sound
napi_value NodeRaylibResumeSound(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Sound sound = get_Sound_arg(args, 0, env, info)
  free(args);
  ResumeSound(sound);
  return n_undefined;
}

// Check if a sound is currently playing
napi_value NodeRaylibIsSoundPlaying(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Sound sound = get_Sound_arg(args, 0, env, info)
  free(args);
  ret=IsSoundPlaying(sound);
  return return_bool(ret);
}

// Set volume for a sound (1.0 is max level)
napi_value NodeRaylibSetSoundVolume(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Sound sound = get_Sound_arg(args, 0, env, info)
  float volume = get_float_arg(args, 1, env, info)
  free(args);
  SetSoundVolume(sound, volume);
  return n_undefined;
}

// Set pitch for a sound (1.0 is base level)
napi_value NodeRaylibSetSoundPitch(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Sound sound = get_Sound_arg(args, 0, env, info)
  float pitch = get_float_arg(args, 1, env, info)
  free(args);
  SetSoundPitch(sound, pitch);
  return n_undefined;
}

// Set pan for a sound (0.5 is center)
napi_value NodeRaylibSetSoundPan(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Sound sound = get_Sound_arg(args, 0, env, info)
  float pan = get_float_arg(args, 1, env, info)
  free(args);
  SetSoundPan(sound, pan);
  return n_undefined;
}

// Copy a wave to a new wave
napi_value NodeRaylibWaveCopy(napi_env env, napi_callback_info info) {
  Wave ret;
  napi_value* args = get_args(env, info, 1);
  Wave wave = get_Wave_arg(args, 0, env, info)
  free(args);
  ret=WaveCopy(wave);
  return return_Wave(ret);
}

// Crop a wave to defined frames range
napi_value NodeRaylibWaveCrop(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  Wave * wave = get_Wave_pointer_arg(args, 0, env, info)
  int initFrame = get_int_arg(args, 1, env, info)
  int finalFrame = get_int_arg(args, 2, env, info)
  free(args);
  WaveCrop(wave, initFrame, finalFrame);
  return n_undefined;
}

// Convert wave data to desired format
napi_value NodeRaylibWaveFormat(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 4);
  Wave * wave = get_Wave_pointer_arg(args, 0, env, info)
  int sampleRate = get_int_arg(args, 1, env, info)
  int sampleSize = get_int_arg(args, 2, env, info)
  int channels = get_int_arg(args, 3, env, info)
  free(args);
  WaveFormat(wave, sampleRate, sampleSize, channels);
  return n_undefined;
}

// Load samples data from wave as a 32bit float data array
napi_value NodeRaylibLoadWaveSamples(napi_env env, napi_callback_info info) {
  float * ret;
  napi_value* args = get_args(env, info, 1);
  Wave wave = get_Wave_arg(args, 0, env, info)
  free(args);
  ret=LoadWaveSamples(wave);
  return return_float_pointer(ret);
}

// Unload samples data loaded with LoadWaveSamples()
napi_value NodeRaylibUnloadWaveSamples(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  float * samples = get_float_pointer_arg(args, 0, env, info)
  free(args);
  UnloadWaveSamples(samples);
  return n_undefined;
}

// Load music stream from file
napi_value NodeRaylibLoadMusicStream(napi_env env, napi_callback_info info) {
  Music ret;
  napi_value* args = get_args(env, info, 1);
  const char * fileName = get_string_arg(args, 0, env, info)
  free(args);
  ret=LoadMusicStream(fileName);
  return return_Music(ret);
}

// Load music stream from data
napi_value NodeRaylibLoadMusicStreamFromMemory(napi_env env, napi_callback_info info) {
  Music ret;
  napi_value* args = get_args(env, info, 3);
  const char * fileType = get_string_arg(args, 0, env, info)
  const unsigned char * data = get_uchar_pointer_arg(args, 1, env, info)
  int dataSize = get_int_arg(args, 2, env, info)
  free(args);
  ret=LoadMusicStreamFromMemory(fileType, data, dataSize);
  return return_Music(ret);
}

// Checks if a music stream is valid (context and buffers initialized)
napi_value NodeRaylibIsMusicValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  ret=IsMusicValid(music);
  return return_bool(ret);
}

// Unload music stream
napi_value NodeRaylibUnloadMusicStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  UnloadMusicStream(music);
  return n_undefined;
}

// Start music playing
napi_value NodeRaylibPlayMusicStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  PlayMusicStream(music);
  return n_undefined;
}

// Check if music is playing
napi_value NodeRaylibIsMusicStreamPlaying(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  ret=IsMusicStreamPlaying(music);
  return return_bool(ret);
}

// Updates buffers for music streaming
napi_value NodeRaylibUpdateMusicStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  UpdateMusicStream(music);
  return n_undefined;
}

// Stop music playing
napi_value NodeRaylibStopMusicStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  StopMusicStream(music);
  return n_undefined;
}

// Pause music playing
napi_value NodeRaylibPauseMusicStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  PauseMusicStream(music);
  return n_undefined;
}

// Resume playing paused music
napi_value NodeRaylibResumeMusicStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  ResumeMusicStream(music);
  return n_undefined;
}

// Seek music to a position (in seconds)
napi_value NodeRaylibSeekMusicStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Music music = get_Music_arg(args, 0, env, info)
  float position = get_float_arg(args, 1, env, info)
  free(args);
  SeekMusicStream(music, position);
  return n_undefined;
}

// Set volume for music (1.0 is max level)
napi_value NodeRaylibSetMusicVolume(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Music music = get_Music_arg(args, 0, env, info)
  float volume = get_float_arg(args, 1, env, info)
  free(args);
  SetMusicVolume(music, volume);
  return n_undefined;
}

// Set pitch for a music (1.0 is base level)
napi_value NodeRaylibSetMusicPitch(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Music music = get_Music_arg(args, 0, env, info)
  float pitch = get_float_arg(args, 1, env, info)
  free(args);
  SetMusicPitch(music, pitch);
  return n_undefined;
}

// Set pan for a music (0.5 is center)
napi_value NodeRaylibSetMusicPan(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  Music music = get_Music_arg(args, 0, env, info)
  float pan = get_float_arg(args, 1, env, info)
  free(args);
  SetMusicPan(music, pan);
  return n_undefined;
}

// Get music time length (in seconds)
napi_value NodeRaylibGetMusicTimeLength(napi_env env, napi_callback_info info) {
  float ret;
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  ret=GetMusicTimeLength(music);
  return return_float(ret);
}

// Get current music time played (in seconds)
napi_value NodeRaylibGetMusicTimePlayed(napi_env env, napi_callback_info info) {
  float ret;
  napi_value* args = get_args(env, info, 1);
  Music music = get_Music_arg(args, 0, env, info)
  free(args);
  ret=GetMusicTimePlayed(music);
  return return_float(ret);
}

// Load audio stream (to stream raw audio pcm data)
napi_value NodeRaylibLoadAudioStream(napi_env env, napi_callback_info info) {
  AudioStream ret;
  napi_value* args = get_args(env, info, 3);
  unsigned int sampleRate = get_uint_arg(args, 0, env, info)
  unsigned int sampleSize = get_uint_arg(args, 1, env, info)
  unsigned int channels = get_uint_arg(args, 2, env, info)
  free(args);
  ret=LoadAudioStream(sampleRate, sampleSize, channels);
  return return_AudioStream(ret);
}

// Checks if an audio stream is valid (buffers initialized)
napi_value NodeRaylibIsAudioStreamValid(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  ret=IsAudioStreamValid(stream);
  return return_bool(ret);
}

// Unload audio stream and free memory
napi_value NodeRaylibUnloadAudioStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  UnloadAudioStream(stream);
  return n_undefined;
}

// Update audio stream buffers with data
napi_value NodeRaylibUpdateAudioStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 3);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  const void * data = get_undefined_arg(args, 1, env, info)
  int frameCount = get_int_arg(args, 2, env, info)
  free(args);
  UpdateAudioStream(stream, data, frameCount);
  return n_undefined;
}

// Check if any audio stream buffers requires refill
napi_value NodeRaylibIsAudioStreamProcessed(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  ret=IsAudioStreamProcessed(stream);
  return return_bool(ret);
}

// Play audio stream
napi_value NodeRaylibPlayAudioStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  PlayAudioStream(stream);
  return n_undefined;
}

// Pause audio stream
napi_value NodeRaylibPauseAudioStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  PauseAudioStream(stream);
  return n_undefined;
}

// Resume audio stream
napi_value NodeRaylibResumeAudioStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  ResumeAudioStream(stream);
  return n_undefined;
}

// Check if audio stream is playing
napi_value NodeRaylibIsAudioStreamPlaying(napi_env env, napi_callback_info info) {
  bool ret;
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  ret=IsAudioStreamPlaying(stream);
  return return_bool(ret);
}

// Stop audio stream
napi_value NodeRaylibStopAudioStream(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  free(args);
  StopAudioStream(stream);
  return n_undefined;
}

// Set volume for audio stream (1.0 is max level)
napi_value NodeRaylibSetAudioStreamVolume(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  float volume = get_float_arg(args, 1, env, info)
  free(args);
  SetAudioStreamVolume(stream, volume);
  return n_undefined;
}

// Set pitch for audio stream (1.0 is base level)
napi_value NodeRaylibSetAudioStreamPitch(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  float pitch = get_float_arg(args, 1, env, info)
  free(args);
  SetAudioStreamPitch(stream, pitch);
  return n_undefined;
}

// Set pan for audio stream (0.5 is centered)
napi_value NodeRaylibSetAudioStreamPan(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  float pan = get_float_arg(args, 1, env, info)
  free(args);
  SetAudioStreamPan(stream, pan);
  return n_undefined;
}

// Default size for new audio streams
napi_value NodeRaylibSetAudioStreamBufferSizeDefault(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  int size = get_int_arg(args, 0, env, info)
  free(args);
  SetAudioStreamBufferSizeDefault(size);
  return n_undefined;
}

// Audio thread callback to request new data
napi_value NodeRaylibSetAudioStreamCallback(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  AudioCallback callback = get_undefined_arg(args, 1, env, info)
  free(args);
  SetAudioStreamCallback(stream, callback);
  return n_undefined;
}

// Attach audio stream processor to stream, receives the samples as 'float'
napi_value NodeRaylibAttachAudioStreamProcessor(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  AudioCallback processor = get_undefined_arg(args, 1, env, info)
  free(args);
  AttachAudioStreamProcessor(stream, processor);
  return n_undefined;
}

// Detach audio stream processor from stream
napi_value NodeRaylibDetachAudioStreamProcessor(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 2);
  AudioStream stream = get_AudioStream_arg(args, 0, env, info)
  AudioCallback processor = get_undefined_arg(args, 1, env, info)
  free(args);
  DetachAudioStreamProcessor(stream, processor);
  return n_undefined;
}

// Attach audio stream processor to the entire audio pipeline, receives the samples as 'float'
napi_value NodeRaylibAttachAudioMixedProcessor(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AudioCallback processor = get_undefined_arg(args, 0, env, info)
  free(args);
  AttachAudioMixedProcessor(processor);
  return n_undefined;
}

// Detach audio stream processor from the entire audio pipeline
napi_value NodeRaylibDetachAudioMixedProcessor(napi_env env, napi_callback_info info) {
  napi_value* args = get_args(env, info, 1);
  AudioCallback processor = get_undefined_arg(args, 0, env, info)
  free(args);
  DetachAudioMixedProcessor(processor);
  return n_undefined;
}

static napi_value Init(napi_env env, napi_value exports) {
  // not sure if there are already better imports for this
  napi_get_undefined(env, &n_undefined);
  napi_get_boolean(env, true, &n_true);
  napi_get_boolean(env, false, &n_false);

  napi_value fn;

  NAPI_CALL(env, napi_create_function(env, "SayHello", NAPI_AUTO_LENGTH, NodeRaylibSayHello, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SayHello", fn));
  
  NAPI_CALL(env, napi_create_function(env, "InitWindow", NAPI_AUTO_LENGTH, NodeRaylibInitWindow, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "InitWindow", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CloseWindow", NAPI_AUTO_LENGTH, NodeRaylibCloseWindow, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CloseWindow", fn));
    
  NAPI_CALL(env, napi_create_function(env, "WindowShouldClose", NAPI_AUTO_LENGTH, NodeRaylibWindowShouldClose, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "WindowShouldClose", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowReady", NAPI_AUTO_LENGTH, NodeRaylibIsWindowReady, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowReady", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowFullscreen", NAPI_AUTO_LENGTH, NodeRaylibIsWindowFullscreen, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowFullscreen", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowHidden", NAPI_AUTO_LENGTH, NodeRaylibIsWindowHidden, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowHidden", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowMinimized", NAPI_AUTO_LENGTH, NodeRaylibIsWindowMinimized, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowMinimized", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowMaximized", NAPI_AUTO_LENGTH, NodeRaylibIsWindowMaximized, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowMaximized", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowFocused", NAPI_AUTO_LENGTH, NodeRaylibIsWindowFocused, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowFocused", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowResized", NAPI_AUTO_LENGTH, NodeRaylibIsWindowResized, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowResized", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWindowState", NAPI_AUTO_LENGTH, NodeRaylibIsWindowState, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWindowState", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowState", NAPI_AUTO_LENGTH, NodeRaylibSetWindowState, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowState", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ClearWindowState", NAPI_AUTO_LENGTH, NodeRaylibClearWindowState, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ClearWindowState", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ToggleFullscreen", NAPI_AUTO_LENGTH, NodeRaylibToggleFullscreen, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ToggleFullscreen", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ToggleBorderlessWindowed", NAPI_AUTO_LENGTH, NodeRaylibToggleBorderlessWindowed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ToggleBorderlessWindowed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MaximizeWindow", NAPI_AUTO_LENGTH, NodeRaylibMaximizeWindow, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MaximizeWindow", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MinimizeWindow", NAPI_AUTO_LENGTH, NodeRaylibMinimizeWindow, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MinimizeWindow", fn));
    
  NAPI_CALL(env, napi_create_function(env, "RestoreWindow", NAPI_AUTO_LENGTH, NodeRaylibRestoreWindow, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "RestoreWindow", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowIcon", NAPI_AUTO_LENGTH, NodeRaylibSetWindowIcon, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowIcon", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowIcons", NAPI_AUTO_LENGTH, NodeRaylibSetWindowIcons, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowIcons", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowTitle", NAPI_AUTO_LENGTH, NodeRaylibSetWindowTitle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowTitle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowPosition", NAPI_AUTO_LENGTH, NodeRaylibSetWindowPosition, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowPosition", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowMonitor", NAPI_AUTO_LENGTH, NodeRaylibSetWindowMonitor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowMonitor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowMinSize", NAPI_AUTO_LENGTH, NodeRaylibSetWindowMinSize, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowMinSize", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowMaxSize", NAPI_AUTO_LENGTH, NodeRaylibSetWindowMaxSize, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowMaxSize", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowSize", NAPI_AUTO_LENGTH, NodeRaylibSetWindowSize, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowSize", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowOpacity", NAPI_AUTO_LENGTH, NodeRaylibSetWindowOpacity, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowOpacity", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetWindowFocused", NAPI_AUTO_LENGTH, NodeRaylibSetWindowFocused, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetWindowFocused", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetWindowHandle", NAPI_AUTO_LENGTH, NodeRaylibGetWindowHandle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetWindowHandle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetScreenWidth", NAPI_AUTO_LENGTH, NodeRaylibGetScreenWidth, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetScreenWidth", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetScreenHeight", NAPI_AUTO_LENGTH, NodeRaylibGetScreenHeight, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetScreenHeight", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRenderWidth", NAPI_AUTO_LENGTH, NodeRaylibGetRenderWidth, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRenderWidth", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRenderHeight", NAPI_AUTO_LENGTH, NodeRaylibGetRenderHeight, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRenderHeight", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorCount", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorCount, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorCount", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCurrentMonitor", NAPI_AUTO_LENGTH, NodeRaylibGetCurrentMonitor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCurrentMonitor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorPosition", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorPosition, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorPosition", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorWidth", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorWidth, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorWidth", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorHeight", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorHeight, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorHeight", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorPhysicalWidth", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorPhysicalWidth, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorPhysicalWidth", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorPhysicalHeight", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorPhysicalHeight, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorPhysicalHeight", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorRefreshRate", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorRefreshRate, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorRefreshRate", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetWindowPosition", NAPI_AUTO_LENGTH, NodeRaylibGetWindowPosition, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetWindowPosition", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetWindowScaleDPI", NAPI_AUTO_LENGTH, NodeRaylibGetWindowScaleDPI, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetWindowScaleDPI", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMonitorName", NAPI_AUTO_LENGTH, NodeRaylibGetMonitorName, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMonitorName", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetClipboardText", NAPI_AUTO_LENGTH, NodeRaylibSetClipboardText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetClipboardText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetClipboardText", NAPI_AUTO_LENGTH, NodeRaylibGetClipboardText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetClipboardText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetClipboardImage", NAPI_AUTO_LENGTH, NodeRaylibGetClipboardImage, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetClipboardImage", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EnableEventWaiting", NAPI_AUTO_LENGTH, NodeRaylibEnableEventWaiting, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EnableEventWaiting", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DisableEventWaiting", NAPI_AUTO_LENGTH, NodeRaylibDisableEventWaiting, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DisableEventWaiting", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ShowCursor", NAPI_AUTO_LENGTH, NodeRaylibShowCursor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ShowCursor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "HideCursor", NAPI_AUTO_LENGTH, NodeRaylibHideCursor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "HideCursor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsCursorHidden", NAPI_AUTO_LENGTH, NodeRaylibIsCursorHidden, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsCursorHidden", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EnableCursor", NAPI_AUTO_LENGTH, NodeRaylibEnableCursor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EnableCursor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DisableCursor", NAPI_AUTO_LENGTH, NodeRaylibDisableCursor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DisableCursor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsCursorOnScreen", NAPI_AUTO_LENGTH, NodeRaylibIsCursorOnScreen, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsCursorOnScreen", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ClearBackground", NAPI_AUTO_LENGTH, NodeRaylibClearBackground, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ClearBackground", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginDrawing", NAPI_AUTO_LENGTH, NodeRaylibBeginDrawing, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginDrawing", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndDrawing", NAPI_AUTO_LENGTH, NodeRaylibEndDrawing, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndDrawing", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginMode2D", NAPI_AUTO_LENGTH, NodeRaylibBeginMode2D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginMode2D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndMode2D", NAPI_AUTO_LENGTH, NodeRaylibEndMode2D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndMode2D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginMode3D", NAPI_AUTO_LENGTH, NodeRaylibBeginMode3D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginMode3D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndMode3D", NAPI_AUTO_LENGTH, NodeRaylibEndMode3D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndMode3D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginTextureMode", NAPI_AUTO_LENGTH, NodeRaylibBeginTextureMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginTextureMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndTextureMode", NAPI_AUTO_LENGTH, NodeRaylibEndTextureMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndTextureMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginShaderMode", NAPI_AUTO_LENGTH, NodeRaylibBeginShaderMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginShaderMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndShaderMode", NAPI_AUTO_LENGTH, NodeRaylibEndShaderMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndShaderMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginBlendMode", NAPI_AUTO_LENGTH, NodeRaylibBeginBlendMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginBlendMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndBlendMode", NAPI_AUTO_LENGTH, NodeRaylibEndBlendMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndBlendMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginScissorMode", NAPI_AUTO_LENGTH, NodeRaylibBeginScissorMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginScissorMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndScissorMode", NAPI_AUTO_LENGTH, NodeRaylibEndScissorMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndScissorMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "BeginVrStereoMode", NAPI_AUTO_LENGTH, NodeRaylibBeginVrStereoMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "BeginVrStereoMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EndVrStereoMode", NAPI_AUTO_LENGTH, NodeRaylibEndVrStereoMode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EndVrStereoMode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadVrStereoConfig", NAPI_AUTO_LENGTH, NodeRaylibLoadVrStereoConfig, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadVrStereoConfig", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadVrStereoConfig", NAPI_AUTO_LENGTH, NodeRaylibUnloadVrStereoConfig, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadVrStereoConfig", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadShader", NAPI_AUTO_LENGTH, NodeRaylibLoadShader, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadShader", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadShaderFromMemory", NAPI_AUTO_LENGTH, NodeRaylibLoadShaderFromMemory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadShaderFromMemory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsShaderValid", NAPI_AUTO_LENGTH, NodeRaylibIsShaderValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsShaderValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetShaderLocation", NAPI_AUTO_LENGTH, NodeRaylibGetShaderLocation, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetShaderLocation", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetShaderLocationAttrib", NAPI_AUTO_LENGTH, NodeRaylibGetShaderLocationAttrib, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetShaderLocationAttrib", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetShaderValue", NAPI_AUTO_LENGTH, NodeRaylibSetShaderValue, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetShaderValue", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetShaderValueV", NAPI_AUTO_LENGTH, NodeRaylibSetShaderValueV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetShaderValueV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetShaderValueMatrix", NAPI_AUTO_LENGTH, NodeRaylibSetShaderValueMatrix, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetShaderValueMatrix", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetShaderValueTexture", NAPI_AUTO_LENGTH, NodeRaylibSetShaderValueTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetShaderValueTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadShader", NAPI_AUTO_LENGTH, NodeRaylibUnloadShader, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadShader", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetScreenToWorldRay", NAPI_AUTO_LENGTH, NodeRaylibGetScreenToWorldRay, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetScreenToWorldRay", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetScreenToWorldRayEx", NAPI_AUTO_LENGTH, NodeRaylibGetScreenToWorldRayEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetScreenToWorldRayEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetWorldToScreen", NAPI_AUTO_LENGTH, NodeRaylibGetWorldToScreen, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetWorldToScreen", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetWorldToScreenEx", NAPI_AUTO_LENGTH, NodeRaylibGetWorldToScreenEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetWorldToScreenEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetWorldToScreen2D", NAPI_AUTO_LENGTH, NodeRaylibGetWorldToScreen2D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetWorldToScreen2D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetScreenToWorld2D", NAPI_AUTO_LENGTH, NodeRaylibGetScreenToWorld2D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetScreenToWorld2D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCameraMatrix", NAPI_AUTO_LENGTH, NodeRaylibGetCameraMatrix, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCameraMatrix", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCameraMatrix2D", NAPI_AUTO_LENGTH, NodeRaylibGetCameraMatrix2D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCameraMatrix2D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetTargetFPS", NAPI_AUTO_LENGTH, NodeRaylibSetTargetFPS, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetTargetFPS", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFrameTime", NAPI_AUTO_LENGTH, NodeRaylibGetFrameTime, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFrameTime", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetTime", NAPI_AUTO_LENGTH, NodeRaylibGetTime, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetTime", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFPS", NAPI_AUTO_LENGTH, NodeRaylibGetFPS, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFPS", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SwapScreenBuffer", NAPI_AUTO_LENGTH, NodeRaylibSwapScreenBuffer, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SwapScreenBuffer", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PollInputEvents", NAPI_AUTO_LENGTH, NodeRaylibPollInputEvents, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PollInputEvents", fn));
    
  NAPI_CALL(env, napi_create_function(env, "WaitTime", NAPI_AUTO_LENGTH, NodeRaylibWaitTime, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "WaitTime", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetRandomSeed", NAPI_AUTO_LENGTH, NodeRaylibSetRandomSeed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetRandomSeed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRandomValue", NAPI_AUTO_LENGTH, NodeRaylibGetRandomValue, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRandomValue", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadRandomSequence", NAPI_AUTO_LENGTH, NodeRaylibLoadRandomSequence, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadRandomSequence", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadRandomSequence", NAPI_AUTO_LENGTH, NodeRaylibUnloadRandomSequence, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadRandomSequence", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TakeScreenshot", NAPI_AUTO_LENGTH, NodeRaylibTakeScreenshot, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TakeScreenshot", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetConfigFlags", NAPI_AUTO_LENGTH, NodeRaylibSetConfigFlags, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetConfigFlags", fn));
    
  NAPI_CALL(env, napi_create_function(env, "OpenURL", NAPI_AUTO_LENGTH, NodeRaylibOpenURL, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "OpenURL", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetTraceLogLevel", NAPI_AUTO_LENGTH, NodeRaylibSetTraceLogLevel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetTraceLogLevel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MemAlloc", NAPI_AUTO_LENGTH, NodeRaylibMemAlloc, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MemAlloc", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MemRealloc", NAPI_AUTO_LENGTH, NodeRaylibMemRealloc, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MemRealloc", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MemFree", NAPI_AUTO_LENGTH, NodeRaylibMemFree, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MemFree", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetTraceLogCallback", NAPI_AUTO_LENGTH, NodeRaylibSetTraceLogCallback, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetTraceLogCallback", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetLoadFileDataCallback", NAPI_AUTO_LENGTH, NodeRaylibSetLoadFileDataCallback, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetLoadFileDataCallback", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetSaveFileDataCallback", NAPI_AUTO_LENGTH, NodeRaylibSetSaveFileDataCallback, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetSaveFileDataCallback", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetLoadFileTextCallback", NAPI_AUTO_LENGTH, NodeRaylibSetLoadFileTextCallback, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetLoadFileTextCallback", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetSaveFileTextCallback", NAPI_AUTO_LENGTH, NodeRaylibSetSaveFileTextCallback, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetSaveFileTextCallback", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadFileData", NAPI_AUTO_LENGTH, NodeRaylibLoadFileData, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadFileData", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadFileData", NAPI_AUTO_LENGTH, NodeRaylibUnloadFileData, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadFileData", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SaveFileData", NAPI_AUTO_LENGTH, NodeRaylibSaveFileData, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SaveFileData", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportDataAsCode", NAPI_AUTO_LENGTH, NodeRaylibExportDataAsCode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportDataAsCode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadFileText", NAPI_AUTO_LENGTH, NodeRaylibLoadFileText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadFileText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadFileText", NAPI_AUTO_LENGTH, NodeRaylibUnloadFileText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadFileText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SaveFileText", NAPI_AUTO_LENGTH, NodeRaylibSaveFileText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SaveFileText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "FileExists", NAPI_AUTO_LENGTH, NodeRaylibFileExists, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "FileExists", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DirectoryExists", NAPI_AUTO_LENGTH, NodeRaylibDirectoryExists, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DirectoryExists", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsFileExtension", NAPI_AUTO_LENGTH, NodeRaylibIsFileExtension, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsFileExtension", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFileLength", NAPI_AUTO_LENGTH, NodeRaylibGetFileLength, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFileLength", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFileExtension", NAPI_AUTO_LENGTH, NodeRaylibGetFileExtension, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFileExtension", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFileName", NAPI_AUTO_LENGTH, NodeRaylibGetFileName, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFileName", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFileNameWithoutExt", NAPI_AUTO_LENGTH, NodeRaylibGetFileNameWithoutExt, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFileNameWithoutExt", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetDirectoryPath", NAPI_AUTO_LENGTH, NodeRaylibGetDirectoryPath, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetDirectoryPath", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetPrevDirectoryPath", NAPI_AUTO_LENGTH, NodeRaylibGetPrevDirectoryPath, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetPrevDirectoryPath", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetWorkingDirectory", NAPI_AUTO_LENGTH, NodeRaylibGetWorkingDirectory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetWorkingDirectory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetApplicationDirectory", NAPI_AUTO_LENGTH, NodeRaylibGetApplicationDirectory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetApplicationDirectory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MakeDirectory", NAPI_AUTO_LENGTH, NodeRaylibMakeDirectory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MakeDirectory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ChangeDirectory", NAPI_AUTO_LENGTH, NodeRaylibChangeDirectory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ChangeDirectory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsPathFile", NAPI_AUTO_LENGTH, NodeRaylibIsPathFile, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsPathFile", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsFileNameValid", NAPI_AUTO_LENGTH, NodeRaylibIsFileNameValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsFileNameValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadDirectoryFiles", NAPI_AUTO_LENGTH, NodeRaylibLoadDirectoryFiles, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadDirectoryFiles", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadDirectoryFilesEx", NAPI_AUTO_LENGTH, NodeRaylibLoadDirectoryFilesEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadDirectoryFilesEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadDirectoryFiles", NAPI_AUTO_LENGTH, NodeRaylibUnloadDirectoryFiles, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadDirectoryFiles", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsFileDropped", NAPI_AUTO_LENGTH, NodeRaylibIsFileDropped, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsFileDropped", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadDroppedFiles", NAPI_AUTO_LENGTH, NodeRaylibLoadDroppedFiles, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadDroppedFiles", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadDroppedFiles", NAPI_AUTO_LENGTH, NodeRaylibUnloadDroppedFiles, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadDroppedFiles", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFileModTime", NAPI_AUTO_LENGTH, NodeRaylibGetFileModTime, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFileModTime", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CompressData", NAPI_AUTO_LENGTH, NodeRaylibCompressData, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CompressData", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DecompressData", NAPI_AUTO_LENGTH, NodeRaylibDecompressData, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DecompressData", fn));
    
  NAPI_CALL(env, napi_create_function(env, "EncodeDataBase64", NAPI_AUTO_LENGTH, NodeRaylibEncodeDataBase64, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "EncodeDataBase64", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DecodeDataBase64", NAPI_AUTO_LENGTH, NodeRaylibDecodeDataBase64, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DecodeDataBase64", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ComputeCRC32", NAPI_AUTO_LENGTH, NodeRaylibComputeCRC32, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ComputeCRC32", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ComputeMD5", NAPI_AUTO_LENGTH, NodeRaylibComputeMD5, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ComputeMD5", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ComputeSHA1", NAPI_AUTO_LENGTH, NodeRaylibComputeSHA1, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ComputeSHA1", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadAutomationEventList", NAPI_AUTO_LENGTH, NodeRaylibLoadAutomationEventList, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadAutomationEventList", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadAutomationEventList", NAPI_AUTO_LENGTH, NodeRaylibUnloadAutomationEventList, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadAutomationEventList", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportAutomationEventList", NAPI_AUTO_LENGTH, NodeRaylibExportAutomationEventList, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportAutomationEventList", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetAutomationEventList", NAPI_AUTO_LENGTH, NodeRaylibSetAutomationEventList, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetAutomationEventList", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetAutomationEventBaseFrame", NAPI_AUTO_LENGTH, NodeRaylibSetAutomationEventBaseFrame, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetAutomationEventBaseFrame", fn));
    
  NAPI_CALL(env, napi_create_function(env, "StartAutomationEventRecording", NAPI_AUTO_LENGTH, NodeRaylibStartAutomationEventRecording, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "StartAutomationEventRecording", fn));
    
  NAPI_CALL(env, napi_create_function(env, "StopAutomationEventRecording", NAPI_AUTO_LENGTH, NodeRaylibStopAutomationEventRecording, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "StopAutomationEventRecording", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PlayAutomationEvent", NAPI_AUTO_LENGTH, NodeRaylibPlayAutomationEvent, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PlayAutomationEvent", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsKeyPressed", NAPI_AUTO_LENGTH, NodeRaylibIsKeyPressed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsKeyPressed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsKeyPressedRepeat", NAPI_AUTO_LENGTH, NodeRaylibIsKeyPressedRepeat, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsKeyPressedRepeat", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsKeyDown", NAPI_AUTO_LENGTH, NodeRaylibIsKeyDown, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsKeyDown", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsKeyReleased", NAPI_AUTO_LENGTH, NodeRaylibIsKeyReleased, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsKeyReleased", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsKeyUp", NAPI_AUTO_LENGTH, NodeRaylibIsKeyUp, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsKeyUp", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetKeyPressed", NAPI_AUTO_LENGTH, NodeRaylibGetKeyPressed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetKeyPressed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCharPressed", NAPI_AUTO_LENGTH, NodeRaylibGetCharPressed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCharPressed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetExitKey", NAPI_AUTO_LENGTH, NodeRaylibSetExitKey, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetExitKey", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsGamepadAvailable", NAPI_AUTO_LENGTH, NodeRaylibIsGamepadAvailable, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsGamepadAvailable", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGamepadName", NAPI_AUTO_LENGTH, NodeRaylibGetGamepadName, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGamepadName", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsGamepadButtonPressed", NAPI_AUTO_LENGTH, NodeRaylibIsGamepadButtonPressed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsGamepadButtonPressed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsGamepadButtonDown", NAPI_AUTO_LENGTH, NodeRaylibIsGamepadButtonDown, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsGamepadButtonDown", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsGamepadButtonReleased", NAPI_AUTO_LENGTH, NodeRaylibIsGamepadButtonReleased, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsGamepadButtonReleased", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsGamepadButtonUp", NAPI_AUTO_LENGTH, NodeRaylibIsGamepadButtonUp, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsGamepadButtonUp", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGamepadButtonPressed", NAPI_AUTO_LENGTH, NodeRaylibGetGamepadButtonPressed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGamepadButtonPressed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGamepadAxisCount", NAPI_AUTO_LENGTH, NodeRaylibGetGamepadAxisCount, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGamepadAxisCount", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGamepadAxisMovement", NAPI_AUTO_LENGTH, NodeRaylibGetGamepadAxisMovement, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGamepadAxisMovement", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetGamepadMappings", NAPI_AUTO_LENGTH, NodeRaylibSetGamepadMappings, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetGamepadMappings", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetGamepadVibration", NAPI_AUTO_LENGTH, NodeRaylibSetGamepadVibration, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetGamepadVibration", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsMouseButtonPressed", NAPI_AUTO_LENGTH, NodeRaylibIsMouseButtonPressed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsMouseButtonPressed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsMouseButtonDown", NAPI_AUTO_LENGTH, NodeRaylibIsMouseButtonDown, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsMouseButtonDown", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsMouseButtonReleased", NAPI_AUTO_LENGTH, NodeRaylibIsMouseButtonReleased, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsMouseButtonReleased", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsMouseButtonUp", NAPI_AUTO_LENGTH, NodeRaylibIsMouseButtonUp, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsMouseButtonUp", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMouseX", NAPI_AUTO_LENGTH, NodeRaylibGetMouseX, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMouseX", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMouseY", NAPI_AUTO_LENGTH, NodeRaylibGetMouseY, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMouseY", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMousePosition", NAPI_AUTO_LENGTH, NodeRaylibGetMousePosition, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMousePosition", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMouseDelta", NAPI_AUTO_LENGTH, NodeRaylibGetMouseDelta, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMouseDelta", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMousePosition", NAPI_AUTO_LENGTH, NodeRaylibSetMousePosition, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMousePosition", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMouseOffset", NAPI_AUTO_LENGTH, NodeRaylibSetMouseOffset, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMouseOffset", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMouseScale", NAPI_AUTO_LENGTH, NodeRaylibSetMouseScale, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMouseScale", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMouseWheelMove", NAPI_AUTO_LENGTH, NodeRaylibGetMouseWheelMove, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMouseWheelMove", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMouseWheelMoveV", NAPI_AUTO_LENGTH, NodeRaylibGetMouseWheelMoveV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMouseWheelMoveV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMouseCursor", NAPI_AUTO_LENGTH, NodeRaylibSetMouseCursor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMouseCursor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetTouchX", NAPI_AUTO_LENGTH, NodeRaylibGetTouchX, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetTouchX", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetTouchY", NAPI_AUTO_LENGTH, NodeRaylibGetTouchY, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetTouchY", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetTouchPosition", NAPI_AUTO_LENGTH, NodeRaylibGetTouchPosition, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetTouchPosition", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetTouchPointId", NAPI_AUTO_LENGTH, NodeRaylibGetTouchPointId, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetTouchPointId", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetTouchPointCount", NAPI_AUTO_LENGTH, NodeRaylibGetTouchPointCount, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetTouchPointCount", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetGesturesEnabled", NAPI_AUTO_LENGTH, NodeRaylibSetGesturesEnabled, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetGesturesEnabled", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsGestureDetected", NAPI_AUTO_LENGTH, NodeRaylibIsGestureDetected, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsGestureDetected", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGestureDetected", NAPI_AUTO_LENGTH, NodeRaylibGetGestureDetected, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGestureDetected", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGestureHoldDuration", NAPI_AUTO_LENGTH, NodeRaylibGetGestureHoldDuration, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGestureHoldDuration", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGestureDragVector", NAPI_AUTO_LENGTH, NodeRaylibGetGestureDragVector, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGestureDragVector", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGestureDragAngle", NAPI_AUTO_LENGTH, NodeRaylibGetGestureDragAngle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGestureDragAngle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGesturePinchVector", NAPI_AUTO_LENGTH, NodeRaylibGetGesturePinchVector, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGesturePinchVector", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGesturePinchAngle", NAPI_AUTO_LENGTH, NodeRaylibGetGesturePinchAngle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGesturePinchAngle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateCamera", NAPI_AUTO_LENGTH, NodeRaylibUpdateCamera, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateCamera", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateCameraPro", NAPI_AUTO_LENGTH, NodeRaylibUpdateCameraPro, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateCameraPro", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetShapesTexture", NAPI_AUTO_LENGTH, NodeRaylibSetShapesTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetShapesTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetShapesTexture", NAPI_AUTO_LENGTH, NodeRaylibGetShapesTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetShapesTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetShapesTextureRectangle", NAPI_AUTO_LENGTH, NodeRaylibGetShapesTextureRectangle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetShapesTextureRectangle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawPixel", NAPI_AUTO_LENGTH, NodeRaylibDrawPixel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawPixel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawPixelV", NAPI_AUTO_LENGTH, NodeRaylibDrawPixelV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawPixelV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawLine", NAPI_AUTO_LENGTH, NodeRaylibDrawLine, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawLine", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawLineV", NAPI_AUTO_LENGTH, NodeRaylibDrawLineV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawLineV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawLineEx", NAPI_AUTO_LENGTH, NodeRaylibDrawLineEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawLineEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawLineStrip", NAPI_AUTO_LENGTH, NodeRaylibDrawLineStrip, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawLineStrip", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawLineBezier", NAPI_AUTO_LENGTH, NodeRaylibDrawLineBezier, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawLineBezier", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircle", NAPI_AUTO_LENGTH, NodeRaylibDrawCircle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircleSector", NAPI_AUTO_LENGTH, NodeRaylibDrawCircleSector, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircleSector", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircleSectorLines", NAPI_AUTO_LENGTH, NodeRaylibDrawCircleSectorLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircleSectorLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircleGradient", NAPI_AUTO_LENGTH, NodeRaylibDrawCircleGradient, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircleGradient", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircleV", NAPI_AUTO_LENGTH, NodeRaylibDrawCircleV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircleV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircleLines", NAPI_AUTO_LENGTH, NodeRaylibDrawCircleLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircleLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircleLinesV", NAPI_AUTO_LENGTH, NodeRaylibDrawCircleLinesV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircleLinesV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawEllipse", NAPI_AUTO_LENGTH, NodeRaylibDrawEllipse, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawEllipse", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawEllipseLines", NAPI_AUTO_LENGTH, NodeRaylibDrawEllipseLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawEllipseLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRing", NAPI_AUTO_LENGTH, NodeRaylibDrawRing, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRing", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRingLines", NAPI_AUTO_LENGTH, NodeRaylibDrawRingLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRingLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangle", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleV", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleRec", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectanglePro", NAPI_AUTO_LENGTH, NodeRaylibDrawRectanglePro, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectanglePro", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleGradientV", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleGradientV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleGradientV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleGradientH", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleGradientH, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleGradientH", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleGradientEx", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleGradientEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleGradientEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleLines", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleLinesEx", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleLinesEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleLinesEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleRounded", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleRounded, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleRounded", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleRoundedLines", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleRoundedLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleRoundedLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRectangleRoundedLinesEx", NAPI_AUTO_LENGTH, NodeRaylibDrawRectangleRoundedLinesEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRectangleRoundedLinesEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTriangle", NAPI_AUTO_LENGTH, NodeRaylibDrawTriangle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTriangle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTriangleLines", NAPI_AUTO_LENGTH, NodeRaylibDrawTriangleLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTriangleLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTriangleFan", NAPI_AUTO_LENGTH, NodeRaylibDrawTriangleFan, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTriangleFan", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTriangleStrip", NAPI_AUTO_LENGTH, NodeRaylibDrawTriangleStrip, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTriangleStrip", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawPoly", NAPI_AUTO_LENGTH, NodeRaylibDrawPoly, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawPoly", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawPolyLines", NAPI_AUTO_LENGTH, NodeRaylibDrawPolyLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawPolyLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawPolyLinesEx", NAPI_AUTO_LENGTH, NodeRaylibDrawPolyLinesEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawPolyLinesEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineLinear", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineLinear, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineLinear", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineBasis", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineBasis, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineBasis", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineCatmullRom", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineCatmullRom, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineCatmullRom", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineBezierQuadratic", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineBezierQuadratic, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineBezierQuadratic", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineBezierCubic", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineBezierCubic, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineBezierCubic", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineSegmentLinear", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineSegmentLinear, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineSegmentLinear", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineSegmentBasis", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineSegmentBasis, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineSegmentBasis", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineSegmentCatmullRom", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineSegmentCatmullRom, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineSegmentCatmullRom", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineSegmentBezierQuadratic", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineSegmentBezierQuadratic, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineSegmentBezierQuadratic", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSplineSegmentBezierCubic", NAPI_AUTO_LENGTH, NodeRaylibDrawSplineSegmentBezierCubic, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSplineSegmentBezierCubic", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetSplinePointLinear", NAPI_AUTO_LENGTH, NodeRaylibGetSplinePointLinear, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetSplinePointLinear", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetSplinePointBasis", NAPI_AUTO_LENGTH, NodeRaylibGetSplinePointBasis, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetSplinePointBasis", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetSplinePointCatmullRom", NAPI_AUTO_LENGTH, NodeRaylibGetSplinePointCatmullRom, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetSplinePointCatmullRom", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetSplinePointBezierQuad", NAPI_AUTO_LENGTH, NodeRaylibGetSplinePointBezierQuad, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetSplinePointBezierQuad", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetSplinePointBezierCubic", NAPI_AUTO_LENGTH, NodeRaylibGetSplinePointBezierCubic, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetSplinePointBezierCubic", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionRecs", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionRecs, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionRecs", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionCircles", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionCircles, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionCircles", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionCircleRec", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionCircleRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionCircleRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionCircleLine", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionCircleLine, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionCircleLine", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionPointRec", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionPointRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionPointRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionPointCircle", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionPointCircle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionPointCircle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionPointTriangle", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionPointTriangle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionPointTriangle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionPointLine", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionPointLine, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionPointLine", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionPointPoly", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionPointPoly, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionPointPoly", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionLines", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCollisionRec", NAPI_AUTO_LENGTH, NodeRaylibGetCollisionRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCollisionRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImage", NAPI_AUTO_LENGTH, NodeRaylibLoadImage, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImage", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImageRaw", NAPI_AUTO_LENGTH, NodeRaylibLoadImageRaw, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImageRaw", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImageAnim", NAPI_AUTO_LENGTH, NodeRaylibLoadImageAnim, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImageAnim", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImageAnimFromMemory", NAPI_AUTO_LENGTH, NodeRaylibLoadImageAnimFromMemory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImageAnimFromMemory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImageFromMemory", NAPI_AUTO_LENGTH, NodeRaylibLoadImageFromMemory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImageFromMemory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImageFromTexture", NAPI_AUTO_LENGTH, NodeRaylibLoadImageFromTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImageFromTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImageFromScreen", NAPI_AUTO_LENGTH, NodeRaylibLoadImageFromScreen, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImageFromScreen", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsImageValid", NAPI_AUTO_LENGTH, NodeRaylibIsImageValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsImageValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadImage", NAPI_AUTO_LENGTH, NodeRaylibUnloadImage, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadImage", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportImage", NAPI_AUTO_LENGTH, NodeRaylibExportImage, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportImage", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportImageToMemory", NAPI_AUTO_LENGTH, NodeRaylibExportImageToMemory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportImageToMemory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportImageAsCode", NAPI_AUTO_LENGTH, NodeRaylibExportImageAsCode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportImageAsCode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageColor", NAPI_AUTO_LENGTH, NodeRaylibGenImageColor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageColor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageGradientLinear", NAPI_AUTO_LENGTH, NodeRaylibGenImageGradientLinear, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageGradientLinear", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageGradientRadial", NAPI_AUTO_LENGTH, NodeRaylibGenImageGradientRadial, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageGradientRadial", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageGradientSquare", NAPI_AUTO_LENGTH, NodeRaylibGenImageGradientSquare, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageGradientSquare", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageChecked", NAPI_AUTO_LENGTH, NodeRaylibGenImageChecked, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageChecked", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageWhiteNoise", NAPI_AUTO_LENGTH, NodeRaylibGenImageWhiteNoise, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageWhiteNoise", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImagePerlinNoise", NAPI_AUTO_LENGTH, NodeRaylibGenImagePerlinNoise, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImagePerlinNoise", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageCellular", NAPI_AUTO_LENGTH, NodeRaylibGenImageCellular, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageCellular", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageText", NAPI_AUTO_LENGTH, NodeRaylibGenImageText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageCopy", NAPI_AUTO_LENGTH, NodeRaylibImageCopy, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageCopy", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageFromImage", NAPI_AUTO_LENGTH, NodeRaylibImageFromImage, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageFromImage", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageFromChannel", NAPI_AUTO_LENGTH, NodeRaylibImageFromChannel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageFromChannel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageText", NAPI_AUTO_LENGTH, NodeRaylibImageText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageTextEx", NAPI_AUTO_LENGTH, NodeRaylibImageTextEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageTextEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageFormat", NAPI_AUTO_LENGTH, NodeRaylibImageFormat, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageFormat", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageToPOT", NAPI_AUTO_LENGTH, NodeRaylibImageToPOT, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageToPOT", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageCrop", NAPI_AUTO_LENGTH, NodeRaylibImageCrop, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageCrop", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageAlphaCrop", NAPI_AUTO_LENGTH, NodeRaylibImageAlphaCrop, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageAlphaCrop", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageAlphaClear", NAPI_AUTO_LENGTH, NodeRaylibImageAlphaClear, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageAlphaClear", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageAlphaMask", NAPI_AUTO_LENGTH, NodeRaylibImageAlphaMask, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageAlphaMask", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageAlphaPremultiply", NAPI_AUTO_LENGTH, NodeRaylibImageAlphaPremultiply, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageAlphaPremultiply", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageBlurGaussian", NAPI_AUTO_LENGTH, NodeRaylibImageBlurGaussian, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageBlurGaussian", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageKernelConvolution", NAPI_AUTO_LENGTH, NodeRaylibImageKernelConvolution, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageKernelConvolution", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageResize", NAPI_AUTO_LENGTH, NodeRaylibImageResize, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageResize", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageResizeNN", NAPI_AUTO_LENGTH, NodeRaylibImageResizeNN, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageResizeNN", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageResizeCanvas", NAPI_AUTO_LENGTH, NodeRaylibImageResizeCanvas, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageResizeCanvas", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageMipmaps", NAPI_AUTO_LENGTH, NodeRaylibImageMipmaps, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageMipmaps", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDither", NAPI_AUTO_LENGTH, NodeRaylibImageDither, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDither", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageFlipVertical", NAPI_AUTO_LENGTH, NodeRaylibImageFlipVertical, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageFlipVertical", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageFlipHorizontal", NAPI_AUTO_LENGTH, NodeRaylibImageFlipHorizontal, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageFlipHorizontal", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageRotate", NAPI_AUTO_LENGTH, NodeRaylibImageRotate, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageRotate", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageRotateCW", NAPI_AUTO_LENGTH, NodeRaylibImageRotateCW, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageRotateCW", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageRotateCCW", NAPI_AUTO_LENGTH, NodeRaylibImageRotateCCW, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageRotateCCW", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageColorTint", NAPI_AUTO_LENGTH, NodeRaylibImageColorTint, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageColorTint", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageColorInvert", NAPI_AUTO_LENGTH, NodeRaylibImageColorInvert, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageColorInvert", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageColorGrayscale", NAPI_AUTO_LENGTH, NodeRaylibImageColorGrayscale, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageColorGrayscale", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageColorContrast", NAPI_AUTO_LENGTH, NodeRaylibImageColorContrast, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageColorContrast", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageColorBrightness", NAPI_AUTO_LENGTH, NodeRaylibImageColorBrightness, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageColorBrightness", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageColorReplace", NAPI_AUTO_LENGTH, NodeRaylibImageColorReplace, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageColorReplace", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImageColors", NAPI_AUTO_LENGTH, NodeRaylibLoadImageColors, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImageColors", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadImagePalette", NAPI_AUTO_LENGTH, NodeRaylibLoadImagePalette, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadImagePalette", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadImageColors", NAPI_AUTO_LENGTH, NodeRaylibUnloadImageColors, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadImageColors", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadImagePalette", NAPI_AUTO_LENGTH, NodeRaylibUnloadImagePalette, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadImagePalette", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetImageAlphaBorder", NAPI_AUTO_LENGTH, NodeRaylibGetImageAlphaBorder, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetImageAlphaBorder", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetImageColor", NAPI_AUTO_LENGTH, NodeRaylibGetImageColor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetImageColor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageClearBackground", NAPI_AUTO_LENGTH, NodeRaylibImageClearBackground, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageClearBackground", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawPixel", NAPI_AUTO_LENGTH, NodeRaylibImageDrawPixel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawPixel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawPixelV", NAPI_AUTO_LENGTH, NodeRaylibImageDrawPixelV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawPixelV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawLine", NAPI_AUTO_LENGTH, NodeRaylibImageDrawLine, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawLine", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawLineV", NAPI_AUTO_LENGTH, NodeRaylibImageDrawLineV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawLineV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawLineEx", NAPI_AUTO_LENGTH, NodeRaylibImageDrawLineEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawLineEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawCircle", NAPI_AUTO_LENGTH, NodeRaylibImageDrawCircle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawCircle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawCircleV", NAPI_AUTO_LENGTH, NodeRaylibImageDrawCircleV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawCircleV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawCircleLines", NAPI_AUTO_LENGTH, NodeRaylibImageDrawCircleLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawCircleLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawCircleLinesV", NAPI_AUTO_LENGTH, NodeRaylibImageDrawCircleLinesV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawCircleLinesV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawRectangle", NAPI_AUTO_LENGTH, NodeRaylibImageDrawRectangle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawRectangle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawRectangleV", NAPI_AUTO_LENGTH, NodeRaylibImageDrawRectangleV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawRectangleV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawRectangleRec", NAPI_AUTO_LENGTH, NodeRaylibImageDrawRectangleRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawRectangleRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawRectangleLines", NAPI_AUTO_LENGTH, NodeRaylibImageDrawRectangleLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawRectangleLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawTriangle", NAPI_AUTO_LENGTH, NodeRaylibImageDrawTriangle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawTriangle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawTriangleEx", NAPI_AUTO_LENGTH, NodeRaylibImageDrawTriangleEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawTriangleEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawTriangleLines", NAPI_AUTO_LENGTH, NodeRaylibImageDrawTriangleLines, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawTriangleLines", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawTriangleFan", NAPI_AUTO_LENGTH, NodeRaylibImageDrawTriangleFan, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawTriangleFan", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawTriangleStrip", NAPI_AUTO_LENGTH, NodeRaylibImageDrawTriangleStrip, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawTriangleStrip", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDraw", NAPI_AUTO_LENGTH, NodeRaylibImageDraw, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDraw", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawText", NAPI_AUTO_LENGTH, NodeRaylibImageDrawText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ImageDrawTextEx", NAPI_AUTO_LENGTH, NodeRaylibImageDrawTextEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ImageDrawTextEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadTexture", NAPI_AUTO_LENGTH, NodeRaylibLoadTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadTextureFromImage", NAPI_AUTO_LENGTH, NodeRaylibLoadTextureFromImage, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadTextureFromImage", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadTextureCubemap", NAPI_AUTO_LENGTH, NodeRaylibLoadTextureCubemap, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadTextureCubemap", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadRenderTexture", NAPI_AUTO_LENGTH, NodeRaylibLoadRenderTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadRenderTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsTextureValid", NAPI_AUTO_LENGTH, NodeRaylibIsTextureValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsTextureValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadTexture", NAPI_AUTO_LENGTH, NodeRaylibUnloadTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsRenderTextureValid", NAPI_AUTO_LENGTH, NodeRaylibIsRenderTextureValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsRenderTextureValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadRenderTexture", NAPI_AUTO_LENGTH, NodeRaylibUnloadRenderTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadRenderTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateTexture", NAPI_AUTO_LENGTH, NodeRaylibUpdateTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateTextureRec", NAPI_AUTO_LENGTH, NodeRaylibUpdateTextureRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateTextureRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenTextureMipmaps", NAPI_AUTO_LENGTH, NodeRaylibGenTextureMipmaps, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenTextureMipmaps", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetTextureFilter", NAPI_AUTO_LENGTH, NodeRaylibSetTextureFilter, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetTextureFilter", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetTextureWrap", NAPI_AUTO_LENGTH, NodeRaylibSetTextureWrap, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetTextureWrap", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTexture", NAPI_AUTO_LENGTH, NodeRaylibDrawTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextureV", NAPI_AUTO_LENGTH, NodeRaylibDrawTextureV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextureV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextureEx", NAPI_AUTO_LENGTH, NodeRaylibDrawTextureEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextureEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextureRec", NAPI_AUTO_LENGTH, NodeRaylibDrawTextureRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextureRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTexturePro", NAPI_AUTO_LENGTH, NodeRaylibDrawTexturePro, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTexturePro", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextureNPatch", NAPI_AUTO_LENGTH, NodeRaylibDrawTextureNPatch, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextureNPatch", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorIsEqual", NAPI_AUTO_LENGTH, NodeRaylibColorIsEqual, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorIsEqual", fn));
    
  NAPI_CALL(env, napi_create_function(env, "Fade", NAPI_AUTO_LENGTH, NodeRaylibFade, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "Fade", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorToInt", NAPI_AUTO_LENGTH, NodeRaylibColorToInt, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorToInt", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorNormalize", NAPI_AUTO_LENGTH, NodeRaylibColorNormalize, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorNormalize", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorFromNormalized", NAPI_AUTO_LENGTH, NodeRaylibColorFromNormalized, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorFromNormalized", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorToHSV", NAPI_AUTO_LENGTH, NodeRaylibColorToHSV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorToHSV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorFromHSV", NAPI_AUTO_LENGTH, NodeRaylibColorFromHSV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorFromHSV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorTint", NAPI_AUTO_LENGTH, NodeRaylibColorTint, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorTint", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorBrightness", NAPI_AUTO_LENGTH, NodeRaylibColorBrightness, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorBrightness", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorContrast", NAPI_AUTO_LENGTH, NodeRaylibColorContrast, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorContrast", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorAlpha", NAPI_AUTO_LENGTH, NodeRaylibColorAlpha, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorAlpha", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorAlphaBlend", NAPI_AUTO_LENGTH, NodeRaylibColorAlphaBlend, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorAlphaBlend", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ColorLerp", NAPI_AUTO_LENGTH, NodeRaylibColorLerp, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ColorLerp", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetColor", NAPI_AUTO_LENGTH, NodeRaylibGetColor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetColor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetPixelColor", NAPI_AUTO_LENGTH, NodeRaylibGetPixelColor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetPixelColor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetPixelColor", NAPI_AUTO_LENGTH, NodeRaylibSetPixelColor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetPixelColor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetPixelDataSize", NAPI_AUTO_LENGTH, NodeRaylibGetPixelDataSize, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetPixelDataSize", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetFontDefault", NAPI_AUTO_LENGTH, NodeRaylibGetFontDefault, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetFontDefault", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadFont", NAPI_AUTO_LENGTH, NodeRaylibLoadFont, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadFont", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadFontEx", NAPI_AUTO_LENGTH, NodeRaylibLoadFontEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadFontEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadFontFromImage", NAPI_AUTO_LENGTH, NodeRaylibLoadFontFromImage, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadFontFromImage", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadFontFromMemory", NAPI_AUTO_LENGTH, NodeRaylibLoadFontFromMemory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadFontFromMemory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsFontValid", NAPI_AUTO_LENGTH, NodeRaylibIsFontValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsFontValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadFontData", NAPI_AUTO_LENGTH, NodeRaylibLoadFontData, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadFontData", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenImageFontAtlas", NAPI_AUTO_LENGTH, NodeRaylibGenImageFontAtlas, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenImageFontAtlas", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadFontData", NAPI_AUTO_LENGTH, NodeRaylibUnloadFontData, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadFontData", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadFont", NAPI_AUTO_LENGTH, NodeRaylibUnloadFont, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadFont", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportFontAsCode", NAPI_AUTO_LENGTH, NodeRaylibExportFontAsCode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportFontAsCode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawFPS", NAPI_AUTO_LENGTH, NodeRaylibDrawFPS, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawFPS", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawText", NAPI_AUTO_LENGTH, NodeRaylibDrawText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextEx", NAPI_AUTO_LENGTH, NodeRaylibDrawTextEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextPro", NAPI_AUTO_LENGTH, NodeRaylibDrawTextPro, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextPro", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextCodepoint", NAPI_AUTO_LENGTH, NodeRaylibDrawTextCodepoint, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextCodepoint", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTextCodepoints", NAPI_AUTO_LENGTH, NodeRaylibDrawTextCodepoints, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTextCodepoints", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetTextLineSpacing", NAPI_AUTO_LENGTH, NodeRaylibSetTextLineSpacing, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetTextLineSpacing", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MeasureText", NAPI_AUTO_LENGTH, NodeRaylibMeasureText, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MeasureText", fn));
    
  NAPI_CALL(env, napi_create_function(env, "MeasureTextEx", NAPI_AUTO_LENGTH, NodeRaylibMeasureTextEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "MeasureTextEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGlyphIndex", NAPI_AUTO_LENGTH, NodeRaylibGetGlyphIndex, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGlyphIndex", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGlyphInfo", NAPI_AUTO_LENGTH, NodeRaylibGetGlyphInfo, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGlyphInfo", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetGlyphAtlasRec", NAPI_AUTO_LENGTH, NodeRaylibGetGlyphAtlasRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetGlyphAtlasRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadUTF8", NAPI_AUTO_LENGTH, NodeRaylibLoadUTF8, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadUTF8", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadUTF8", NAPI_AUTO_LENGTH, NodeRaylibUnloadUTF8, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadUTF8", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadCodepoints", NAPI_AUTO_LENGTH, NodeRaylibLoadCodepoints, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadCodepoints", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadCodepoints", NAPI_AUTO_LENGTH, NodeRaylibUnloadCodepoints, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadCodepoints", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCodepointCount", NAPI_AUTO_LENGTH, NodeRaylibGetCodepointCount, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCodepointCount", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCodepoint", NAPI_AUTO_LENGTH, NodeRaylibGetCodepoint, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCodepoint", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCodepointNext", NAPI_AUTO_LENGTH, NodeRaylibGetCodepointNext, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCodepointNext", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetCodepointPrevious", NAPI_AUTO_LENGTH, NodeRaylibGetCodepointPrevious, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetCodepointPrevious", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CodepointToUTF8", NAPI_AUTO_LENGTH, NodeRaylibCodepointToUTF8, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CodepointToUTF8", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextCopy", NAPI_AUTO_LENGTH, NodeRaylibTextCopy, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextCopy", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextIsEqual", NAPI_AUTO_LENGTH, NodeRaylibTextIsEqual, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextIsEqual", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextLength", NAPI_AUTO_LENGTH, NodeRaylibTextLength, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextLength", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextSubtext", NAPI_AUTO_LENGTH, NodeRaylibTextSubtext, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextSubtext", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextReplace", NAPI_AUTO_LENGTH, NodeRaylibTextReplace, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextReplace", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextInsert", NAPI_AUTO_LENGTH, NodeRaylibTextInsert, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextInsert", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextJoin", NAPI_AUTO_LENGTH, NodeRaylibTextJoin, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextJoin", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextSplit", NAPI_AUTO_LENGTH, NodeRaylibTextSplit, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextSplit", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextAppend", NAPI_AUTO_LENGTH, NodeRaylibTextAppend, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextAppend", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextFindIndex", NAPI_AUTO_LENGTH, NodeRaylibTextFindIndex, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextFindIndex", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextToUpper", NAPI_AUTO_LENGTH, NodeRaylibTextToUpper, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextToUpper", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextToLower", NAPI_AUTO_LENGTH, NodeRaylibTextToLower, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextToLower", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextToPascal", NAPI_AUTO_LENGTH, NodeRaylibTextToPascal, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextToPascal", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextToSnake", NAPI_AUTO_LENGTH, NodeRaylibTextToSnake, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextToSnake", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextToCamel", NAPI_AUTO_LENGTH, NodeRaylibTextToCamel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextToCamel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextToInteger", NAPI_AUTO_LENGTH, NodeRaylibTextToInteger, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextToInteger", fn));
    
  NAPI_CALL(env, napi_create_function(env, "TextToFloat", NAPI_AUTO_LENGTH, NodeRaylibTextToFloat, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "TextToFloat", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawLine3D", NAPI_AUTO_LENGTH, NodeRaylibDrawLine3D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawLine3D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawPoint3D", NAPI_AUTO_LENGTH, NodeRaylibDrawPoint3D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawPoint3D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCircle3D", NAPI_AUTO_LENGTH, NodeRaylibDrawCircle3D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCircle3D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTriangle3D", NAPI_AUTO_LENGTH, NodeRaylibDrawTriangle3D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTriangle3D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawTriangleStrip3D", NAPI_AUTO_LENGTH, NodeRaylibDrawTriangleStrip3D, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawTriangleStrip3D", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCube", NAPI_AUTO_LENGTH, NodeRaylibDrawCube, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCube", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCubeV", NAPI_AUTO_LENGTH, NodeRaylibDrawCubeV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCubeV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCubeWires", NAPI_AUTO_LENGTH, NodeRaylibDrawCubeWires, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCubeWires", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCubeWiresV", NAPI_AUTO_LENGTH, NodeRaylibDrawCubeWiresV, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCubeWiresV", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSphere", NAPI_AUTO_LENGTH, NodeRaylibDrawSphere, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSphere", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSphereEx", NAPI_AUTO_LENGTH, NodeRaylibDrawSphereEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSphereEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawSphereWires", NAPI_AUTO_LENGTH, NodeRaylibDrawSphereWires, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawSphereWires", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCylinder", NAPI_AUTO_LENGTH, NodeRaylibDrawCylinder, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCylinder", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCylinderEx", NAPI_AUTO_LENGTH, NodeRaylibDrawCylinderEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCylinderEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCylinderWires", NAPI_AUTO_LENGTH, NodeRaylibDrawCylinderWires, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCylinderWires", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCylinderWiresEx", NAPI_AUTO_LENGTH, NodeRaylibDrawCylinderWiresEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCylinderWiresEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCapsule", NAPI_AUTO_LENGTH, NodeRaylibDrawCapsule, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCapsule", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawCapsuleWires", NAPI_AUTO_LENGTH, NodeRaylibDrawCapsuleWires, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawCapsuleWires", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawPlane", NAPI_AUTO_LENGTH, NodeRaylibDrawPlane, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawPlane", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawRay", NAPI_AUTO_LENGTH, NodeRaylibDrawRay, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawRay", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawGrid", NAPI_AUTO_LENGTH, NodeRaylibDrawGrid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawGrid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadModel", NAPI_AUTO_LENGTH, NodeRaylibLoadModel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadModel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadModelFromMesh", NAPI_AUTO_LENGTH, NodeRaylibLoadModelFromMesh, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadModelFromMesh", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsModelValid", NAPI_AUTO_LENGTH, NodeRaylibIsModelValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsModelValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadModel", NAPI_AUTO_LENGTH, NodeRaylibUnloadModel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadModel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetModelBoundingBox", NAPI_AUTO_LENGTH, NodeRaylibGetModelBoundingBox, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetModelBoundingBox", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawModel", NAPI_AUTO_LENGTH, NodeRaylibDrawModel, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawModel", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawModelEx", NAPI_AUTO_LENGTH, NodeRaylibDrawModelEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawModelEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawModelWires", NAPI_AUTO_LENGTH, NodeRaylibDrawModelWires, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawModelWires", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawModelWiresEx", NAPI_AUTO_LENGTH, NodeRaylibDrawModelWiresEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawModelWiresEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawModelPoints", NAPI_AUTO_LENGTH, NodeRaylibDrawModelPoints, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawModelPoints", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawModelPointsEx", NAPI_AUTO_LENGTH, NodeRaylibDrawModelPointsEx, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawModelPointsEx", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawBoundingBox", NAPI_AUTO_LENGTH, NodeRaylibDrawBoundingBox, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawBoundingBox", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawBillboard", NAPI_AUTO_LENGTH, NodeRaylibDrawBillboard, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawBillboard", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawBillboardRec", NAPI_AUTO_LENGTH, NodeRaylibDrawBillboardRec, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawBillboardRec", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawBillboardPro", NAPI_AUTO_LENGTH, NodeRaylibDrawBillboardPro, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawBillboardPro", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UploadMesh", NAPI_AUTO_LENGTH, NodeRaylibUploadMesh, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UploadMesh", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateMeshBuffer", NAPI_AUTO_LENGTH, NodeRaylibUpdateMeshBuffer, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateMeshBuffer", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadMesh", NAPI_AUTO_LENGTH, NodeRaylibUnloadMesh, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadMesh", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawMesh", NAPI_AUTO_LENGTH, NodeRaylibDrawMesh, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawMesh", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DrawMeshInstanced", NAPI_AUTO_LENGTH, NodeRaylibDrawMeshInstanced, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DrawMeshInstanced", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMeshBoundingBox", NAPI_AUTO_LENGTH, NodeRaylibGetMeshBoundingBox, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMeshBoundingBox", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshTangents", NAPI_AUTO_LENGTH, NodeRaylibGenMeshTangents, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshTangents", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportMesh", NAPI_AUTO_LENGTH, NodeRaylibExportMesh, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportMesh", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportMeshAsCode", NAPI_AUTO_LENGTH, NodeRaylibExportMeshAsCode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportMeshAsCode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshPoly", NAPI_AUTO_LENGTH, NodeRaylibGenMeshPoly, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshPoly", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshPlane", NAPI_AUTO_LENGTH, NodeRaylibGenMeshPlane, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshPlane", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshCube", NAPI_AUTO_LENGTH, NodeRaylibGenMeshCube, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshCube", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshSphere", NAPI_AUTO_LENGTH, NodeRaylibGenMeshSphere, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshSphere", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshHemiSphere", NAPI_AUTO_LENGTH, NodeRaylibGenMeshHemiSphere, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshHemiSphere", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshCylinder", NAPI_AUTO_LENGTH, NodeRaylibGenMeshCylinder, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshCylinder", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshCone", NAPI_AUTO_LENGTH, NodeRaylibGenMeshCone, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshCone", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshTorus", NAPI_AUTO_LENGTH, NodeRaylibGenMeshTorus, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshTorus", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshKnot", NAPI_AUTO_LENGTH, NodeRaylibGenMeshKnot, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshKnot", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshHeightmap", NAPI_AUTO_LENGTH, NodeRaylibGenMeshHeightmap, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshHeightmap", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GenMeshCubicmap", NAPI_AUTO_LENGTH, NodeRaylibGenMeshCubicmap, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GenMeshCubicmap", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadMaterials", NAPI_AUTO_LENGTH, NodeRaylibLoadMaterials, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadMaterials", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadMaterialDefault", NAPI_AUTO_LENGTH, NodeRaylibLoadMaterialDefault, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadMaterialDefault", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsMaterialValid", NAPI_AUTO_LENGTH, NodeRaylibIsMaterialValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsMaterialValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadMaterial", NAPI_AUTO_LENGTH, NodeRaylibUnloadMaterial, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadMaterial", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMaterialTexture", NAPI_AUTO_LENGTH, NodeRaylibSetMaterialTexture, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMaterialTexture", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetModelMeshMaterial", NAPI_AUTO_LENGTH, NodeRaylibSetModelMeshMaterial, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetModelMeshMaterial", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadModelAnimations", NAPI_AUTO_LENGTH, NodeRaylibLoadModelAnimations, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadModelAnimations", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateModelAnimation", NAPI_AUTO_LENGTH, NodeRaylibUpdateModelAnimation, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateModelAnimation", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateModelAnimationBones", NAPI_AUTO_LENGTH, NodeRaylibUpdateModelAnimationBones, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateModelAnimationBones", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadModelAnimation", NAPI_AUTO_LENGTH, NodeRaylibUnloadModelAnimation, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadModelAnimation", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadModelAnimations", NAPI_AUTO_LENGTH, NodeRaylibUnloadModelAnimations, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadModelAnimations", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsModelAnimationValid", NAPI_AUTO_LENGTH, NodeRaylibIsModelAnimationValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsModelAnimationValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionSpheres", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionSpheres, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionSpheres", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionBoxes", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionBoxes, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionBoxes", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CheckCollisionBoxSphere", NAPI_AUTO_LENGTH, NodeRaylibCheckCollisionBoxSphere, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CheckCollisionBoxSphere", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRayCollisionSphere", NAPI_AUTO_LENGTH, NodeRaylibGetRayCollisionSphere, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRayCollisionSphere", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRayCollisionBox", NAPI_AUTO_LENGTH, NodeRaylibGetRayCollisionBox, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRayCollisionBox", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRayCollisionMesh", NAPI_AUTO_LENGTH, NodeRaylibGetRayCollisionMesh, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRayCollisionMesh", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRayCollisionTriangle", NAPI_AUTO_LENGTH, NodeRaylibGetRayCollisionTriangle, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRayCollisionTriangle", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetRayCollisionQuad", NAPI_AUTO_LENGTH, NodeRaylibGetRayCollisionQuad, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetRayCollisionQuad", fn));
    
  NAPI_CALL(env, napi_create_function(env, "InitAudioDevice", NAPI_AUTO_LENGTH, NodeRaylibInitAudioDevice, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "InitAudioDevice", fn));
    
  NAPI_CALL(env, napi_create_function(env, "CloseAudioDevice", NAPI_AUTO_LENGTH, NodeRaylibCloseAudioDevice, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "CloseAudioDevice", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsAudioDeviceReady", NAPI_AUTO_LENGTH, NodeRaylibIsAudioDeviceReady, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsAudioDeviceReady", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMasterVolume", NAPI_AUTO_LENGTH, NodeRaylibSetMasterVolume, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMasterVolume", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMasterVolume", NAPI_AUTO_LENGTH, NodeRaylibGetMasterVolume, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMasterVolume", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadWave", NAPI_AUTO_LENGTH, NodeRaylibLoadWave, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadWave", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadWaveFromMemory", NAPI_AUTO_LENGTH, NodeRaylibLoadWaveFromMemory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadWaveFromMemory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsWaveValid", NAPI_AUTO_LENGTH, NodeRaylibIsWaveValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsWaveValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadSound", NAPI_AUTO_LENGTH, NodeRaylibLoadSound, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadSound", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadSoundFromWave", NAPI_AUTO_LENGTH, NodeRaylibLoadSoundFromWave, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadSoundFromWave", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadSoundAlias", NAPI_AUTO_LENGTH, NodeRaylibLoadSoundAlias, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadSoundAlias", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsSoundValid", NAPI_AUTO_LENGTH, NodeRaylibIsSoundValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsSoundValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateSound", NAPI_AUTO_LENGTH, NodeRaylibUpdateSound, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateSound", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadWave", NAPI_AUTO_LENGTH, NodeRaylibUnloadWave, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadWave", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadSound", NAPI_AUTO_LENGTH, NodeRaylibUnloadSound, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadSound", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadSoundAlias", NAPI_AUTO_LENGTH, NodeRaylibUnloadSoundAlias, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadSoundAlias", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportWave", NAPI_AUTO_LENGTH, NodeRaylibExportWave, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportWave", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ExportWaveAsCode", NAPI_AUTO_LENGTH, NodeRaylibExportWaveAsCode, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ExportWaveAsCode", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PlaySound", NAPI_AUTO_LENGTH, NodeRaylibPlaySound, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PlaySound", fn));
    
  NAPI_CALL(env, napi_create_function(env, "StopSound", NAPI_AUTO_LENGTH, NodeRaylibStopSound, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "StopSound", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PauseSound", NAPI_AUTO_LENGTH, NodeRaylibPauseSound, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PauseSound", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ResumeSound", NAPI_AUTO_LENGTH, NodeRaylibResumeSound, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ResumeSound", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsSoundPlaying", NAPI_AUTO_LENGTH, NodeRaylibIsSoundPlaying, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsSoundPlaying", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetSoundVolume", NAPI_AUTO_LENGTH, NodeRaylibSetSoundVolume, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetSoundVolume", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetSoundPitch", NAPI_AUTO_LENGTH, NodeRaylibSetSoundPitch, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetSoundPitch", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetSoundPan", NAPI_AUTO_LENGTH, NodeRaylibSetSoundPan, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetSoundPan", fn));
    
  NAPI_CALL(env, napi_create_function(env, "WaveCopy", NAPI_AUTO_LENGTH, NodeRaylibWaveCopy, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "WaveCopy", fn));
    
  NAPI_CALL(env, napi_create_function(env, "WaveCrop", NAPI_AUTO_LENGTH, NodeRaylibWaveCrop, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "WaveCrop", fn));
    
  NAPI_CALL(env, napi_create_function(env, "WaveFormat", NAPI_AUTO_LENGTH, NodeRaylibWaveFormat, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "WaveFormat", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadWaveSamples", NAPI_AUTO_LENGTH, NodeRaylibLoadWaveSamples, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadWaveSamples", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadWaveSamples", NAPI_AUTO_LENGTH, NodeRaylibUnloadWaveSamples, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadWaveSamples", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadMusicStream", NAPI_AUTO_LENGTH, NodeRaylibLoadMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadMusicStreamFromMemory", NAPI_AUTO_LENGTH, NodeRaylibLoadMusicStreamFromMemory, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadMusicStreamFromMemory", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsMusicValid", NAPI_AUTO_LENGTH, NodeRaylibIsMusicValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsMusicValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadMusicStream", NAPI_AUTO_LENGTH, NodeRaylibUnloadMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PlayMusicStream", NAPI_AUTO_LENGTH, NodeRaylibPlayMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PlayMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsMusicStreamPlaying", NAPI_AUTO_LENGTH, NodeRaylibIsMusicStreamPlaying, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsMusicStreamPlaying", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateMusicStream", NAPI_AUTO_LENGTH, NodeRaylibUpdateMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "StopMusicStream", NAPI_AUTO_LENGTH, NodeRaylibStopMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "StopMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PauseMusicStream", NAPI_AUTO_LENGTH, NodeRaylibPauseMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PauseMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ResumeMusicStream", NAPI_AUTO_LENGTH, NodeRaylibResumeMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ResumeMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SeekMusicStream", NAPI_AUTO_LENGTH, NodeRaylibSeekMusicStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SeekMusicStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMusicVolume", NAPI_AUTO_LENGTH, NodeRaylibSetMusicVolume, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMusicVolume", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMusicPitch", NAPI_AUTO_LENGTH, NodeRaylibSetMusicPitch, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMusicPitch", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetMusicPan", NAPI_AUTO_LENGTH, NodeRaylibSetMusicPan, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetMusicPan", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMusicTimeLength", NAPI_AUTO_LENGTH, NodeRaylibGetMusicTimeLength, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMusicTimeLength", fn));
    
  NAPI_CALL(env, napi_create_function(env, "GetMusicTimePlayed", NAPI_AUTO_LENGTH, NodeRaylibGetMusicTimePlayed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "GetMusicTimePlayed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "LoadAudioStream", NAPI_AUTO_LENGTH, NodeRaylibLoadAudioStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "LoadAudioStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsAudioStreamValid", NAPI_AUTO_LENGTH, NodeRaylibIsAudioStreamValid, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsAudioStreamValid", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UnloadAudioStream", NAPI_AUTO_LENGTH, NodeRaylibUnloadAudioStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UnloadAudioStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "UpdateAudioStream", NAPI_AUTO_LENGTH, NodeRaylibUpdateAudioStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "UpdateAudioStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsAudioStreamProcessed", NAPI_AUTO_LENGTH, NodeRaylibIsAudioStreamProcessed, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsAudioStreamProcessed", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PlayAudioStream", NAPI_AUTO_LENGTH, NodeRaylibPlayAudioStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PlayAudioStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "PauseAudioStream", NAPI_AUTO_LENGTH, NodeRaylibPauseAudioStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "PauseAudioStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "ResumeAudioStream", NAPI_AUTO_LENGTH, NodeRaylibResumeAudioStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "ResumeAudioStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "IsAudioStreamPlaying", NAPI_AUTO_LENGTH, NodeRaylibIsAudioStreamPlaying, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "IsAudioStreamPlaying", fn));
    
  NAPI_CALL(env, napi_create_function(env, "StopAudioStream", NAPI_AUTO_LENGTH, NodeRaylibStopAudioStream, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "StopAudioStream", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetAudioStreamVolume", NAPI_AUTO_LENGTH, NodeRaylibSetAudioStreamVolume, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetAudioStreamVolume", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetAudioStreamPitch", NAPI_AUTO_LENGTH, NodeRaylibSetAudioStreamPitch, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetAudioStreamPitch", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetAudioStreamPan", NAPI_AUTO_LENGTH, NodeRaylibSetAudioStreamPan, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetAudioStreamPan", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetAudioStreamBufferSizeDefault", NAPI_AUTO_LENGTH, NodeRaylibSetAudioStreamBufferSizeDefault, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetAudioStreamBufferSizeDefault", fn));
    
  NAPI_CALL(env, napi_create_function(env, "SetAudioStreamCallback", NAPI_AUTO_LENGTH, NodeRaylibSetAudioStreamCallback, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "SetAudioStreamCallback", fn));
    
  NAPI_CALL(env, napi_create_function(env, "AttachAudioStreamProcessor", NAPI_AUTO_LENGTH, NodeRaylibAttachAudioStreamProcessor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "AttachAudioStreamProcessor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DetachAudioStreamProcessor", NAPI_AUTO_LENGTH, NodeRaylibDetachAudioStreamProcessor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DetachAudioStreamProcessor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "AttachAudioMixedProcessor", NAPI_AUTO_LENGTH, NodeRaylibAttachAudioMixedProcessor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "AttachAudioMixedProcessor", fn));
    
  NAPI_CALL(env, napi_create_function(env, "DetachAudioMixedProcessor", NAPI_AUTO_LENGTH, NodeRaylibDetachAudioMixedProcessor, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "DetachAudioMixedProcessor", fn));
    

  return exports;
}
NAPI_MODULE(raylib, Init)

  