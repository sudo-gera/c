// types = { path = "../types" }
use types::all_types_context;
pub fn init(context: &mut all_types_context){
    context.new_attr::<i64>(String::from("load_capacity"), String::from("plane"));
}
