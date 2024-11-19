const native = require('./build/Release/node-raylib.node')

// TODO: I think all these exports could go directly in node-raylib.node

exports.SayHello = native.SayHello

exports.InitWindow = native.InitWindow
exports.SetTargetFPS = native.SetTargetFPS
exports.WindowShouldClose = native.WindowShouldClose
exports.ClearBackground = native.ClearBackground
exports.DrawText = native.DrawText
exports.EndDrawing = native.EndDrawing
exports.CloseWindow = native.CloseWindow
exports.BeginDrawing = native.BeginDrawing

exports.LIGHTGRAY = Object.freeze({ r: 200, g: 200, b: 200, a: 255 }) // Light Gray
exports.GRAY = Object.freeze({ r: 130, g: 130, b: 130, a: 255 }) // Gray
exports.DARKGRAY = Object.freeze({ r: 80, g: 80, b: 80, a: 255 }) // Dark Gray
exports.YELLOW = Object.freeze({ r: 253, g: 249, b: 0, a: 255 }) // Yellow
exports.GOLD = Object.freeze({ r: 255, g: 203, b: 0, a: 255 }) // Gold
exports.ORANGE = Object.freeze({ r: 255, g: 161, b: 0, a: 255 }) // Orange
exports.PINK = Object.freeze({ r: 255, g: 109, b: 194, a: 255 }) // Pink
exports.RED = Object.freeze({ r: 230, g: 41, b: 55, a: 255 }) // Red
exports.MAROON = Object.freeze({ r: 190, g: 33, b: 55, a: 255 }) // Maroon
exports.GREEN = Object.freeze({ r: 0, g: 228, b: 48, a: 255 }) // Green
exports.LIME = Object.freeze({ r: 0, g: 158, b: 47, a: 255 }) // Lime
exports.DARKGREEN = Object.freeze({ r: 0, g: 117, b: 44, a: 255 }) // Dark Green
exports.SKYBLUE = Object.freeze({ r: 102, g: 191, b: 255, a: 255 }) // Sky Blue
exports.BLUE = Object.freeze({ r: 0, g: 121, b: 241, a: 255 }) // Blue
exports.DARKBLUE = Object.freeze({ r: 0, g: 82, b: 172, a: 255 }) // Dark Blue
exports.PURPLE = Object.freeze({ r: 200, g: 122, b: 255, a: 255 }) // Purple
exports.VIOLET = Object.freeze({ r: 135, g: 60, b: 190, a: 255 }) // Violet
exports.DARKPURPLE = Object.freeze({ r: 112, g: 31, b: 126, a: 255 }) // Dark Purple
exports.BEIGE = Object.freeze({ r: 211, g: 176, b: 131, a: 255 }) // Beige
exports.BROWN = Object.freeze({ r: 127, g: 106, b: 79, a: 255 }) // Brown
exports.DARKBROWN = Object.freeze({ r: 76, g: 63, b: 47, a: 255 }) // Dark Brown
exports.WHITE = Object.freeze({ r: 255, g: 255, b: 255, a: 255 }) // White
exports.BLACK = Object.freeze({ r: 0, g: 0, b: 0, a: 255 }) // Black
exports.BLANK = Object.freeze({ r: 0, g: 0, b: 0, a: 0 }) // Blank (Transparent)
exports.MAGENTA = Object.freeze({ r: 255, g: 0, b: 255, a: 255 }) // Magenta
exports.RAYWHITE = Object.freeze({ r: 245, g: 245, b: 245, a: 255 }) // My own White (raylib logo)
