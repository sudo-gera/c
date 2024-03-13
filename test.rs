use std::borrow::Borrow;
use std::cell::{RefCell, Ref, RefMut};
use std::collections::btree_map::{OccupiedEntry, VacantEntry};
use std::collections::{BTreeMap, HashMap, HashSet};
use std::hash::Hash;
use std::{default, option};
use std::collections::hash_map::Entry::{Vacant, Occupied};

type Key<K> = K;
type KeyRef<'a, K> = Option<&'a K>;
type Dict<'a, K, V> = HashMap<K, Val<'a, K, V>>;

#[derive(Debug)]
struct Others<'a, K>{
    newer: KeyRef<'a, K>,
    older: KeyRef<'a, K>,
}

#[derive(Debug)]
struct Val<'a, K, V>{
    others: RefCell<Others<'a, K>>,
    val: Option<V>,
}

impl<'a, K/* : Clone + Hash + Ord*/, V> Val<'a, K, V> {
    pub fn new(val : Option<V>) -> Self{
        Self{
            others: RefCell::new(Others{
                newer: None,
                older: None,
            }),
            val,
        }
    }
}

// type K = Vec<i32>;
// type V = Vec<i32>;

// type CacheKey<'a, K> = Option<&'a K>;
// type CacheVal<'a, K, V> = (RefCell<Item<'a, K>>, Option<V>);
// type CacheDict<'a, K, V> = HashMap<CacheKey<'a, K>, CacheVal<'a, K, V>>;

fn add<'a, K, V>(left: &Val<'a, K, V>, lkey: KeyRef<'a, K>, right: &Val<'a, K, V>, rkey: KeyRef<'a, K>){
    left.others.borrow_mut().newer = rkey;
    right.others.borrow_mut().older = lkey;
}

fn sub<'a, K, V>(left: &Val<'a, K, V>, lkey: KeyRef<'a, K>, right: &Val<'a, K, V>, rkey: KeyRef<'a, K>){
    left.others.borrow_mut().newer = lkey;
    right.others.borrow_mut().older = rkey;
}

struct Cache<'a, K, V>{
    capacity: usize,
    data: Dict<'a, K, V>,
    root: Val<'a, K, V>,
}

impl<'a, K: /*Clone +*/ Hash + Eq /*+ Ord*/, V> Cache<'a, K, V> {
    pub fn new(capacity: usize) -> Self{
        let mut data = Dict::<K,V>::default();
        // data.entry(&None).or_insert(Val::new(None));
        Self{
            capacity,
            data,
            root: Val::<'a, K, V>::new(None),
        }
    }

    fn data_get<'b>(&self, k: KeyRef<'b, K>) -> &Val<'a, K, V>{
        match k{
            None => &self.root,
            Some(x) => &self.data[x],
        }
    }

    fn extract<'b>(&mut self, it: &Val<'a, K, V>, key: KeyRef<'b, K>){
        let okey = it.others.borrow().older;
        let nkey = it.others.borrow().newer;
        let older = self.data_get(okey);
        let newer = self.data_get(nkey);
        sub(older, okey, it, key);
        sub(it, key, newer, nkey);
        add(older, okey, newer, nkey);
        // self.data.remove(&key);
    }

    fn insert_as_newest<'b>(&mut self, it: &Val<'a, K, V>, key: KeyRef<'b, K>){
        let nkey = self.root.others.borrow().newer;
        let newer = self.data_get(nkey);
        let okey: KeyRef<'a, K> = None;
        let older = self.data_get(None);
        sub(older, okey, newer, nkey);
        add(older, okey, &it, key);
        add(&it, key, newer, nkey);
        // self.data.insert(key, it);
    }

    pub fn get(&mut self, k: &K) -> Option<&V>{
        if self.data.contains_key(k){
            let k = k.clone();
            let it = &self.data[k];
            self.extract(it, Some(k));
            self.insert_as_newest(it, Some(k));
        };
        None

        // let q = Some(k).as_deref().as_deref();
        // None
        // self.data
        // .get(&Some(k))
        // .map(|q| Ref::map(q.borrow(), |e|e.val.as_ref().unwrap()))
    }

    // pub fn set(&mut self, k: Option<&'a K>, v: V) -> Option<Ref<V>>{
    //     self.check();
    //     it = self.data.get(k, None);
    //     if it is not None:
    //         self.extract(it, k);
    //         self.insert_as_newest(Item(v), k);
    //         self.check();
    //         return it.val;
    //     else:
    //         if len(self.data) == self.capacity + 1:
    //             older = self.data[None].older;
    //             assert older is not None;
    //             self.extract(self.data[self.data[None].older], older);
    //         self.insert_as_newest(Item(v), k);
    //         self.check();
    //         return None;
    // }
}




fn main(){
    let q: RefCell<Vec<i32>> = RefCell::new(vec![1,2,3]);
    let w = q.borrow_mut();



}
