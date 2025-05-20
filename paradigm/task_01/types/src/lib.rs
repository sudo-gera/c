use std::str::*;
use std::cell::*;
use anyhow::*;
use std::collections::*;
use object::*;
use std::rc::*;
use std::sync::*;
use std::io::*;
use anyhow::Error;
use anyhow::Result;

pub type read_buf_type = Rc<RefCell<dyn BufRead>>;
pub type write_buf_type = Rc<RefCell<dyn Write>>;

// // pub fn add(left: u64, right: u64) -> u64 {
// //     left + right
// // }


// type read_buf_type = Rc<RefCell<dyn BufRead>>;
// type write_buf_type = Rc<RefCell<BufWriter<dyn Write>>>;


// // type on_read_type = Rc<dyn Fn(read_buf_type)->Result<Object, Error>>;

pub fn read_trimmed_line(input: read_buf_type) -> Result<String, Error>{
    let mut one_line = String::new();
    let mut input_binding = input.borrow_mut();
    input_binding.read_line(&mut one_line)?;
    drop(input_binding);
    one_line = one_line.to_string().trim().to_string();
    return Ok(one_line);
}

// // struct type_info{
// //     name: String,
// //     bases: Vec<String>,
// //     on_read: on_read_type,
// // }

// // struct read_dispatcher{
// //     types: HashMap::<String, type_info>,
// // }

// // impl read_dispatcher{
// //     pub fn new() -> Self{
// //         return Self{
// //             types: HashMap::new(),
// //         }
// //     }
// //     pub fn new_type(&mut self, name: String, bases: Vec<String>, on_read: on_read_type)->(){
// //         self.types.insert(
// //             name.clone(),
// //             type_info{
// //                 name,
// //                 bases,
// //                 on_read,
// //             },
// //         );
// //     }
// //     pub fn read_object(&self, input: Rc<RefCell<dyn BufRead>>, name: String) -> Result<Object, Error>{
// //         let mut one_line = read_trimmed_line(input.clone());
// //         match self.types.get(&one_line){
// //             Some(typ) => {
// //                 return (typ.on_read)(
// //                     input.clone()
// //                 )
// //             }
// //             None => {
// //                 return Err(anyhow!("Unknown type: {}", one_line))
// //             }
// //         }
// //     }
// // }


// // #[cfg(test)]
// // mod tests {
// //     use super::*;
// //     use std::io::{Cursor, Read, Seek, SeekFrom, Write};

// //     #[test]
// //     fn it_works() {
// //         let result = add(2, 2);
// //         assert_eq!(result, 4);
// //     }

// //     #[test]
// //     fn it_works__a() {
// //         let dispatcher = read_dispatcher::new();
// //         dispatcher.new_type(
// //             String::from("int"),
// //             vec![],
// //             Rc::new(
// //                 |input: read_buf_type| {
// //                     let mut one_line = read_trimmed_line(input.clone());
// //                     let value = one_line.parse::<i32>()?;
// //                     let obj = Object::new();
// //                     obj.set_attr(
// //                         String::from("type"),
// //                         String::from("int"),
// //                     );
// //                     obj.set_attr(
// //                         String::from("value"),
// //                         value,
// //                     );
// //                 }
// //             ) as on_read_type
// //         )

// //         let mut c = Cursor::new(Vec::new());
// //         c.write_all("int\n0").unwrap();
// //         c.seek(SeekFrom::Start(0)).unwrap();

// //     }

// // }

// // pub fn add(left: u64, right: u64) -> u64 {
// //     left + right
// // }

// // trait type_can_be_used_for_io{
// //     fn type_name(&self) -> String;
// //     fn new_by_reading_from_stream(stream: read_buf_type) -> Self;
// //     fn write_to_stream(&self, stream: write_buf_type) -> Self;
// // }


// // Define a static shared value
// static counter: Arc<Mutex<Config>> = Arc::new(Mutex::new(Config { value: 10 }));

// // A simple struct to hold configuration data
// #[derive(Debug)]
// struct Config {
//     value: i32,
// }

// // static counter :Arc::<Mutex::<i32> >  = Arc::new(Mutex::new(0));

trait can_covert_str_to_printable_type {
    fn str_to_printable(&self, s: String) -> Result<
        Box<
            dyn ToString
        >
    >;
}

struct str_to_printable_converter<T>{
    value: Option<T>,
}

impl<T> str_to_printable_converter<T>{
    pub fn new() -> Self{
        return Self{
            value: None
        };
    }
}

impl <T: FromStr + ToString + 'static> can_covert_str_to_printable_type for str_to_printable_converter<T>
where
    <T as std::str::FromStr>::Err: std::error::Error + Send + Sync,
{
    fn str_to_printable(&self, s: String) -> Result<Box<dyn ToString>>
    {
        return Ok(
            Box::new(
                s.parse::<T>()?
            ) as Box<dyn ToString>
        );
    }
}

// fn str_to_printable<T: FromStr + ToString + 'static>(s: String) -> Result<Box<dyn ToString>, Error>
// where <T as std::str::FromStr>::Err: std::error::Error, <T as std::str::FromStr>::Err: Send, <T as std::str::FromStr>::Err: Sync
// {
//     return Ok(
//         Box::new(
//             s.parse::<T>()?
//         ) as Box<dyn ToString>
//     );
// }

