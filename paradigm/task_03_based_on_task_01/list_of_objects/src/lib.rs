use std::cell::*;
use std::rc::*;
use std::io::*;
use types::*;
use object::*;
use double_linked_list::*;
use std::collections::*;
use anyhow::*;
use anyhow::Result;

pub struct ListOfObjects{
    data: DoubleLinkedList<Object>,
    methods: Rc<RefCell<Object>>,
}

impl ListOfObjects{
    pub fn read_all_objects_from_stream(stdin: ReadStream, context: &AllTypesContext) -> anyhow::Result<ListOfObjects>{
        let mut list = DoubleLinkedList::<Object>::new();
        let len = read_trimmed_line(stdin.clone())?.parse::<i32>()?;
        for _ in 0..len{
            let mut oilist = DoubleLinkedList::<Object>::from_one_item(
                context.read_obj_from_stream(stdin.clone())?
            );
            list.concat_by_stealing_from(&mut oilist);
        }
        let mem_stdin = Rc::new(
            RefCell::new(
                Cursor::new(
                    Vec::new()
                ),
            )
        );
        mem_stdin.borrow_mut().write_all(b"list_of_objects")?;
        mem_stdin.borrow_mut().seek(SeekFrom::Start(0))?;
        let obj = Rc::new(
            RefCell::new(
                context.read_obj_from_stream(
                    mem_stdin.clone()
                    as ReadStream
                )?
            )
        );
        Ok(
            Self{
                data: list,
                methods: obj,
            }
        )
    }

    pub fn methods(&mut self) -> Rc<RefCell<Object>>{
        self.methods.clone()
    }
}

fn write_all_objects_to_stream(list: &mut ListOfObjects, stdout: WriteStream, context: &AllTypesContext) -> Result<()>{
    if !list.data.empty(){
        let mut iter = list.data.first_iter();
        loop {
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
            if iter == list.data.last_iter(){
                break;
            }
            iter = iter.next();
        }
    }
    Ok(())
}

pub type WriteAllObjectsToStreamMethod = Rc<dyn Fn(&mut ListOfObjects, WriteStream, &AllTypesContext)->Result<()>>;

pub fn init(context: &mut AllTypesContext){
    context.new_type(String::from("list_of_objects"), HashSet::new());
    context.new_attr_with_default_value(
        String::from("write_all_objects_to_stream"),
        Rc::new(write_all_objects_to_stream)
        as
        WriteAllObjectsToStreamMethod,
        String::from("list_of_objects")
    );
}
