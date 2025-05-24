// use std::cell::RefCell;
use std::rc::Rc;
// types = { path = "../types" }
use types::*;
// use object::*;
use anyhow::*;
use anyhow::Result;
// use std::io::*;
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
    // context.new_attr_with_default_value(
    //     String::from("ideal_time"),
    //     Rc::new(ideal_time)
    //     as IdealTimeMethod,
    //     String::from("transport"),
    // );
    // let mem_stdin = Rc::new(
    //     RefCell::new(
    //         Cursor::new(
    //             Vec::new()
    //         ),
    //     )
    // );
    // mem_stdin.borrow_mut().write_all(b"object").unwrap();
    // mem_stdin.borrow_mut().seek(SeekFrom::Start(0)).unwrap();
    // let obj = Rc::new(
    //     RefCell::new(
    //         context.read_obj_from_stream(
    //             mem_stdin.clone()
    //             as ReadStream
    //         ).unwrap()
    //     )
    // );
    // let write_to_stream_old = obj.borrow_mut().get_attr::<WriteToStreamMethod>(&String::from("write_to_stream")).unwrap().clone();
    // let write_to_stream_new = move |context: &AllTypesContext, obj: Rc<RefCell<Object>>, stream: WriteStream| -> Result<()>{
    //     write_to_stream_old(context, obj.clone(), stream.clone())?;
    //     stream.borrow_mut().write_all(b"    ")?;
    //     stream.borrow_mut().write_all(b"ideal_time")?;
    //     stream.borrow_mut().write_all(b"\n")?;
    //     stream.borrow_mut().write_all(b"    ")?;
    //     stream.borrow_mut().write_all(b"    ")?;
    //     stream.borrow_mut().write_all(ideal_time(obj.clone())?.to_string().as_bytes())?;
    //     stream.borrow_mut().write_all(b"\n")?;
    //     Ok(())
    // };
    context.new_attr_with_default_value(
        String::from("write_object_pairs_to_stream"),
        Rc::new(write_object_pairs_to_stream)
        as WriteObjectPairsToStreamMethod,
        String::from("list_of_objects"),
    );
}
