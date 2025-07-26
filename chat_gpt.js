'use strict';
function ans(){
    document.querySelector("#column-center > div > div > div.chat-input > div.chat-input-container > div.rows-wrapper-wrapper > div > div.new-message-wrapper > button.btn-icon.tgico-none.toggle-emoticons").click()
    setTimeout(()=>{
        var q=document.querySelector("#content-emoji > div");
        (a=>a[Math.floor(Math.random()*a.length)])(q.children[7].children[1].children).click()
        document.querySelector("#column-center > div > div > div.chat-input > div.chat-input-container > div.btn-send-container > button").click()
    },128);
}


var last=new Set();

function get(){
    var q=new Set([...document.querySelector("#column-center > div > div > div.bubbles.has-groups.has-sticky-dates > div > div").getElementsByTagName('*')].filter(e=>e.classList.contains('bubble-content-wrapper')))
    var w=[];
    q.forEach(e=>last.has(e)?0:[w.push(e),last.add(e)]);
    return w;
}

var el=getEventListeners(document.querySelector("#column-center > div > div > div.chat-input > div > div.rows-wrapper-wrapper > div > div.new-message-wrapper > div.input-message-container > div:nth-child(1)"));

function type_text(t){
    document.querySelector("#column-center > div > div > div.chat-input > div > div.rows-wrapper-wrapper > div > div.new-message-wrapper > div.input-message-container > div:nth-child(1)").innerText=t;
    el.input.forEach(e=>e.listener());
}

function click_send(){
    document.querySelector("#column-center > div > div > div.chat-input > div > div.btn-send-container > button > div").click();
}

var last_reply_html='';
function _(){
    setInterval(()=>{
        var l=document.querySelector("#column-center > div > div > div.chat-input > div > div.rows-wrapper-wrapper > div > div.reply-wrapper > div.reply").innerHTML;
        if (l!=last_reply_html){
            type_text(l.slice(0,64));
            click_send();
        }
        last_reply_html=l;
    },256);
}

function get_from_local_server(p){
    ''+p;
    var e=async e=>{
        while (1){
            try{
                var e='http://localhost:'+p;
                var e=await fetch(e);
                var e=await e.text();
                if (e){
                    type_text(e);
                    click_send();
                }
            }catch(e){
                console.log(e);
                await new Promise(c=>{setTimeout(c,1000);});
            }
        }
    }
    return e();
}

var observeDOM = (function(){
  var MutationObserver = window.MutationObserver || window.WebKitMutationObserver;

  return function( obj, callback ){
    if( !obj || obj.nodeType !== 1 ) return; 

    if( MutationObserver ){
      // define a new observer
      var mutationObserver = new MutationObserver(callback)

      // have the observer observe for changes in children
      mutationObserver.observe( obj, { childList:true, subtree:true })
      return mutationObserver
    }
    
    // browser support fallback
    else if( window.addEventListener ){
      obj.addEventListener('DOMNodeInserted', callback, false)
      obj.addEventListener('DOMNodeRemoved', callback, false)
    }
  }
})()

// var msg_list_node = document.querySelector("#column-center > div > div > div.bubbles.scrolled-down.has-groups.has-sticky-dates");
var msg_list_node = document.querySelector("#column-center > div > div > div.bubbles.has-groups.has-sticky-dates");
// var msg_list_node = document.querySelector("#MiddleColumn > div.messages-layout > div.Transition > div > div.MessageList.custom-scroll.no-avatars.with-default-bg.scrolled > div");


// observeDOM( msg_list_node, function(m,o){ 
//     console.log(o);
//    var addedNodes = [], removedNodes = [];

//    m.forEach(record => record.addedNodes.length & addedNodes.push(...record.addedNodes))
   
//    m.forEach(record => record.removedNodes.length & removedNodes.push(...record.removedNodes))

// //   console.clear();
//     addedNodes.forEach(n=>{
//         if (n.classList.contains('bubbles-group-last')){
//             if (n.children[0].classList.contains('is-in')){
//                 console.log(n);
//                 console.log(n.children[0].children[0].children[0].children[0].innerText);
//             }
//         }
//     });
// //   console.log('Added:', addedNodes, 'Removed:', removedNodes);
// });

var need_ans = 0;
var recv_int = null;

function jsonEscapeUTF(s) {return s.replace(/[^\x20-\x7F]/g, x => "\\u" + ("000"+x.codePointAt(0).toString(16)).slice(-4))}

function send_msg(text){
    return new Promise(on_done=>{
        if (text.length<5){
            return on_done('Query should be 5 symbols at least.');
        }
        type_text(text);
        click_send();
        recv_int = setInterval(() => {
            // var msg_list = [...msg_list_node.children].flatMap(c=>[...c.children]);
            var msg_list = [...msg_list_node.children].flatMap(c=>[...c.children]).flatMap(c=>[...c.children]).flatMap(c=>[...c.children]);
            var last = msg_list[msg_list.length-1];
            if (last.children[0].children[0].children[1] !== undefined){
                var text = last.children[0].children[0].children[0].children[0].childNodes[0].data;
                on_done(text);
                clearInterval(recv_int);
            }
        }, 100);
    })
}

var delay = [100];
async function main_loop(){
    while(1){
        try{
            var query = await (await fetch('http://127.0.0.1:5205/')).json()
            var resp = await send_msg(query.value);
            await (await fetch('http://127.0.0.1:5205/' + 
                btoa(jsonEscapeUTF(JSON.stringify({
                    value: resp,
                    token: query.token
                })))
            )).text()
            delay[0] = 100;
        }catch(e){
            console.log(e);
            await new Promise(on_done=>setTimeout(on_done, delay[0]));
            if (delay[0] < 1000){
                delay[0] *= 2;
            }
        }
    }
}
main_loop();


