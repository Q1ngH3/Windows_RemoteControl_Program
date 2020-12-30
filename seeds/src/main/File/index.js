/*
 * @Auther: MercyLin
 * @Description: 文件相关操作
 * @Date: 2020-09-10 12:24:36
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:13:31
 * @FilePath: \my-project\src\main\File\index.js
 */

export function fileNotFound () {
  console.log('file dose not exist')
}

export function updateFilepreview (content) {
  console.log('updateFilepreview: ' + content)
}

/**
 * @description: 保存文件到download目录
 * @param {Buffer} file 文件内容
 * @param {String} fileName 文件名
 * @return {String}
 */
export function saveFile (file, fileName) {
  var path = require('path')
  var fs = require('fs')
  var url = path.resolve('./') + '\\download\\'
  console.log('2333' + url)

  if (!fs.existsSync(url)) {
    fs.mkdirSync(url)
  }

  fs.writeFileSync(url + fileName, Buffer.from(file.toString(), 'base64'), function (error) {
    if (error) {
      console.log('啊这')
    } else {
      console.log('写入成功')
    }
  })
  return url + fileName
}
