
abstract class IComponent {
    constructor(data: QYData) {
        this.data = data;
    }
    data: QYData;
    isPage: boolean;
    callbacks: Map<string, any> = new Map;
    test() {
        console.log("测试方法成功");
    }
    setData(key: string, value: any) {
        this.data.update(key, value);
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

export interface QYData {
    update(key: string, value: any);

}

//页面
export class QYPage extends IComponent {
    constructor(data: QYData) {
        super(data);
        this.isPage = true;
    }
}

//组件
export class QYComponent extends IComponent {
}
