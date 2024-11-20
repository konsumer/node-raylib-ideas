// this will generate a checklist of the API for GH issue
import { readFile } from 'node:fs/promises'

// pull the version that is tied to the current version in this lib (synced to raylib version)
const { version } = JSON.parse(await readFile('package.json'))
const api = await fetch(`https://raw.githubusercontent.com/RobLoach/raylib-api/refs/tags/v${version}/raylib.json`).then((r) => r.json())

console.log(`Raylib ${version} Checklist`)

const naturalCollator = new Intl.Collator(undefined, {numeric: true, sensitivity: 'base'});
const sortByName = (a, b) => naturalCollator.compare(a.name, b.name)

console.log('### functions')
for (const f of api.functions.sort(sortByName)) {
  console.log(`- [ ] \`${f.name}(${(f.params||[]).map(p => `${p.type} ${p.name}`).join(', ')})\``)
}
