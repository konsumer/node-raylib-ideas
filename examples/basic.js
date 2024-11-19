const r = require('../index.js')

r.InitWindow(800, 450, 'raylib [core] example - basic window')
r.SetTargetFPS(60)

while (!r.WindowShouldClose()) {
  r.BeginDrawing()
  r.ClearBackground(r.RAYWHITE)
  r.DrawText('Congrats! You created your first node-raylib window!', 120, 200, 20, r.LIGHTGRAY)
  r.EndDrawing()
}

r.CloseWindow()
