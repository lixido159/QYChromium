const path = require("path")
module.exports = {
  entry: "./src/index.js", // 打包的文件入口
  output: { 
    path: path.resolve(__dirname, './build'), // 打包后输出的文件目录
    filename: 'bundle.js' // 打包后输出的文件名称
  }
}
