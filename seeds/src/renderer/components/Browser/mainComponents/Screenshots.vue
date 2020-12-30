<template>
  <el-container>
    <el-aside width="400px">
      <el-table
          :data="$store.state.screenshotList"
          style="width: 100%"
          height="400"
          @row-dblclick="showScreenshot"
      >
        <el-scrollbar>
          <el-table-column
              prop="name"
              label="name">
          </el-table-column>
          <el-table-column
              prop="time"
              label="ScreenshotTime">
          </el-table-column>
        </el-scrollbar>
      </el-table>
    </el-aside>
    <el-main style="margin: 0;padding: 0;">
      <el-image
          v-if="url !== ''"
          style="width: 100%;padding-top: 75px;"
          :src="url"
          :preview-src-list="srcList">
      </el-image>
    </el-main>
  </el-container>
</template>

<script>
export default {
  name: 'Screenshots',
  data () {
    return {
      url: '',
      srcList: ['']
    }
  },
  methods: {
    showScreenshot (row) {
      this.url = '/picture/' + row.name
      this.srcList[0] = '/picture/' + row.name
    }
  }
}
</script>

<style scoped>

</style>
