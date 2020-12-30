/*
 * @Auther: MercyLin
 * @Description: targetlist相关操作
 * @Date: 2020-09-10 12:24:36
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:19:45
 * @FilePath: \my-project\src\main\TargetList\index.js
 */

import { clientList } from '../Connect/server'

/**
 * @description: 断开靶机
 * @param {Target} target 靶机
 */
export function disconnectTarget (target) {
  for (let i = 0, len = clientList.length; i < len; i++) {
    if (clientList[i] === target) {
      clientList.splice(i, i + 1)
      console.log('del ' + target.socket.remoteAddress + ':' + target.socket.remotePort)
      break
    }
  }
}

/**
 * @description: 获取靶机列表
 * @return {JSON} 靶机列表
 */
export function getTargetList () {
  let targetList = []
  for (let i = 0, len = clientList.length; i < len; i++) {
    let client = clientList[i]
    targetList.push({
      uuid: client.uuid,
      ip: client.socket.remoteAddress,
      port: client.socket.remotePort,
      user: client.user,
      system: client.system
    })
  }
  return targetList
}
