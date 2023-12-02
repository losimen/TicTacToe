import { createApp } from 'vue'
import "./style.css"
import App from './App.vue'
import './samples/node-api'

// import { library } from '@fortawesome/fontawesome-svg-core'
// import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome'
// import {faUserSecret, faX, faO, faUser, faComputer} from '@fortawesome/free-solid-svg-icons'
import Toast from "vue-toastification";
import "vue-toastification/dist/index.css";

createApp(App)
  .use(Toast, {})
  .mount('#app')
  .$nextTick(() => {
    postMessage({ payload: 'removeLoading' }, '*')
  })
