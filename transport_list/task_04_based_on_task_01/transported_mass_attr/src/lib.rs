
use types::AllTypesContext;
pub fn init(context: &mut AllTypesContext){
    context.new_attr::<f64>(String::from("transported_mass"), String::from("transport"));
}
