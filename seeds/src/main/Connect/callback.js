/*
 * @Auther: MercyLin
 * @Description: Request callback pool
 * @Date: 2020-09-09 14:30:21
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-10 22:10:52
 * @FilePath: \my-project\src\main\Connect\callback.js
 */
/**
 * Request callback pool
 */
import config from '../config'

const callbacks = new Map() // Callback sequence number to function mappings
let packetID = 0 //

/**
 * Register callback
 * @param {Function} callback
 * @returns {number} packetID
 */

function register (callback) {
  packetID = (packetID + 1) % config.connection.MAX_SEQUENCE_NUMBER
  while (callbacks.has(packetID)) {
    packetID = (packetID + 1) % config.connection.MAX_SEQUENCE_NUMBER
  }
  callbacks.set(packetID, callback)
  return packetID
}

/**
 * Get callback by packetID
 * @param {number} packetID
 * @returns {Function} callback
 */
function get (packetID) {
  return callbacks.get(packetID)
}

/**
 * Delete callback by packetID
 * @param {number} packetID
 */
function del (packetID) {
  callbacks.delete(packetID)
}

export default {
  register,
  get,
  del
}
