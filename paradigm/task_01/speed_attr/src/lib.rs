// use types::all_types_context;

// pub fn init(context: &mut all_types_context){
//     context.add_static_attr::<i64>("transport", "speed");
// }
// use types::all_types_context;
use types::*;

// pub fn init(context: &mut all_types_context){
//     context.add_static_attr::<i64>("transport", "distance");
// }

use std::sync::RwLock;
#[macro_use]
extern crate lazy_static;

lazy_static! {
    static ref _speed_attr_: () = append(3);
}
