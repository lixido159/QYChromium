import { QYContext, QYPage, componentFunction, pageFunction } from "../../global/page-comp"
import comp1 from "./qycomp/test"

function qyEntry(page: QYPage){

    const colors = ["red", "green", "black", "white"];
    let index = 0;
    let height = 80;

    page.setData("height",  height);
    page.render("qy", "name");
    let show = true;
    page.setData("show",  show);
    let number = 1;
    page.setData("number",  number);
    page.on("qymouse", (event: QYMouseEvent)=> {
        if (index >= colors.length)
                index = 0;
        height += 10;
        number++;
        page.setData("number",  number);
    });


};

qyNative.entry = pageFunction(qyEntry);
qyNative.compLoader =  {
    'qycomp-test': componentFunction(comp1)
};
