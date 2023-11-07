
import { QYData, QYPage } from "./global/page-comp"

function qyEntry(data: QYData){
    console.log("进入入口" + data);
    data.update("name", "yinquan");
};
qyNative.entry = qyEntry;
