// Raylib for nodejs 5.5.0

const native = require('./build/Release/node-raylib.node')
const { vsprintf } = require('./src/vsprintf.js')

exports.SayHello = native.SayHello

// vargs are a bit annoying over NAPI, so I format here, and only use 1 string param
// Users should probly use template-strings anyway in JS...
exports.TraceLog = function (level, text, ...args) {
  native.TraceLog(level, vsprintf(text, args))
}
exports.TextFormat = function (text, ...args) {
  return vsprintf(text, args)
}


// Initialize window and OpenGL context
exports.InitWindow=native.InitWindow

// Close window and unload OpenGL context
exports.CloseWindow=native.CloseWindow

// Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
exports.WindowShouldClose=native.WindowShouldClose

// Check if window has been initialized successfully
exports.IsWindowReady=native.IsWindowReady

// Check if window is currently fullscreen
exports.IsWindowFullscreen=native.IsWindowFullscreen

// Check if window is currently hidden
exports.IsWindowHidden=native.IsWindowHidden

// Check if window is currently minimized
exports.IsWindowMinimized=native.IsWindowMinimized

// Check if window is currently maximized
exports.IsWindowMaximized=native.IsWindowMaximized

// Check if window is currently focused
exports.IsWindowFocused=native.IsWindowFocused

// Check if window has been resized last frame
exports.IsWindowResized=native.IsWindowResized

// Check if one specific window flag is enabled
exports.IsWindowState=native.IsWindowState

// Set window configuration state using flags
exports.SetWindowState=native.SetWindowState

// Clear window configuration state flags
exports.ClearWindowState=native.ClearWindowState

// Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
exports.ToggleFullscreen=native.ToggleFullscreen

// Toggle window state: borderless windowed, resizes window to match monitor resolution
exports.ToggleBorderlessWindowed=native.ToggleBorderlessWindowed

// Set window state: maximized, if resizable
exports.MaximizeWindow=native.MaximizeWindow

// Set window state: minimized, if resizable
exports.MinimizeWindow=native.MinimizeWindow

// Set window state: not minimized/maximized
exports.RestoreWindow=native.RestoreWindow

// Set icon for window (single image, RGBA 32bit)
exports.SetWindowIcon=native.SetWindowIcon

// Set icon for window (multiple images, RGBA 32bit)
exports.SetWindowIcons=native.SetWindowIcons

// Set title for window
exports.SetWindowTitle=native.SetWindowTitle

// Set window position on screen
exports.SetWindowPosition=native.SetWindowPosition

// Set monitor for the current window
exports.SetWindowMonitor=native.SetWindowMonitor

// Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
exports.SetWindowMinSize=native.SetWindowMinSize

// Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
exports.SetWindowMaxSize=native.SetWindowMaxSize

// Set window dimensions
exports.SetWindowSize=native.SetWindowSize

// Set window opacity [0.0f..1.0f]
exports.SetWindowOpacity=native.SetWindowOpacity

// Set window focused
exports.SetWindowFocused=native.SetWindowFocused

// Get native window handle
exports.GetWindowHandle=native.GetWindowHandle

// Get current screen width
exports.GetScreenWidth=native.GetScreenWidth

// Get current screen height
exports.GetScreenHeight=native.GetScreenHeight

// Get current render width (it considers HiDPI)
exports.GetRenderWidth=native.GetRenderWidth

// Get current render height (it considers HiDPI)
exports.GetRenderHeight=native.GetRenderHeight

// Get number of connected monitors
exports.GetMonitorCount=native.GetMonitorCount

// Get current monitor where window is placed
exports.GetCurrentMonitor=native.GetCurrentMonitor

// Get specified monitor position
exports.GetMonitorPosition=native.GetMonitorPosition

// Get specified monitor width (current video mode used by monitor)
exports.GetMonitorWidth=native.GetMonitorWidth

// Get specified monitor height (current video mode used by monitor)
exports.GetMonitorHeight=native.GetMonitorHeight

// Get specified monitor physical width in millimetres
exports.GetMonitorPhysicalWidth=native.GetMonitorPhysicalWidth

// Get specified monitor physical height in millimetres
exports.GetMonitorPhysicalHeight=native.GetMonitorPhysicalHeight

// Get specified monitor refresh rate
exports.GetMonitorRefreshRate=native.GetMonitorRefreshRate

// Get window position XY on monitor
exports.GetWindowPosition=native.GetWindowPosition

// Get window scale DPI factor
exports.GetWindowScaleDPI=native.GetWindowScaleDPI

// Get the human-readable, UTF-8 encoded name of the specified monitor
exports.GetMonitorName=native.GetMonitorName

// Set clipboard text content
exports.SetClipboardText=native.SetClipboardText

// Get clipboard text content
exports.GetClipboardText=native.GetClipboardText

// Get clipboard image content
exports.GetClipboardImage=native.GetClipboardImage

// Enable waiting for events on EndDrawing(), no automatic event polling
exports.EnableEventWaiting=native.EnableEventWaiting

// Disable waiting for events on EndDrawing(), automatic events polling
exports.DisableEventWaiting=native.DisableEventWaiting

// Shows cursor
exports.ShowCursor=native.ShowCursor

// Hides cursor
exports.HideCursor=native.HideCursor

// Check if cursor is not visible
exports.IsCursorHidden=native.IsCursorHidden

// Enables cursor (unlock cursor)
exports.EnableCursor=native.EnableCursor

// Disables cursor (lock cursor)
exports.DisableCursor=native.DisableCursor

// Check if cursor is on the screen
exports.IsCursorOnScreen=native.IsCursorOnScreen

// Set background color (framebuffer clear color)
exports.ClearBackground=native.ClearBackground

// Setup canvas (framebuffer) to start drawing
exports.BeginDrawing=native.BeginDrawing

// End canvas drawing and swap buffers (double buffering)
exports.EndDrawing=native.EndDrawing

// Begin 2D mode with custom camera (2D)
exports.BeginMode2D=native.BeginMode2D

// Ends 2D mode with custom camera
exports.EndMode2D=native.EndMode2D

// Begin 3D mode with custom camera (3D)
exports.BeginMode3D=native.BeginMode3D

// Ends 3D mode and returns to default 2D orthographic mode
exports.EndMode3D=native.EndMode3D

// Begin drawing to render texture
exports.BeginTextureMode=native.BeginTextureMode

// Ends drawing to render texture
exports.EndTextureMode=native.EndTextureMode

// Begin custom shader drawing
exports.BeginShaderMode=native.BeginShaderMode

// End custom shader drawing (use default shader)
exports.EndShaderMode=native.EndShaderMode

// Begin blending mode (alpha, additive, multiplied, subtract, custom)
exports.BeginBlendMode=native.BeginBlendMode

// End blending mode (reset to default: alpha blending)
exports.EndBlendMode=native.EndBlendMode

// Begin scissor mode (define screen area for following drawing)
exports.BeginScissorMode=native.BeginScissorMode

// End scissor mode
exports.EndScissorMode=native.EndScissorMode

// Begin stereo rendering (requires VR simulator)
exports.BeginVrStereoMode=native.BeginVrStereoMode

// End stereo rendering (requires VR simulator)
exports.EndVrStereoMode=native.EndVrStereoMode

// Load VR stereo config for VR simulator device parameters
exports.LoadVrStereoConfig=native.LoadVrStereoConfig

// Unload VR stereo config
exports.UnloadVrStereoConfig=native.UnloadVrStereoConfig

// Load shader from files and bind default locations
exports.LoadShader=native.LoadShader

// Load shader from code strings and bind default locations
exports.LoadShaderFromMemory=native.LoadShaderFromMemory

// Check if a shader is valid (loaded on GPU)
exports.IsShaderValid=native.IsShaderValid

// Get shader uniform location
exports.GetShaderLocation=native.GetShaderLocation

// Get shader attribute location
exports.GetShaderLocationAttrib=native.GetShaderLocationAttrib

// Set shader uniform value
exports.SetShaderValue=native.SetShaderValue

// Set shader uniform value vector
exports.SetShaderValueV=native.SetShaderValueV

// Set shader uniform value (matrix 4x4)
exports.SetShaderValueMatrix=native.SetShaderValueMatrix

// Set shader uniform value for texture (sampler2d)
exports.SetShaderValueTexture=native.SetShaderValueTexture

// Unload shader from GPU memory (VRAM)
exports.UnloadShader=native.UnloadShader

// Get a ray trace from screen position (i.e mouse)
exports.GetScreenToWorldRay=native.GetScreenToWorldRay

// Get a ray trace from screen position (i.e mouse) in a viewport
exports.GetScreenToWorldRayEx=native.GetScreenToWorldRayEx

// Get the screen space position for a 3d world space position
exports.GetWorldToScreen=native.GetWorldToScreen

// Get size position for a 3d world space position
exports.GetWorldToScreenEx=native.GetWorldToScreenEx

// Get the screen space position for a 2d camera world space position
exports.GetWorldToScreen2D=native.GetWorldToScreen2D

// Get the world space position for a 2d camera screen space position
exports.GetScreenToWorld2D=native.GetScreenToWorld2D

// Get camera transform matrix (view matrix)
exports.GetCameraMatrix=native.GetCameraMatrix

// Get camera 2d transform matrix
exports.GetCameraMatrix2D=native.GetCameraMatrix2D

// Set target FPS (maximum)
exports.SetTargetFPS=native.SetTargetFPS

// Get time in seconds for last frame drawn (delta time)
exports.GetFrameTime=native.GetFrameTime

// Get elapsed time in seconds since InitWindow()
exports.GetTime=native.GetTime

// Get current FPS
exports.GetFPS=native.GetFPS

// Swap back buffer with front buffer (screen drawing)
exports.SwapScreenBuffer=native.SwapScreenBuffer

// Register all input events
exports.PollInputEvents=native.PollInputEvents

// Wait for some time (halt program execution)
exports.WaitTime=native.WaitTime

// Set the seed for the random number generator
exports.SetRandomSeed=native.SetRandomSeed

// Get a random value between min and max (both included)
exports.GetRandomValue=native.GetRandomValue

// Load random values sequence, no values repeated
exports.LoadRandomSequence=native.LoadRandomSequence

// Unload random values sequence
exports.UnloadRandomSequence=native.UnloadRandomSequence

// Takes a screenshot of current screen (filename extension defines format)
exports.TakeScreenshot=native.TakeScreenshot

// Setup init configuration flags (view FLAGS)
exports.SetConfigFlags=native.SetConfigFlags

// Open URL with default system browser (if available)
exports.OpenURL=native.OpenURL

