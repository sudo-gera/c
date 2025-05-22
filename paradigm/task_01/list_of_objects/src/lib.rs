use types::*;
use object::*;
use anyhow::*;
use double_linked_list::*;

pub struct ListOfObjects{
    data: DoubleLinkedList<Object>,
    obj: Object,
}

impl ListOfObjects{
    pub fn new() -> Self{
        Self{
            data: DoubleLinkedList::new(),
            obj: Object::new(),
        }
    }

    pub fn read_all_objects_from_stream(stdin: ReadStream, context: &AllTypesContext) -> Result<ListOfObjects>{
        let mut list = ListOfObjects::new();
        let len = read_trimmed_line(stdin.clone())?.parse::<i32>()?;
        for _ in 0..len{
            let mut oilist = ListOfObjects::from_one_item(
                context.read_obj_from_stream(stdin.clone())?
            );
            list.concat_by_stealing_from(&mut oilist);
        }
        Ok(list)
    }

    pub fn write_all_objects_to_stream(list: &mut ListOfObjects, stdout: WriteStream, context: &AllTypesContext) -> Result<()>{
        if !list.empty(){
            let mut iter = list.first_iter();
            loop {
                context.write_to_stream(
                    iter.value_rcrc(),
                    stdout.clone()
                )?;
                if iter == list.last_iter(){
                    break;
                }
                iter = iter.next();
            }
        }
        Ok(())
    }
}


// type ListOfObjects = DoubleLinkedList<Object>;


