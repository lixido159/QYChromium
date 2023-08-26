import {repeat, shout} from './lib.js';
let r = repeat('hello');
let s = shout('Modules in action');
console.log(r);
console.log(s);
console.log(123123);

import('./lib.mjs')
 .then((module) => {
  let a = module.repeat('hello');
  let b = module.shout ('Modules in action');
  print(a);
  print(b);
 });

// Dynamic import