// Set the current threshold (minimum) log level
exports.SetTraceLogLevel=native.SetTraceLogLevel

// Internal memory allocator
exports.MemAlloc=native.MemAlloc

// Internal memory reallocator
exports.MemRealloc=native.MemRealloc

// Internal memory free
exports.MemFree=native.MemFree

// Set custom trace log
exports.SetTraceLogCallback=native.SetTraceLogCallback

// Set custom file binary data loader
exports.SetLoadFileDataCallback=native.SetLoadFileDataCallback

// Set custom file binary data saver
exports.SetSaveFileDataCallback=native.SetSaveFileDataCallback

// Set custom file text data loader
exports.SetLoadFileTextCallback=native.SetLoadFileTextCallback

// Set custom file text data saver
exports.SetSaveFileTextCallback=native.SetSaveFileTextCallback

// Load file data as byte array (read)
exports.LoadFileData=native.LoadFileData

// Unload file data allocated by LoadFileData()
exports.UnloadFileData=native.UnloadFileData

// Save data to file from byte array (write), returns true on success
exports.SaveFileData=native.SaveFileData

// Export data to code (.h), returns true on success
exports.ExportDataAsCode=native.ExportDataAsCode

// Load text data from file (read), returns a '\0' terminated string
exports.LoadFileText=native.LoadFileText

// Unload file text data allocated by LoadFileText()
exports.UnloadFileText=native.UnloadFileText

// Save text data to file (write), string must be '\0' terminated, returns true on success
exports.SaveFileText=native.SaveFileText

// Check if file exists
exports.FileExists=native.FileExists

// Check if a directory path exists
exports.DirectoryExists=native.DirectoryExists

// Check file extension (including point: .png, .wav)
exports.IsFileExtension=native.IsFileExtension

// Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
exports.GetFileLength=native.GetFileLength

// Get pointer to extension for a filename string (includes dot: '.png')
exports.GetFileExtension=native.GetFileExtension

// Get pointer to filename for a path string
exports.GetFileName=native.GetFileName

// Get filename string without extension (uses static string)
exports.GetFileNameWithoutExt=native.GetFileNameWithoutExt

// Get full path for a given fileName with path (uses static string)
exports.GetDirectoryPath=native.GetDirectoryPath

// Get previous directory path for a given path (uses static string)
exports.GetPrevDirectoryPath=native.GetPrevDirectoryPath

// Get current working directory (uses static string)
exports.GetWorkingDirectory=native.GetWorkingDirectory

// Get the directory of the running application (uses static string)
exports.GetApplicationDirectory=native.GetApplicationDirectory

// Create directories (including full path requested), returns 0 on success
exports.MakeDirectory=native.MakeDirectory

// Change working directory, return true on success
exports.ChangeDirectory=native.ChangeDirectory

// Check if a given path is a file or a directory
exports.IsPathFile=native.IsPathFile

// Check if fileName is valid for the platform/OS
exports.IsFileNameValid=native.IsFileNameValid

// Load directory filepaths
exports.LoadDirectoryFiles=native.LoadDirectoryFiles

// Load directory filepaths with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result
exports.LoadDirectoryFilesEx=native.LoadDirectoryFilesEx

// Unload filepaths
exports.UnloadDirectoryFiles=native.UnloadDirectoryFiles

// Check if a file has been dropped into window
exports.IsFileDropped=native.IsFileDropped

// Load dropped filepaths
exports.LoadDroppedFiles=native.LoadDroppedFiles

// Unload dropped filepaths
exports.UnloadDroppedFiles=native.UnloadDroppedFiles

// Get file modification time (last write time)
exports.GetFileModTime=native.GetFileModTime

// Compress data (DEFLATE algorithm), memory must be MemFree()
exports.CompressData=native.CompressData

// Decompress data (DEFLATE algorithm), memory must be MemFree()
exports.DecompressData=native.DecompressData

// Encode data to Base64 string, memory must be MemFree()
exports.EncodeDataBase64=native.EncodeDataBase64

// Decode Base64 string data, memory must be MemFree()
exports.DecodeDataBase64=native.DecodeDataBase64

// Compute CRC32 hash code
exports.ComputeCRC32=native.ComputeCRC32

// Compute MD5 hash code, returns static int[4] (16 bytes)
exports.ComputeMD5=native.ComputeMD5

// Compute SHA1 hash code, returns static int[5] (20 bytes)
exports.ComputeSHA1=native.ComputeSHA1

// Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
exports.LoadAutomationEventList=native.LoadAutomationEventList

// Unload automation events list from file
exports.UnloadAutomationEventList=native.UnloadAutomationEventList

// Export automation events list as text file
exports.ExportAutomationEventList=native.ExportAutomationEventList

// Set automation event list to record to
exports.SetAutomationEventList=native.SetAutomationEventList

// Set automation event internal base frame to start recording
exports.SetAutomationEventBaseFrame=native.SetAutomationEventBaseFrame

// Start recording automation events (AutomationEventList must be set)
exports.StartAutomationEventRecording=native.StartAutomationEventRecording

// Stop recording automation events
exports.StopAutomationEventRecording=native.StopAutomationEventRecording

// Play a recorded automation event
exports.PlayAutomationEvent=native.PlayAutomationEvent

// Check if a key has been pressed once
exports.IsKeyPressed=native.IsKeyPressed

// Check if a key has been pressed again
exports.IsKeyPressedRepeat=native.IsKeyPressedRepeat

// Check if a key is being pressed
exports.IsKeyDown=native.IsKeyDown

// Check if a key has been released once
exports.IsKeyReleased=native.IsKeyReleased

// Check if a key is NOT being pressed
exports.IsKeyUp=native.IsKeyUp

// Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
exports.GetKeyPressed=native.GetKeyPressed

// Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
exports.GetCharPressed=native.GetCharPressed

// Set a custom key to exit program (default is ESC)
exports.SetExitKey=native.SetExitKey

// Check if a gamepad is available
exports.IsGamepadAvailable=native.IsGamepadAvailable

// Get gamepad internal name id
exports.GetGamepadName=native.GetGamepadName

// Check if a gamepad button has been pressed once
exports.IsGamepadButtonPressed=native.IsGamepadButtonPressed

// Check if a gamepad button is being pressed
exports.IsGamepadButtonDown=native.IsGamepadButtonDown

// Check if a gamepad button has been released once
exports.IsGamepadButtonReleased=native.IsGamepadButtonReleased

// Check if a gamepad button is NOT being pressed
exports.IsGamepadButtonUp=native.IsGamepadButtonUp

// Get the last gamepad button pressed
exports.GetGamepadButtonPressed=native.GetGamepadButtonPressed

// Get gamepad axis count for a gamepad
exports.GetGamepadAxisCount=native.GetGamepadAxisCount

// Get axis movement value for a gamepad axis
exports.GetGamepadAxisMovement=native.GetGamepadAxisMovement

// Set internal gamepad mappings (SDL_GameControllerDB)
exports.SetGamepadMappings=native.SetGamepadMappings

// Set gamepad vibration for both motors (duration in seconds)
exports.SetGamepadVibration=native.SetGamepadVibration

// Check if a mouse button has been pressed once
exports.IsMouseButtonPressed=native.IsMouseButtonPressed

// Check if a mouse button is being pressed
exports.IsMouseButtonDown=native.IsMouseButtonDown

// Check if a mouse button has been released once
exports.IsMouseButtonReleased=native.IsMouseButtonReleased

// Check if a mouse button is NOT being pressed
exports.IsMouseButtonUp=native.IsMouseButtonUp

// Get mouse position X
exports.GetMouseX=native.GetMouseX

// Get mouse position Y
exports.GetMouseY=native.GetMouseY

// Get mouse position XY
exports.GetMousePosition=native.GetMousePosition

// Get mouse delta between frames
exports.GetMouseDelta=native.GetMouseDelta

// Set mouse position XY
exports.SetMousePosition=native.SetMousePosition

// Set mouse offset
exports.SetMouseOffset=native.SetMouseOffset

// Set mouse scaling
exports.SetMouseScale=native.SetMouseScale

// Get mouse wheel movement for X or Y, whichever is larger
exports.GetMouseWheelMove=native.GetMouseWheelMove

// Get mouse wheel movement for both X and Y
exports.GetMouseWheelMoveV=native.GetMouseWheelMoveV

// Set mouse cursor
exports.SetMouseCursor=native.SetMouseCursor

// Get touch position X for touch point 0 (relative to screen size)
exports.GetTouchX=native.GetTouchX

// Get touch position Y for touch point 0 (relative to screen size)
exports.GetTouchY=native.GetTouchY

// Get touch position XY for a touch point index (relative to screen size)
exports.GetTouchPosition=native.GetTouchPosition

// Get touch point identifier for given index
exports.GetTouchPointId=native.GetTouchPointId

// Get number of touch points
exports.GetTouchPointCount=native.GetTouchPointCount

// Enable a set of gestures using flags
exports.SetGesturesEnabled=native.SetGesturesEnabled

// Check if a gesture have been detected
exports.IsGestureDetected=native.IsGestureDetected

// Get latest detected gesture
exports.GetGestureDetected=native.GetGestureDetected

// Get gesture hold time in seconds
exports.GetGestureHoldDuration=native.GetGestureHoldDuration

// Get gesture drag vector
exports.GetGestureDragVector=native.GetGestureDragVector

// Get gesture drag angle
exports.GetGestureDragAngle=native.GetGestureDragAngle

// Get gesture pinch delta
exports.GetGesturePinchVector=native.GetGesturePinchVector

// Get gesture pinch angle
exports.GetGesturePinchAngle=native.GetGesturePinchAngle

// Update camera position for selected mode
exports.UpdateCamera=native.UpdateCamera

// Update camera movement/rotation
exports.UpdateCameraPro=native.UpdateCameraPro

// Set texture and rectangle to be used on shapes drawing
exports.SetShapesTexture=native.SetShapesTexture

// Get texture that is used for shapes drawing
exports.GetShapesTexture=native.GetShapesTexture

// Get texture source rectangle that is used for shapes drawing
exports.GetShapesTextureRectangle=native.GetShapesTextureRectangle

// Draw a pixel using geometry [Can be slow, use with care]
exports.DrawPixel=native.DrawPixel

// Draw a pixel using geometry (Vector version) [Can be slow, use with care]
exports.DrawPixelV=native.DrawPixelV

// Draw a line
exports.DrawLine=native.DrawLine

// Draw a line (using gl lines)
exports.DrawLineV=native.DrawLineV

// Draw a line (using triangles/quads)
exports.DrawLineEx=native.DrawLineEx

// Draw lines sequence (using gl lines)
exports.DrawLineStrip=native.DrawLineStrip

