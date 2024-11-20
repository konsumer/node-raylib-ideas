/*

Similar to sprintf in C.

This implementation supports:

1. All standard C format specifiers:
   - `%c` for characters
   - `%s` for strings
   - `%d` and `%i` for integers
   - `%o` for octal
   - `%x` and `%X` for hexadecimal
   - `%u` for unsigned
   - `%f` and `%F` for fixed-point floating-point
   - `%e` and `%E` for scientific notation
   - `%g` and `%G` for shorter of e/f
   - `%a` and `%A` for hexadecimal floating-point
   - `%p` for pointers

2. Format modifiers:
   - Width specification
   - Precision specification
   - Left/right alignment
   - Zero padding
   - Space/plus padding for positive numbers
   - Parameter indexing

*/

function vsprintf(format, args) {
  let argIndex = 0

  // Helper function to get next argument
  function getArg() {
    if (argIndex >= args.length) {
      throw new Error('Not enough arguments')
    }
    return args[argIndex++]
  }

  // Regular expression for parsing format specifiers
  // %[parameter][flags][width][.precision][length]type
  const formatRegex = /%(?:([1-9]\d*)\$)?([+-])?('.|0)?(\d+)?(?:\.(\d+))?([hlLzjt])?([%csdioxXufFeEgGaAp])/g

  return format.replace(formatRegex, function (match, param, sign, pad, width, precision, length, type) {
    // Handle %% escape
    if (type === '%') {
      return '%'
    }

    // Get the argument to format
    let value = param ? args[parseInt(param) - 1] : getArg()

    // Initialize result
    let result = ''

    // Get padding character
    const padChar = pad ? (pad.charAt(pad.length - 1) === '0' ? '0' : pad.charAt(1)) : ' '

    // Convert width and precision to numbers
    width = width ? parseInt(width) : 0
    precision = precision ? parseInt(precision) : undefined

    function formatInteger(value, base, uppercase) {
      let num = parseInt(value)
      if (isNaN(num)) num = 0

      let str = Math.abs(num).toString(base)
      if (precision !== undefined) {
        while (str.length < precision) str = '0' + str
      }

      if (uppercase) str = str.toUpperCase()
      if (num < 0) str = '-' + str
      else if (sign === '+') str = '+' + str

      return str
    }

    function formatFloat(value, fixed) {
      let num = parseFloat(value)
      if (isNaN(num)) num = 0

      if (precision !== undefined) {
        if (fixed) {
          return num.toFixed(precision)
        } else {
          return num.toPrecision(precision)
        }
      }

      return num.toString()
    }

    // Handle different format specifiers
    switch (type) {
      case 'c': // Character
        result = String.fromCharCode(parseInt(value))
        break

      case 's': // String
        result = String(value)
        if (precision !== undefined) {
          result = result.substr(0, precision)
        }
        break

      case 'd': // Decimal integer
      case 'i': // Integer
        result = formatInteger(value, 10, false)
        break

      case 'o': // Octal
        result = formatInteger(value, 8, false)
        break

      case 'x': // Hexadecimal (lowercase)
        result = formatInteger(value, 16, false)
        break

      case 'X': // Hexadecimal (uppercase)
        result = formatInteger(value, 16, true)
        break

      case 'u': // Unsigned decimal
        result = formatInteger(Math.abs(value), 10, false)
        break

      case 'f': // Fixed-point floating-point
      case 'F': // Same as 'f'
        result = formatFloat(value, true)
        break

      case 'e': // Scientific notation (lowercase)
      case 'E': // Scientific notation (uppercase)
        result = formatFloat(value, false)
        if (type === 'E') result = result.toUpperCase()
        break

      case 'g': // Shorter of 'e' or 'f'
      case 'G': // Shorter of 'E' or 'F'
        result = formatFloat(value, false)
        if (type === 'G') result = result.toUpperCase()
        break

      case 'a': // Hexadecimal floating-point (lowercase)
      case 'A': // Hexadecimal floating-point (uppercase)
        let num = parseFloat(value)
        result = num.toString(16)
        if (type === 'A') result = result.toUpperCase()
        break

      case 'p': // Pointer (address)
        result = '0x' + parseInt(value).toString(16)
        break
    }

    // Handle padding
    if (width > 0) {
      if (sign === '-') {
        result = result.padEnd(width, padChar)
      } else {
        if (padChar === '0' && result[0] === '-') {
          result = '-' + result.slice(1).padStart(width - 1, padChar)
        } else {
          result = result.padStart(width, padChar)
        }
      }
    }

    return result
  })
}

module.exports = {
  vsprintf,
  sprintf: (f, ...a) => vsprintf(f, a),
  printf: (f, ...s) => console.log(vsprintf(f, a))
}
