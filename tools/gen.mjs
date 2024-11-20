// this will generate the nan bindings

import { readFile, writeFile } from 'node:fs/promises'
import generateC from './gen_c.mjs'
import generateJS from './gen_js.mjs'

// pull the version that is tied to the current version in this lib (synced to raylib version)
const { version } = JSON.parse(await readFile('package.json'))
const api = await fetch(`https://raw.githubusercontent.com/RobLoach/raylib-api/refs/tags/v${version}/raylib.json`).then((r) => r.json())

await writeFile('src/lib.c', generateC(version, api))
await writeFile('index.js', generateJS(version, api))
