/*
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-06 23:37:02
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-11 01:07:20
 * @FilePath: \seeds\src\main\Connect\request\file.js
 */
import { sendRequest } from '../index'

export default{
  getFilePreview: path => sendRequest('getFilePreview', { rootPath: path }),
  transFile: (path, name) => sendRequest('transFile', { filepath: path + name })
}
