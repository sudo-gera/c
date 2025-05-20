use std::collections::HashSet;

// types = { path = "../types" }
use types::all_types_context;
pub fn init(context: &mut all_types_context){
    context.new_type(String::from("train"), HashSet::from([String::from("transport")]));
}
