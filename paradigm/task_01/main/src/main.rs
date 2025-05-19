// // use base::add;

// use types::counter;

// fn main() {
//     println!("Hello, world!");
//     println!("{:?}", counter.borrow_ref());
//     // println!("{}", add(1,2));
// }

// use types::*;
// use std::sync::RwLock;
// #[macro_use]
// extern crate lazy_static;

// lazy_static! {
//     static ref _main_: RwLock<((),i32)> = RwLock::new( (append(2), 0));
// }

// fn main(){
//     _main_.write().unwrap().1 = 1;
//     println!("{:?}", get_clone());
// }

// use std::sync::RwLock;
// #[macro_use]
// extern crate lazy_static;

// lazy_static! {
//     static ref data: RwLock<Vec<i32>> = RwLock::new(vec![]);
// }

// fn update_it(number: i32) {
//     println!("You wanted me to update to {}", number);

//     let mut w = data.write().unwrap();
//     w.push(number);
//     println!("After, it is: {:?}", w);
// }

// fn get_number() -> Vec<i32> {
//     let r1 = data.read().unwrap();
//     return r1.clone();
// }

// fn main() {
//     print!("r1: {:?}", get_number());
//     update_it(20);
//     update_it(22);
//     print!("r2: {:?}", get_number());
// }

fn main(){
    abstract_transport::init();
    speed_attr::init();
    distance_attr::init();
}