// Draw line segment cubic-bezier in-out interpolation
exports.DrawLineBezier=native.DrawLineBezier

// Draw a color-filled circle
exports.DrawCircle=native.DrawCircle

// Draw a piece of a circle
exports.DrawCircleSector=native.DrawCircleSector

// Draw circle sector outline
exports.DrawCircleSectorLines=native.DrawCircleSectorLines

// Draw a gradient-filled circle
exports.DrawCircleGradient=native.DrawCircleGradient

// Draw a color-filled circle (Vector version)
exports.DrawCircleV=native.DrawCircleV

// Draw circle outline
exports.DrawCircleLines=native.DrawCircleLines

// Draw circle outline (Vector version)
exports.DrawCircleLinesV=native.DrawCircleLinesV

// Draw ellipse
exports.DrawEllipse=native.DrawEllipse

// Draw ellipse outline
exports.DrawEllipseLines=native.DrawEllipseLines

// Draw ring
exports.DrawRing=native.DrawRing

// Draw ring outline
exports.DrawRingLines=native.DrawRingLines

// Draw a color-filled rectangle
exports.DrawRectangle=native.DrawRectangle

// Draw a color-filled rectangle (Vector version)
exports.DrawRectangleV=native.DrawRectangleV

// Draw a color-filled rectangle
exports.DrawRectangleRec=native.DrawRectangleRec

// Draw a color-filled rectangle with pro parameters
exports.DrawRectanglePro=native.DrawRectanglePro

// Draw a vertical-gradient-filled rectangle
exports.DrawRectangleGradientV=native.DrawRectangleGradientV

// Draw a horizontal-gradient-filled rectangle
exports.DrawRectangleGradientH=native.DrawRectangleGradientH

// Draw a gradient-filled rectangle with custom vertex colors
exports.DrawRectangleGradientEx=native.DrawRectangleGradientEx

// Draw rectangle outline
exports.DrawRectangleLines=native.DrawRectangleLines

// Draw rectangle outline with extended parameters
exports.DrawRectangleLinesEx=native.DrawRectangleLinesEx

// Draw rectangle with rounded edges
exports.DrawRectangleRounded=native.DrawRectangleRounded

// Draw rectangle lines with rounded edges
exports.DrawRectangleRoundedLines=native.DrawRectangleRoundedLines

// Draw rectangle with rounded edges outline
exports.DrawRectangleRoundedLinesEx=native.DrawRectangleRoundedLinesEx

// Draw a color-filled triangle (vertex in counter-clockwise order!)
exports.DrawTriangle=native.DrawTriangle

// Draw triangle outline (vertex in counter-clockwise order!)
exports.DrawTriangleLines=native.DrawTriangleLines

// Draw a triangle fan defined by points (first vertex is the center)
exports.DrawTriangleFan=native.DrawTriangleFan

// Draw a triangle strip defined by points
exports.DrawTriangleStrip=native.DrawTriangleStrip

// Draw a regular polygon (Vector version)
exports.DrawPoly=native.DrawPoly

// Draw a polygon outline of n sides
exports.DrawPolyLines=native.DrawPolyLines

// Draw a polygon outline of n sides with extended parameters
exports.DrawPolyLinesEx=native.DrawPolyLinesEx

// Draw spline: Linear, minimum 2 points
exports.DrawSplineLinear=native.DrawSplineLinear

// Draw spline: B-Spline, minimum 4 points
exports.DrawSplineBasis=native.DrawSplineBasis

// Draw spline: Catmull-Rom, minimum 4 points
exports.DrawSplineCatmullRom=native.DrawSplineCatmullRom

// Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
exports.DrawSplineBezierQuadratic=native.DrawSplineBezierQuadratic

// Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
exports.DrawSplineBezierCubic=native.DrawSplineBezierCubic

// Draw spline segment: Linear, 2 points
exports.DrawSplineSegmentLinear=native.DrawSplineSegmentLinear

// Draw spline segment: B-Spline, 4 points
exports.DrawSplineSegmentBasis=native.DrawSplineSegmentBasis

// Draw spline segment: Catmull-Rom, 4 points
exports.DrawSplineSegmentCatmullRom=native.DrawSplineSegmentCatmullRom

// Draw spline segment: Quadratic Bezier, 2 points, 1 control point
exports.DrawSplineSegmentBezierQuadratic=native.DrawSplineSegmentBezierQuadratic

// Draw spline segment: Cubic Bezier, 2 points, 2 control points
exports.DrawSplineSegmentBezierCubic=native.DrawSplineSegmentBezierCubic

// Get (evaluate) spline point: Linear
exports.GetSplinePointLinear=native.GetSplinePointLinear

// Get (evaluate) spline point: B-Spline
exports.GetSplinePointBasis=native.GetSplinePointBasis

// Get (evaluate) spline point: Catmull-Rom
exports.GetSplinePointCatmullRom=native.GetSplinePointCatmullRom

// Get (evaluate) spline point: Quadratic Bezier
exports.GetSplinePointBezierQuad=native.GetSplinePointBezierQuad

// Get (evaluate) spline point: Cubic Bezier
exports.GetSplinePointBezierCubic=native.GetSplinePointBezierCubic

// Check collision between two rectangles
exports.CheckCollisionRecs=native.CheckCollisionRecs

// Check collision between two circles
exports.CheckCollisionCircles=native.CheckCollisionCircles

// Check collision between circle and rectangle
exports.CheckCollisionCircleRec=native.CheckCollisionCircleRec

// Check if circle collides with a line created betweeen two points [p1] and [p2]
exports.CheckCollisionCircleLine=native.CheckCollisionCircleLine

// Check if point is inside rectangle
exports.CheckCollisionPointRec=native.CheckCollisionPointRec

// Check if point is inside circle
exports.CheckCollisionPointCircle=native.CheckCollisionPointCircle

// Check if point is inside a triangle
exports.CheckCollisionPointTriangle=native.CheckCollisionPointTriangle

// Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
exports.CheckCollisionPointLine=native.CheckCollisionPointLine

// Check if point is within a polygon described by array of vertices
exports.CheckCollisionPointPoly=native.CheckCollisionPointPoly

// Check the collision between two lines defined by two points each, returns collision point by reference
exports.CheckCollisionLines=native.CheckCollisionLines

// Get collision rectangle for two rectangles collision
exports.GetCollisionRec=native.GetCollisionRec

// Load image from file into CPU memory (RAM)
exports.LoadImage=native.LoadImage

// Load image from RAW file data
exports.LoadImageRaw=native.LoadImageRaw

// Load image sequence from file (frames appended to image.data)
exports.LoadImageAnim=native.LoadImageAnim

// Load image sequence from memory buffer
exports.LoadImageAnimFromMemory=native.LoadImageAnimFromMemory

// Load image from memory buffer, fileType refers to extension: i.e. '.png'
exports.LoadImageFromMemory=native.LoadImageFromMemory

// Load image from GPU texture data
exports.LoadImageFromTexture=native.LoadImageFromTexture

// Load image from screen buffer and (screenshot)
exports.LoadImageFromScreen=native.LoadImageFromScreen

// Check if an image is valid (data and parameters)
exports.IsImageValid=native.IsImageValid

// Unload image from CPU memory (RAM)
exports.UnloadImage=native.UnloadImage

// Export image data to file, returns true on success
exports.ExportImage=native.ExportImage

// Export image to memory buffer
exports.ExportImageToMemory=native.ExportImageToMemory

// Export image as code file defining an array of bytes, returns true on success
exports.ExportImageAsCode=native.ExportImageAsCode

// Generate image: plain color
exports.GenImageColor=native.GenImageColor

// Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
exports.GenImageGradientLinear=native.GenImageGradientLinear

// Generate image: radial gradient
exports.GenImageGradientRadial=native.GenImageGradientRadial

// Generate image: square gradient
exports.GenImageGradientSquare=native.GenImageGradientSquare

// Generate image: checked
exports.GenImageChecked=native.GenImageChecked

// Generate image: white noise
exports.GenImageWhiteNoise=native.GenImageWhiteNoise

// Generate image: perlin noise
exports.GenImagePerlinNoise=native.GenImagePerlinNoise

// Generate image: cellular algorithm, bigger tileSize means bigger cells
exports.GenImageCellular=native.GenImageCellular

// Generate image: grayscale image from text data
exports.GenImageText=native.GenImageText

// Create an image duplicate (useful for transformations)
exports.ImageCopy=native.ImageCopy

// Create an image from another image piece
exports.ImageFromImage=native.ImageFromImage

// Create an image from a selected channel of another image (GRAYSCALE)
exports.ImageFromChannel=native.ImageFromChannel

// Create an image from text (default font)
exports.ImageText=native.ImageText

// Create an image from text (custom sprite font)
exports.ImageTextEx=native.ImageTextEx

// Convert image data to desired format
exports.ImageFormat=native.ImageFormat

// Convert image to POT (power-of-two)
exports.ImageToPOT=native.ImageToPOT

// Crop an image to a defined rectangle
exports.ImageCrop=native.ImageCrop

// Crop image depending on alpha value
exports.ImageAlphaCrop=native.ImageAlphaCrop

// Clear alpha channel to desired color
exports.ImageAlphaClear=native.ImageAlphaClear

// Apply alpha mask to image
exports.ImageAlphaMask=native.ImageAlphaMask

// Premultiply alpha channel
exports.ImageAlphaPremultiply=native.ImageAlphaPremultiply

// Apply Gaussian blur using a box blur approximation
exports.ImageBlurGaussian=native.ImageBlurGaussian

// Apply custom square convolution kernel to image
exports.ImageKernelConvolution=native.ImageKernelConvolution

// Resize image (Bicubic scaling algorithm)
exports.ImageResize=native.ImageResize

// Resize image (Nearest-Neighbor scaling algorithm)
exports.ImageResizeNN=native.ImageResizeNN

// Resize canvas and fill with color
exports.ImageResizeCanvas=native.ImageResizeCanvas

// Compute all mipmap levels for a provided image
exports.ImageMipmaps=native.ImageMipmaps

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
exports.ImageDither=native.ImageDither

// Flip image vertically
exports.ImageFlipVertical=native.ImageFlipVertical

// Flip image horizontally
exports.ImageFlipHorizontal=native.ImageFlipHorizontal

// Rotate image by input angle in degrees (-359 to 359)
exports.ImageRotate=native.ImageRotate

// Rotate image clockwise 90deg
exports.ImageRotateCW=native.ImageRotateCW

// Rotate image counter-clockwise 90deg
exports.ImageRotateCCW=native.ImageRotateCCW

