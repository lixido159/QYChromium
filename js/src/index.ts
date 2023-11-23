
import { QYData, QYPage } from "./global/page-comp"

function qyEntry(data: QYData){
    const page = new QYPage(data);
    console.log("进入入口" );
    page.setData("color", "green");
    page.on("qymouseup", ()=> {

    });
    return page;
};
qyNative.entry = qyEntry;
