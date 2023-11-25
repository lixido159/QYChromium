import { QYData, QYPage } from "./global/page-comp"

function qyEntry(data: QYData){
    const page = new QYPage(data);
    const colors = ["red", "green", "black", "white"];
    let index = 0;
    page.on("qymouse", (event: QYMouseEvent)=> {
        console.log(`测试 ${event.x}  ${event.y}   ${event.type}`);
        if (index >= colors.length)
                index = 0;
        page.setData("color",  colors[index++]);
    });
    return page;
};

qyNative.entry = qyEntry;
