
import { QYPage } from "./global/page-comp"

function qyEntry(){
    console.log("进入入口")
    const page = new QYPage();
    return page;
};
qyNative.entry = qyEntry;
