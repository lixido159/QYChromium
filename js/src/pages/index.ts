import { QYContext, QYPage, componentFunction, pageFunction } from "./global/page-comp"
import comp1 from "./qycomp/test"

function qyEntry(page: QYPage){
    const colors = ["red", "green", "black", "white"];
    let index = 0;
    page.on("qymouse", (event: QYMouseEvent)=> {
        if (index >= colors.length)
                index = 0;
        page.setData("color",  colors[index++]);
        page.render("qy", "name");
    });
};
qyNative.entry = pageFunction(qyEntry);
qyNative.compLoader =  {
    'qycomp-test': componentFunction(comp1)
};
