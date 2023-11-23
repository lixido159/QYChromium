import { QYData, QYPage } from "./global/page-comp"

function qyEntry(data: QYData){
    const page = new QYPage(data);
    const colors = ["red", "green", "black", "white"];
    let index = 0;
    page.on("qymouseup", ()=> {
        if (index >= colors.length)
                index = 0;
        page.setData("color",  colors[index++]);
    });
    return page;
};

qyNative.entry = qyEntry;
