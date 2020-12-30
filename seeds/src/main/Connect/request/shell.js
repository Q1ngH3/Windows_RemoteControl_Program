/*
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-07 17:26:31
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:11:55
 * @FilePath: \my-project\src\main\Connect\request\shell.js
 */

import { sendRequest } from '../index'

export default{
  startShell: () => sendRequest('shell', { method: 'start' }),
  stopShell: () => sendRequest('shell', { method: 'stop' }),
  sendCommand: (cmdlines) => sendRequest('sendCommand', { cmd: cmdlines })
}
