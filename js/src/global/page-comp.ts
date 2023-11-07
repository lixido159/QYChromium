
abstract class IComponent {
    constructor() {
    }
    isPage: boolean;
    test() {
        console.log("测试方法成功");
    }
    abstract setData(key: string, value: any);
}

export class QYData {
    update(key: string, value: any) {

    }
}

//页面
export class QYPage extends IComponent {
    constructor() {
        super();
        this.isPage = true;
    }
    setData(key: string, value: any) {

    }
}

//组件
export class QYComponent extends IComponent {
    constructor() {
        super();
    }
    setData(key: string, value: any) {

    }
}