// Modify image color: tint
exports.ImageColorTint=native.ImageColorTint

// Modify image color: invert
exports.ImageColorInvert=native.ImageColorInvert

// Modify image color: grayscale
exports.ImageColorGrayscale=native.ImageColorGrayscale

// Modify image color: contrast (-100 to 100)
exports.ImageColorContrast=native.ImageColorContrast

// Modify image color: brightness (-255 to 255)
exports.ImageColorBrightness=native.ImageColorBrightness

// Modify image color: replace color
exports.ImageColorReplace=native.ImageColorReplace

// Load color data from image as a Color array (RGBA - 32bit)
exports.LoadImageColors=native.LoadImageColors

// Load colors palette from image as a Color array (RGBA - 32bit)
exports.LoadImagePalette=native.LoadImagePalette

// Unload color data loaded with LoadImageColors()
exports.UnloadImageColors=native.UnloadImageColors

// Unload colors palette loaded with LoadImagePalette()
exports.UnloadImagePalette=native.UnloadImagePalette

// Get image alpha border rectangle
exports.GetImageAlphaBorder=native.GetImageAlphaBorder

// Get image pixel color at (x, y) position
exports.GetImageColor=native.GetImageColor

// Clear image background with given color
exports.ImageClearBackground=native.ImageClearBackground

// Draw pixel within an image
exports.ImageDrawPixel=native.ImageDrawPixel

// Draw pixel within an image (Vector version)
exports.ImageDrawPixelV=native.ImageDrawPixelV

// Draw line within an image
exports.ImageDrawLine=native.ImageDrawLine

// Draw line within an image (Vector version)
exports.ImageDrawLineV=native.ImageDrawLineV

// Draw a line defining thickness within an image
exports.ImageDrawLineEx=native.ImageDrawLineEx

// Draw a filled circle within an image
exports.ImageDrawCircle=native.ImageDrawCircle

// Draw a filled circle within an image (Vector version)
exports.ImageDrawCircleV=native.ImageDrawCircleV

// Draw circle outline within an image
exports.ImageDrawCircleLines=native.ImageDrawCircleLines

// Draw circle outline within an image (Vector version)
exports.ImageDrawCircleLinesV=native.ImageDrawCircleLinesV

// Draw rectangle within an image
exports.ImageDrawRectangle=native.ImageDrawRectangle

// Draw rectangle within an image (Vector version)
exports.ImageDrawRectangleV=native.ImageDrawRectangleV

// Draw rectangle within an image
exports.ImageDrawRectangleRec=native.ImageDrawRectangleRec

// Draw rectangle lines within an image
exports.ImageDrawRectangleLines=native.ImageDrawRectangleLines

// Draw triangle within an image
exports.ImageDrawTriangle=native.ImageDrawTriangle

// Draw triangle with interpolated colors within an image
exports.ImageDrawTriangleEx=native.ImageDrawTriangleEx

// Draw triangle outline within an image
exports.ImageDrawTriangleLines=native.ImageDrawTriangleLines

// Draw a triangle fan defined by points within an image (first vertex is the center)
exports.ImageDrawTriangleFan=native.ImageDrawTriangleFan

// Draw a triangle strip defined by points within an image
exports.ImageDrawTriangleStrip=native.ImageDrawTriangleStrip

// Draw a source image within a destination image (tint applied to source)
exports.ImageDraw=native.ImageDraw

// Draw text (using default font) within an image (destination)
exports.ImageDrawText=native.ImageDrawText

// Draw text (custom sprite font) within an image (destination)
exports.ImageDrawTextEx=native.ImageDrawTextEx

// Load texture from file into GPU memory (VRAM)
exports.LoadTexture=native.LoadTexture

// Load texture from image data
exports.LoadTextureFromImage=native.LoadTextureFromImage

// Load cubemap from image, multiple image cubemap layouts supported
exports.LoadTextureCubemap=native.LoadTextureCubemap

// Load texture for rendering (framebuffer)
exports.LoadRenderTexture=native.LoadRenderTexture

// Check if a texture is valid (loaded in GPU)
exports.IsTextureValid=native.IsTextureValid

// Unload texture from GPU memory (VRAM)
exports.UnloadTexture=native.UnloadTexture

// Check if a render texture is valid (loaded in GPU)
exports.IsRenderTextureValid=native.IsRenderTextureValid

// Unload render texture from GPU memory (VRAM)
exports.UnloadRenderTexture=native.UnloadRenderTexture

// Update GPU texture with new data
exports.UpdateTexture=native.UpdateTexture

// Update GPU texture rectangle with new data
exports.UpdateTextureRec=native.UpdateTextureRec

// Generate GPU mipmaps for a texture
exports.GenTextureMipmaps=native.GenTextureMipmaps

// Set texture scaling filter mode
exports.SetTextureFilter=native.SetTextureFilter

// Set texture wrapping mode
exports.SetTextureWrap=native.SetTextureWrap

// Draw a Texture2D
exports.DrawTexture=native.DrawTexture

// Draw a Texture2D with position defined as Vector2
exports.DrawTextureV=native.DrawTextureV

// Draw a Texture2D with extended parameters
exports.DrawTextureEx=native.DrawTextureEx

// Draw a part of a texture defined by a rectangle
exports.DrawTextureRec=native.DrawTextureRec

// Draw a part of a texture defined by a rectangle with 'pro' parameters
exports.DrawTexturePro=native.DrawTexturePro

// Draws a texture (or part of it) that stretches or shrinks nicely
exports.DrawTextureNPatch=native.DrawTextureNPatch

// Check if two colors are equal
exports.ColorIsEqual=native.ColorIsEqual

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
exports.Fade=native.Fade

// Get hexadecimal value for a Color (0xRRGGBBAA)
exports.ColorToInt=native.ColorToInt

// Get Color normalized as float [0..1]
exports.ColorNormalize=native.ColorNormalize

// Get Color from normalized values [0..1]
exports.ColorFromNormalized=native.ColorFromNormalized

// Get HSV values for a Color, hue [0..360], saturation/value [0..1]
exports.ColorToHSV=native.ColorToHSV

// Get a Color from HSV values, hue [0..360], saturation/value [0..1]
exports.ColorFromHSV=native.ColorFromHSV

// Get color multiplied with another color
exports.ColorTint=native.ColorTint

// Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
exports.ColorBrightness=native.ColorBrightness

// Get color with contrast correction, contrast values between -1.0f and 1.0f
exports.ColorContrast=native.ColorContrast

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
exports.ColorAlpha=native.ColorAlpha

// Get src alpha-blended into dst color with tint
exports.ColorAlphaBlend=native.ColorAlphaBlend

// Get color lerp interpolation between two colors, factor [0.0f..1.0f]
exports.ColorLerp=native.ColorLerp

// Get Color structure from hexadecimal value
exports.GetColor=native.GetColor

// Get Color from a source pixel pointer of certain format
exports.GetPixelColor=native.GetPixelColor

// Set color formatted into destination pixel pointer
exports.SetPixelColor=native.SetPixelColor

// Get pixel data size in bytes for certain format
exports.GetPixelDataSize=native.GetPixelDataSize

// Get the default Font
exports.GetFontDefault=native.GetFontDefault

// Load font from file into GPU memory (VRAM)
exports.LoadFont=native.LoadFont

// Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height
exports.LoadFontEx=native.LoadFontEx

// Load font from Image (XNA style)
exports.LoadFontFromImage=native.LoadFontFromImage

// Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
exports.LoadFontFromMemory=native.LoadFontFromMemory

// Check if a font is valid (font data loaded, WARNING: GPU texture not checked)
exports.IsFontValid=native.IsFontValid

// Load font data for further use
exports.LoadFontData=native.LoadFontData

// Generate image font atlas using chars info
exports.GenImageFontAtlas=native.GenImageFontAtlas

// Unload font chars info data (RAM)
exports.UnloadFontData=native.UnloadFontData

// Unload font from GPU memory (VRAM)
exports.UnloadFont=native.UnloadFont

// Export font as code file, returns true on success
exports.ExportFontAsCode=native.ExportFontAsCode

// Draw current FPS
exports.DrawFPS=native.DrawFPS

// Draw text (using default font)
exports.DrawText=native.DrawText

// Draw text using font and additional parameters
exports.DrawTextEx=native.DrawTextEx

// Draw text using Font and pro parameters (rotation)
exports.DrawTextPro=native.DrawTextPro

// Draw one character (codepoint)
exports.DrawTextCodepoint=native.DrawTextCodepoint

// Draw multiple character (codepoint)
exports.DrawTextCodepoints=native.DrawTextCodepoints

// Set vertical line spacing when drawing with line-breaks
exports.SetTextLineSpacing=native.SetTextLineSpacing

// Measure string width for default font
exports.MeasureText=native.MeasureText

// Measure string size for Font
exports.MeasureTextEx=native.MeasureTextEx

// Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
exports.GetGlyphIndex=native.GetGlyphIndex

// Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
exports.GetGlyphInfo=native.GetGlyphInfo

// Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
exports.GetGlyphAtlasRec=native.GetGlyphAtlasRec

// Load UTF-8 text encoded from codepoints array
exports.LoadUTF8=native.LoadUTF8

// Unload UTF-8 text encoded from codepoints array
exports.UnloadUTF8=native.UnloadUTF8

// Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
exports.LoadCodepoints=native.LoadCodepoints

// Unload codepoints data from memory
exports.UnloadCodepoints=native.UnloadCodepoints

// Get total number of codepoints in a UTF-8 encoded string
exports.GetCodepointCount=native.GetCodepointCount

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
exports.GetCodepoint=native.GetCodepoint

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
exports.GetCodepointNext=native.GetCodepointNext

// Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
exports.GetCodepointPrevious=native.GetCodepointPrevious

// Encode one codepoint into UTF-8 byte array (array length returned as parameter)
exports.CodepointToUTF8=native.CodepointToUTF8

// Copy one string to another, returns bytes copied
exports.TextCopy=native.TextCopy

// Check if two text string are equal
exports.TextIsEqual=native.TextIsEqual

// Get text length, checks for '\0' ending
exports.TextLength=native.TextLength

// Get a piece of a text string
exports.TextSubtext=native.TextSubtext

// Replace text string (WARNING: memory must be freed!)
exports.TextReplace=native.TextReplace

// Insert text in a position (WARNING: memory must be freed!)
exports.TextInsert=native.TextInsert

// Join text strings with delimiter
exports.TextJoin=native.TextJoin

// Split text into multiple strings
exports.TextSplit=native.TextSplit

// Append text at specific position and move cursor!
exports.TextAppend=native.TextAppend

// Find first text occurrence within a string
exports.TextFindIndex=native.TextFindIndex

