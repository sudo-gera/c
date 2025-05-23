use std::collections::HashMap;
use std::fmt::Debug;
use std::any::Any;


#[derive(Debug)]
pub struct Object{
    attrs: HashMap<String, Box<dyn Any>>
}

impl Default for Object {
    fn default() -> Self {
        Self::new()
    }
}

impl Object{
    pub fn new() -> Self{
        let this: Object = Self{
            attrs: HashMap::new(),
        };
        this
    }

    pub fn get_attr<T: 'static>(&self, key: &String) -> Option<&T>{
        // println!("get key={:?}, size={:?}", key, self.attrs.len());
        match self.attrs.get(key){
            Some(val) => {
                match val.downcast_ref::<T>(){
                    Some(val) => {
                        Some(val)
                    }
                    None => {
                        // println!("wrong type");
                        None
                    }
                }
            }
            None => {
                // println!("no key");
                None
            }
        }
    }

    pub fn get_attr_mut<T: 'static>(&mut self, key: &String) -> Option<&mut T>{
        // println!("get key={:?}, size={:?}", key, self.attrs.len());
        match self.attrs.get_mut(key){
            Some(val) => {
                match val.downcast_mut::<T>(){
                    Some(val) => {
                        Some(val)
                    }
                    None => {
                        // println!("wrong type");
                        None
                    }
                }
            }
            None => {
                // println!("no key");
                None
            }
        }
    }

    pub fn set_attr<T: 'static>(&mut self, key: &String, value: T){
        println!("set key={:?}, size={:?}", key, self.attrs.len());
        self.attrs.insert(
            key.to_string(),
            Box::new(value) as Box<dyn Any>
        );
    }
}

#[cfg(test)]
mod tests {
    use std::{mem::swap};

    use super::*;
    use std::rc::*;

    #[test]
    fn get_and_set_attr() {
        let mut obj = Object::new();
        obj.set_attr(
            &String::from("k"),
            vec![1,2,3]
        );
        let a = obj.get_attr::<Vec<i32>>(
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
                    let a = obj.get_attr_mut::<Vec<i32>>(
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

        let a = obj.get_attr::<Vec<i32>>(
            &String::from("k")
        ).unwrap();
        assert_eq!(*a, [4,5,6]);
        assert_eq!(v, [1,2,3]);
    }
}
