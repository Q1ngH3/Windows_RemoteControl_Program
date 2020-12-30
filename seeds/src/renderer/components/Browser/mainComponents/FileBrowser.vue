<template>
  <el-container>
    <el-main id="fileList">
      <el-row>
        <el-col :span="14">
          <el-breadcrumb separator="\" style="padding-left: 10px;padding-top: 7px">
            <el-breadcrumb-item v-for="p in $store.state.currentPath">{{ p }}</el-breadcrumb-item>
          </el-breadcrumb>
        </el-col>
        <el-col :span="10">
          <span style="font-size: 12px;text-align: right;color: #717377">当前靶机uuid:&nbsp;&nbsp;{{$store.state.currentUUID}}</span>
        </el-col>
      </el-row>
      <el-table
          :default-sort="{prop:'attrib',order:'descending'}"
          :data="$store.state.currentFileList"
          style="width: 100%;user-select: none"
          height="367"
          :row-class-name="tableRowClassName"
          @row-dblclick="doubleClick"
          @row-contextmenu="rightClick"
      >
        <el-table-column
            :sortable='true'
            prop="name"
            label="文件名称"
            min-width="70%">
          <template slot-scope="scope">
            <i v-if="scope.row.attrib=='folder'" class="el-icon-folder"></i>
            <i v-if="scope.row.attrib=='file'" class="el-icon-document"></i>
            <span>{{ scope.row.Name }}</span>
          </template>
        </el-table-column>
        <el-table-column
            :sortable='true'
            prop="attrib"
            label="文件类型"
            min-width="30%">
        </el-table-column>
      </el-table>
      <div id="fileBrowserMenu">
        <div class="menu" v-for="(item,index) in menus" :key="index" @click.stop="infoClick(index)">{{ item }}</div>
      </div>
    </el-main>
  </el-container>
</template>
<script>
import {ipcRenderer} from 'electron'

export default {
  name: 'FileBrowser',
  data () {
    return {
      menus: ['文件下载'],
      currentFileName: ''
    }
  },
  methods: {
    /**
     * @description: 求取文件预览目录
     * @param {string} rootPath 请求浏览的目录默认为C:\\
     * @return {undefined} filePreview 文件预览目录
     */
    requestFilePreview (rootPath = 'C:\\') {
      ipcRenderer.once('filepreview', (event, filePreview) => {
        let tmp = JSON.parse(filePreview)
        let filePath = tmp['position'].split('\\')
        console.log(filePath)
        this.$store.commit('updateCurrentPath', filePath)
        let fileList = tmp['fileInfo']
        let index = fileList.findIndex(obj => obj.Name === '.')
        if (index >= 0) {
          fileList.splice(index, index)
        }
        this.$store.commit('updateCurrentFileList', fileList)
      })
      ipcRenderer.send('requestFilePreview', rootPath)
    },
    /**
     * @description: 获取文件
     * @return {string} url 文件保存路径
     */
    getFile (p, f) {
      ipcRenderer.once('transfile', (event, url) => {
        this.$alert('文件保存在：' + url, {
          confirmButtonText: '确定',
          callback: action => {
            let fileBrowerMenu = document.querySelector('#fileBrowserMenu')
            fileBrowerMenu.style.display = 'none'
          }
        })
      })
      ipcRenderer.send('requestFile', { path: p, fileName: f })
    },
    tableRowClassName ({row, rowIndex}) {
      row.index = rowIndex
    },
    doubleClick (row, column, cell, event) {
      if (row.attrib === 'folder') {
        let path
        if (row.Name === '..') {
          let tmp = this.$store.state.currentPath.slice(0, this.$store.state.currentPath.length - 2).concat([''])
          console.log(tmp)
          console.log(this.$store.state.currentPath)
          path = tmp.join('\\')
        } else {
          path = this.$store.state.currentPath.join('\\') + row.Name + '\\'
        }
        console.log(path)
        this.requestFilePreview(path)
      }
      console.log(row.Name, column)
    },
    rightClick (row, column, event) {
      var fileBrowserMenu = document.querySelector('#fileBrowserMenu')
      fileBrowserMenu.style.left = (event.clientX - 200) + 'px'
      fileBrowserMenu.style.top = (event.clientY - 60) + 'px'
      if (row.attrib === 'file') {
        fileBrowserMenu.style.display = 'block'
      }
      console.log(row, column)
      this.currentFileName = row.Name
    },
    infoClick (index) {
      let path = this.$store.state.currentPath.join('\\')
      if (this.menus[index] === '文件下载') {
        this.getFile(path, this.currentFileName)
      }
    }
  }
}
</script>

<style scoped>
#fileList {
  margin: 0;
  padding: 10px;
}

#fileBrowserMenu {
  font-size: 12px;
  width: 100px;
  height: 25px;
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
