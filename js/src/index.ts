
import { QYData, QYPage } from "./global/page-comp"

function qyEntry(data: QYData){
    console.log("进入入口" + setTimeout);
    data.update("color", "red");
    // setTimeout(()=> {
    //     data.update("color", "green");
    // }, 4000);
};
qyNative.entry = qyEntry;
