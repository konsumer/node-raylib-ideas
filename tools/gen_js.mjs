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

// get the byte-size of a type
function getSize(api, type) {
  const mappedStructs = api.structs.reduce((a, c) => ({ ...a, [c.name]: c }), {})

  // pointers are 32bit
  if (type.includes('*')) {
    return 4
  }

  // arrays are size * typeSize
  if (type.includes('[')) {
    const t = type.split('[')
    return getSize(api, t[0]) * t[1].split(']')[0]
  }

  // structs are size of all fields addded
  if (mappedStructs[type]) {
    return mappedStructs[type].fields.reduce((a, c) => a + getSize(api, c.type), 0)
  }

  // the rest (atoms) have a size
  switch (type) {
    case 'bool':
    case 'char':
    case 'unsigned char':
      return 1
    case 'int':
    case 'unsigned int':
    case 'float':
      return 4
    default:
      console.log(`SIZE? ${type}`)
      return 0
  }
}

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
    if (d.type === 'GUARD') {
      continue
    }
    if (d.type === 'MACRO') {
      continue
    } else if (d.type === 'COLOR') {
      out.push(`exports.${d.name}=${getColor(d.value)} // ${d.description}`)
    } else if (d.type === 'STRING') {
      out.push(`exports.${d.name}='${d.value}'`)
    } else if (d.type === 'INT' || d.type === 'FLOAT') {
      out.push(`exports.${d.name}=${d.value}`)
    }
  }

  out.push('exports.DEG2RAD=exports.PI/180')
  out.push('exports.RAD2DEG=180/exports.PI')

  out.push('')

  let code = ''
  for (const s of api.structs) {
    s.fields = s.fields || []
    const size = s.fields.reduce((a, c) => a + getSize(api, c.type), 0)
    code += `  // ${s.description}
    exports.${s.name} = class ${s.name} {
      constructor(init = {}, _address) {
        this._size = ${size}
        this._address = _address || native.malloc(this._size)
  `

    let offset = 0
    for (const f of s.fields) {
      const t = mappedStructs[f.type.replace(' ', '').replace('*', '')]
      if (!t) {
        code += `\n      this.${f.name} = init.${f.name} || ${defaultValue(f.type)}`
      } else {
        code += `\n      this.${f.name} = new exports.${t.name}(init.${f.name} || {}, this._address + ${offset})`
      }
      offset += getSize(f.type)
    }

    code += `
      }
      ${outputGetters(s)}
    }\n\n`
  }

  out.push(code)

  for (const a of api.aliases) {
    out.push(`exports.${a.name}=exports.${a.type} // ${a.description}`)
  }

  return out.join('\n')
}
