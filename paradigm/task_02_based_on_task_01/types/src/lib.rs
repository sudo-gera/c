use std::fmt;
use std::str::*;
use std::cell::*;
use anyhow::*;
use std::collections::*;
use object::*;
use std::any::*;
use std::rc::*;
use std::io::*;
use anyhow::Result;

pub type ReadStream = Rc<RefCell<dyn BufRead>>;
pub type WriteStream = Rc<RefCell<dyn Write>>;

pub fn read_trimmed_line(input: ReadStream) -> Result<String>{
    let mut one_line = String::new();
    let mut input_binding = input.borrow_mut();
    input_binding.read_line(&mut one_line)?;
    drop(input_binding);
    one_line = one_line.to_string().trim().to_string();
    Ok(one_line)
}

pub trait CanBeAttr : ToString{
    fn to_rc_any(&self) -> Rc<dyn Any>;
}

struct AttrWrapper<T>{
    value: Rc<T>
}

impl<T> AttrWrapper<T>{
    pub fn new(value: T) -> Self{
        AttrWrapper{
            value: Rc::new(
                value
            ),
        }
    }
}

impl<T: ToString + 'static> fmt::Display for AttrWrapper<T>{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.value.to_string())
    }
}

impl <T: ToString + 'static> CanBeAttr for AttrWrapper<T>{
    fn to_rc_any(&self) -> Rc<dyn Any>{
        self.value.clone() as Rc<dyn Any>
    }
}

pub type InitStep = Rc<
    dyn Fn(
        &mut Object
    )
>;


trait CanConvertStrToAttr {
    fn str_to_printable(&self, s: String) -> Result<
        Rc<
            RefCell<
                dyn CanBeAttr
            >
        >
    >;
}


struct StrToAttrConverter<T>{
    _value: Option<T>,
}

impl<T> StrToAttrConverter<T>{
    pub fn new() -> Self{
        Self{
            _value: None
        }
    }
}

impl <T: FromStr + ToString + 'static> CanConvertStrToAttr for StrToAttrConverter<T>
where
    <T as std::str::FromStr>::Err: std::error::Error + Send + Sync,
{
    fn str_to_printable(&self, s: String) -> Result<Rc<RefCell<dyn CanBeAttr>>>
    {
        Ok(
            Rc::new(
                RefCell::new(
                    AttrWrapper::new(
                        s.parse::<T>()?
                    )
                )
            ) as Rc<RefCell<dyn CanBeAttr>>
        )
    }
}

pub struct TypeInfo{
    type_name: String,
    bases: HashSet<String>,
    attrs: HashMap<
        String,
        Rc<
            dyn CanConvertStrToAttr
        >
    >,
    init_steps: Vec<InitStep>,
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
            init_steps: Vec::new(),
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
            Rc::new(
                StrToAttrConverter::<
                    T
                >::new()
            )
            as
            Rc<dyn CanConvertStrToAttr>
        );
    }


    pub fn new_attr_with_default_value<T: Clone + 'static>(&mut self, attr_name: String, value: T, type_name: String){
        self.types.get_mut(&type_name).unwrap().init_steps.push(
            Rc::new(
                move |obj: &mut Object| {
                    obj.set_attr(&attr_name, value.clone());
                }
            )
            as
            InitStep
        );
    }

    fn get_all_attrs(&self, type_name: String) -> Result<
        HashMap<
            String,
            Rc<
                dyn CanConvertStrToAttr
            >
        >
    >{
        let ti = self.types.get(&type_name).unwrap();
        let mut attrs = ti.attrs.clone();
        let type_names = self.get_all_base_type_names(type_name.clone())?;
        for cur_type_ in type_names.iter(){
            let cur_type : &String = cur_type_;
            for (attr_name, attr_fn) in self.types.get(cur_type).unwrap().attrs.iter(){
                attrs.insert(attr_name.to_string(), attr_fn.clone());
            }
        }
        Ok(attrs)
    }

    fn get_all_base_type_names(&self, type_name: String) -> Result<HashSet<String>>{
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
        }
        Ok(types_watched)
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
        let type_names = self.get_all_base_type_names(type_name.clone())?;
        for cur_type in type_names.iter(){
            for init_step in self.types.get(cur_type).unwrap().init_steps.iter(){
                init_step.clone()(&mut obj);
            }
        }
        Ok(obj)
    }
}

pub type WriteToStreamMethod = Rc<dyn Fn(&AllTypesContext,Rc<RefCell<Object>>,WriteStream) -> Result<()>>;


fn write_to_stream(context: &AllTypesContext, obj: Rc<RefCell<Object>>, stream: WriteStream) -> Result<()>{
    let type_name : String = obj.borrow_mut().get_attr::<String>(&String::from("__type_name__")).unwrap().to_string();
    stream.borrow_mut().write_all(type_name.as_bytes()).unwrap();
    stream.borrow_mut().write_all(b"\n").unwrap();
    let mut attr_names : Vec<String> = vec![];
    for (attr_name, _attr_fn) in context.get_all_attrs(type_name)?.iter(){
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
                Rc<
                    RefCell<
                        dyn CanBeAttr
                    >
                >
            >(
                attr_name
            ).unwrap().borrow_mut().to_string().as_bytes()
        )?;
        stream.borrow_mut().write_all(b"\n")?;
    }
    Ok(())
}

pub fn init(context: &mut AllTypesContext){
    context.new_type(String::from("object"), HashSet::new());
    context.new_attr_with_default_value(
        String::from("write_to_stream"),
        Rc::new(write_to_stream)
        as
        WriteToStreamMethod,
        String::from("object")
    );
}
