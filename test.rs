#![forbid(unsafe_code)]

use std::collections::HashMap;
use std::hash::Hash;

#[derive(Debug)]
struct Item<V> {
    val: Option<V>,
    newer: u64,
    older: u64,
}

impl<V> Item<V> {
    pub fn new(v: Option<V>) -> Self {
        Self {
            val: v,
            newer: 0,
            older: 0,
        }
    }
}
#[derive(Debug)]
pub struct LRUCache<K, V> {
    counter: u64,
    capacity: usize,
    keys: HashMap<K, u64>,
    data: HashMap<u64, Item<V>>, // circular doubly linked list
}

impl<K: Eq + Hash, V> LRUCache<K, V> {
    pub fn new(capacity: usize) -> Self {
        assert!(capacity != 0);
        Self {
            counter: 2, // 0 is for none, 1 is reserved as never used
            capacity,
            keys: HashMap::<K, u64>::default(),
            data: HashMap::<u64, Item<V>>::from([(0, Item::<V>::new(None))]),
        }
    }

    fn extract(&mut self, key: u64) -> Item<V> {
        let okey = self.data[&key].older;
        let nkey = self.data[&key].newer;
        self.data.entry(key).and_modify(|v| v.older = key);
        self.data.entry(key).and_modify(|v| v.newer = key);
        self.data.entry(okey).and_modify(|v| v.newer = nkey);
        self.data.entry(nkey).and_modify(|v| v.older = okey);
        self.data.remove(&key).unwrap()
    }

    fn insert_as_newest(&mut self, mut it: Item<V>, key: u64) {
        let nkey = self.data[&0].newer;
        let okey = 0;
        self.data.entry(0).and_modify(|v| v.newer = key);
        it.older = okey;
        it.newer = nkey;
        self.data.entry(nkey).and_modify(|v| v.older = key);
        self.data.insert(key, it);
    }

    fn key_to_int(&mut self, key: &K) -> u64 {
        if self.keys.len() > self.data.len() * 2 {
            // Frees at least self.data.len() elements in self.keys.
            // Every insert() increases self.keys.len() by at most 1.
            // So it is O(1) in average.
            let mut keys = HashMap::<K, u64>::default();
            std::mem::swap(&mut keys, &mut self.keys);
            keys.into_iter()
                .filter(|(_, v)| self.data.get(v).is_some())
                .collect::<Vec<_>>()
                .into_iter()
                .map(|(k, v)| self.keys.insert(k, v))
                .for_each(drop);
        }
        *self.keys.get(key).unwrap_or(&1)
    }

    pub fn get(&mut self, key: &K) -> Option<&V> {
        let k = self.key_to_int(key);
        self.data.get(&k)?;
        let it = self.extract(k);
        self.insert_as_newest(it, k);
        self.data[&k].val.as_ref()
    }

    pub fn insert(&mut self, key: K, value: V) -> Option<V> {
        let mut k = self.key_to_int(&key);
        if k == 1 {
            self.keys.insert(key, self.counter);
            k = self.counter;
            self.counter += 1;
        }
        if self.data.get(&k).is_some() {
            let it = self.extract(k);
            self.insert_as_newest(Item::new(Some(value)), k);
            return it.val;
        }
        if self.data.len() - 1 == self.capacity {
            let older = self.data[&0].older;
            self.extract(older);
        }
        self.insert_as_newest(Item::new(Some(value)), k);
        None
    }
}
























struct NaiveLRUCache<K, V> {
    capacity: usize,
    cache: Vec<(K, V)>,
}

impl<K: Eq, V> NaiveLRUCache<K, V> {
    pub fn new(capacity: usize) -> Self {
        assert!(capacity > 0);
        Self {
            capacity,
            cache: Vec::new(),
        }
    }

    pub fn get(&mut self, key: &K) -> Option<&V> {
        let index = self.cache.iter().position(|(a, _)| a == key)?;
        let pair = self.cache.remove(index);
        self.cache.push(pair);
        Some(&self.cache.last().unwrap().1)
    }

    pub fn insert(&mut self, key: K, value: V) -> Option<V> {
        if let Some(index) = self.cache.iter().position(|(a, _)| a == &key) {
            let (_, old_value) = self.cache.remove(index);
            self.cache.push((key, value));
            Some(old_value)
        } else {
            if self.cache.len() == self.capacity {
                self.cache.remove(0);
            }
            self.cache.push((key, value));
            None
        }
    }
}

