use std::rc::Rc;

use types::*;
use anyhow::*;
use anyhow::Result;
use list_of_objects::*;

pub type WriteObjectPairsToStreamMethod = Rc<dyn Fn(&mut ListOfObjects, WriteStream) -> Result<()>>;

fn write_object_pairs_to_stream(list: &mut ListOfObjects, stdout: WriteStream) -> Result<()>{
    if !list.data().borrow_mut().empty(){
        let mut iter1 = list.data().borrow_mut().first_iter();
        loop {
            let mut iter2 = list.data().borrow_mut().first_iter();
            loop {
                let type_name1 = iter1.value_rcrc().borrow_mut().get_attr::<String>(&String::from("__type_name__")).unwrap().to_string();
                let type_name2 = iter2.value_rcrc().borrow_mut().get_attr::<String>(&String::from("__type_name__")).unwrap().to_string();
                writeln!(
                    stdout.borrow_mut(),
                    "{} and {}",
                    type_name1,
                    type_name2,
                )?;
                if iter2 == list.data().borrow_mut().last_iter(){
                    break;
                }
                iter2 = iter2.next();
            }
            if iter1 == list.data().borrow_mut().last_iter(){
                break;
            }
            iter1 = iter1.next();
        }
    }
    Ok(())
}

pub fn init(context: &mut AllTypesContext){
    context.new_attr_with_default_value(
        String::from("write_object_pairs_to_stream"),
        Rc::new(write_object_pairs_to_stream)
        as WriteObjectPairsToStreamMethod,
        String::from("list_of_objects"),
    );
}