pub struct type_info{
    type_name: String,
    bases: HashSet<String>,
    attrs: HashMap<
        String,
        Rc<
            dyn can_covert_str_to_printable_type
        >
    >,
}

pub struct all_types_context{
    types: HashMap<String, type_info>,
}

impl all_types_context{

    pub fn new() -> Self{
        return Self{
            types: HashMap::new(),
        }
    }

    pub fn new_type(&mut self, type_name: String, bases: HashSet<String>) -> (){
        let mut ti = type_info{
            type_name: type_name.clone(),
            bases: bases.clone(),
            attrs: HashMap::new(),
        };
        for base in bases.iter() {
            for (attr_name, attr_fn) in self.types.get(base).unwrap().attrs.iter(){
                ti.attrs.insert(attr_name.clone(), attr_fn.clone());
            }
        }
        // println!("inserting {:?}", type_name);
        self.types.insert(
            type_name.clone(),
            ti,
        );
        return;
    }

    pub fn new_attr<T: FromStr + ToString + 'static>(&mut self, attr_name: String, type_name: String) -> ()
    where <T as std::str::FromStr>::Err: std::error::Error, <T as std::str::FromStr>::Err: Send, <T as std::str::FromStr>::Err: Sync
    {
        // println!("updating {:?}", type_name);
        self.types.get_mut(
            &type_name.clone(),
        ).unwrap().attrs.insert(
            attr_name,
            // Rc::new(|x: String|str_to_printable::<T>(x))
            Rc::new(str_to_printable_converter::<T>::new())
            as
            Rc<dyn can_covert_str_to_printable_type>
        );
    }

    pub fn read_obj_from_stream(&self, stream: read_buf_type) -> Result<Object>{
        let type_name = read_trimmed_line(stream.clone())?;
        let ti = self.types.get(&type_name).unwrap();
        let mut obj = Object::new();
        obj.set_attr(&String::from("__type_name__"), ti.type_name.clone());
        let mut attrs = ti.attrs.clone();
        while attrs.len() != 0{
            let attr_name = read_trimmed_line(stream.clone())?;
            obj.set_attr(
                &attr_name,
                attrs.get(&attr_name).unwrap().str_to_printable(
                    read_trimmed_line(
                        stream.clone()
                    )?
                )?
            );
            attrs.remove(&attr_name);
        }
        return Ok(obj);
    }

    pub fn write_to_stream(&self, obj: Rc<RefCell<Object>>, stream: write_buf_type) -> Result<(), Error>{
        let type_name : String = obj.borrow_mut().get_attr::<String>(&String::from("__type_name__")).unwrap().to_string();
        stream.borrow_mut().write_all(type_name.as_bytes()).unwrap();
        stream.borrow_mut().write_all(b"\n").unwrap();
        let ti = self.types.get(&type_name).unwrap();
        let mut attr_names : Vec<String> = vec![];
        for (attr_name, attr_fn) in ti.attrs.iter(){
            attr_names.push(attr_name.clone());
        }
        attr_names.sort();
        for attr_name in attr_names.iter(){
            stream.borrow_mut().write_all(b"    ")?;
            stream.borrow_mut().write_all(attr_name.as_bytes())?;
            stream.borrow_mut().write_all(b"\n")?;
            stream.borrow_mut().write_all(b"    ")?;
            stream.borrow_mut().write_all(b"    ")?;
            stream.borrow_mut().write_all(
                obj.borrow_mut().get_attr::<
                    Box<
                        dyn ToString
                    >
                >(
                    &attr_name
                ).unwrap().to_string().as_bytes()
            )?;
            stream.borrow_mut().write_all(b"\n")?;
        }
        return Ok(());
    }

}

// #[cfg(test)]
// mod tests {
//     use super::*;

//     #[test]
//     fn it_works() {
//         let result = add(2, 2);
//         assert_eq!(result, 4);

//         // let context = all_types_context();
//         // context.new_type(
//         //     String::from("base"),
//         //     vec![]
//         // );
//         // context.add_static_attr::<i64>(
//         //     String::from("base"),
//         //     String::from("base_attr_i64")
//         // );
//         // context.new_type(String::from("der"), vec![String::from("base")]);
//         // context.add_static_attr::<i64>(String::from("der"), String::from("der_attr_i64"));



//         // let mut c = Cursor::new(Vec::new());
//         // c.write_all(&"").unwrap();
//         // c.seek(SeekFrom::Start(0)).unwrap();

//         // c.read_to_end(&mut out).unwrap();

//         // println!("{:?}", out);

//     }
// }
// use std::sync::RwLock;
// #[macro_use]
// extern crate lazy_static;

// lazy_static! {
//     static ref data: RwLock<Vec<i32>> = RwLock::new(vec![]);
// }

// pub fn append(number: i32){
//     println!("You wanted me to update to {}", number);

//     let mut w = data.write().unwrap();
//     w.push(number);
//     println!("After, it is: {:?}", w);
// }

// pub fn get_clone() -> Vec<i32> {
//     let r1 = data.read().unwrap();
//     return r1.clone();
// }

// fn main() {
//     print!("r1: {:?}", get_number());
//     update_it(20);
//     update_it(22);
//     print!("r2: {:?}", get_number());
// }

