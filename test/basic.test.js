import * as raylib from '../index.js'

test('should have tests', () => {
  expect(1+1).toBe(2)
})

test('raylib.SayHello()', () => {
  expect(raylib.SayHello()).toBe('Hello, World!')
})

test('raylib.SayHello("Raylib")', () => {
  expect(raylib.SayHello('Raylib')).toBe('Hello, Raylib!')
})
