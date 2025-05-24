
use types::AllTypesContext;
pub fn init(context: &mut AllTypesContext){
    context.new_attr::<i64>(String::from("load_capacity"), String::from("plane"));
}
