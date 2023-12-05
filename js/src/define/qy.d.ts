import {QYComponent, QYContext, QYData, QYPage} from "../global/page-comp"
declare global {
    //Native实现
    interface QYNative {
        entry(context: QYContext): QYPage;
        compLoader: Object;
    }

    enum QYMouseEventType {
        unknown = 0,
        leftMouseDown,
        leftMouseUp,
        rightMouseDown,
        rightMouseUp,
        mouseMove
    } 

    interface QYMouseEvent {
        x: number;
        y: number;
        type: QYMouseEventType;
    }

    const qyNative: QYNative;

}
