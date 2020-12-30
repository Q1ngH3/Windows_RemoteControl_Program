<template>
  <div id="app">
    <el-container>
      <el-aside width="200px" style="padding: 0;height: 100%">
        <navMenu></navMenu>
      </el-aside>
    <el-container>
      <el-header>
      <navHeader></navHeader>
      </el-header>
        <el-scrollbar style="height:100%;">
        <el-main  style="padding: 0;overflow-x: hidden">
          <targetList></targetList>
          <router-view>
            <browser></browser>
          </router-view>
        </el-main>
      </el-scrollbar>
    </el-container>
    </el-container>
  </div>
</template>

<script>

import navMenu from '@/components/navMenu'
import Browser from '@/components/Browser/Browser'
import TargetList from '@/components/TargetList/TargetList'
import navHeader from '@/components/navHeader/navHeader'

export default {
  name: 'my-project',
  components: {
    navMenu,
    Browser,
    TargetList,
    navHeader
  }
}
</script>

<style>
html, body, #app, .el-container {
        margin: 0;
        padding: 0;
        /*统一设置高度为100%*/
        height: 100%;
    }
.el-header{
  background-color: #edf2f4 !important;
}
.el-table__body-wrapper::-webkit-scrollbar{
    /*width: 0;宽度为0隐藏*/
    width: 0px;
}
.el-table__body-wrapper::-webkit-scrollbar-thumb{
    border-radius: 2px;
    height: 50px;
    background: #eee;
}
.el-table__body-wrapper::-webkit-scrollbar-track{
    overflow-x: hidden;
    overflow-y: hidden;
    box-shadow: inset 0 0 5px rgba(0, 0, 0, 0.2);
    border-radius: 2px;
    background: rgba(0,0,0,0.4);
}
body .el-table th.gutter{
    display: table-cell!important;
}
</style>
