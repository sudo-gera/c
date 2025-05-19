// use std::cell::*;
// use anyhow::*;
// use std::collections::*;
// use object::*;
// use std::rc::*;
// use std::sync::*;
// use std::io::*;

// // pub fn add(left: u64, right: u64) -> u64 {
// //     left + right
// // }


// type read_buf_type = Rc<RefCell<dyn BufRead>>;
// type write_buf_type = Rc<RefCell<BufWriter<dyn Write>>>;


// // type on_read_type = Rc<dyn Fn(read_buf_type)->Result<Object, Error>>;

// // pub fn read_trimmed_line(read_buf_type) -> Result<String, Error>{
// //     let mut one_line = String::new();
// //     let mut input_binding = input.borrow_mut();
// //     input_binding.read_line(&mut one_line)?;
// //     drop(input_binding);
// //     one_line = one_line.to_string().trim().to_string();
// //     return Ok(one_line);
// // }

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

// struct all_types_context{

// }

// impl all_types_context{

//     pub fn create_type(&mut self, type_name: String, bases: Vec<String>) -> (){
//     }

//     // pub fn add_dynamic_attr(&mut self, type_name: String, attr_name: String, attr_type_name: String) -> (){
        
//     // }

//     pub fn add_static_attr<T>(&mut self, type_name: String, attr_name: String) -> (){
//     }

// }

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
use std::sync::RwLock;
#[macro_use]
extern crate lazy_static;

lazy_static! {
    static ref data: RwLock<Vec<i32>> = RwLock::new(vec![]);
}

pub fn append(number: i32){
    println!("You wanted me to update to {}", number);

    let mut w = data.write().unwrap();
    w.push(number);
    println!("After, it is: {:?}", w);
}

pub fn get_clone() -> Vec<i32> {
    let r1 = data.read().unwrap();
    return r1.clone();
}

// fn main() {
//     print!("r1: {:?}", get_number());
//     update_it(20);
//     update_it(22);
//     print!("r2: {:?}", get_number());
// }
