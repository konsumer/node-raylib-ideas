const {
  InitWindow,
  SetTargetFPS,
  WindowShouldClose,
  ClearBackground,
  DrawText,
  LIGHTGRAY,
  EndDrawing,
  CloseWindow
} = require('./index.js')

InitWindow(800, 450, 'raylib [core] example - basic window')
SetTargetFPS(60)

while (!WindowShouldClose()) {
  BeginDrawing()
  ClearBackground(RAYWHITE)
  DrawText('Congrats! You created your first node-raylib window!', 120, 200, 20, LIGHTGRAY)
  EndDrawing()
}

CloseWindow()
