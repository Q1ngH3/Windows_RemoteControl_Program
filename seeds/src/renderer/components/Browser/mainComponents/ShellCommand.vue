<!--
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-11 11:27:19
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-11 18:29:02
 * @FilePath: \seeds\src\renderer\components\Browser\mainComponents\ShellCommand.vue
-->
<template>
  <div :model = '$store.state.commandList'>
    <el-input
      v-model="commandLines"
      placeholder="请输入命令"
      style="width:94%">
    </el-input>
    <el-button
      icon="el-icon-check"
      circle
      @click="sendCommand">
    </el-button>
    <div id="text">
    <ul>
      <template v-for="item in $store.state.commandList">
        <li style="color: cornflowerblue">{{item.cmd}}</li>
        <li style="color: white">{{item.res}}</li>
        <li style="color: #8d98a2">=======</li>
      </template>
    </ul>
  </div>
  </div>
</template>

<script>
import { ipcRenderer } from 'electron'
export default {
  name: 'ShellCommand',
  data () {
    return {
      commandLines: ''
    }
  },
  methods: {
    /**
     * @description: 请求shell
     * @return {boolean} status shell连接状态
     */
    requestShell () {
      ipcRenderer.once('getShell', (event, status) => {
        alert('Vue:' + status)
      })
      ipcRenderer.send('requestShell', 'start')
    },
    /**
     * @description: 请求断开shell
     * @return {boolean} status shell连接状态
     */
    stopShell () {
      ipcRenderer.once('stopShell', (event, status) => {
        alert('Vue:' + status)
      })
      ipcRenderer.send('requestShell', 'stop')
    },
    /**
     * @description: 发送shell指令
     * @param {string} commandLines 命令行
     * @return {string} shell指令回复
     */
    sendCommand () {
      ipcRenderer.once('commandSended', (event, res) => {
        let set = {
          cmd : this.commandLines,
          res : res
        }
        this.$store.commit('updateCommandList',set)
        this.commandLines = ''
      })
      ipcRenderer.send('sendCommand', this.commandLines)
    }
  }
}
</script>

<style>
.el-button--goon.is-active,
.el-button--goon:active {
  background: #2b2d42;
  border-color: #2b2d42;
  color: #fff;
}

.el-button--goon:focus,
.el-button--goon:hover {
  background: #2b2d42;
  border-color: #2b2d42;
  color: #fff;
}

.el-button--goon {
  color: #fff;
  background-color: #2b2d42;
  border-color: #2b2d42;
}
ul {
  margin: 0;
  padding: 0;
  list-style: none;
}

#text {
  font-size: 14px;
  margin: 0px;
  padding: 3px;
  background-color: #000;
  height: 400px;
  overflow-y: auto;
}
</style>
