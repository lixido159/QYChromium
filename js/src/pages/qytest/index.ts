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
    page.setData("number",  1);
    page.on("qymouse", (event: QYMouseEvent)=> {
        if (index >= colors.length)
                index = 0;
        height += 10;
        
        show = !show;
        page.setData("show",  show);
    });


};

qyNative.entry = pageFunction(qyEntry);
qyNative.compLoader =  {
    'qycomp-test': componentFunction(comp1)
};
