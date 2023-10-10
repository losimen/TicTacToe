<template>
  <h1>Hello from main</h1>
  <button @click="onClick">Count is: {{ count }}</button>
</template>


<script setup lang="ts">
import {ref} from "vue";
import {sayHi} from "../../utils/serialCommunication";

let count = ref(0);

function onClick() {
  sayHi();
  count.value += 1;
}

</script>

