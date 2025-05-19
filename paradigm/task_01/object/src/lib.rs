use std::cell::RefCell;
use std::collections::HashMap;
use std::fmt::Debug;
use std::any::Any;
use std::io::repeat;
use std::rc::Rc;
use std::vec;


#[derive(Debug)]
pub struct Object{
    attrs: HashMap<String, Box<dyn Any>>
}

impl Object{
    pub fn new() -> Self{
        let mut this: Object = Self{
            attrs: HashMap::new(),
        };
        return this;
    }

    pub fn get_attr<T: 'static>(&mut self, key: &String) -> Option<&mut T>{
        println!("started get_attr");
        match self.attrs.get_mut(key){
            Some(val) => {
                match val.downcast_mut::<T>(){
                    Some(val) => {
                        println!("final value");
                        return Some(val);
                    }
                    None => {
                        println!("any.downcast -> none");
                        return None;
                    }
                }
            }
            None => {
                println!("hash_map.get_mut -> none");
                return None;
            }
        }
    }

    pub fn set_attr<T: 'static>(&mut self, key: &String, value: T) -> (){
        self.attrs.insert(
            key.to_string(),
            Box::new(value) as Box<dyn Any>
        );
    }
}

#[cfg(test)]
mod tests {
    use std::{any::TypeId, mem::swap};

    use super::*;

    #[test]
    fn get_and_set_attr() {
        let mut obj = Object::new();
        obj.set_attr(
            &String::from("k"),
            vec![1,2,3]
        );
        let a: &mut Vec<i32> = obj.get_attr::<Vec<i32>>(
            &String::from("k")
        ).unwrap();
        assert_eq!(*a, [1,2,3]);
        assert!(
            obj.get_attr::<Vec<u32>>(
                &String::from("k")
            ).is_none()
        );
        assert!(
            obj.get_attr::<Vec<i32>>(
                &String::from("k1")
            ).is_none()
        );
    }

    #[test]
    fn get_and_set_method() {
        let mut obj = Object::new();

        obj.set_attr(
            &String::from("k"),
            vec![1,2,3]
        );

        obj.set_attr(
            &String::from("m"),
            Rc::new(
                |obj: &mut Object, v: &mut Vec<i32>| {
                    let a = obj.get_attr::<Vec<i32>>(
                        &String::from("k")
                    ).unwrap();
                    swap(a, v);
                }
            ) as
            Rc<dyn Fn(&mut Object, &mut Vec<i32>)->()>
        );

        let mut v = vec![4,5,6];

        obj.get_attr::<
            Rc<dyn Fn(&mut Object, &mut Vec<i32>)->()>
        >(
            &String::from("m")
        ).unwrap().clone()(&mut obj, &mut v);

        let a: &mut Vec<i32> = obj.get_attr::<Vec<i32>>(
            &String::from("k")
        ).unwrap();
        assert_eq!(*a, [4,5,6]);
        assert_eq!(v, [1,2,3]);
    }
}
