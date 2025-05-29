from __future__ import annotations
import typing
import weakref

object_descriptor_get = typing.TypeVar('object_descriptor_get')
object_descriptor_set = typing.TypeVar('object_descriptor_set')

class object_descriptor(typing.Generic[object_descriptor_get, object_descriptor_set]):
    def __init__(self) -> None:
        self.object_to_object_descriptor : weakref.WeakValueDictionary[int, base_object_descriptor[object_descriptor_get, object_descriptor_set]] = weakref.WeakValueDictionary()

    @typing.overload
    def __get__(self, instance: None, instance_class: typing.Type[object]) -> object_descriptor[object_descriptor_get, object_descriptor_set]:
        ...

    @typing.overload
    def __get__(self, instance: object, instance_class: typing.Type[object]) -> object_descriptor_get:
        ...

    def __get__(self, instance: object|None, instance_class: typing.Type[object]) -> object_descriptor_get|object_descriptor[object_descriptor_get, object_descriptor_set]:
        if instance is None:
            return self
        else:
            return self.object_to_object_descriptor[id(instance)].object_get()
    
    def __set__(self, instance: object, value: object_descriptor_set) -> None:
        return self.object_to_object_descriptor[id(instance)].object_set(value)

class base_object_descriptor(typing.Generic[object_descriptor_get, object_descriptor_set]):
    def object_get(self) -> object_descriptor_get:
        assert False
    
    def object_set(self, value: object_descriptor_set) -> None:
        assert False

    def init(self, instance: object, desc: object_descriptor[object_descriptor_get, object_descriptor_set]) -> None:
        desc.object_to_object_descriptor[id(instance)] = self

class user_object_descriptor(base_object_descriptor[bytes, str]):
    def __init__(self) -> None:
        self.value = ''

    def object_get(self) -> bytes:
        return self.value.encode()
    
    def object_set(self, value: str) -> None:
        self.value = value

# user_object_attr : object_descriptor[bytes, str] = object_descriptor()

class user_object:
    attr : object_descriptor[bytes, str] = object_descriptor()

    def __init__(self) -> None:
        self.attr_object = user_object_descriptor()
        self.attr_object.init(self, type(self).attr)
        self.attr=''
        print(self.attr+b'')

a=user_object()

