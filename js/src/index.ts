
import { QYData, QYPage } from "./global/page-comp"

function qyEntry(data: QYData){
    console.log("进入入口" + data);
    data.update("color", "red");
};
qyNative.entry = qyEntry;
