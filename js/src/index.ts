import {shout, repeat} from "./lib"
qy.entry= () =>{
    console.log("入口执行");
    shout("咆哮");
};
console.log(`入口 ${shout("咆哮")}`);