// Get upper case version of provided string
exports.TextToUpper=native.TextToUpper

// Get lower case version of provided string
exports.TextToLower=native.TextToLower

// Get Pascal case notation version of provided string
exports.TextToPascal=native.TextToPascal

// Get Snake case notation version of provided string
exports.TextToSnake=native.TextToSnake

// Get Camel case notation version of provided string
exports.TextToCamel=native.TextToCamel

// Get integer value from text (negative values not supported)
exports.TextToInteger=native.TextToInteger

// Get float value from text (negative values not supported)
exports.TextToFloat=native.TextToFloat

// Draw a line in 3D world space
exports.DrawLine3D=native.DrawLine3D

// Draw a point in 3D space, actually a small line
exports.DrawPoint3D=native.DrawPoint3D

// Draw a circle in 3D world space
exports.DrawCircle3D=native.DrawCircle3D

// Draw a color-filled triangle (vertex in counter-clockwise order!)
exports.DrawTriangle3D=native.DrawTriangle3D

// Draw a triangle strip defined by points
exports.DrawTriangleStrip3D=native.DrawTriangleStrip3D

// Draw cube
exports.DrawCube=native.DrawCube

// Draw cube (Vector version)
exports.DrawCubeV=native.DrawCubeV

// Draw cube wires
exports.DrawCubeWires=native.DrawCubeWires

// Draw cube wires (Vector version)
exports.DrawCubeWiresV=native.DrawCubeWiresV

// Draw sphere
exports.DrawSphere=native.DrawSphere

// Draw sphere with extended parameters
exports.DrawSphereEx=native.DrawSphereEx

// Draw sphere wires
exports.DrawSphereWires=native.DrawSphereWires

// Draw a cylinder/cone
exports.DrawCylinder=native.DrawCylinder

// Draw a cylinder with base at startPos and top at endPos
exports.DrawCylinderEx=native.DrawCylinderEx

// Draw a cylinder/cone wires
exports.DrawCylinderWires=native.DrawCylinderWires

// Draw a cylinder wires with base at startPos and top at endPos
exports.DrawCylinderWiresEx=native.DrawCylinderWiresEx

// Draw a capsule with the center of its sphere caps at startPos and endPos
exports.DrawCapsule=native.DrawCapsule

// Draw capsule wireframe with the center of its sphere caps at startPos and endPos
exports.DrawCapsuleWires=native.DrawCapsuleWires

// Draw a plane XZ
exports.DrawPlane=native.DrawPlane

// Draw a ray line
exports.DrawRay=native.DrawRay

// Draw a grid (centered at (0, 0, 0))
exports.DrawGrid=native.DrawGrid

// Load model from files (meshes and materials)
exports.LoadModel=native.LoadModel

// Load model from generated mesh (default material)
exports.LoadModelFromMesh=native.LoadModelFromMesh

// Check if a model is valid (loaded in GPU, VAO/VBOs)
exports.IsModelValid=native.IsModelValid

// Unload model (including meshes) from memory (RAM and/or VRAM)
exports.UnloadModel=native.UnloadModel

// Compute model bounding box limits (considers all meshes)
exports.GetModelBoundingBox=native.GetModelBoundingBox

// Draw a model (with texture if set)
exports.DrawModel=native.DrawModel

// Draw a model with extended parameters
exports.DrawModelEx=native.DrawModelEx

// Draw a model wires (with texture if set)
exports.DrawModelWires=native.DrawModelWires

// Draw a model wires (with texture if set) with extended parameters
exports.DrawModelWiresEx=native.DrawModelWiresEx

// Draw a model as points
exports.DrawModelPoints=native.DrawModelPoints

// Draw a model as points with extended parameters
exports.DrawModelPointsEx=native.DrawModelPointsEx

// Draw bounding box (wires)
exports.DrawBoundingBox=native.DrawBoundingBox

// Draw a billboard texture
exports.DrawBillboard=native.DrawBillboard

// Draw a billboard texture defined by source
exports.DrawBillboardRec=native.DrawBillboardRec

// Draw a billboard texture defined by source and rotation
exports.DrawBillboardPro=native.DrawBillboardPro

// Upload mesh vertex data in GPU and provide VAO/VBO ids
exports.UploadMesh=native.UploadMesh

// Update mesh vertex data in GPU for a specific buffer index
exports.UpdateMeshBuffer=native.UpdateMeshBuffer

// Unload mesh data from CPU and GPU
exports.UnloadMesh=native.UnloadMesh

// Draw a 3d mesh with material and transform
exports.DrawMesh=native.DrawMesh

// Draw multiple mesh instances with material and different transforms
exports.DrawMeshInstanced=native.DrawMeshInstanced

// Compute mesh bounding box limits
exports.GetMeshBoundingBox=native.GetMeshBoundingBox

// Compute mesh tangents
exports.GenMeshTangents=native.GenMeshTangents

// Export mesh data to file, returns true on success
exports.ExportMesh=native.ExportMesh

// Export mesh as code file (.h) defining multiple arrays of vertex attributes
exports.ExportMeshAsCode=native.ExportMeshAsCode

// Generate polygonal mesh
exports.GenMeshPoly=native.GenMeshPoly

// Generate plane mesh (with subdivisions)
exports.GenMeshPlane=native.GenMeshPlane

// Generate cuboid mesh
exports.GenMeshCube=native.GenMeshCube

// Generate sphere mesh (standard sphere)
exports.GenMeshSphere=native.GenMeshSphere

// Generate half-sphere mesh (no bottom cap)
exports.GenMeshHemiSphere=native.GenMeshHemiSphere

// Generate cylinder mesh
exports.GenMeshCylinder=native.GenMeshCylinder

// Generate cone/pyramid mesh
exports.GenMeshCone=native.GenMeshCone

// Generate torus mesh
exports.GenMeshTorus=native.GenMeshTorus

// Generate trefoil knot mesh
exports.GenMeshKnot=native.GenMeshKnot

// Generate heightmap mesh from image data
exports.GenMeshHeightmap=native.GenMeshHeightmap

// Generate cubes-based map mesh from image data
exports.GenMeshCubicmap=native.GenMeshCubicmap

// Load materials from model file
exports.LoadMaterials=native.LoadMaterials

// Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
exports.LoadMaterialDefault=native.LoadMaterialDefault

// Check if a material is valid (shader assigned, map textures loaded in GPU)
exports.IsMaterialValid=native.IsMaterialValid

// Unload material from GPU memory (VRAM)
exports.UnloadMaterial=native.UnloadMaterial

// Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
exports.SetMaterialTexture=native.SetMaterialTexture

// Set material for a mesh
exports.SetModelMeshMaterial=native.SetModelMeshMaterial

// Load model animations from file
exports.LoadModelAnimations=native.LoadModelAnimations

// Update model animation pose (CPU)
exports.UpdateModelAnimation=native.UpdateModelAnimation

// Update model animation mesh bone matrices (GPU skinning)
exports.UpdateModelAnimationBones=native.UpdateModelAnimationBones

// Unload animation data
exports.UnloadModelAnimation=native.UnloadModelAnimation

// Unload animation array data
exports.UnloadModelAnimations=native.UnloadModelAnimations

// Check model animation skeleton match
exports.IsModelAnimationValid=native.IsModelAnimationValid

// Check collision between two spheres
exports.CheckCollisionSpheres=native.CheckCollisionSpheres

// Check collision between two bounding boxes
exports.CheckCollisionBoxes=native.CheckCollisionBoxes

// Check collision between box and sphere
exports.CheckCollisionBoxSphere=native.CheckCollisionBoxSphere

// Get collision info between ray and sphere
exports.GetRayCollisionSphere=native.GetRayCollisionSphere

// Get collision info between ray and box
exports.GetRayCollisionBox=native.GetRayCollisionBox

// Get collision info between ray and mesh
exports.GetRayCollisionMesh=native.GetRayCollisionMesh

// Get collision info between ray and triangle
exports.GetRayCollisionTriangle=native.GetRayCollisionTriangle

// Get collision info between ray and quad
exports.GetRayCollisionQuad=native.GetRayCollisionQuad

// Initialize audio device and context
exports.InitAudioDevice=native.InitAudioDevice

// Close the audio device and context
exports.CloseAudioDevice=native.CloseAudioDevice

// Check if audio device has been initialized successfully
exports.IsAudioDeviceReady=native.IsAudioDeviceReady

// Set master volume (listener)
exports.SetMasterVolume=native.SetMasterVolume

// Get master volume (listener)
exports.GetMasterVolume=native.GetMasterVolume

// Load wave data from file
exports.LoadWave=native.LoadWave

// Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
exports.LoadWaveFromMemory=native.LoadWaveFromMemory

// Checks if wave data is valid (data loaded and parameters)
exports.IsWaveValid=native.IsWaveValid

// Load sound from file
exports.LoadSound=native.LoadSound

// Load sound from wave data
exports.LoadSoundFromWave=native.LoadSoundFromWave

// Create a new sound that shares the same sample data as the source sound, does not own the sound data
exports.LoadSoundAlias=native.LoadSoundAlias

// Checks if a sound is valid (data loaded and buffers initialized)
exports.IsSoundValid=native.IsSoundValid

// Update sound buffer with new data
exports.UpdateSound=native.UpdateSound

// Unload wave data
exports.UnloadWave=native.UnloadWave

// Unload sound
exports.UnloadSound=native.UnloadSound

// Unload a sound alias (does not deallocate sample data)
exports.UnloadSoundAlias=native.UnloadSoundAlias

// Export wave data to file, returns true on success
exports.ExportWave=native.ExportWave

// Export wave sample data to code (.h), returns true on success
exports.ExportWaveAsCode=native.ExportWaveAsCode

// Play a sound
exports.PlaySound=native.PlaySound

// Stop playing a sound
exports.StopSound=native.StopSound

// Pause a sound
exports.PauseSound=native.PauseSound

// Resume a paused sound
exports.ResumeSound=native.ResumeSound

// Check if a sound is currently playing
exports.IsSoundPlaying=native.IsSoundPlaying

// Set volume for a sound (1.0 is max level)
exports.SetSoundVolume=native.SetSoundVolume

// Set pitch for a sound (1.0 is base level)
exports.SetSoundPitch=native.SetSoundPitch

// Set pan for a sound (0.5 is center)
exports.SetSoundPan=native.SetSoundPan

// Copy a wave to a new wave
exports.WaveCopy=native.WaveCopy

// Crop a wave to defined frames range
exports.WaveCrop=native.WaveCrop

// Convert wave data to desired format
exports.WaveFormat=native.WaveFormat

