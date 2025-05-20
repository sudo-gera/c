use std::fmt;
use std::str::*;
use types::*;

enum VesselTypeEnum{
    Liner,
    Tow,
    Tanker,
}

struct VesselTypeHolder{
    value: VesselTypeEnum,
}

impl FromStr for VesselTypeHolder{
    type Err = std::io::Error;

    fn from_str(s: &str) -> Result<Self, Self::Err>{
        match s{
            "liner" => Ok(Self{value: VesselTypeEnum::Liner}),
            "tow" => Ok(Self{value: VesselTypeEnum::Tow}),
            "tanker" => Ok(Self{value: VesselTypeEnum::Tanker}),
            _ => panic!()
        }
    }
}

impl fmt::Display for VesselTypeHolder{

    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let str = match self.value{
            VesselTypeEnum::Liner => String::from("liner"),
            VesselTypeEnum::Tow => String::from("tow"),
            VesselTypeEnum::Tanker => String::from("tanker"),
        };
        write!(f, "{}", str)
    }
}

pub fn init(context: &mut AllTypesContext){
    context.new_attr::<VesselTypeHolder>(String::from("vessel_type"), String::from("sheep"));
}
