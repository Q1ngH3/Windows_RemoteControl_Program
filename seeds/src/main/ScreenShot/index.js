/*
 * @Auther: MercyLin
 * @Description: 截屏相关操作
 * @Date: 2020-09-08 22:45:56
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:15:29
 * @FilePath: \my-project\src\main\ScreenShot\index.js
 */

export function updateScreenShot (content) {
  console.log('new Screenshot:' + content)
}

/**
 * @description: 保存截图到picture目录
 * @param {Buffer} file 文件内容
 * @return {String}
 */
export function saveScreenShot (file) {
  var path = require('path')
  var fs = require('fs')
  var url = path.resolve('./') + '\\picture\\'
  console.log('2333' + url)

  if (!fs.existsSync(url)) {
    fs.mkdirSync(url)
  }

  var myDate = new Date()

  let fileName = `scrennshot_${myDate.getTime()}.jpg`
  fs.writeFileSync(url + fileName, Buffer.from(file.toString(), 'base64'), function (error) {
    if (error) {
      console.log('啊这')
    } else {
      console.log('写入成功')
    }
  })

  return url + fileName
}
