var ic=console.log
function get_task_name(){
    'use strict';
    var bar = document.querySelector("#page-navbar > ul > li.lastli > span > a > span");
    if (bar != null){
        return bar.innerText;
    }else{
        return bar;
    }
}

function take_file_from_user(){
    'use strict';
    return new Promise(resolve=>{
        var input = document.createElement('input');
        input.type = 'file';
        input.onchange = input => {
            var file = input.target.files[0];
            var reader = new FileReader();
            reader.readAsText(file,'UTF-8');
            reader.onload = readerEvent => {
                var content = readerEvent.target.result;
                resolve(content);
            }
        }
        input.click();
    });
}

function give_file_to_user(data,filename){
    'use strict';
    var blob = new Blob([data]);
    var url = URL.createObjectURL(blob);
    var a = document.createElement('a');
    a.href = url;
    a.download = filename;
    a.click();
}

function get_answers_as_obj_with_html(){
    'use strict';
    var result = {};
    for (var num = 0; num < 256; ++num) {
        var name = 'q' + num;
        var q = document.getElementById(name);
        if (q != null) {
            result[num] = q.innerHTML;
        }
    }
    return result;
}

function get_answers_as_obj_with_nodes(){
    'use strict';
    var result = {};
    for (var num = 0; num < 256; ++num) {
        var name = 'q' + num;
        var q = document.getElementById(name);
        if (q != null) {
            result[num] = q;
        }
    }
    return result;
}

function store_answers_as_JSON_with_html_to_local_storage(){
    'use strict';
    var obj = get_answers_as_obj_with_html();
    localStorage['__awvcp__q__all__'] = JSON.stringify(obj);
}

function load_answers_as_obj_with_html_from_local_storage(){
    'use strict';
    var json = localStorage['__awvcp__q__all__'];
    return JSON.parse(json);
}

function parse_answers_from_obj_with_html(obj){
    'use strict';
    var result={};
    for (var num in obj){
        if (typeof(obj[num])=='string'){
            var elements = [...new DOMParser().parseFromString(obj[num], "text/html").getElementsByTagName("*")];
        }else{
            var elements = [...obj[num].getElementsByTagName("*")];
        }
        var name = 'task '+num;
        result[name]=[];
        elements.forEach(element=>{
            if (element.id.startsWith('yui')){
                console.log(element);
            }
            if (element.tagName=='SPAN' && element.classList.contains('feedbackspan')){
                element.childNodes.forEach(node=>{
                    // ic(node);
                    if (node.tagName==undefined && node.data!=undefined && node.data.startsWith('Правильный ответ: ')){
                        result[name].push(node.data.slice('Правильный ответ: '.length));
                    }
                });
            }
            if (element.tagName=='DIV' && element.classList.contains('rightanswer') && !element.classList.contains('que')){
                var sel=element.innerText;
                if (sel.indexOf(' → ')!=-1){
                    var task=element.parentNode.parentNode.parentNode.childNodes[0];
                    sel=sel.split(' → ');
                    // var d=[];
                    // for (e=1;e<sel.length;++e){
                    //     d.push([sel[e-1],sel[e]]);
                    // }
                    // var y=[];
                    var queries=[];
                    [...task.getElementsByTagName('tr')].forEach(tr=>{
                        var query = tr.childNodes[0].innerText.trim();
                        queries.push(query);
                    });
                    [...task.getElementsByTagName('tr')].forEach(tr=>{
                        var query = tr.childNodes[0].innerText.trim();
                        var answers = [...tr.childNodes[1].childNodes[1].childNodes];
                        answers = answers.map(ans=>ans.innerText.trim());
                        answers.push('Правильный ответ: ');
                        var candidates=[];
                        sel.forEach((fragment,fragind)=>{
                            answers.forEach((ans)=>{
                                // ic([fragment,ans,query]);
                                // ic([fragment.indexOf(ans)]);
                                // ic(fragment.slice(fragment.indexOf(ans)+ans.length));
                                if (fragment.indexOf(ans)!=-1 && fragment.slice(fragment.indexOf(ans)+ans.length).indexOf(query)!=-1) {
                                    candidates.push([
                                        fragment.length - ans.length - (fragind == sel.length - 1 ? query.length : 0),
                                        fragind,
                                        ans,
                                        fragment
                                    ]);
                                }
                            })
                        });
                        candidates.sort((a,b)=> a[0]-b[0]);
                        // ic(query)
                        // ic(candidates)
                        // ic(sel)
                        var fragind=candidates[0][1]+1
                        var fragment=sel[fragind];
                        candidates=[];
                        queries.forEach(query=>{
                            answers.forEach(ans=>{
                                if (fragment.indexOf(ans)!=-1 && (fragment.slice(fragment.indexOf(ans)+ans.length).indexOf(query)!=-1 || fragind==sel.length-1)) {
                                    candidates.push([
                                        fragment.length - ans.length - (fragind == sel.length - 1 ? query.length : 0),
                                        ans,
                                        fragind,
                                        fragment
                                    ]);
                                }
                            });
                        });
                        candidates.sort((a,b)=> a[0]-b[0]);
                        var answer=candidates[0][1];
                        // result[name].push([
                        //     query,answer
                        // ]);
                        if (result[name].length!=undefined){
                            result[name]={};
                        }
                        result[name][query]=answer;
                    });
                }else{
                    result[name].push(sel);
                }
            }
            if (element.tagName=='INPUT' && element.classList.contains('correct')){
                result[name].push(element.value);
            }
            if (element.tagName=='INPUT' && element.classList.contains('incorrect')) {
                var g=[...element.parentNode.childNodes];
                g.forEach((ans,ind)=>{
                    if (ans.isSameNode(element)){
                        // ic([ind,g]);
                        if (g[ind+2]!=undefined && g[ind+2].title=='Correct answer'){
                            result[name].push(g[ind+2].innerText.slice(1,-1));
                        }
                    }
                });
            }
        });
    }
    return result;
}