// Load samples data from wave as a 32bit float data array
exports.LoadWaveSamples=native.LoadWaveSamples

// Unload samples data loaded with LoadWaveSamples()
exports.UnloadWaveSamples=native.UnloadWaveSamples

// Load music stream from file
exports.LoadMusicStream=native.LoadMusicStream

// Load music stream from data
exports.LoadMusicStreamFromMemory=native.LoadMusicStreamFromMemory

// Checks if a music stream is valid (context and buffers initialized)
exports.IsMusicValid=native.IsMusicValid

// Unload music stream
exports.UnloadMusicStream=native.UnloadMusicStream

// Start music playing
exports.PlayMusicStream=native.PlayMusicStream

// Check if music is playing
exports.IsMusicStreamPlaying=native.IsMusicStreamPlaying

// Updates buffers for music streaming
exports.UpdateMusicStream=native.UpdateMusicStream

// Stop music playing
exports.StopMusicStream=native.StopMusicStream

// Pause music playing
exports.PauseMusicStream=native.PauseMusicStream

// Resume playing paused music
exports.ResumeMusicStream=native.ResumeMusicStream

// Seek music to a position (in seconds)
exports.SeekMusicStream=native.SeekMusicStream

// Set volume for music (1.0 is max level)
exports.SetMusicVolume=native.SetMusicVolume

// Set pitch for a music (1.0 is base level)
exports.SetMusicPitch=native.SetMusicPitch

// Set pan for a music (0.5 is center)
exports.SetMusicPan=native.SetMusicPan

// Get music time length (in seconds)
exports.GetMusicTimeLength=native.GetMusicTimeLength

// Get current music time played (in seconds)
exports.GetMusicTimePlayed=native.GetMusicTimePlayed

// Load audio stream (to stream raw audio pcm data)
exports.LoadAudioStream=native.LoadAudioStream

// Checks if an audio stream is valid (buffers initialized)
exports.IsAudioStreamValid=native.IsAudioStreamValid

// Unload audio stream and free memory
exports.UnloadAudioStream=native.UnloadAudioStream

// Update audio stream buffers with data
exports.UpdateAudioStream=native.UpdateAudioStream

// Check if any audio stream buffers requires refill
exports.IsAudioStreamProcessed=native.IsAudioStreamProcessed

// Play audio stream
exports.PlayAudioStream=native.PlayAudioStream

// Pause audio stream
exports.PauseAudioStream=native.PauseAudioStream

// Resume audio stream
exports.ResumeAudioStream=native.ResumeAudioStream

// Check if audio stream is playing
exports.IsAudioStreamPlaying=native.IsAudioStreamPlaying

// Stop audio stream
exports.StopAudioStream=native.StopAudioStream

// Set volume for audio stream (1.0 is max level)
exports.SetAudioStreamVolume=native.SetAudioStreamVolume

// Set pitch for audio stream (1.0 is base level)
exports.SetAudioStreamPitch=native.SetAudioStreamPitch

// Set pan for audio stream (0.5 is centered)
exports.SetAudioStreamPan=native.SetAudioStreamPan

// Default size for new audio streams
exports.SetAudioStreamBufferSizeDefault=native.SetAudioStreamBufferSizeDefault

// Audio thread callback to request new data
exports.SetAudioStreamCallback=native.SetAudioStreamCallback

// Attach audio stream processor to stream, receives the samples as 'float'
exports.AttachAudioStreamProcessor=native.AttachAudioStreamProcessor

// Detach audio stream processor from stream
exports.DetachAudioStreamProcessor=native.DetachAudioStreamProcessor

// Attach audio stream processor to the entire audio pipeline, receives the samples as 'float'
exports.AttachAudioMixedProcessor=native.AttachAudioMixedProcessor

// Detach audio stream processor from the entire audio pipeline
exports.DetachAudioMixedProcessor=native.DetachAudioMixedProcessor

// ConfigFlags: System/Window config flags
exports.FLAG_VSYNC_HINT=64 // Set to try enabling V-Sync on GPU
exports.FLAG_FULLSCREEN_MODE=2 // Set to run program in fullscreen
exports.FLAG_WINDOW_RESIZABLE=4 // Set to allow resizable window
exports.FLAG_WINDOW_UNDECORATED=8 // Set to disable window decoration (frame and buttons)
exports.FLAG_WINDOW_HIDDEN=128 // Set to hide window
exports.FLAG_WINDOW_MINIMIZED=512 // Set to minimize window (iconify)
exports.FLAG_WINDOW_MAXIMIZED=1024 // Set to maximize window (expanded to monitor)
exports.FLAG_WINDOW_UNFOCUSED=2048 // Set to window non focused
exports.FLAG_WINDOW_TOPMOST=4096 // Set to window always on top
exports.FLAG_WINDOW_ALWAYS_RUN=256 // Set to allow windows running while minimized
exports.FLAG_WINDOW_TRANSPARENT=16 // Set to allow transparent framebuffer
exports.FLAG_WINDOW_HIGHDPI=8192 // Set to support HighDPI
exports.FLAG_WINDOW_MOUSE_PASSTHROUGH=16384 // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
exports.FLAG_BORDERLESS_WINDOWED_MODE=32768 // Set to run program in borderless windowed mode
exports.FLAG_MSAA_4X_HINT=32 // Set to try enabling MSAA 4X
exports.FLAG_INTERLACED_HINT=65536 // Set to try enabling interlaced video format (for V3D)

// TraceLogLevel: Trace log level
exports.LOG_ALL=0 // Display all logs
exports.LOG_TRACE=1 // Trace logging, intended for internal use only
exports.LOG_DEBUG=2 // Debug logging, used for internal debugging, it should be disabled on release builds
exports.LOG_INFO=3 // Info logging, used for program execution info
exports.LOG_WARNING=4 // Warning logging, used on recoverable failures
exports.LOG_ERROR=5 // Error logging, used on unrecoverable failures
exports.LOG_FATAL=6 // Fatal logging, used to abort program: exit(EXIT_FAILURE)
exports.LOG_NONE=7 // Disable logging

// KeyboardKey: Keyboard keys (US keyboard layout)
exports.KEY_NULL=0 // Key: NULL, used for no key pressed
exports.KEY_APOSTROPHE=39 // Key: '
exports.KEY_COMMA=44 // Key: ,
exports.KEY_MINUS=45 // Key: -
exports.KEY_PERIOD=46 // Key: .
exports.KEY_SLASH=47 // Key: /
exports.KEY_ZERO=48 // Key: 0
exports.KEY_ONE=49 // Key: 1
exports.KEY_TWO=50 // Key: 2
exports.KEY_THREE=51 // Key: 3
exports.KEY_FOUR=52 // Key: 4
exports.KEY_FIVE=53 // Key: 5
exports.KEY_SIX=54 // Key: 6
exports.KEY_SEVEN=55 // Key: 7
exports.KEY_EIGHT=56 // Key: 8
exports.KEY_NINE=57 // Key: 9
exports.KEY_SEMICOLON=59 // Key: ;
exports.KEY_EQUAL=61 // Key: =
exports.KEY_A=65 // Key: A | a
exports.KEY_B=66 // Key: B | b
exports.KEY_C=67 // Key: C | c
exports.KEY_D=68 // Key: D | d
exports.KEY_E=69 // Key: E | e
exports.KEY_F=70 // Key: F | f
exports.KEY_G=71 // Key: G | g
exports.KEY_H=72 // Key: H | h
exports.KEY_I=73 // Key: I | i
exports.KEY_J=74 // Key: J | j
exports.KEY_K=75 // Key: K | k
exports.KEY_L=76 // Key: L | l
exports.KEY_M=77 // Key: M | m
exports.KEY_N=78 // Key: N | n
exports.KEY_O=79 // Key: O | o
exports.KEY_P=80 // Key: P | p
exports.KEY_Q=81 // Key: Q | q
exports.KEY_R=82 // Key: R | r
exports.KEY_S=83 // Key: S | s
exports.KEY_T=84 // Key: T | t
exports.KEY_U=85 // Key: U | u
exports.KEY_V=86 // Key: V | v
exports.KEY_W=87 // Key: W | w
exports.KEY_X=88 // Key: X | x
exports.KEY_Y=89 // Key: Y | y
exports.KEY_Z=90 // Key: Z | z
exports.KEY_LEFT_BRACKET=91 // Key: [
exports.KEY_BACKSLASH=92 // Key: '\'
exports.KEY_RIGHT_BRACKET=93 // Key: ]
exports.KEY_GRAVE=96 // Key: `
exports.KEY_SPACE=32 // Key: Space
exports.KEY_ESCAPE=256 // Key: Esc
exports.KEY_ENTER=257 // Key: Enter
exports.KEY_TAB=258 // Key: Tab
exports.KEY_BACKSPACE=259 // Key: Backspace
exports.KEY_INSERT=260 // Key: Ins
exports.KEY_DELETE=261 // Key: Del
exports.KEY_RIGHT=262 // Key: Cursor right
exports.KEY_LEFT=263 // Key: Cursor left
exports.KEY_DOWN=264 // Key: Cursor down
exports.KEY_UP=265 // Key: Cursor up
exports.KEY_PAGE_UP=266 // Key: Page up
exports.KEY_PAGE_DOWN=267 // Key: Page down
exports.KEY_HOME=268 // Key: Home
exports.KEY_END=269 // Key: End
exports.KEY_CAPS_LOCK=280 // Key: Caps lock
exports.KEY_SCROLL_LOCK=281 // Key: Scroll down
exports.KEY_NUM_LOCK=282 // Key: Num lock
exports.KEY_PRINT_SCREEN=283 // Key: Print screen
exports.KEY_PAUSE=284 // Key: Pause
exports.KEY_F1=290 // Key: F1
exports.KEY_F2=291 // Key: F2
exports.KEY_F3=292 // Key: F3
exports.KEY_F4=293 // Key: F4
exports.KEY_F5=294 // Key: F5
exports.KEY_F6=295 // Key: F6
exports.KEY_F7=296 // Key: F7
exports.KEY_F8=297 // Key: F8
exports.KEY_F9=298 // Key: F9
exports.KEY_F10=299 // Key: F10
exports.KEY_F11=300 // Key: F11
exports.KEY_F12=301 // Key: F12
exports.KEY_LEFT_SHIFT=340 // Key: Shift left
exports.KEY_LEFT_CONTROL=341 // Key: Control left
exports.KEY_LEFT_ALT=342 // Key: Alt left
exports.KEY_LEFT_SUPER=343 // Key: Super left
exports.KEY_RIGHT_SHIFT=344 // Key: Shift right
exports.KEY_RIGHT_CONTROL=345 // Key: Control right
exports.KEY_RIGHT_ALT=346 // Key: Alt right
exports.KEY_RIGHT_SUPER=347 // Key: Super right
exports.KEY_KB_MENU=348 // Key: KB menu
exports.KEY_KP_0=320 // Key: Keypad 0
exports.KEY_KP_1=321 // Key: Keypad 1
exports.KEY_KP_2=322 // Key: Keypad 2
exports.KEY_KP_3=323 // Key: Keypad 3
exports.KEY_KP_4=324 // Key: Keypad 4
exports.KEY_KP_5=325 // Key: Keypad 5
exports.KEY_KP_6=326 // Key: Keypad 6
exports.KEY_KP_7=327 // Key: Keypad 7
exports.KEY_KP_8=328 // Key: Keypad 8
exports.KEY_KP_9=329 // Key: Keypad 9
exports.KEY_KP_DECIMAL=330 // Key: Keypad .
exports.KEY_KP_DIVIDE=331 // Key: Keypad /
exports.KEY_KP_MULTIPLY=332 // Key: Keypad *
exports.KEY_KP_SUBTRACT=333 // Key: Keypad -
exports.KEY_KP_ADD=334 // Key: Keypad +
exports.KEY_KP_ENTER=335 // Key: Keypad Enter
exports.KEY_KP_EQUAL=336 // Key: Keypad =
exports.KEY_BACK=4 // Key: Android back button
exports.KEY_MENU=5 // Key: Android menu button
exports.KEY_VOLUME_UP=24 // Key: Android volume up button
exports.KEY_VOLUME_DOWN=25 // Key: Android volume down button

