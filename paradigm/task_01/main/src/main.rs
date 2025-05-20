use std::cell::*;
use std::rc::*;
use std::io::*;
use types::*;
use list_of_objects::*;

fn create_context() -> AllTypesContext{
    let mut context = AllTypesContext::new();
    transport_type::init(&mut context);
    speed_attr::init(&mut context);
    distance_attr::init(&mut context);
    plane_type::init(&mut context);
    train_type::init(&mut context);
    flight_range_attr::init(&mut context);
    load_capacity_attr::init(&mut context);
    wagon_number_attr::init(&mut context);
    context
}

fn main_with_streams(stdin: ReadStream, stdout: WriteStream){
    let context = create_context();
    let mut list = read_all_objects_from_stream(
        stdin.clone(),
        &context
    ).unwrap();
    write_all_objects_to_stream(
        &mut list,
        stdout.clone(),
        &context
    ).unwrap();
}

fn main(){
    main_with_streams(
        Rc::new(
            RefCell::new(
                stdin().lock(),
            )
        ) as ReadStream,
        Rc::new(
            RefCell::new(
                stdout().lock(),
            )
        ) as WriteStream,
    );
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn input_output_works() {
        // in-memory streams to replace stdin and stdout
        let stdin = Rc::new(
            RefCell::new(
                Cursor::new(
                    Vec::new()
                ),
            )
        );
        let stdout = Rc::new(
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
            stdin.clone() as ReadStream,
            stdout.clone() as WriteStream,
        );
        stdout.borrow_mut().seek(SeekFrom::Start(0)).unwrap();
        let mut out = Vec::new();
        stdout.borrow_mut().read_to_end(&mut out).unwrap();
        assert_eq!(data_out.to_vec(), out);
    }
}
