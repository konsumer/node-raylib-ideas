This is instructions for developers to update the Raylib version.

- Update the `version` in package.json that you want to target. Only [Raylib tagged releases](https://github.com/raysan5/raylib/releases) can be targeted.
- `npm run clean` to delete any built files
- `npm run gen` to re-generate the bindings.
- `npm run compile` to compile a new version
- `npm test` to test the new version

If all is working, tag for next release:

```
git commit -am "release 5.x.x"
npm version 5.x.x
git push --tags
```

Now, go to [releases](https://github.com/RobLoach/node-raylib/releases) and create a new tagged release for it. This will trigger a build, and new release `.node` files will be attached to it.
