<script setup>
import HelloWorld from './components/HelloWorld.vue';
import {onMounted} from "vue";
const { SerialPort } = require('serialport')
const tableify = require('tableify')


// Create a SerialPort instance using the exposed function

onMounted(() => {
  console.log("Hello from main")

  async function listSerialPorts() {
    await SerialPort.list().then((ports, err) => {
      console.log("ports", ports)
    })
  }

  // Встановлення параметрів порту
  const port = new SerialPort({
    path: '/dev/cu.wchusbserial140', // Шлях до порту
    baudRate: 9600, // Швидкість обміну даними повинна бути такою ж, як і на Arduino
  })

// Обробник події для отримання даних
  port.on('data', (data) => {
    const response = data.toString('utf-8')
    console.log('Отримана відповідь від Arduino:', response)
  })
})

</script>

<template>
  <div>
    <a href="https://vitejs.dev" target="_blank">
      <img src="/vite.svg" class="logo" alt="Vite logo" />
    </a>
    <a href="https://vuejs.org/" target="_blank">
      <img src="./assets/vue.svg" class="logo vue" alt="Vue logo" />
    </a>
  </div>
  <HelloWorld msg="Vite + Vue" />
</template>

<style scoped>
.logo {
  height: 6em;
  padding: 1.5em;
  will-change: filter;
  transition: filter 300ms;
}
.logo:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}
.logo.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}
</style>