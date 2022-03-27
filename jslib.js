async function setItem(name,value) {
	return await aurlopen('localstorage/set/'+name+'/'+JSON.stringify(value))
}

async function getItem(name) {
	return await aurlopen('localstorage/get/'+name)
}

function len(q){
	return q.length
}

ic=console.log

function t_urlopen_json(url,f){
	fetch(url).then((r)=>{r.json().then(f)})
}

function t_urlopen_text(url,f){
	fetch(url).then((r)=>{r.text().then(f)})
}

async function urlopen_json(url){
	return await((await(fetch(url))).json())
}

async function urlopen_text(url){
	return await((await(fetch(url))).json())
}

function sleep(s) {
	return new Promise(resolve => setTimeout(resolve, 1000*s));
}

