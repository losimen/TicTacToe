import { createApp } from 'vue'
import App from './App.vue'

import { library } from '@fortawesome/fontawesome-svg-core'
import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome'
import { faUserSecret, faX, faO } from '@fortawesome/free-solid-svg-icons'
import Toast from "vue-toastification";
import "vue-toastification/dist/index.css";

library.add(faUserSecret, faX, faO)

createApp(App)
  .use(Toast, {})
  .component('font-awesome-icon', FontAwesomeIcon)
  .mount('#app')
