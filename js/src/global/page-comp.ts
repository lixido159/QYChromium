


abstract class IComponent {
    constructor(context: QYContext) {
        this.context = context;
    }
    context: QYContext;
    isPage: boolean;
    callbacks: Map<string, any> = new Map;
    test() {
        console.log("测试方法成功");
    }

    setData(key: string, value: any) {
        this.context.data.update(key, value);
    }

    render(id: string, props:{}) {
        const element = this.context.dom.getElementById(id);
        if (!element) {
            return;
        }
        const comp = element.getComponent();
        comp.call("render", props);
    }

    on(key:string, func:any) {
        this.callbacks.set(key, func);
    }

    call(key:string, ...args: any) {
        const func = this.callbacks.get(key);
        if (func) {
            func.apply(null, args);
        }
    }

}



export interface QYContext {
    data: QYData;
    dom: QYDom;
    render(id:string, pros:any): void;
    
}

//
export interface QYData {
    update(key: string, value: any);
}

//Dom代表page和component的widget
export interface QYDom {
    getElementById(id:string): QYElement;
}

//QYElement代表每一个wideget
export interface QYElement {
    getComponent(): IComponent;
}

//页面
export class QYPage extends IComponent {
    constructor(context: QYContext) {
        super(context);
        this.isPage = true;
    }
}

//组件
export class QYComponent extends IComponent {
}

export function pageFunction(callback: (page:QYPage)=>void) {
    return function(context:QYContext) {
        const page = new QYPage(context);
        callback(page)
        return page;
    }
}


export function componentFunction(callback: (comp:QYComponent)=>void) {
    return function(context:QYContext) {
        const comp = new QYComponent(context);
        callback(comp)
        return comp;
    }
}

