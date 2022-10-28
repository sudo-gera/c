'use strict'
var ic=console.log
function __set(){
    'use strict'
    var q=document.getElementById('q1').parentElement.childNodes;
    var a={}
    for (var w=0;w<q.length;++w){
        if (q[w].id[0]=='q'){
            a[q[w].id.slice(1)]=q[w].innerHTML;
        }
    }
    return a;
}

function __get(l){
    l=JSON.parse(JSON.stringify(l));
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
            if (f[t].tagName=='DIV' && f[t].classList.contains('qtext')){
                var cn=f[t].getElementsByTagName('*');
                for (var e in cn){
                    if (cn[e].tagName=='INPUT' && cn[e].classList.contains('typetext') && cn[e].classList.contains('correct')){
                        a.push(cn[e].value);
                    }
                    if (cn[e].tagName=='INPUT' && cn[e].classList.contains('typetext') && cn[e].classList.contains('incorrect')){
                        var cnt=cn[e].parentElement.querySelector('span.aftergapfeedback').innerText;
                        a.push(cnt.slice(1,-1));
                    }
                }
            }
        }
        l[i]=a;
    }
    return l;
}

function __hex(q){
    'use strict'
    var a=[]
    var w=0;
    for (w=0;w<q.length;++w){
        a.push(q[w].charCodeAt(0));
    }
    return a;
}

function __put(l){
    l=__get(l);
    for (var i=0;i<256;++i){
        var a=document.getElementById('q'+i);
        if (a==undefined){
            continue;
        }
        var s=a.getElementsByTagName("*");
        var z=l[i];
        if (z==undefined){
            z=[];
        }
        for (var w=0;w<s.length;++w){
            ic(s[w])
            ic(JSON.parse(JSON.stringify(l)))
            if (s[w].tagName=='INPUT' && s[w].type=='text'){
                // ic(s)
                // ic(s[w])
                // ic(z)
                // ic(i)
                // ic(l)
                s[w].value=z.shift();
            }
            if (s[w].tagName=='INPUT' && s[w].type=='radio'){
                var x=z.shift();
                var d=s[w].parentElement.childNodes[1];
                var t=''
                for (e in d.childNodes){
                    if (d.childNodes[e].tagName==undefined && d.childNodes[e].data!=undefined){
                        t+=d.childNodes[e].data;
                    }
                }
                d=t;
                if (x==undefined || x.trim().indexOf(d.trim())!=-1){
                    s[w].checked=true;
                }else{
                    s[w].checked=false;
                }
                z.unshift(x);
            }
            if (s[w].tagName=='SELECT'){
                try{
                    var k=s[w].parentElement.parentElement.childNodes[0].childNodes[0].innerText;
                }catch(err){
                    var k=undefined;
                }
                var x=z.shift();
                if (typeof x=='string' || typeof x=='undefined'){
                    var q=s[w].childNodes;
                    s[w].value=Math.floor(Math.random()*q.length);
                    for (var r=0;r<q.length;++r){
                        if (x==q[r].innerText){
                            s[w].value=r;
                        }
                    }
                }else{
                    // ic(JSON.parse(JSON.stringify(x)))
                    var q=s[w].childNodes;
                    s[w].value=Math.floor(Math.random()*q.length);
                    for (var e=0;e<x.length;++e){
                        ic(x[e][0],'|',k)
                        if (x[e][0].trim().endsWith(k.trim())){
                            for (var r=0;r<q.length;++r){
                                ic(x[e][1],'|',q[r].innerText)
                                if (x[e][1].trim().startsWith(q[r].innerText.trim())){
                                    s[w].value=r;
                                    // x.splice(e,1);
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
function __all(){
    var all_emp=1;
    try{
        var a=__set();
        var g=__get(a);
        for (var w in g){
            if (g[w].length){
                all_emp=0;
            }
        }
    }catch{}
    if (all_emp){
        var j=localStorage['__awvcp__q__all__'];
        if (j==undefined){
            j='{}'
        }
        __put(JSON.parse(j));
    }else{
        localStorage['__awvcp__q__all__']=JSON.stringify(a);
    }
}

window.______all=__all;

__all();