// MouseButton: Mouse buttons
exports.MOUSE_BUTTON_LEFT=0 // Mouse button left
exports.MOUSE_BUTTON_RIGHT=1 // Mouse button right
exports.MOUSE_BUTTON_MIDDLE=2 // Mouse button middle (pressed wheel)
exports.MOUSE_BUTTON_SIDE=3 // Mouse button side (advanced mouse device)
exports.MOUSE_BUTTON_EXTRA=4 // Mouse button extra (advanced mouse device)
exports.MOUSE_BUTTON_FORWARD=5 // Mouse button forward (advanced mouse device)
exports.MOUSE_BUTTON_BACK=6 // Mouse button back (advanced mouse device)

// MouseCursor: Mouse cursor
exports.MOUSE_CURSOR_DEFAULT=0 // Default pointer shape
exports.MOUSE_CURSOR_ARROW=1 // Arrow shape
exports.MOUSE_CURSOR_IBEAM=2 // Text writing cursor shape
exports.MOUSE_CURSOR_CROSSHAIR=3 // Cross shape
exports.MOUSE_CURSOR_POINTING_HAND=4 // Pointing hand cursor
exports.MOUSE_CURSOR_RESIZE_EW=5 // Horizontal resize/move arrow shape
exports.MOUSE_CURSOR_RESIZE_NS=6 // Vertical resize/move arrow shape
exports.MOUSE_CURSOR_RESIZE_NWSE=7 // Top-left to bottom-right diagonal resize/move arrow shape
exports.MOUSE_CURSOR_RESIZE_NESW=8 // The top-right to bottom-left diagonal resize/move arrow shape
exports.MOUSE_CURSOR_RESIZE_ALL=9 // The omnidirectional resize/move cursor shape
exports.MOUSE_CURSOR_NOT_ALLOWED=10 // The operation-not-allowed shape

// GamepadButton: Gamepad buttons
exports.GAMEPAD_BUTTON_UNKNOWN=0 // Unknown button, just for error checking
exports.GAMEPAD_BUTTON_LEFT_FACE_UP=1 // Gamepad left DPAD up button
exports.GAMEPAD_BUTTON_LEFT_FACE_RIGHT=2 // Gamepad left DPAD right button
exports.GAMEPAD_BUTTON_LEFT_FACE_DOWN=3 // Gamepad left DPAD down button
exports.GAMEPAD_BUTTON_LEFT_FACE_LEFT=4 // Gamepad left DPAD left button
exports.GAMEPAD_BUTTON_RIGHT_FACE_UP=5 // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
exports.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT=6 // Gamepad right button right (i.e. PS3: Circle, Xbox: B)
exports.GAMEPAD_BUTTON_RIGHT_FACE_DOWN=7 // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
exports.GAMEPAD_BUTTON_RIGHT_FACE_LEFT=8 // Gamepad right button left (i.e. PS3: Square, Xbox: X)
exports.GAMEPAD_BUTTON_LEFT_TRIGGER_1=9 // Gamepad top/back trigger left (first), it could be a trailing button
exports.GAMEPAD_BUTTON_LEFT_TRIGGER_2=10 // Gamepad top/back trigger left (second), it could be a trailing button
exports.GAMEPAD_BUTTON_RIGHT_TRIGGER_1=11 // Gamepad top/back trigger right (first), it could be a trailing button
exports.GAMEPAD_BUTTON_RIGHT_TRIGGER_2=12 // Gamepad top/back trigger right (second), it could be a trailing button
exports.GAMEPAD_BUTTON_MIDDLE_LEFT=13 // Gamepad center buttons, left one (i.e. PS3: Select)
exports.GAMEPAD_BUTTON_MIDDLE=14 // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
exports.GAMEPAD_BUTTON_MIDDLE_RIGHT=15 // Gamepad center buttons, right one (i.e. PS3: Start)
exports.GAMEPAD_BUTTON_LEFT_THUMB=16 // Gamepad joystick pressed button left
exports.GAMEPAD_BUTTON_RIGHT_THUMB=17 // Gamepad joystick pressed button right

// GamepadAxis: Gamepad axis
exports.GAMEPAD_AXIS_LEFT_X=0 // Gamepad left stick X axis
exports.GAMEPAD_AXIS_LEFT_Y=1 // Gamepad left stick Y axis
exports.GAMEPAD_AXIS_RIGHT_X=2 // Gamepad right stick X axis
exports.GAMEPAD_AXIS_RIGHT_Y=3 // Gamepad right stick Y axis
exports.GAMEPAD_AXIS_LEFT_TRIGGER=4 // Gamepad back trigger left, pressure level: [1..-1]
exports.GAMEPAD_AXIS_RIGHT_TRIGGER=5 // Gamepad back trigger right, pressure level: [1..-1]

// MaterialMapIndex: Material map index
exports.MATERIAL_MAP_ALBEDO=0 // Albedo material (same as: MATERIAL_MAP_DIFFUSE)
exports.MATERIAL_MAP_METALNESS=1 // Metalness material (same as: MATERIAL_MAP_SPECULAR)
exports.MATERIAL_MAP_NORMAL=2 // Normal material
exports.MATERIAL_MAP_ROUGHNESS=3 // Roughness material
exports.MATERIAL_MAP_OCCLUSION=4 // Ambient occlusion material
exports.MATERIAL_MAP_EMISSION=5 // Emission material
exports.MATERIAL_MAP_HEIGHT=6 // Heightmap material
exports.MATERIAL_MAP_CUBEMAP=7 // Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
exports.MATERIAL_MAP_IRRADIANCE=8 // Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
exports.MATERIAL_MAP_PREFILTER=9 // Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
exports.MATERIAL_MAP_BRDF=10 // Brdf material

// ShaderLocationIndex: Shader location index
exports.SHADER_LOC_VERTEX_POSITION=0 // Shader location: vertex attribute: position
exports.SHADER_LOC_VERTEX_TEXCOORD01=1 // Shader location: vertex attribute: texcoord01
exports.SHADER_LOC_VERTEX_TEXCOORD02=2 // Shader location: vertex attribute: texcoord02
exports.SHADER_LOC_VERTEX_NORMAL=3 // Shader location: vertex attribute: normal
exports.SHADER_LOC_VERTEX_TANGENT=4 // Shader location: vertex attribute: tangent
exports.SHADER_LOC_VERTEX_COLOR=5 // Shader location: vertex attribute: color
exports.SHADER_LOC_MATRIX_MVP=6 // Shader location: matrix uniform: model-view-projection
exports.SHADER_LOC_MATRIX_VIEW=7 // Shader location: matrix uniform: view (camera transform)
exports.SHADER_LOC_MATRIX_PROJECTION=8 // Shader location: matrix uniform: projection
exports.SHADER_LOC_MATRIX_MODEL=9 // Shader location: matrix uniform: model (transform)
exports.SHADER_LOC_MATRIX_NORMAL=10 // Shader location: matrix uniform: normal
exports.SHADER_LOC_VECTOR_VIEW=11 // Shader location: vector uniform: view
exports.SHADER_LOC_COLOR_DIFFUSE=12 // Shader location: vector uniform: diffuse color
exports.SHADER_LOC_COLOR_SPECULAR=13 // Shader location: vector uniform: specular color
exports.SHADER_LOC_COLOR_AMBIENT=14 // Shader location: vector uniform: ambient color
exports.SHADER_LOC_MAP_ALBEDO=15 // Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
exports.SHADER_LOC_MAP_METALNESS=16 // Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
exports.SHADER_LOC_MAP_NORMAL=17 // Shader location: sampler2d texture: normal
exports.SHADER_LOC_MAP_ROUGHNESS=18 // Shader location: sampler2d texture: roughness
exports.SHADER_LOC_MAP_OCCLUSION=19 // Shader location: sampler2d texture: occlusion
exports.SHADER_LOC_MAP_EMISSION=20 // Shader location: sampler2d texture: emission
exports.SHADER_LOC_MAP_HEIGHT=21 // Shader location: sampler2d texture: height
exports.SHADER_LOC_MAP_CUBEMAP=22 // Shader location: samplerCube texture: cubemap
exports.SHADER_LOC_MAP_IRRADIANCE=23 // Shader location: samplerCube texture: irradiance
exports.SHADER_LOC_MAP_PREFILTER=24 // Shader location: samplerCube texture: prefilter
exports.SHADER_LOC_MAP_BRDF=25 // Shader location: sampler2d texture: brdf
exports.SHADER_LOC_VERTEX_BONEIDS=26 // Shader location: vertex attribute: boneIds
exports.SHADER_LOC_VERTEX_BONEWEIGHTS=27 // Shader location: vertex attribute: boneWeights
exports.SHADER_LOC_BONE_MATRICES=28 // Shader location: array of matrices uniform: boneMatrices

