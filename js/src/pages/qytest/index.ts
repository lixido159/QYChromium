import { QYContext, QYPage, componentFunction, pageFunction } from "../../global/page-comp"
import comp1 from "./qycomp/test"

function qyEntry(page: QYPage){
    const colors = ["red", "green", "black", "white"];
    let index = 0;
    let height = 80;
    page.setData("height",  height);
    page.render("qy", "name");
    let number = 1;
    page.on("qymouse", (event: QYMouseEvent)=> {
        if (index >= colors.length)
                index = 0;
        height += 10;
        // page.setData("height",  height); 
        page.setData("first",  (++number) % 3 == 0);
        page.setData("second",  number % 3 == 1);

    });
};
qyNative.entry = pageFunction(qyEntry);
qyNative.compLoader =  {
    'qycomp-test': componentFunction(comp1)
};
