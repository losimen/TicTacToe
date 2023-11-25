import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
const path = require('path')

// https://vitejs.dev/config/

export default defineConfig({
  base: path.resolve(__dirname, './dist'),
  plugins: [vue({
    template: {
      compilerOptions: {
        isCustomElement: (tag) => ['md-linedivider'].includes(tag),
      }
    }
  })],
  pluginOptions: {
    electronBuilder: {
      externals: ["serialport"],
    },
  },
})
