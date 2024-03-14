use std::collections::HashMap;
use std::collections::hash_map;

struct Item<V>{
    val: Option<V>,
    newer: u64,
    older: u64,
}

impl<V> Item<V> {
    pub fn new(v: Option<V>) -> Self{
        Self{
            val: v,
            newer: 0,
            older: 0,
        }
    }
}

// fn add<V>(left: &mut hash_map::Entry<u64, Item<V>>, lkey: u64, right: &mut hash_map::Entry<u64, Item<V>>, rkey: u64){
//     left.
//     left.and_modify(|v|v.newer = rkey);
//     right.and_modify(|v|v.older = lkey);
// }

// fn sub<V>(left: &mut Item<V>, lkey: u64, right: &mut Item<V>, rkey: u64){
//     left.newer = lkey;
//     right.older = rkey;
// }

struct Cache<K,V>{
    counter: u64,
    capacity: usize,
    keys: HashMap<K, u64>,
    data: HashMap<u64, Item<V>>,
    // root : Item<V>,
}

impl<K,V> Cache<K,V> {
    pub fn new(capacity: usize) -> Self{
        Self{
            counter: 0,
            capacity,
            keys: HashMap::<K,u64>::default(),
            data: HashMap::<u64,Item<V>>::from([(0, Item::<V>::new(None))]),
        }
    }

    fn data_get(&mut self, k: u64) -> hash_map::Entry<u64, Item<V>>{
        return self.data.entry(k);
    }

    fn extract(&mut self, it: &mut Item<V>, key: u64){
        let (okey, nkey) = (it.older, it.newer);
        let (older, newer) = (self.data_get(okey), self.data_get(nkey));
        // sub(older, okey, it, key);
        // sub(it, key, newer, nkey);
        add(&mut older, okey, &mut newer, nkey);
        self.data.remove(&key);
    }
}


fn main(){

}
