use std::cell::*;
use anyhow::*;
use std::collections::*;
use object::*;
use std::rc::*;
use std::sync::*;
use std::io::*;



// // use base::add;

// use types::counter;

// fn main() {
//     println!("Hello, world!");
//     println!("{:?}", counter.borrow_ref());
//     // println!("{}", add(1,2));
// }

// use types::*;
// use std::sync::RwLock;
// #[macro_use]
// extern crate lazy_static;

// lazy_static! {
//     static ref _main_: RwLock<((),i32)> = RwLock::new( (append(2), 0));
// }

// fn main(){
//     _main_.write().unwrap().1 = 1;
//     println!("{:?}", get_clone());
// }

// use std::sync::RwLock;
// #[macro_use]
// extern crate lazy_static;

// lazy_static! {
//     static ref data: RwLock<Vec<i32>> = RwLock::new(vec![]);
// }

// fn update_it(number: i32) {
//     println!("You wanted me to update to {}", number);

//     let mut w = data.write().unwrap();
//     w.push(number);
//     println!("After, it is: {:?}", w);
// }

// fn get_number() -> Vec<i32> {
//     let r1 = data.read().unwrap();
//     return r1.clone();
// }

// fn main() {
//     print!("r1: {:?}", get_number());
//     update_it(20);
//     update_it(22);
//     print!("r2: {:?}", get_number());
// }
use std::io::*;
use types::*;

fn one_line_copy(stdin: read_buf_type, stdout: write_buf_type){
    let mut one_line = String::new();
    stdin.borrow_mut().read_line(&mut one_line).unwrap();
    stdout.borrow_mut().write_all(one_line.as_bytes()).unwrap();
}

fn main_with_streams(stdin: read_buf_type, stdout: write_buf_type){
    let mut context = all_types_context::new();
    transport_type::init(&mut context);
    speed_attr::init(&mut context);
    distance_attr::init(&mut context);
    plane_type::init(&mut context);
    train_type::init(&mut context);
    flight_range_attr::init(&mut context);
    load_capacity_attr::init(&mut context);
    wagon_number_attr::init(&mut context);

    let mut list = double_linked_list::double_linked_list::<Object>::new();
    let len = read_trimmed_line(stdin.clone()).unwrap().parse::<i32>().unwrap();
    for i in 0..len{
        let mut oilist = double_linked_list::double_linked_list::<Object>::from_one_item(
            context.read_obj_from_stream(stdin.clone()).unwrap()
        );
        list.concat_by_stealing_from(&mut oilist);
    }

    if len != 0{
        let mut iter = list.first_iter();
        loop {
            context.write_to_stream(
                iter.value_rcrc(),
                stdout.clone()
            );
            if iter == list.last_iter(){
                break;
            }
            iter = iter.next();
        }
    }
}

fn main(){
    main_with_streams(
        Rc::new(
            RefCell::new(
                stdin().lock(),
            )
        ) as read_buf_type,
        Rc::new(
            RefCell::new(
                stdout().lock(),
            )
        ) as write_buf_type,
    );
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn one_line() {
        let mut stdin = Rc::new(
            RefCell::new(
                Cursor::new(
                    Vec::new()
                ),
            )
        );
        let mut stdout = Rc::new(
            RefCell::new(
                Cursor::new(
                    Vec::new()
                ),
            )
        );
        let data = b"123\n";
        stdin.borrow_mut().write_all(data).unwrap();
        stdin.borrow_mut().seek(SeekFrom::Start(0)).unwrap();
        one_line_copy(
            stdin.clone() as read_buf_type,
            stdout.clone() as write_buf_type,
        );
        stdout.borrow_mut().seek(SeekFrom::Start(0)).unwrap();
        let mut out = Vec::new();
        stdout.borrow_mut().read_to_end(&mut out).unwrap();
        assert_eq!(data.to_vec(), out);
    }

    #[test]
    fn input_output_works() {
        // in-memory streams to replace stdin and stdout
        let mut stdin = Rc::new(
            RefCell::new(
                Cursor::new(
                    Vec::new()
                ),
            )
        );
        let mut stdout = Rc::new(
            RefCell::new(
                Cursor::new(
                    Vec::new()
                ),
            )
        );
        let data_in = b"2
plane
    distance
        2
    flight_range
        3
    load_capacity
        4
    speed
        1
train
    distance
        2
    speed
        1
    wagon_number
        3
";
        let data_out = b"plane
    distance
        2
    flight_range
        3
    load_capacity
        4
    speed
        1
train
    distance
        2
    speed
        1
    wagon_number
        3
";
        stdin.borrow_mut().write_all(data_in).unwrap();
        stdin.borrow_mut().seek(SeekFrom::Start(0)).unwrap();
        main_with_streams(
            stdin.clone() as read_buf_type,
            stdout.clone() as write_buf_type,
        );
        stdout.borrow_mut().seek(SeekFrom::Start(0)).unwrap();
        let mut out = Vec::new();
        stdout.borrow_mut().read_to_end(&mut out).unwrap();
        assert_eq!(data_out.to_vec(), out);
    }
}
