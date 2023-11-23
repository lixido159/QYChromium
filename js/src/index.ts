
import { QYData, QYPage } from "./global/page-comp"
function qyEntry(data: QYData){
    // const page = new QYPage(data);
    // console.log("进入入口" );
    // page.setData("color", "green");
    // page.on("qymouseup", ()=> {
    //     page.setData("color", "red");
    // });
    // return page;
    const colors = ["red", "green", "black", "white"];
    const map = new Map;
    let index = 0;
    map.set("qymouseup", ()=> {
        if (index >= colors.length)
            index = 0;
        console.log("全寅"+ colors[index])
        data.update("color",  colors[index++])});
    return {
        on : ()=>{},
        call : (key, ...args)=>{
            map.get(key)(args);
        }
};
};
qyNative.entry = qyEntry;
