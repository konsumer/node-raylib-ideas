// this will generate the nan bindings

import { readFile, writeFile } from 'node:fs/promises'
import generateC from './gen_c.mjs'

// pull the version that is tied to the current version in this lib (synced to raylib version)
const { version } = JSON.parse(await readFile('package.json'))
const api = await fetch(`https://raw.githubusercontent.com/RobLoach/raylib-api/refs/tags/v${version}/raylib.json`).then((r) => r.json())

// await writeFile('src/lib.c', generateC(version, api))

const allTypes = new Set()
const argTypes = new Set()
const retTypes = new Set()

for (const f of api.functions) {
  retTypes.add(f.returnType)
  allTypes.add(f.returnType)
  for (const { type } of Object.values(f.params || {})) {
    argTypes.add(type)
    allTypes.add(type)
  }
}

// console.log(allTypes)
// console.log(argTypes)
// console.log(retTypes)

const map = {}
for (const a of allTypes) {
  if (!a.includes('void') && !a.includes('Callback')) {
    map[a] = a.replace(/^const /, '').replace(/[* ]+$/, '_pointer')
  }
}
console.log(JSON.stringify(map, null, 2))
