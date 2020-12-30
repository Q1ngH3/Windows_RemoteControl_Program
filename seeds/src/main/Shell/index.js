/*
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-08 13:03:24
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:17:45
 * @FilePath: \my-project\src\main\Shell\index.js
 */

/**
 * @description: 连接shell
 * @param {Target} target 靶机
 * @param {boolean} status 状态码
 * @return {type}
 */
export function shellConnect (target, status) {
  target.isShellConnected = status
  console.log('shell ' + (status ? 'connected' : 'disconnected'))
}

export function updateShellResponse (response) {
  console.log('get responese: ' + response)
}
