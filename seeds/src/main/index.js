/*
 * @Auther: MercyLin
 * @Description: description
 * @Date: 2020-09-09 00:11:40
 * @LastEditors: MercyLin
 * @LastEditTime: 2020-09-11 01:07:55
 * @FilePath: \seeds\src\main\index.js
 */

'use strict'

import { app, BrowserWindow, ipcMain } from 'electron'

import { registerIpc } from './ipc'

/**
 * Set `__static` path to static files in production
 * https://simulatedgreg.gitbooks.io/electron-vue/content/en/using-static-assets.html
 */
if (process.env.NODE_ENV !== 'development') {
  global.__static = require('path').join(__dirname, '/static').replace(/\\/g, '\\\\')
}

let mainWindow
const winURL = process.env.NODE_ENV === 'development'
  ? `http://localhost:9080`
  : `file://${__dirname}/index.html`

function createWindow () {
  /**
   * Initial window options
   */
  mainWindow = new BrowserWindow({
    height: 800,
    useContentSize: true,
    width: 1200,
    frame: false,
    webPreferences: {
      defaultFontFamily: {
        standard: 'Microsoft YaHei'
      }
    }
  })

  mainWindow.setMenu(null)
  mainWindow.loadURL(winURL)
  if (process.env.NODE_ENV === 'development') {
    // 想在开发环境中做的操作
    mainWindow.webContents.openDevTools()
  }

  mainWindow.on('closed', () => {
    mainWindow = null
  })
}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow()
  }
})

registerIpc()

ipcMain.on('min', e => mainWindow.minimize())
ipcMain.on('max', e => {
  if (mainWindow.isMaximized()) {
    mainWindow.unmaximize()
  } else {
    mainWindow.maximize()
  }
})
ipcMain.on('close', e => mainWindow.close())
/**
 * Auto Updater
 *
 * Uncomment the following code below and install `electron-updater` to
 * support auto updating. Code Signing with a valid certificate is required.
 * https://simulatedgreg.gitbooks.io/electron-vue/content/en/using-electron-builder.html#auto-updating
 */

/*
import { autoUpdater } from 'electron-updater'

autoUpdater.on('update-downloaded', () => {
  autoUpdater.quitAndInstall()
})

app.on('ready', () => {
  if (process.env.NODE_ENV === 'production') autoUpdater.checkForUpdates()
})
 */
