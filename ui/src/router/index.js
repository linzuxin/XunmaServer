import Vue from 'vue'
import Router from 'vue-router'
import ZnMain from '@/components/zn_main'

Vue.use(Router)

export default new Router({
  routes: [{
    path: '/',
    name: 'ZnMain',
    component: ZnMain
  }]
})
