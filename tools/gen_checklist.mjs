// this will generate a checklist of the API for GH issue

import { readFile } from 'node:fs/promises'
import * as implemented from '../index.js'
import { glob } from 'glob'

// pull the version that is tied to the current version in this lib (synced to raylib version)
const { version } = JSON.parse(await readFile('package.json'))
const api = await fetch(`https://raw.githubusercontent.com/RobLoach/raylib-api/refs/tags/v${version}/raylib.json`).then((r) => r.json())

const existing = Object.keys(implemented)

const naturalCollator = new Intl.Collator(undefined, { numeric: true, sensitivity: 'base' })
const sortByName = (a, b) => naturalCollator.compare(a.name, b.name)
const functions = api.functions.sort(sortByName)

const tested = ['FileExists'] // this is in bin/node-raylib

for (const fn of await glob('examples/**/*.js')) {
  const s = await readFile(fn, 'utf8')
  for (const f of functions) {
    if (s.includes(`${f.name}(`)) {
      tested.push(f.name)
    }
  }
}

console.log(`This is a list of the remaining API functions for Raylib ${version}.\n`)

function outPutFunction(f) {
  return `- [${existing.includes(f.name) ? 'X' : ' '}] \`${f.name}(${(f.params || []).map((p) => `${p.type} ${p.name}`).join(', ')})\``
}

console.log('### complete\n')
console.log('These are tested with demo-code.\n')
for (const f of functions) {
  if (tested.includes(f.name)) {
    console.log(outPutFunction(f))
  }
}

console.log('\n### untested\n')
console.log('These are untested, but those with check-marks are exported.\n')
for (const f of functions) {
  if (!tested.includes(f.name)) {
    console.log(outPutFunction(f))
  }
}
