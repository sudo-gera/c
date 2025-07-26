use std::rc::Rc;
use types::*;
use anyhow::*;
use anyhow::Result;
use list_of_objects::*;

fn write_only_planes_to_stream(list: &mut ListOfObjects, stdout: WriteStream, context: &AllTypesContext) -> Result<()>{
    if !list.data().borrow_mut().empty(){
        let mut iter = list.data().borrow_mut().first_iter();
        loop {
            if iter.value_rcrc().borrow_mut().get_attr::<String>(&String::from("__type_name__")).unwrap() == "plane"{
                let write_to_stream = iter.value_rcrc()
                .borrow_mut()
                .get_attr::<
                    WriteToStreamMethod
                >(&String::from("write_to_stream"))
                .unwrap()
                .clone();
                write_to_stream(
                    context,
                    iter.value_rcrc(),
                    stdout.clone()
                )?;
            }
            if iter == list.data().borrow_mut().last_iter(){
                break;
            }
            iter = iter.next();
        }
    }
    Ok(())
}

pub fn init(context: &mut AllTypesContext){
    context.new_attr_with_default_value(
        String::from("write_only_planes_to_stream"),
        Rc::new(write_only_planes_to_stream)
        as WriteAllObjectsToStreamMethod,
        String::from("list_of_objects"),
    );
}
