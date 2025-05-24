// types = { path = "../types" }
use types::AllTypesContext;
pub fn init(context: &mut AllTypesContext){
    context.new_attr::<i64>(String::from("distance"), String::from("transport"));
}
