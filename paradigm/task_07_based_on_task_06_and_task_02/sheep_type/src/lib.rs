use std::collections::HashSet;

// types = { path = "../types" }
use types::AllTypesContext;
pub fn init(context: &mut AllTypesContext){
    context.new_type(String::from("sheep"), HashSet::from([String::from("transport")]));
}
