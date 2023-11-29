<template>
  <header>
    <h1>TIC-TAC-TOE</h1>
  </header>

  <LoadingSpinner v-if="isLoading"/>
  <div v-else>
    <TurnIndicator v-show="!isEnded" :turnNum="turn"/>
    <WinIndicator v-show="isEnded" :turnNum="turn" :isTie="isTie"/>

    <div class="cont-slot">
      <MarkSlot v-for="slotID in 9" :key="slotID - 1" @click="onMarkSlotClick(slotID - 1)" :turnNum="board[slotID - 1]"/>
    </div>

    <button id="btn-reset" @click="onResetBoard">Reset</button>
  </div>
<!--  <button id="btn-reset" @click="showToast">Check</button>-->
</template>


<script>
import MarkSlot from "./components/MarkSlot.vue";
import TurnIndicator from "./components/TurnIndicator.vue";
import WinIndicator from "./components/WinIndicator.vue";
const { SerialPort } = require('serialport')
import ArduinoIO from './services/io/ArduinoIO'

import { useToast } from "vue-toastification";
import LoadingSpinner from "./components/LoadingSpinner.vue";

function onResetBoard() {
  arduinoIO.onSendData('reset-board')
}

// function onCheck() {
//   arduinoIO.onSendData('check-baby')
// }

function onMarkSlotClick(id) {
  arduinoIO.onSendData('mark-slot', {id: id})
}

let port = new SerialPort({
  path: '/dev/tty.usbserial-1140',
  baudRate: 38400,
})

const arduinoIO = new ArduinoIO()

export default {
  name: "App",
  components: {
    LoadingSpinner,
    MarkSlot,
    TurnIndicator,
    WinIndicator
  },
  methods: {
    onResetBoard,
    onMarkSlotClick,
    // onCheck,
    showError(message) {
      this.toast.error(message)
    }
  },
  setup() {
    const toast = useToast();

    return { toast }
  },
  data() {
    return {
      turn: 0,
      board: [-1, -1, -1, -1, -1, -1, -1, -1, -1],
      isEnded: false,
      isTie: false,
      isLoading: true,
    }
  },
  mounted() {
    port.on('data', (data) => {
      arduinoIO.processData(data)
    })

    setTimeout(() => {
      this.isLoading = false
    }, 2000)


    arduinoIO.setApp(this)
    arduinoIO.setPort(port)
  }
}
</script>


<style>
@font-face {
  font-family: "Iosevka Aile Lite";
  /*noinspection CssInvalidPropertyValue*/
  src: "./assets/font/iosevka-aile-lite-regular.ttf"
}

* {
  --clr-fg: #fecea8;
  --clr-bg: #2a363b;
  --clr-acc: #99b898;
  --clr-acc-x: #4e92b5;
  --clr-acc-o: #b54e4e;
  --clr-faded: #5d6468;
  font-family: "Iosevka Aile Lite", sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}

body {
  background: var(--clr-bg);
}

h1 {
  color: var(--clr-bg);
  background-color: var(--clr-acc);
  padding: 0 1em;
  margin-top: 0;
  margin-bottom: 0.5em;
}

button {
  font-size: 1rem;
  color: var(--clr-bg);
  background-color: var(--clr-acc);
  cursor: pointer;
  width: fit-content;
  padding: 0.5em;
  border: 0;
  border-radius: 0.2em;
  margin: 0.2em;
}

#app {
  color: var(--clr-fg);
  display: flex;
  flex-direction: column;
  align-items: center;
  width: fit-content;
  border-radius: 0.2em;
  margin: 60px auto 0;
  box-shadow: 0 0 30px rgba(0, 0, 0, 0.2);
}

.cont-slot {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  grid-template-rows: repeat(3, 1fr);
  width: fit-content;
  margin-bottom: 0.5em;
}

#btn-reset {
  font-weight: 700;
  padding: 0.5em 3em;
  margin-bottom: 1em;
}
</style>


