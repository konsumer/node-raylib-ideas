I am working on improvments around [node-raylib](https://github.com/RobLoach/node-raylib), here.

## Primary Goals

- use plain node_api, in C (which may help with this working in deno & bun)
- complete code-gen, less edgecases, no manual code
- faster/simpler build

## TODO

- Even though I don't really like typescript, I should use it to build the interface for otheres, and for things like enums.
- figure out better standalone compile maybe [sea](https://nodejs.org/api/single-executable-applications.html) or [nexe-natives](https://github.com/nmarus/nexe-natives).
- detect DRM/X on import, on pi (for simpler import) checking `DISPLAY` might be a simple way (detect "no X")
- DRM is available on things than pi. I should test more.
- Integrate prebuild libs & node-raylib bin into release for all platforms
- universal binaries for mac (arm64/x86-64)
- cross build (via [toolchain](https://medium.com/@au42/the-useful-raspberrypi-cross-compile-guide-ea56054de187)) for pi, including DRM.
- currently, objects are used for structs, but I should probly use "magic classes" and pointers to cut down on copying
- [wasm](https://github.com/devongovett/napi-wasm?tab=readme-ov-file) would be a neat way to add browser-support (for single codebase for both)
