const edgecaseFunctions = [
  // these use text-formatting in js
  'TextFormat',
  'TraceLog',

  // need to figure out callbacks
  'AttachAudioMixedProcessor',
  'AttachAudioStreamProcessor',
  'DetachAudioMixedProcessor',
  'DetachAudioStreamProcessor',
  'SetAudioStreamCallback',
  'SetLoadFileDataCallback',
  'SetLoadFileTextCallback',
  'SetTraceLogCallback'
]

const rColor = /([0-9]+)/g

const getColor = (s) => {
  let o = []
  for (const n of s.matchAll(rColor)) {
    o.push(n[0])
  }
  return `{ r:${o[0]}, g:${o[1]}, b:${o[2]}, a:${o[3]} }`
}

export default function generateJS(version, api) {
  const out = []

  out.push(`// Raylib for nodejs ${version}

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

`)

  for (const f of api.functions) {
    if (edgecaseFunctions.includes(f.name)) {
      continue
    }
    out.push(`// ${f.description}`)
    out.push(`exports.${f.name}=native.${f.name}\n`)
  }

  for (const e of api.enums) {
    out.push(`// ${e.name}: ${e.description}`)
    for (const v of e.values) {
      out.push(`exports.${v.name}=${v.value} // ${v.description}`)
    }
    out.push('')
  }

  for (const d of api.defines) {
    if (d.type === 'MACRO') {
      continue
    }
    if (d.type === 'COLOR') {
      out.push(`exports.${d.name}=${getColor(d.value)} // ${d.description}`)
    }
  }

  out.push('')

  for (const a of api.aliases) {
    out.push(`exports.${a.name}=exports.${a.type} // ${a.description}`)
  }

  return out.join('\n')
}
