use std::cell::RefCell;
use std::rc::Rc;

use types::*;
use object::*;
use anyhow::*;
use anyhow::Result;
use std::io::*;

pub type IdealTimeMethod = Rc<dyn Fn(Rc<RefCell<Object>>)->Result<f64>>;

fn ideal_time(obj_ptr: Rc<RefCell<Object>>) -> Result<f64>{
    let obj = obj_ptr.borrow_mut();
    let distance = *(
        obj.get_attr::<
            Rc<
                RefCell<
                    dyn CanBeAttr
                >
            >
        >(
            &String::from("distance")
        ).unwrap()
        .borrow_mut()
        .to_rc_any()
    ).downcast_ref::<i64>().unwrap() as f64;

    let speed = *(
        obj.get_attr::<
            Rc<
                RefCell<
                    dyn CanBeAttr
                >
            >
        >(
            &String::from("speed")
        ).unwrap()
        .borrow_mut()
        .to_rc_any()
    ).downcast_ref::<i64>().unwrap() as f64;

    Ok(distance / speed)
}

pub fn init(context: &mut AllTypesContext){
    context.new_attr_with_default_value(
        String::from("ideal_time"),
        Rc::new(ideal_time)
        as IdealTimeMethod,
        String::from("transport"),
    );
    let mem_stdin = Rc::new(
        RefCell::new(
            Cursor::new(
                Vec::new()
            ),
        )
    );
    mem_stdin.borrow_mut().write_all(b"object").unwrap();
    mem_stdin.borrow_mut().seek(SeekFrom::Start(0)).unwrap();
    let obj = Rc::new(
        RefCell::new(
            context.read_obj_from_stream(
                mem_stdin.clone()
                as ReadStream
            ).unwrap()
        )
    );
    let write_to_stream_old = obj.borrow_mut().get_attr::<WriteToStreamMethod>(&String::from("write_to_stream")).unwrap().clone();
    let write_to_stream_new = move |context: &AllTypesContext, obj: Rc<RefCell<Object>>, stream: WriteStream| -> Result<()>{
        write_to_stream_old(context, obj.clone(), stream.clone())?;
        stream.borrow_mut().write_all(b"    ")?;
        stream.borrow_mut().write_all(b"ideal_time")?;
        stream.borrow_mut().write_all(b"\n")?;
        stream.borrow_mut().write_all(b"    ")?;
        stream.borrow_mut().write_all(b"    ")?;
        stream.borrow_mut().write_all(ideal_time(obj.clone())?.to_string().as_bytes())?;
        stream.borrow_mut().write_all(b"\n")?;
        Ok(())
    };
    context.new_attr_with_default_value(
        String::from("write_to_stream"),
        Rc::new(write_to_stream_new)
        as WriteToStreamMethod,
        String::from("object"),
    );
}
