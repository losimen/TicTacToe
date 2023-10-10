const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  configureWebpack: {
    resolve: {
      fallback: {
        "os": require.resolve("os-browserify/browser"),
        "path": require.resolve("path-browserify"),
        "fs": require.resolve("browserify-fs"),
        "stream": require.resolve("stream-browserify"),
        "util": require.resolve("util/"),
        "child_process": require.resolve("child_process")
      }
    }
  }
})
