I am working on improvments around [node-raylib](https://github.com/RobLoach/node-raylib), here.

- use plain node_api, in C (which may help with this working in deno & bun)
- complete code-gen, less edgecases, no manual code
- faster/simpler build

## TODO

- Even though I don't really like typescript, I should use it to build the interface for otheres, and for things like enums.
- figure out better standalone compile [maybe sea](https://nodejs.org/api/single-executable-applications.html).
- detect DRM/X on import, on pi (for simpler import)
- Integrate prebuild libs & node-raylib bin into release for all platforms
- universal binaries for mac (arm64/x86-64)
- cross build (via [toolchain](https://medium.com/@au42/the-useful-raspberrypi-cross-compile-guide-ea56054de187)) for pi, including DRM.
