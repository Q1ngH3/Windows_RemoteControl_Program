import Vue from 'vue'
import Router from 'vue-router'
import BasicIndex from '@/components/Browser/mainComponents/BasicIndex'
import FileBrowser from '@/components/Browser/mainComponents/FileBrowser'
import Keyboard from '@/components/Browser/mainComponents/Keyboard'
import Screenshots from '@/components/Browser/mainComponents/Screenshots'
import ShellCommand from '@/components/Browser/mainComponents/ShellCommand'

Vue.use(Router)

// 解决ElementUI导航栏中的vue-router在3.0版本以上重复点菜单报错问题
const originalPush = Router.prototype.push
Router.prototype.push = function push (location) {
  return originalPush.call(this, location).catch(err => err)
}

export default new Router({
  routes: [
    {
      path: '/index',
      name: '_index',
      component: BasicIndex
    }, {
      path: '/FileBrowser',
      name: '_FileBrowser',
      component: FileBrowser
    }, {
      path: '/Keyboard',
      name: '_Keyboard',
      component: Keyboard
    }, {
      path: '/Screenshots',
      name: '_Screenshots',
      component: Screenshots
    }, {
      path: '/ShellCommand',
      name: '_ShellCommand',
      component: ShellCommand
    }
  ]
})
