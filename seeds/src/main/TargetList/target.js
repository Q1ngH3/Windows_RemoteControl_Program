/*
 * @Auther: MercyLin
 * @Description: Target对象
 * @Date: 2020-09-10 12:24:36
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:21:22
 * @FilePath: \my-project\src\main\TargetList\target.js
 */

export default class Target {
  uuid
  isShellConnected = false
  socket
  user = 'guest'
  system = 'windows 2077'
  filepreviewQueue = []
  screenShotQueue = []
  fileQueue = []
  commandQueue = []
  constructor (socket) {
    this.uuid = guid()
    this.socket = socket
  }
}

/**
 * @description: 生成uuid
 */

function guid () {
  function S4 () {
    return (((1 + Math.random()) * 0x10000) | 0).toString(16).substring(1)
  }

  return (S4() + S4() + '-' + S4() + '-' + S4() + '-' + S4() + '-' + S4() + S4() + S4())
}
