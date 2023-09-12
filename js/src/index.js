import {shout, repeat} from "./lib.js"
qy.entry= () =>{
    console.log("入口");
    shout("咆哮");
};
console.log(`入口 ${shout("咆哮")}`);
