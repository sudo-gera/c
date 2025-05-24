// use std::cell::RefCell;
use std::rc::Rc;
// types = { path = "../types" }
use types::*;
// use object::*;
use anyhow::*;
use anyhow::Result;
// use std::io::*;
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
        String::from("write_only_planes_to_stream"),
        Rc::new(write_only_planes_to_stream)
        as WriteAllObjectsToStreamMethod,
        String::from("list_of_objects"),
    );
}
