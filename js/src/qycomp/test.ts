import { QYComponent, QYContext } from "../global/page-comp";


export default function(comp: QYComponent) {
    let index = 0;    
    comp.on("render", props => {
        const colors = ["red", "green", "black", "white"];
        if (index >= colors.length)
                index = 0;
        comp.setData("color",  colors[index++]);

    });
    comp.on("qymouse", (event: QYMouseEvent)=> {
        const colors = ["red", "green", "black", "white"];
        if (index >= colors.length)
                index = 0;
        comp.setData("color",  colors[index++]);
    });
}