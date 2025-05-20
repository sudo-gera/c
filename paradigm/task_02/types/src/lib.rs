use std::str::*;
use std::cell::*;
use anyhow::*;
use std::collections::*;
use object::*;
use std::rc::*;
use std::io::*;
use anyhow::Error;
use anyhow::Result;

pub type ReadStream = Rc<RefCell<dyn BufRead>>;
pub type WriteStream = Rc<RefCell<dyn Write>>;

pub fn read_trimmed_line(input: ReadStream) -> Result<String, Error>{
    let mut one_line = String::new();
    let mut input_binding = input.borrow_mut();
    input_binding.read_line(&mut one_line)?;
    drop(input_binding);
    one_line = one_line.to_string().trim().to_string();
    Ok(one_line)
}

trait CanCovertStrToPrintableType {
    fn str_to_printable(&self, s: String) -> Result<
        Box<
            dyn ToString
        >
    >;
}

struct StrToPrintableConverter<T>{
    _value: Option<T>,
}

impl<T> StrToPrintableConverter<T>{
    pub fn new() -> Self{
        Self{
            _value: None
        }
    }
}

impl <T: FromStr + ToString + 'static> CanCovertStrToPrintableType for StrToPrintableConverter<T>
where
    <T as std::str::FromStr>::Err: std::error::Error + Send + Sync,
{
    fn str_to_printable(&self, s: String) -> Result<Box<dyn ToString>>
    {
        Ok(
            Box::new(
                s.parse::<T>()?
            ) as Box<dyn ToString>
        )
    }
}

pub struct TypeInfo{
    type_name: String,
    bases: HashSet<String>,
    attrs: HashMap<
        String,
        Rc<
            dyn CanCovertStrToPrintableType
        >
    >,
}

pub struct AllTypesContext{
    types: HashMap<String, TypeInfo>,
}

impl Default for AllTypesContext {
    fn default() -> Self {
        Self::new()
    }
}

impl AllTypesContext{

    pub fn new() -> Self{
        Self{
            types: HashMap::new(),
        }
    }

    pub fn new_type(&mut self, type_name: String, bases: HashSet<String>){
        let ti = TypeInfo{
            type_name: type_name.clone(),
            bases,
            attrs: HashMap::new(),
        };
        self.types.insert(
            type_name.clone(),
            ti,
        );
    }

    pub fn new_attr<T: FromStr + ToString + 'static>(&mut self, attr_name: String, type_name: String)
    where <T as std::str::FromStr>::Err: std::error::Error, <T as std::str::FromStr>::Err: Send, <T as std::str::FromStr>::Err: Sync
    {
        self.types.get_mut(
            &type_name.clone(),
        ).unwrap().attrs.insert(
            attr_name,
            Rc::new(StrToPrintableConverter::<T>::new())
            as
            Rc<dyn CanCovertStrToPrintableType>
        );
    }

    fn get_all_attrs(&self, type_name: String) -> Result<
        HashMap<
            String,
            Rc<
                dyn CanCovertStrToPrintableType
            >
        >
    >{
        let ti = self.types.get(&type_name).unwrap();
        let mut attrs = ti.attrs.clone();
        let mut types_watched : HashSet<String> = HashSet::from([]);
        let mut types_not_watched : HashSet<String> = HashSet::from([type_name]);
        while !types_not_watched.is_empty(){
            let cur_type = types_not_watched.iter().next().unwrap().clone();
            types_not_watched.remove(&cur_type);
            types_watched.insert(cur_type.clone());
            for cur_base in self.types.get(&cur_type).unwrap().bases.iter(){
                if !types_watched.contains(cur_base){
                    types_not_watched.insert(cur_base.clone());
                }
            }
            for (attr_name, attr_fn) in self.types.get(&cur_type).unwrap().attrs.iter(){
                attrs.insert(attr_name.to_string(), attr_fn.clone());
            }
        }
        Ok(attrs)
    }

    pub fn read_obj_from_stream(&self, stream: ReadStream) -> Result<Object>{
        let type_name = read_trimmed_line(stream.clone())?;
        let ti = self.types.get(&type_name).unwrap();
        let mut obj = Object::new();
        obj.set_attr(&String::from("__type_name__"), ti.type_name.clone());
        let mut attrs = self.get_all_attrs(type_name.clone())?;
        while !attrs.is_empty(){
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
        Ok(obj)
    }

    pub fn write_to_stream(&self, obj: Rc<RefCell<Object>>, stream: WriteStream) -> Result<(), Error>{
        let type_name : String = obj.borrow_mut().get_attr::<String>(&String::from("__type_name__")).unwrap().to_string();
        stream.borrow_mut().write_all(type_name.as_bytes()).unwrap();
        stream.borrow_mut().write_all(b"\n").unwrap();
        let mut attr_names : Vec<String> = vec![];
        for (attr_name, _attr_fn) in self.get_all_attrs(type_name)?.iter(){
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
                    attr_name
                ).unwrap().to_string().as_bytes()
            )?;
            stream.borrow_mut().write_all(b"\n")?;
        }
        Ok(())
    }

}
