const path = require("path")
module.exports = {
  entry: "./src/index.ts", // 打包的文件入口
  output: { 
    path: path.resolve(__dirname, './build'), // 打包后输出的文件目录
    filename: 'bundle.js' // 打包后输出的文件名称
  },
  module: {
    // 指定要加载的规则
    rules: [
        // 用ts-loader 处理以ts结尾的文件
        {
            // test 指定的是规则生效的文件
            test: /\.ts$/,    // 表示去【匹配所有以ts结尾的文件
            // t要使用的loader
            use: 'ts-loader',
            // 要排除的文件
            exclude: /node-modules/
        }
    ]
  },
  resolve: {
    extensions: ['.tsx', '.ts', '.js'],
  },
}
