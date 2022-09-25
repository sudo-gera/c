'use strict'
var ic=console.log
function set(){
    'use strict'
    var q=document.getElementById('q1').parentElement.childNodes;
    var a={}
    for (var w=0;w<q.length;++w){
        if (q[w].id[0]=='q'){
            a[q[w].id.slice(1)]=q[w].innerHTML;
        }
    }
    localStorage['__awvcp__q__all__']=JSON.stringify(a);
}

function get(i){
    'use strict'
    var l=JSON.parse(localStorage['__awvcp__q__all__'])
    for (var i in l){
        var d = new DOMParser().parseFromString(l[i], "text/html");
        var f=d.getElementsByTagName("*");
        var a=[];
        for (var t=0;t<f.length;++t){
            if (f[t].tagName=='SPAN' && f[t].classList.contains('feedbackspan')){
                for (var e=0;e<f[t].childNodes.length;++e){
                    if (f[t].childNodes[e].tagName==undefined && f[t].childNodes[e].data!=undefined && f[t].childNodes[e].data.startsWith('Правильный ответ: ')){
                        a.push(f[t].childNodes[e].data.slice('Правильный ответ: '.length));
                    }
                }
            }
            if (f[t].tagName=='DIV' && f[t].classList.contains('rightanswer')){
                var sel=f[t].innerText;
                if (sel.indexOf(' → ')!=-1){
                    sel=sel.split(' → ');
                    var d=[]
                    for (e=1;e<sel.length;++e){
                        d.push([sel[e-1],sel[e]]);
                    }
                    a.push(d);
                }else{
                    a.push(sel);
                }
            }
        }
        l[i]=a;
    }
    return l;
}

function hex(q){
    'use strict'
    var a=[]
    var w=0;
    for (w=0;w<q.length;++w){
        a.push(q[w].charCodeAt(0));
    }
    return a;
}

function put(){
    'use strict'
    var l=get();
    for (var i in l){
        var a=document.getElementById('q'+i);
        if (a==undefined){
            continue;
        }
        var s=a.getElementsByTagName("*");
        var z=l[i];
        for (var w=0;w<s.length;++w){
            if (s[w].tagName=='INPUT' && s[w].type=='text'){
                s[w].value=z.shift();
            }
            if (s[w].tagName=='INPUT' && s[w].type=='radio'){
                var x=z.shift();
                var d=s[w].parentElement.childNodes[1].innerText;
                if (x!=undefined && x.indexOf(d)!=-1){
                    s[w].checked=true;
                }else{
                    s[w].checked=false;
                    z.unshift(x);
                }
            }
            if (s[w].tagName=='SELECT'){
                try{
                    var k=s[w].parentElement.parentElement.childNodes[0].childNodes[0].innerText;
                }catch(err){
                    var k=undefined;
                }
                var x=z.shift();
                if (typeof x=='string'){
                    var q=s[w].childNodes;
                    for (var r=0;r<q.length;++r){
                        if (x==q[r].innerText){
                            s[w].value=r;
                        }
                    }
                }else{
                    for (e=0;e<x.length;++e){
                        if (x[e][0].endsWith(k)){
                            var q=s[w].childNodes;
                            for (var r=0;r<q.length;++r){
                                if (x[e][1].startsWith(q[r].innerText)){
                                    s[w].value=r;
                                    x.splice(e,1);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    z.unshift(x);
                }
           }
        }
    }
}
window.____set=set;
window.____put=put;