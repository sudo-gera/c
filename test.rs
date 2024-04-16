use std::{borrow::Borrow, collections::BTreeMap};
#[derive(PartialOrd)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Ord)]
#[derive(Debug)]
struct Q{
    value: i64
}
impl Q {
    pub fn new(value: i64)->Self{
        return Self{value};
    }
}

#[derive(PartialOrd)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Ord)]
#[derive(Debug)]
struct W{

}

impl W{
    fn new() -> Self{
        return Self{};
    }
}

impl Borrow<W> for Q{
    fn borrow(&self)->&W{
        unimplemented!();
    }
}

fn main(){
    let mut a=BTreeMap::<Q, Q>::new();
    a.insert(Q::new(10), Q::new(11));
    a.insert(Q::new(20), Q::new(21));
    println!("{:#?}", a);
    let s = a.first_key_value();
    let d = W::new();
    a.remove(&d);
}
