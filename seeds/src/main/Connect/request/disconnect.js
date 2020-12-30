/*
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-07 17:13:34
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:11:26
 * @FilePath: \my-project\src\main\Connect\request\disconnect.js
 */

import { sendRequest } from '../index'

export default{
  disconnect: () => sendRequest('disconnect')
}