// ShaderUniformDataType: Shader uniform data type
exports.SHADER_UNIFORM_FLOAT=0 // Shader uniform type: float
exports.SHADER_UNIFORM_VEC2=1 // Shader uniform type: vec2 (2 float)
exports.SHADER_UNIFORM_VEC3=2 // Shader uniform type: vec3 (3 float)
exports.SHADER_UNIFORM_VEC4=3 // Shader uniform type: vec4 (4 float)
exports.SHADER_UNIFORM_INT=4 // Shader uniform type: int
exports.SHADER_UNIFORM_IVEC2=5 // Shader uniform type: ivec2 (2 int)
exports.SHADER_UNIFORM_IVEC3=6 // Shader uniform type: ivec3 (3 int)
exports.SHADER_UNIFORM_IVEC4=7 // Shader uniform type: ivec4 (4 int)
exports.SHADER_UNIFORM_SAMPLER2D=8 // Shader uniform type: sampler2d

// ShaderAttributeDataType: Shader attribute data types
exports.SHADER_ATTRIB_FLOAT=0 // Shader attribute type: float
exports.SHADER_ATTRIB_VEC2=1 // Shader attribute type: vec2 (2 float)
exports.SHADER_ATTRIB_VEC3=2 // Shader attribute type: vec3 (3 float)
exports.SHADER_ATTRIB_VEC4=3 // Shader attribute type: vec4 (4 float)

// PixelFormat: Pixel formats
exports.PIXELFORMAT_UNCOMPRESSED_GRAYSCALE=1 // 8 bit per pixel (no alpha)
exports.PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA=2 // 8*2 bpp (2 channels)
exports.PIXELFORMAT_UNCOMPRESSED_R5G6B5=3 // 16 bpp
exports.PIXELFORMAT_UNCOMPRESSED_R8G8B8=4 // 24 bpp
exports.PIXELFORMAT_UNCOMPRESSED_R5G5B5A1=5 // 16 bpp (1 bit alpha)
exports.PIXELFORMAT_UNCOMPRESSED_R4G4B4A4=6 // 16 bpp (4 bit alpha)
exports.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8=7 // 32 bpp
exports.PIXELFORMAT_UNCOMPRESSED_R32=8 // 32 bpp (1 channel - float)
exports.PIXELFORMAT_UNCOMPRESSED_R32G32B32=9 // 32*3 bpp (3 channels - float)
exports.PIXELFORMAT_UNCOMPRESSED_R32G32B32A32=10 // 32*4 bpp (4 channels - float)
exports.PIXELFORMAT_UNCOMPRESSED_R16=11 // 16 bpp (1 channel - half float)
exports.PIXELFORMAT_UNCOMPRESSED_R16G16B16=12 // 16*3 bpp (3 channels - half float)
exports.PIXELFORMAT_UNCOMPRESSED_R16G16B16A16=13 // 16*4 bpp (4 channels - half float)
exports.PIXELFORMAT_COMPRESSED_DXT1_RGB=14 // 4 bpp (no alpha)
exports.PIXELFORMAT_COMPRESSED_DXT1_RGBA=15 // 4 bpp (1 bit alpha)
exports.PIXELFORMAT_COMPRESSED_DXT3_RGBA=16 // 8 bpp
exports.PIXELFORMAT_COMPRESSED_DXT5_RGBA=17 // 8 bpp
exports.PIXELFORMAT_COMPRESSED_ETC1_RGB=18 // 4 bpp
exports.PIXELFORMAT_COMPRESSED_ETC2_RGB=19 // 4 bpp
exports.PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA=20 // 8 bpp
exports.PIXELFORMAT_COMPRESSED_PVRT_RGB=21 // 4 bpp
exports.PIXELFORMAT_COMPRESSED_PVRT_RGBA=22 // 4 bpp
exports.PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA=23 // 8 bpp
exports.PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA=24 // 2 bpp

// TextureFilter: Texture parameters: filter mode
exports.TEXTURE_FILTER_POINT=0 // No filter, just pixel approximation
exports.TEXTURE_FILTER_BILINEAR=1 // Linear filtering
exports.TEXTURE_FILTER_TRILINEAR=2 // Trilinear filtering (linear with mipmaps)
exports.TEXTURE_FILTER_ANISOTROPIC_4X=3 // Anisotropic filtering 4x
exports.TEXTURE_FILTER_ANISOTROPIC_8X=4 // Anisotropic filtering 8x
exports.TEXTURE_FILTER_ANISOTROPIC_16X=5 // Anisotropic filtering 16x

// TextureWrap: Texture parameters: wrap mode
exports.TEXTURE_WRAP_REPEAT=0 // Repeats texture in tiled mode
exports.TEXTURE_WRAP_CLAMP=1 // Clamps texture to edge pixel in tiled mode
exports.TEXTURE_WRAP_MIRROR_REPEAT=2 // Mirrors and repeats the texture in tiled mode
exports.TEXTURE_WRAP_MIRROR_CLAMP=3 // Mirrors and clamps to border the texture in tiled mode

// CubemapLayout: Cubemap layouts
exports.CUBEMAP_LAYOUT_AUTO_DETECT=0 // Automatically detect layout type
exports.CUBEMAP_LAYOUT_LINE_VERTICAL=1 // Layout is defined by a vertical line with faces
exports.CUBEMAP_LAYOUT_LINE_HORIZONTAL=2 // Layout is defined by a horizontal line with faces
exports.CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR=3 // Layout is defined by a 3x4 cross with cubemap faces
exports.CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE=4 // Layout is defined by a 4x3 cross with cubemap faces

// FontType: Font type, defines generation method
exports.FONT_DEFAULT=0 // Default font generation, anti-aliased
exports.FONT_BITMAP=1 // Bitmap font generation, no anti-aliasing
exports.FONT_SDF=2 // SDF font generation, requires external shader

// BlendMode: Color blending modes (pre-defined)
exports.BLEND_ALPHA=0 // Blend textures considering alpha (default)
exports.BLEND_ADDITIVE=1 // Blend textures adding colors
exports.BLEND_MULTIPLIED=2 // Blend textures multiplying colors
exports.BLEND_ADD_COLORS=3 // Blend textures adding colors (alternative)
exports.BLEND_SUBTRACT_COLORS=4 // Blend textures subtracting colors (alternative)
exports.BLEND_ALPHA_PREMULTIPLY=5 // Blend premultiplied textures considering alpha
exports.BLEND_CUSTOM=6 // Blend textures using custom src/dst factors (use rlSetBlendFactors())
exports.BLEND_CUSTOM_SEPARATE=7 // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())

// Gesture: Gesture
exports.GESTURE_NONE=0 // No gesture
exports.GESTURE_TAP=1 // Tap gesture
exports.GESTURE_DOUBLETAP=2 // Double tap gesture
exports.GESTURE_HOLD=4 // Hold gesture
exports.GESTURE_DRAG=8 // Drag gesture
exports.GESTURE_SWIPE_RIGHT=16 // Swipe right gesture
exports.GESTURE_SWIPE_LEFT=32 // Swipe left gesture
exports.GESTURE_SWIPE_UP=64 // Swipe up gesture
exports.GESTURE_SWIPE_DOWN=128 // Swipe down gesture
exports.GESTURE_PINCH_IN=256 // Pinch in gesture
exports.GESTURE_PINCH_OUT=512 // Pinch out gesture

// CameraMode: Camera system modes
exports.CAMERA_CUSTOM=0 // Camera custom, controlled by user (UpdateCamera() does nothing)
exports.CAMERA_FREE=1 // Camera free mode
exports.CAMERA_ORBITAL=2 // Camera orbital, around target, zoom supported
exports.CAMERA_FIRST_PERSON=3 // Camera first person
exports.CAMERA_THIRD_PERSON=4 // Camera third person

// CameraProjection: Camera projection
exports.CAMERA_PERSPECTIVE=0 // Perspective projection
exports.CAMERA_ORTHOGRAPHIC=1 // Orthographic projection

// NPatchLayout: N-patch layout
exports.NPATCH_NINE_PATCH=0 // Npatch layout: 3x3 tiles
exports.NPATCH_THREE_PATCH_VERTICAL=1 // Npatch layout: 1x3 tiles
exports.NPATCH_THREE_PATCH_HORIZONTAL=2 // Npatch layout: 3x1 tiles

exports.LIGHTGRAY={ r:200, g:200, b:200, a:255 } // Light Gray
exports.GRAY={ r:130, g:130, b:130, a:255 } // Gray
exports.DARKGRAY={ r:80, g:80, b:80, a:255 } // Dark Gray
exports.YELLOW={ r:253, g:249, b:0, a:255 } // Yellow
exports.GOLD={ r:255, g:203, b:0, a:255 } // Gold
exports.ORANGE={ r:255, g:161, b:0, a:255 } // Orange
exports.PINK={ r:255, g:109, b:194, a:255 } // Pink
exports.RED={ r:230, g:41, b:55, a:255 } // Red
exports.MAROON={ r:190, g:33, b:55, a:255 } // Maroon
exports.GREEN={ r:0, g:228, b:48, a:255 } // Green
exports.LIME={ r:0, g:158, b:47, a:255 } // Lime
exports.DARKGREEN={ r:0, g:117, b:44, a:255 } // Dark Green
exports.SKYBLUE={ r:102, g:191, b:255, a:255 } // Sky Blue
exports.BLUE={ r:0, g:121, b:241, a:255 } // Blue
exports.DARKBLUE={ r:0, g:82, b:172, a:255 } // Dark Blue
exports.PURPLE={ r:200, g:122, b:255, a:255 } // Purple
exports.VIOLET={ r:135, g:60, b:190, a:255 } // Violet
exports.DARKPURPLE={ r:112, g:31, b:126, a:255 } // Dark Purple
exports.BEIGE={ r:211, g:176, b:131, a:255 } // Beige
exports.BROWN={ r:127, g:106, b:79, a:255 } // Brown
exports.DARKBROWN={ r:76, g:63, b:47, a:255 } // Dark Brown
exports.WHITE={ r:255, g:255, b:255, a:255 } // White
exports.BLACK={ r:0, g:0, b:0, a:255 } // Black
exports.BLANK={ r:0, g:0, b:0, a:0 } // Blank (Transparent)
exports.MAGENTA={ r:255, g:0, b:255, a:255 } // Magenta
exports.RAYWHITE={ r:245, g:245, b:245, a:255 } // My own White (raylib logo)

exports.Quaternion=exports.Vector4 // Quaternion, 4 components (Vector4 alias)
exports.Texture2D=exports.Texture // Texture2D, same as Texture
exports.TextureCubemap=exports.Texture // TextureCubemap, same as Texture
exports.RenderTexture2D=exports.RenderTexture // RenderTexture2D, same as RenderTexture
exports.Camera=exports.Camera3D // Camera type fallback, defaults to Camera3D