fn should_compile() {
    #[derive(Clone, Hash, PartialEq, Eq, PartialOrd, Ord)]
    struct Key {
        _key: i32,
    }
    struct Value {
        _value: i32,
    }
    LRUCache::<Key, Value>::new(1);
}


fn it_works1() {
    let mut cache = LRUCache::new(2);
    assert_eq!(cache.insert(1, 1), None);
    assert_eq!(cache.insert(2, 2), None);
    assert_eq!(cache.get(&1), Some(&1));
    assert_eq!(cache.insert(3, 3), None);
    assert_eq!(cache.get(&2), None);
    assert_eq!(cache.insert(4, 4), None);
    assert_eq!(cache.get(&1), None);
    assert_eq!(cache.get(&3), Some(&3));
    assert_eq!(cache.get(&4), Some(&4));
}


fn it_works2() {
    let mut cache = LRUCache::new(2);
    assert_eq!(cache.get(&2), None);
    assert_eq!(cache.insert(2, 6), None);
    assert_eq!(cache.get(&1), None);
    assert_eq!(cache.insert(1, 5), None);
    assert_eq!(cache.insert(1, 2), Some(5));
    assert_eq!(cache.get(&1), Some(&2));
    assert_eq!(cache.get(&2), Some(&6));
}


fn it_works3() {
    let mut cache = LRUCache::new(2);
    assert_eq!(cache.insert(2, 1), None);
    assert_eq!(cache.insert(2, 2), Some(1));
    assert_eq!(cache.get(&2), Some(&2));
    assert_eq!(cache.insert(1, 1), None);
    assert_eq!(cache.insert(4, 1), None);
    assert_eq!(cache.get(&2), None);
}


fn it_works4() {
    let mut cache = LRUCache::new(2);
    assert_eq!(cache.insert(2, 1), None);
    assert_eq!(cache.insert(1, 1), None);
    assert_eq!(cache.get(&2), Some(&1));
    assert_eq!(cache.insert(4, 1), None);
    assert_eq!(cache.get(&1), None);
    assert_eq!(cache.get(&2), Some(&1));
}

struct Rand{
    state: u64,
}

impl Rand{
    pub fn thread_rng()->Self{
        Self{state: 1}
    }
    fn gen_64(&mut self)->u64{
        self.state ^= self.state << 21;
        self.state ^= self.state >> 35;
        self.state ^= self.state << 4;
        self.state
    }
    pub fn gen_range(&mut self, q:std::ops::Range<u64>)->u64{
        self.gen_64()%(q.end-q.start)+q.start
    }
    pub fn gen<T>(&mut self)->u64{
        self.gen_64()
    }
}




fn small_capacity() {
    let mut cache = LRUCache::new(10);
    let mut naive = NaiveLRUCache::new(10);
    let mut rng = Rand::thread_rng();
    for _ in 0..500000 {
        if rng.gen_range(0..3) == 0 {
            let key = rng.gen_range(0..30);
            assert_eq!(cache.get(&key), naive.get(&key));
        } else {
            let key = rng.gen_range(0..30);
            let value = rng.gen::<i8>();
            assert_eq!(cache.insert(key, value), naive.insert(key, value));
        }
    }
}


fn big_capacity() {
    let mut cache = LRUCache::new(1000);
    let mut naive = NaiveLRUCache::new(1000);
    let mut rng = Rand::thread_rng();
    for _ in 0..500000 {
        if rng.gen_range(0..3) == 0 {
            let key = rng.gen_range(0..3000);
            assert_eq!(cache.get(&key), naive.get(&key));
        } else {
            let key = rng.gen_range(0..3000);
            let value = rng.gen::<i8>();
            assert_eq!(cache.insert(key, value), naive.insert(key, value));
        }
    }
}


fn stress() {
    let mut cache = LRUCache::new(100000);
    let mut rng = Rand::thread_rng();
    for _ in 0..500000 {
        if rng.gen_range(0..3) == 0 {
            let key = rng.gen_range(0..1000000);
            cache.get(&key);
        } else {
            let key = rng.gen_range(0..1000000);
            let value = rng.gen::<i8>();
            cache.insert(key, value);
        }
    }
}

fn main(){
    should_compile();
    it_works1();
    it_works2();
    it_works3();
    it_works4();
    small_capacity();
    big_capacity();
    stress();
}
