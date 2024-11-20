const r = require('raylib')

r.InitWindow(800, 450, 'raylib [core] example - basic window')
r.SetTargetFPS(60)

// these are equivilant
r.TraceLog(r.LOG_INFO, 'Hi from %s!', 'node-raylib')
console.log(r.TextFormat('Hi from %s!', 'node-raylib'))

while (!r.WindowShouldClose()) {
  r.BeginDrawing()
  r.ClearBackground(r.RAYWHITE)
  r.DrawText('Congrats! You created your first node-raylib window!', 120, 200, 20, r.LIGHTGRAY)
  r.EndDrawing()
  r.DrawFPS(10, 10)
}

r.CloseWindow()
