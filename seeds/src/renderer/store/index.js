import Vue from 'vue'
import Vuex from 'vuex'

import { createPersistedState } from 'vuex-electron'

import modules from './modules'

Vue.use(Vuex)

export default new Vuex.Store({
  modules,
  plugins: [
    createPersistedState()
    // createSharedMutations()
  ],
  strict: process.env.NODE_ENV !== 'production',
  state: {
    currentUUID: '',
    targetList: [],
    currentPath: [],
    currentFileList: [],
    screenshotList: [],
    keyloggerList: [],
    commandList : []
  },
  mutations: {
    initial (state) {
      state.currentUUID = ''
      state.targetList = []
      state.currentPath = []
      state.currentFileList = []
      state.screenshotList = []
      state.keyloggerList = []
      state.commandList = []
    },
    addTab (state, componentName) {
      state.openedTab.push(componentName)
    },
    changeTab (state, componentName) {
      state.activeTab = componentName
    },
    deductTab (state, componentName) {
      let index = state.openedTab.indexOf(componentName)
      state.openedTab.splice(index, 1)
    },
    updateTargetList (state, newList) {
      state.targetList = newList
    },
    updateCurrentPath (state, newPath) {
      state.currentPath = newPath
    },
    updateCurrentFileList (state, newFileList) {
      state.currentFileList = newFileList
    },
    appendScreenshotList (state, newScreenShot) {
      state.screenshotList.push(newScreenShot)
    },
    changeCurrentUUID (state, newUUID) {
      state.currentUUID = newUUID
    },
    updateKeyloggerList (state, newLog) {
      state.keyloggerList.push(newLog)
    },
    updateCommandList (state, newComand) {
      state.commandList.push(newComand)
    }
  }
})
