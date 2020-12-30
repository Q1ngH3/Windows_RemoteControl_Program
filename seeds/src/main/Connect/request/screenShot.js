/*
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-07 17:25:30
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:11:48
 * @FilePath: \my-project\src\main\Connect\request\screenShot.js
 */

import { sendRequest } from '../index'

export default{
  screenShot: () => sendRequest('screenShot')
}
