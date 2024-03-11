use std::cell::{RefCell, Ref, RefMut};
use std::collections::{BTreeMap, HashMap};
use std::hash::Hash;

#[derive(Debug)]
struct Item<K, V>{
    newer: Option<K>,
    older: Option<K>,
    val: Option<V>,
}

impl<K: Clone + Hash + Ord, V> Item<K, V> {
    pub fn new(val : Option<V>) -> Self{
        Self{
            newer: None,
            older: None,
            val
        }
    }

    // def add(self: item[K, V], skey: K | None,
    //         oth: item[K, V], okey: K | None) -> None:
    //     self.newer = okey;
    //     oth.older = skey;

    // def sub(self: item[K, V], skey: K | None,
    //         oth: item[K, V], okey: K | None) -> None:
    //     self.newer = skey;
    //     oth.older = okey;
}








fn main(){
    let q: RefCell<Vec<i32>> = RefCell::new(vec![1,2,3]);
    let w = q.borrow_mut();
    


}