function convert_answers_to_json(ans){
    'use strict';
    return JSON.stringify(ans,null,4);
}

function save_answers_to_file(){
    'use strict';
    var obj = get_answers_as_obj_with_nodes();
    var ans = parse_answers_from_obj_with_html(obj);
    var name = get_task_name();
    ans['task name']=name;
    var json = convert_answers_to_json(ans);
    name += '.txt';
    give_file_to_user(json,name);
}

function print_answers(){
    'use strict';
    var obj = get_answers_as_obj_with_nodes();
    var ans = parse_answers_from_obj_with_html(obj);
    var name = get_task_name();
    ans['task name']=name;
    var json = convert_answers_to_json(ans);
    ic(json);
}

async function load_answers_from_file(){
    'use strict';
    var json=await take_file_from_user();
    var ans=JSON.parse(json);
    put_answers_to_page(ans);
} 

function put_answers_to_page(ans){
    'use strict';
    for (var num = 0; num < 256; ++num) {
        var qname = 'q' + num;
        var name = 'task ' + num;
        var element=document.getElementById(qname);
        if (element==undefined){
            continue;
        }
        var answer=ans[name];
        if (answer==undefined){
            var json=JSON.stringify(ans);
            answer=[];
        }
        if (answer.length==undefined){
            var x=[];
            for (var w in answer){
                x.push([w,answer[w]]);
            }
            answer=x;
        }
        [...element.getElementsByTagName('*')].forEach(elem=>{
            if (elem.tagName=='INPUT' && elem.type=='text'){
                var x=answer.shift();
                elem.value=x;
            }
            if (elem.tagName=='INPUT' && elem.type=='radio'){
                var x=answer.shift();
                var d=elem.parentElement.childNodes[1];
                var t='';
                for (e in d.childNodes){
                    if (d.childNodes[e].tagName==undefined && d.childNodes[e].data!=undefined){
                        t+=d.childNodes[e].data;
                    }
                }
                d=t;
                if (x==undefined || x.trim().indexOf(d.trim())!=-1){
                    elem.checked=true;
                }else{
                    elem.checked=false;
                }
                answer.unshift(x);
            }
            if (elem.tagName=='SELECT' && elem.classList.contains('select') && elem.classList.contains('custom-select')){
                // ic(elem);
                try{
                    var k=elem.parentElement.parentElement.childNodes[0].childNodes[0].innerText;
                }catch(err){
                    var k=undefined;
                }
                var x=answer;
                // var x=answer.shift();
                if (typeof(x) == 'undefined' || typeof(x[0]) == 'string' || typeof(x[0]) == 'undefined'){
                    x=answer.shift();
                    ic(JSON.parse(JSON.stringify(x)))
                    ic(JSON.parse(JSON.stringify(answer)))
                    ic(elem)
                    var q=elem.childNodes;
                    elem.value=Math.floor(Math.random()*q.length);
                    for (var r=0;r<q.length;++r){
                        ic([q[r].innerText,x,q[r].innerText==x]);
                        ic([r,q[r].value]);
                        if (x==q[r].innerText){
                            elem.value=q[r].value;
                        }
                    }
                }else{
                    ic(JSON.parse(JSON.stringify(x)))
                    var q=elem.childNodes;
                    elem.value=Math.floor(Math.random()*q.length);
                    for (var e=0;e<x.length;++e){
                        // ic(x[e][0],'|',k)
                        if (x[e][0].trim()==k.trim()){
                            for (var r=0;r<q.length;++r){
                                ic(x[e][1],'|',q[r].innerText)
                                if (x[e][1].trim()==q[r].innerText.trim()){
                                    elem.value=r;
                                    // x.splice(e,1);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    // answer.unshift(x);
                }
           }
        });
    }
}

function put_answers_to_page_from_local_storage(){
    'use strict';
    var obj = load_answers_as_obj_with_html_from_local_storage();
    var ans = parse_answers_from_obj_with_html(obj);
    put_answers_to_page(ans);
}


function main(){
    'use strict'
    if (get_task_name()!=null){
        save_answers_to_file();
    }else{
        load_answers_from_file();
    }
}

// main();

