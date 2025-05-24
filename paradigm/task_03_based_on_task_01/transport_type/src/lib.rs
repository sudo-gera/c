use std::collections::HashSet;



use types::AllTypesContext;
pub fn init(context: &mut AllTypesContext){
    context.new_type(String::from("transport"), HashSet::from([String::from("object")]));
}
