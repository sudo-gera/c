from __future__ import annotations
from operator import *
from itertools import *
from functools import *
from typing_extensions import *
import pathlib
import json
import typing as typing_basic
import typing_extensions
import sys
import random
from dataclasses import dataclass, replace
from urllib.request import urlopen

if sys.version_info < (3, 11):
    from collections.abc import Callable as caCallable
    call_R = TypeVar("call_R")
    call_P = ParamSpec("call_P")
    def call(obj: caCallable[call_P, call_R], /, *args: call_P.args, **kwargs: call_P.kwargs) -> call_R:
        return obj(*args, **kwargs)

get_tqdm_T = TypeVar('get_tqdm_T')
def get_tqdm() -> Callable[[get_tqdm_T], get_tqdm_T]:
    identity_T = TypeVar('identity_T')
    def identity(arg: identity_T) -> identity_T:
        return arg

    try:
        from tqdm import tqdm
        return tqdm
    except Exception as e:
        print(f'failed to import tqdm. {type(e).__name__}:{e}', file=sys.stderr)
        return identity_T
tqdm = get_tqdm()


# Category = Literal[
#     'Letter keys', 'Generic desktop keys', 'Mouse keys',
#     'Arrow keys', 'Mouse buttons', 'Media controls',
#     'International keys', 'Generic GUI application control keys',
#     'Japanese', 'Others', 'Keys in pc keyboards',
#     'Controls and symbols', 'Software function',
#     'D-pad', 'Function keys', 'Modifier keys',
#     'Sticky modifier keys', 'Keypad keys',
#     'Application launch keys', 'Remote control buttons',
#     'Disable this key', 'Number keys'
# ]
# Modifiers = Literal[
#     'caps_lock', 'left_control',
#     'left_shift', 'left_option',
#     'left_command', 'right_control',
#     'right_shift', 'right_option',
#     'right_command', 'fn'
# ]
# ButtonTypes = Literal[
#     'key_code',
#     'consumer_key_code',
#     'pointing_button',
#     'generic_desktop',
#     'apple_vendor_top_case_key_code'
# ]

Layouts = Literal['en', 'ru']
PossibleFingerCountValues = Literal[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# AllButtonsButtonDescriptionData = TypedDict('AllButtonsButtonDescriptionData', {'key_code': str})
# AllButtonsButtonDescription = TypedDict(
#     'AllButtonsButtonDescription',
#     {'label': str, 'category': Category, 'not_from': bool, 'unsafe_from': bool, 'not_to': bool, 'data': list[AllButtonsButtonDescriptionData]}
# )

home = pathlib.Path.home()
conf_file_path = home / '.config' / 'karabiner' / 'assets' / 'complex_modifications' / 'auto_generated_conf.json'
dir_with_this_file = pathlib.Path(__file__).resolve().parent
buttons_list_file_path = dir_with_this_file / 'simple_modifications.json'

# @dataclasses.dataclass
# class ButtonDescriptionData:
#     key_code: str

# @dataclasses.dataclass
# class ButtonDescription:
#     label: str
#     category: Category
#     not_from: bool
#     unsafe_from: bool
#     not_to: bool
#     pair: ButtonPair

def get_buttons_list_bin_data() -> bytes:
    try:
        buttons_list_bin_data = urlopen('https://raw.githubusercontent.com/pqrs-org/Karabiner-Elements/refs/heads/main/src/apps/SettingsWindow/Resources/simple_modifications.json').read()
        assert isinstance(buttons_list_bin_data, bytes)
        json.loads(buttons_list_bin_data)
    except Exception as e:
        print(f'failed to load keys. {type(e).__name__}:{e}')
        with buttons_list_file_path.open('rb') as file:
            buttons_list_bin_data = file.read()
    return buttons_list_bin_data
buttons_list_bin_data = get_buttons_list_bin_data()

def get_buttons_list_json_data() -> list[Any]:
    assert buttons_list_bin_data is not None
    buttons_list_json_data = json.loads(buttons_list_bin_data)

    with buttons_list_file_path.open('wb') as file:
        file.write(buttons_list_bin_data)

    assert isinstance(buttons_list_json_data, list)
    return buttons_list_json_data
buttons_list_json_data = get_buttons_list_json_data()

# true_or_missing_keys : Final = ('not_from', 'not_to', 'unsafe_from')

button_key_t = NewType('button_key_t', str)
button_value_t = NewType('button_value_t', str)
category_t = NewType('category_t', str)

@dataclass(frozen=True)
class Button:
    label: bool
    not_from: bool
    not_to: bool
    unsafe_from: bool
    button_key: button_key_t
    button_value: button_value_t
    category: category_t

def get_buttons() -> dict[str, Button]:
    buttons: dict[str, Button] = {}

    current_category : str|None = None
    for button_json in buttons_list_json_data:
        assert isinstance(button_json, dict)
        if 'category' in button_json.keys():
            assert set(button_json.keys()) == {'category'}
            category = button_json['category']
            assert isinstance(category, str)
            current_category = category
        else:
            category = current_category
            assert category is not None
            true_or_missing_keys : Final = {'not_from', 'not_to', 'unsafe_from'}
            must_present_keys : Final = {'label', 'data'}
            assert must_present_keys <= button_json.keys() <= must_present_keys | true_or_missing_keys
            for key in true_or_missing_keys:
                assert button_json.get(key, True) is True
            not_from = button_json.get('not_from', False)
            not_to = button_json.get('not_to', False)
            unsafe_from = button_json.get('unsafe_from', False)
            if not_from:
                continue
            label : str = button_json['label']
            assert isinstance(label, str)
            data : list[dict[str, str]] = button_json['data']
            assert isinstance(data, list)
            assert len(data) == 1
            assert isinstance(data[0], dict)
            assert len(data[0]) == 1
            [(key, value)] = [*data[0].items()]
            assert isinstance(key, str)
            assert isinstance(value, str)
            assert key not in buttons
            buttons[value]=Button(
                label=label,
                not_from=not_from,
                not_to=not_to,
                unsafe_from=unsafe_from,
                button_key=button_key_t(key),
                button_value=button_value_t(value),
                category=category_t(current_category),
            )
    
    return buttons
buttons = get_buttons()
        
ButtonPair = Annotated[
    tuple[str, str],
    [
        (button.button_key, buttons.button_values)
        for button in buttons.values()
    ]
]

class input_event_t:
    caps_lock: bool
    left_control: bool
    left_shift: bool
    left_option: bool
    left_command: bool
    right_control: bool
    right_shift: bool
    right_option: bool
    right_command: bool
    fn: bool
    layout: Layouts
    exact_finger_count: PossibleFingerCountValues
    button_pair: button_pair_t

def all_values_impl(x: Any) -> Any:
    if isinstance(x, str):
        x = eval(x)
    tx = x
    if tx is bool:
        return (False, True)
    if isinstance(tx, type(Literal[None])):
        return x.__args__
    if isinstance(tx, type(Annotated[type, None])):
        return x.__metadata__[0]
    print(repr(x))
    assert False

def all_values(x: Any) -> tuple[Any, ...]:
    return tuple([*all_values_impl(x)])

class product_with_len:
    def __init__(self, *args_: Any) -> None:
        args = [list(arg) for arg in args_]
        self.len = reduce(mul, [len(arg) for arg in args], 1)
        self.generator = product(*args)
    def __iter__(self) -> product_with_len:
        return self
    def __next__(self) -> Any:
        return self.generator.__next__()
    def __len__(self) -> int:
        return self.len
    def __length_hint__(self) -> int:
        return self.len

all_events_generator = product_with_len(*[
    all_values(eval(attr_type))
    for attr_type in input_event_t.__annotations__.values()
])


@dataclass(frozen=True)
class event_t:
    caps_lock: bool
    left_control: bool
    left_shift: bool
    left_option: bool
    left_command: bool
    right_control: bool
    right_shift: bool
    right_option: bool
    right_command: bool
    fn: bool
    layout: Layouts
    multitouch_extension_finger_count_total: PossibleFingerCountValues
    button_pair: ButtonPair

# @dataclass(frozen=True)
# class output_event_t:
#     caps_lock: bool
#     left_control: bool
#     left_shift: bool
#     left_option: bool
#     left_command: bool
#     right_control: bool
#     right_shift: bool
#     right_option: bool
#     right_command: bool
#     fn: bool
#     layout: Layouts
#     button_key: button_key_t
#     button_value: button_value_t

#######################################################################################################################################

def decide_what_to_do(input_event: event_t) -> tuple[event_t]:
    output_events : tuple[event_t] = (input_event,)

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                button_key='key_code',
                button_value='left_command',
            )
        ]
        if output_event.button_pair[1] == 'left_fn' else
        [
            replace(
                output_event,
                button_key='key_code',
                button_value='left_command',
            ),
            replace(
                output_event,
                button_key='key_code',
                button_value='left_control',
            ),
        ]
        if output_event.button_pair[1] == 'left_option' else
        [
            replace(
                output_event,
                button_key='key_code',
                button_value='left_option',
            ),
        ]
        if output_event.button_pair[1] == 'left_command' else
        [
            replace(
                output_event,
                button_key='key_code',
                button_value='right_option',
            ),
        ]
        if output_event.button_pair[1] == 'right_command' else
        [
            replace(
                output_event,
                button_key='key_code',
                button_value='right_command',
            ),
        ]
        if output_event.button_pair[1] == 'right_option' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                left_command=output_event.left_option,
                left_option=output_event.left_command,
                right_command=output_event.right_option,
                right_option=output_event.right_command,
            ),
        ]
        if output_event.button_pair[1] == 'delete_or_backspace' or buttons[tuple(output_event.button_pair)[1]].category == 'Arrow keys' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                button_key = 'page_up',
            ),
        ]
        if input_event.multitouch_extension_finger_count_total >= 1 and input_event.button_pair[1] == 'up_arrow' else
        [
            replace(
                output_event,
                button_key = 'page_down',
            ),
        ]
        if input_event.multitouch_extension_finger_count_total >= 1 and input_event.button_pair[1] == 'down_arrow' else
        [
            replace(
                output_event,
                button_key = 'page_left',
            ),
        ]
        if input_event.multitouch_extension_finger_count_total >= 1 and input_event.button_pair[1] == 'home' else
        [
            replace(
                output_event,
                button_key = 'page_right',
            ),
        ]
        if input_event.multitouch_extension_finger_count_total >= 1 and input_event.button_pair[1] == 'end' else
        [
            replace(
                output_event,
                button_key = 'delete_or_backspace',
            ),
        ]
        if input_event.multitouch_extension_finger_count_total >= 1 and input_event.button_pair[1] == 'delete_forward' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                left_option=True,
                left_shift=True,
                fn=True,
            ),
        ]
        if buttons[tuple(input_event.button_pair)[1]].category == 'Function keys' and input_event.button_pair[1] in 'f1 f2 f11 f12'.split() else
        [
            replace(
                output_event,
                fn=True,
            ),
        ]
        if buttons[tuple(input_event.button_pair)[1]].category == 'Function keys' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                button_pair = ('key_code', 'slash'),
                left_shift = False,
                right_shift = False,
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == '6' and (input_event.left_shift or input_event.right_shift) else
        [
            replace(
                output_event,
                button_pair = ('key_code', 'slash'),
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == '7' and (input_event.left_shift or input_event.right_shift) else
        [
            replace(
                output_event,
                button_pair = ('key_code', '6'),
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == 'slash' and (input_event.left_shift or input_event.right_shift) else
        [
            replace(
                output_event,
                button_pair = ('key_code', '7'),
                left_shift = True,
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == 'slash' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    return output_events

#######################################################################################################################################

@dataclass(frozen=True)
class optimized_event_k:
    caps_lock: tuple[bool, tuple[bool, ...]]
    left_control: tuple[bool, tuple[bool, ...]]
    left_shift: tuple[bool, tuple[bool, ...]]
    left_option: tuple[bool, tuple[bool, ...]]
    left_command: tuple[bool, tuple[bool, ...]]
    right_control: tuple[bool, tuple[bool, ...]]
    right_shift: tuple[bool, tuple[bool, ...]]
    right_option: tuple[bool, tuple[bool, ...]]
    right_command: tuple[bool, tuple[bool, ...]]
    fn: tuple[bool, tuple[bool, ...]]
    layout: tuple[bool, tuple[Layouts, ...]]
    multitouch_extension_finger_count: tuple[bool,tuple[PossibleFingerCountValues, ...]]
    button_pair: ButtonPair

@dataclass(frozen=True)
class optimized_event_v:
    caps_lock: bool
    left_control: bool
    left_shift: bool
    left_option: bool
    left_command: bool
    right_control: bool
    right_shift: bool
    right_option: bool
    right_command: bool
    fn: bool
    button_pair: ButtonPair

print('making decicions...')

optimized_manipulators = dict[event_t, tuple[event_t, ...]]

for from_event_params in tqdm(product_with_len(*[
        all_values(attr_type)
        for attr_type in event_t.__annotations__.values()
    ])):
    from_event = event_t(*from_event_params)















#     from_event = event_t(*from_event_params)
#     to_events = decide_what_to_do(from_event)
#     if from_event != to_event:
#         manipulators.append((from_event, to_event))
#     # manipulators.append((from_event, to_event))


# # @call
# # def all_buttons() -> list[AllButtonsButtonDescription]:
# #     @call
# #     def data() -> tuple[Any, bytes]:
# #         try:
# #             bin_data = urlopen('https://raw.githubusercontent.com/pqrs-org/Karabiner-Elements/refs/heads/main/src/apps/SettingsWindow/Resources/simple_modifications.json').read()
# #             return json.loads(bin_data), bin_data
# #         except Exception as e:
# #             print(f'failed to load keys. {type(e).__name__}:{e}')
# #             with all_possible_keys_file_path.open('rb') as file:
# #                 bin_data = file.read()
# #                 return json.loads(bin_data), bin_data
# #     j_data, bin_data = data

# #     with all_possible_keys_file_path.open('wb') as file:
# #         file.write(bin_data)

# #     all_buttons : list[ButtonDescription] = []
# #     category = j_data[0]
# #     assert 'category' in category
# #     for button in j_data:
# #         if 'category' in button:
# #             category = button
# #         else:
# #             all_buttons.append(category | button)

# #     true_or_missing_keys : Final = ('not_from', 'not_to', 'unsafe_from')

# #     for true_or_missing_key in true_or_missing_keys:
# #         assert all([
# #             isinstance(button.get(true_or_missing_key, True), bool)
# #             and
# #             button.get(true_or_missing_key, True) == True
# #             for button in all_buttons
# #         ])

# #         for button in all_buttons:
# #             button[true_or_missing_key] = button.get(true_or_missing_key, False)

# #     for button in all_buttons:
# #         assert set(button.keys()) == set(AllButtonsButtonDescription.__annotations__.keys())

# #     assert all([
# #         isinstance(button['data'], list)
# #         and (
# #             button['not_from']
# #             or
# #             len(button['data']) == 1
# #             and
# #             isinstance(button['data'][0], dict)
# #             and
# #             frozenset(button['data'][0].keys()) in {
# #                 frozenset([button_type])
# #                 for button_type in typing.cast(typing.Any, ButtonTypes).__args__
# #             }
# #             and
# #             len(button['data'][0].values()) == 1
# #             and
# #             isinstance([*button['data'][0].values()][0], str)
# #         )
# #         for button in all_buttons
# #     ])

# #     return all_buttons

# # category_by_button_pair : dict[ButtonPair, Category] = {
# #     cast(
# #         tuple[str, str],
# #         tuple([
# #             *button['data'][0].keys()
# #         ] + [
# #             *button['data'][0].values()
# #         ])
# #     ):button['category']
# #     for button in all_buttons if not button['not_from']
# # }

# # ButtonPair = Annotated[
# #     tuple[str, str],
# #     list(category_by_button_pair)
# # ]

# # assert sorted(typing.cast(typing.Any, ButtonPair).__metadata__[0]) == sorted(category_by_button_pair)

# # categories = {
# #     button['category']
# #     for button in all_buttons
# # }

# # def all_values_impl(x: typing.Any) -> typing.Any:
# #     if isinstance(x, str):
# #         x = eval(x)
# #     tx = x
# #     if tx is bool:
# #         # if random.random() < 0.1:
# #             # return (False, True)
# #         # return (False, )
# #         return (False, True)
# #     if isinstance(tx, type(typing.Literal[None])):
# #         return x.__args__
# #     if isinstance(tx, type(typing.Annotated[type, None])):
# #         return x.__metadata__[0]
# #     print(repr(x))
# #     assert False
# # def all_values(x: typing.Any) -> tuple[typing.Any, ...]:

# #     return tuple([*all_values_impl(x)])

# # @dataclasses.dataclass(frozen=True)
# # class event_t:
# #     caps_lock: bool
# #     left_control: bool
# #     left_shift: bool
# #     left_option: bool
# #     left_command: bool
# #     right_control: bool
# #     right_shift: bool
# #     right_option: bool
# #     right_command: bool
# #     fn: bool
# #     layout: Layouts
# #     multitouch_extension_finger_count_total: PossibleFingerCountValues
# #     button_pair: ButtonPair

# # class product_with_len:
# #     def __init__(self, *args_: Any) -> None:
# #         args = [list(arg) for arg in args_]
# #         self.len = reduce(mul, [len(arg) for arg in args], 1)
# #         self.generator = product(*args)
# #     def __iter__(self) -> product_with_len:
# #         return self
# #     def __next__(self) -> Any:
# #         return self.generator.__next__()
# #     def __len__(self) -> int:
# #         return self.len
# #     def __length_hint__(self) -> int:
# #         return self.len


# # all_events_generator = product_with_len(*[
# #     all_values(eval(attr_type))
# #     for attr_type in event_t.__annotations__.values()
# # ])

# # T = typing.TypeVar('T')

# # def identity(arg: T) -> T:
# #     return arg

# # tqdm : typing.Callable[[typing.Any], typing.Any] = identity
# # try:
# #     from tqdm import tqdm as _tqdm
# #     tqdm = _tqdm
# # except Exception as e:
# #     print(f'failed to import tqdm. {type(e).__name__}:{e}')

# # import copy
# # from typing import *

# # #######################################################################################################################################

# # def decide_what_to_do(event: event_t) -> event_t:
# #     new_event_args = copy.deepcopy(vars(event))
# #     def swap(a: str,s: str) -> None:
# #         nonlocal new_event_args
# #         new_event_args[a], new_event_args[s] = new_event_args[s], new_event_args[a]
# #     @call
# #     def process_modifiers() -> None:
# #         ...
# #         # swap('left_command', 'fn')
# #         # swap('left_option', 'fn')
# #         # swap('right_option', 'right_command')
# #     @call
# #     def process_self_modifiers() -> None:
# #         if category_by_button_pair[event.button_pair] != 'Modifier keys':
# #             return
# #         if event.button_pair[1] == 'left_command':
# #             new_event_args['button_pair'] = ('key_code', 'left_option')
# #         if event.button_pair[1] == 'keyboard_fn':
# #             new_event_args['button_pair'] = ('key_code', 'left_command')
# #         if event.button_pair[1] == 'left_option':
# #             new_event_args['button_pair'] = ('apple_vendor_top_case_key_code', 'keyboard_fn')
# #         if event.button_pair[1] == 'right_command':
# #             new_event_args['button_pair'] = ('key_code', 'right_option')
# #         if event.button_pair[1] == 'right_option':
# #             new_event_args['button_pair'] = ('key_code', 'right_command')
# #     @call
# #     def process_arrow_mods() -> None:
# #         if event.button_pair[1] != 'delete_or_backspace':
# #             if category_by_button_pair[event.button_pair] != 'Arrow keys':
# #                 return
# #         swap('left_command', 'left_option')
# #         swap('right_command', 'right_option')
# #     @call
# #     def process_touchpad() -> None:
# #         if event.multitouch_extension_finger_count_total == 0:
# #             return
# #         button_pair = [*event.button_pair]
# #         if button_pair[1] == 'up_arrow':
# #             button_pair[1] = 'page_up'
# #         if button_pair[1] == 'down_arrow':
# #             button_pair[1] = 'page_down'
# #         if button_pair[1] == 'left_arrow':
# #             button_pair[1] = 'home'
# #         if button_pair[1] == 'right_arrow':
# #             button_pair[1] = 'end'
# #         if button_pair[1] == 'delete_or_backspace':
# #             button_pair[1] = 'delete_forward'
# #         new_event_args['button_pair'] = tuple(button_pair)
# #     @call
# #     def process_functions() -> None:
# #         if category_by_button_pair[event.button_pair] != 'Function keys':
# #             return
# #         if event.multitouch_extension_finger_count_total == 0:
# #             return
# #         new_event_args['fn'] = True
# #         if event.button_pair[1] in 'f1 f2 f11 f12'.split():
# #             new_event_args['right_option'] = True
# #             new_event_args['right_shift'] = True
# #     @call
# #     def process_space() -> None:
# #         if event.button_pair[1] != 'spacebar':
# #             return
# #         swap('fn', 'left_option')
# #     @call
# #     def process_punct() -> None:
# #         if event.layout != 'ru':
# #             return
# #         if event.button_pair[1] == '6' and (event.left_shift or event.right_shift):
# #             new_event_args['button_pair'] = ('key_code', 'slash')
# #             new_event_args['left_shift'] = False
# #             new_event_args['right_shift'] = False
# #         if event.button_pair[1] == '7' and (event.left_shift or event.right_shift):
# #             new_event_args['button_pair'] = ('key_code', 'slash')
# #             new_event_args['left_shift'] = event.left_shift
# #             new_event_args['right_shift'] = event.right_shift
# #         if event.button_pair[1] == 'slash':
# #             if event.left_shift or event.right_shift:
# #                 new_event_args['button_pair'] = ('key_code', '6')
# #                 new_event_args['left_shift'] = event.left_shift
# #                 new_event_args['right_shift'] = event.right_shift
# #             else:
# #                 new_event_args['button_pair'] = ('key_code', '7')
# #                 new_event_args['right_shift'] = True
# #     event = event_t(**new_event_args)
# #     return event

# # #######################################################################################################################################

# # @dataclass(frozen=True)
# # class optimized_event_k:
# #     caps_lock: tuple[bool, tuple[bool, ...]]
# #     left_control: tuple[bool, tuple[bool, ...]]
# #     left_shift: tuple[bool, tuple[bool, ...]]
# #     left_option: tuple[bool, tuple[bool, ...]]
# #     left_command: tuple[bool, tuple[bool, ...]]
# #     right_control: tuple[bool, tuple[bool, ...]]
# #     right_shift: tuple[bool, tuple[bool, ...]]
# #     right_option: tuple[bool, tuple[bool, ...]]
# #     right_command: tuple[bool, tuple[bool, ...]]
# #     fn: tuple[bool, tuple[bool, ...]]
# #     layout: tuple[bool, tuple[Layouts, ...]]
# #     multitouch_extension_finger_count: tuple[bool,tuple[PossibleFingerCountValues, ...]]
# #     button_pair: ButtonPair

# # @dataclass(frozen=True)
# # class optimized_event_v:
# #     caps_lock: bool
# #     left_control: bool
# #     left_shift: bool
# #     left_option: bool
# #     left_command: bool
# #     right_control: bool
# #     right_shift: bool
# #     right_option: bool
# #     right_command: bool
# #     fn: bool
# #     button_pair: ButtonPair

# # print('making decicions...')

# # optimized_manipulators = dict[event_t, tuple[event_t, ...]]

# # manipulators : list[tuple[event_t, event_t]] = []

# # for from_event_params in tqdm(product_with_len(*[
# #         all_values(attr_type)
# #         for attr_type in event_t.__annotations__.values()
# #     ])):
# #     from_event = event_t(*from_event_params)
# #     to_events = decide_what_to_do(from_event)
# #     if from_event != to_event:
# #         manipulators.append((from_event, to_event))
# #     # manipulators.append((from_event, to_event))

# # print('making decicions...')

# # manipulators : list[tuple[event_t, event_t]] = []
# # for from_event_params in tqdm(product_with_len(*[
# #         all_values(attr_type)
# #         for attr_type in event_t.__annotations__.values()
# #     ])):
# #     from_event = event_t(*from_event_params)
# #     to_event = decide_what_to_do(from_event)
# #     if from_event != to_event:
# #         manipulators.append((from_event, to_event))
# #     # manipulators.append((from_event, to_event))

# # @dataclasses.dataclass(frozen=True)
# # class optimized_event_k:
# #     caps_lock: tuple[bool, tuple[bool, ...]]
# #     left_control: tuple[bool, tuple[bool, ...]]
# #     left_shift: tuple[bool, tuple[bool, ...]]
# #     left_option: tuple[bool, tuple[bool, ...]]
# #     left_command: tuple[bool, tuple[bool, ...]]
# #     right_control: tuple[bool, tuple[bool, ...]]
# #     right_shift: tuple[bool, tuple[bool, ...]]
# #     right_option: tuple[bool, tuple[bool, ...]]
# #     right_command: tuple[bool, tuple[bool, ...]]
# #     fn: tuple[bool, tuple[bool, ...]]
# #     layout: tuple[bool, tuple[Layouts, ...]]
# #     multitouch_extension_finger_count: tuple[bool,tuple[PossibleFingerCountValues, ...]]
# #     button_pair: ButtonPair

# # @dataclasses.dataclass(frozen=True)
# # class optimized_event_v:
# #     caps_lock: bool
# #     left_control: bool
# #     left_shift: bool
# #     left_option: bool
# #     left_command: bool
# #     right_control: bool
# #     right_shift: bool
# #     right_option: bool
# #     right_command: bool
# #     fn: bool
# #     button_pair: ButtonPair

# print('checking data...')

# assert len(dict(tqdm(manipulators))) == len(manipulators)

# print('preparing for optimization...')

# optimized_manipulators = {
#     optimized_event_k(
#         caps_lock=(False, (f.caps_lock, )),
#         left_control=(False, (f.left_control, )),
#         left_shift=(False, (f.left_shift, )),
#         left_option=(False, (f.left_option, )),
#         left_command=(False, (f.left_command, )),
#         right_control=(False, (f.right_control, )),
#         right_shift=(False, (f.right_shift, )),
#         right_option=(False, (f.right_option, )),
#         right_command=(False, (f.right_command, )),
#         fn=(False, (f.fn, )),
#         layout=(False, (f.layout, )),
#         multitouch_extension_finger_count=(False, (f.multitouch_extension_finger_count_total, )),
#         button_pair=f.button_pair,
#     ):optimized_event_v(
#         caps_lock=t.caps_lock,
#         left_control=t.left_control,
#         left_shift=t.left_shift,
#         left_option=t.left_option,
#         left_command=t.left_command,
#         right_control=t.right_control,
#         right_shift=t.right_shift,
#         right_option=t.right_option,
#         right_command=t.right_command,
#         fn=t.fn,
#         button_pair=t.button_pair,
#     )
#     for f, t in tqdm(manipulators)
# }



# # while 1:
# #     dict_changed = False
# #     for manipulator_from, manipulator_to in tqdm([*optimized_manipulators.items()]):
# #         if manipulator_from not in optimized_manipulators:
# #             continue
# #         if len(manipulator_from.multitouch_extension_finger_count[1])>1:
# #             continue
# #         alternatives = [
# #             optimized_event_k(**(vars(manipulator_from) | dict(multitouch_extension_finger_count=(False, (finger_count,)))))
# #             for finger_count in sorted([*cast(Any, PossibleFingerCountValues).__args__])
# #         ]
# #         alternatives = [
# #             alternative
# #             for alternative in alternatives
# #             if optimized_manipulators.get(alternative, None) == manipulator_to
# #         ]
# #         if len(alternatives) < 2:
# #             continue
# #         dict_changed = True
# #         optimized_manipulators[
# #             optimized_event_k(
# #                 **(
# #                     vars(manipulator_from) | dict(
# #                         multitouch_extension_finger_count=(
# #                             True,
# #                             tuple(
# #                                 sorted(
# #                                     {*cast(Any, PossibleFingerCountValues).__args__}
# #                                     -
# #                                     {
# #                                         *chain(
# #                                             *[
# #                                                 alternative.multitouch_extension_finger_count[1]
# #                                                 for alternative in alternatives
# #                                             ]
# #                                         )
# #                                     }
# #                                 ),
# #                             )
# #                         ),
# #                     )
# #                 ),
# #             )
# #         ] = manipulator_to
# #         for alternative in alternatives:
# #             del optimized_manipulators[alternative]
# #     if not dict_changed:
# #         break

# # while 1:
# #     dict_changed = False
# #     for manipulator_from, manipulator_to in tqdm([*optimized_manipulators.items()]):
# #         if manipulator_from not in optimized_manipulators:
# #             continue
# #         if len(manipulator_from.layout[1])>1:
# #             continue
# #         alternatives = [
# #             optimized_event_k(**(vars(manipulator_from) | dict(layout=(False, (layout,)))))
# #             for layout in sorted([*cast(Any, Layouts).__args__])
# #         ]
# #         alternatives = [
# #             alternative
# #             for alternative in alternatives
# #             if optimized_manipulators.get(alternative, None) == manipulator_to
# #         ]
# #         if len(alternatives) < 2:
# #             continue

# #         straight_alternatives = {
# #             *chain(
# #                 *[
# #                     alternative.layout[1]
# #                     for alternative in alternatives
# #                 ]
# #             )
# #         }
# #         reverse_alternatives = {*cast(Any, Layouts).__args__} - straight_alternatives

# #         dict_changed = True
# #         optimized_manipulators[
# #             optimized_event_k(
# #                 **(
# #                     vars(manipulator_from) | dict(
# #                         layout=(
# #                             True,
# #                             tuple(sorted(reverse_alternatives),),
# #                         ) if len(reverse_alternatives) < len(straight_alternatives) else (
# #                             False,
# #                             tuple(sorted(straight_alternatives),),
# #                         ),
# #                     )
# #                 ),
# #             )
# #         ] = manipulator_to
# #         for alternative in alternatives:
# #             del optimized_manipulators[alternative]
# #     if not dict_changed:
# #         break

# # for modifier in sorted([*cast(Any, Layouts).__args__]):

# def remove_duplicates(attr_name: str, possible_values: list[typing.Any]) -> None:
#     for c in count():
#         dict_changed = False
#         print(f'preparing for optimizing {attr_name} parameter, iteration={c}')
#         copied_keys = [*tqdm(optimized_manipulators.items())]
#         print(f'optimizing {attr_name} parameter, iteration={c}')
#         for manipulator_from, manipulator_to in tqdm(copied_keys):
#             if manipulator_from not in optimized_manipulators:
#                 continue
#             if len(getattr(manipulator_from, attr_name)[1])>1:
#                 continue
#             alternatives = [
#                 optimized_event_k(**(vars(manipulator_from) | {attr_name: (False, (possible_value,))}))
#                 for possible_value in possible_values
#             ]
#             alternatives = [
#                 alternative
#                 for alternative in alternatives
#                 if optimized_manipulators.get(alternative, None) == (
#                     manipulator_to
#                     if attr_name not in dir(manipulator_to) else
#                     optimized_event_v(
#                         **(
#                             vars(manipulator_to) | {
#                                 attr_name: getattr(alternative, attr_name)[1][0]
#                             }
#                         )
#                     )
#                 )
#             ]
#             if len(alternatives) < 2:
#                 continue

#             straight_alternatives = {
#                 *chain(
#                     *[
#                         getattr(alternative, attr_name)[1]
#                         for alternative in alternatives
#                     ]
#                 )
#             }
#             reverse_alternatives = set(possible_values) - straight_alternatives

#             dict_changed = True
#             optimized_manipulators[
#                 optimized_event_k(
#                     **(
#                         vars(manipulator_from) | {
#                             attr_name: (
#                                 True,
#                                 tuple(sorted(reverse_alternatives)),
#                             ) if len(reverse_alternatives) < len(straight_alternatives) else (
#                                 False,
#                                 tuple(sorted(straight_alternatives)),
#                             ),
#                         }
#                     ),
#                 )
#             ] = manipulator_to
#             for alternative in alternatives:
#                 del optimized_manipulators[alternative]
#         if not dict_changed:
#             break

# remove_duplicates('multitouch_extension_finger_count', sorted(cast(Any, PossibleFingerCountValues).__args__))
# remove_duplicates('layout', sorted(cast(Any, Layouts).__args__))
# for modifier in sorted([*cast(Any, Modifiers).__args__]):
#     remove_duplicates(modifier, [False, True])



# # while 1:
# #     for manipulator_from, manipulator_to in optimized_manipulators.items():
# #         if manipulator_from.multitouch_extension_finger_count_is_unless:
# #             continue
# #         alternatives = [
# #             optimized_event_k(**(vars(manipulator_from) | dict(multitouch_extension_finger_count=finger_count)))
# #             for finger_count in sorted([*cast(Any, PossibleFingerCountValues).__args__])
# #         ]
# #         result_count : dict[optimized_event_v, int] = {}
# #         for alternative in alternatives:
# #             result_count[optimized_manipulators[alternative]] = 0
# #         for alternative in alternatives:
# #             result_count[optimized_manipulators[alternative]] += 1
# #         popular_alternative = max(alternatives, key=lambda alternative: result_count[optimized_manipulators[alternative]])





# #         if optimized_manipulators.get(alternatives[-1], None) != manipulator_to:
# #             continue
# #         while alternatives and alternatives[0] not in optimized_manipulators:
# #             alternatives[:1] = []
# #         if not alternatives:
# #             continue
# #         if any([
# #             alternative not in optimized_manipulators
# #             for alternative in alternatives
# #         ]):
# #             continue
# #         min_i = min([
# #             min_i
# #             for min_i in range(len(alternatives))
# #             if all([
# #                 optimized_manipulators[alternatives[i]] == manipulator_to
# #                 for i in range(min_i, len(alternatives))
# #             ])
# #         ])
# #         if min_i == len(alternatives)-1:
# #             continue
# #         optimized_manipulators[
# #             optimized_event_k(
# #                 **(
# #                     vars(manipulator_from) | dict(
# #                         multitouch_extension_finger_count=alternatives[min_i].multitouch_extension_finger_count,
# #                         multitouch_extension_finger_count_is_unless=True,
# #                     )
# #                 ),
# #             )
# #         ] = manipulator_to
# #         for alternative in alternatives[min_i:]:
# #             del optimized_manipulators[alternative]
# #         break
# #     else:
# #         break


# # while 1:
# #     for manipulator_from, manipulator_to in optimized_manipulators.items():
# #         if manipulator_from.multitouch_extension_finger_count_is_unless:
# #             continue
# #         alternatives = [
# #             optimized_event_k(**(vars(manipulator_from) | dict(multitouch_extension_finger_count=finger_count)))
# #             for finger_count in sorted([*cast(Any, PossibleFingerCountValues).__args__])
# #         ]
# #         if optimized_manipulators.get(alternatives[-1], None) != manipulator_to:
# #             continue
# #         while alternatives and alternatives[0] not in optimized_manipulators:
# #             alternatives[:1] = []
# #         if not alternatives:
# #             continue
# #         if any([
# #             alternative not in optimized_manipulators
# #             for alternative in alternatives
# #         ]):
# #             continue
# #         min_i = min([
# #             min_i
# #             for min_i in range(len(alternatives))
# #             if all([
# #                 optimized_manipulators[alternatives[i]] == manipulator_to
# #                 for i in range(min_i, len(alternatives))
# #             ])
# #         ])
# #         if min_i == len(alternatives)-1:
# #             continue
# #         optimized_manipulators[
# #             optimized_event_k(
# #                 **(
# #                     vars(manipulator_from) | dict(
# #                         multitouch_extension_finger_count=alternatives[min_i].multitouch_extension_finger_count,
# #                         multitouch_extension_finger_count_is_unless=True,
# #                     )
# #                 ),
# #             )
# #         ] = manipulator_to
# #         for alternative in alternatives[min_i:]:
# #             del optimized_manipulators[alternative]
# #         break
# #     else:
# #         break

# print(f'converting to json format')

# whole_file = dict(
#     title='auto generated',
#     rules=[
#         dict(
#             description='auto generated',
#             manipulators=[
#                 {
#                     'type': 'basic',
#                     'from':{
#                         manipulator_from.button_pair[0]: manipulator_from.button_pair[1],
#                         'modifiers': {
#                             'mandatory': [
#                                 modifier
#                                 for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
#                                 if
#                                 not getattr(manipulator_from, modifier)[0]
#                                 and getattr(manipulator_from, modifier)[1][0]
#                             ],
#                             'optional': [
#                                 modifier
#                                 for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
#                                 if getattr(manipulator_from, modifier)[0]
#                             ],
#                         },
#                     },
#                     'to': [
#                         {
#                             manipulator_to.button_pair[0]: manipulator_to.button_pair[1],
#                             'modifiers': [
#                                 modifier
#                                 for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
#                                 if getattr(manipulator_to, modifier)
#                             ],
#                         }
#                     ],
#                     'conditions': [
#                         *[
#                             {
#                                 "name": "multitouch_extension_finger_count_total",
#                                 "type": "variable_unless" if manipulator_from.multitouch_extension_finger_count[0] else "variable_if",
#                                 "value": multitouch_extension_finger_count,
#                             }
#                             for multitouch_extension_finger_count in manipulator_from.multitouch_extension_finger_count[1]
#                         ],
#                         *(
#                             [
#                                 {
#                                     "input_sources": [
#                                         { "language": '^' + layout + '$' }
#                                         for layout in manipulator_from.layout[1]
#                                     ],
#                                     "type": "input_source_unless" if manipulator_from.layout[0] else "input_source_if"
#                                 }
#                             ] if manipulator_from.layout[1] else []
#                         )
#                     ]
#                 }
#                 for manipulator_from, manipulator_to in tqdm(optimized_manipulators.items())
#             ],
#         )
#     ]
# )

# print(f'saving to {conf_file_path!r}')
# with conf_file_path.open('w') as file:
#     json.dump(whole_file, file, indent=4)

# # print(
# # [
# # [*button['data'][0].values()][0]
# # for button in all_buttons
# #     if button['category'] == 'Modifier keys'
# # ]
# # )

# # print(categories)

# # for button in all_buttons:
# #     if not button['not_from']:
# #         print(f"{button['category']:40s} {button['label']}")
#     # if button['category'] == 'Modifier keys':
#     #     print(button)
#         # print(f"{button['category']:40s} {button['label']}")

# # for category in categories:
# #     print(
# #         category,
# #         random.choice([
# #             button['label']
# #             for button in all_buttons
# #             if button['category'] == category
# #         ]),
# #         random.choice([
# #             button['label']
# #             for button in all_buttons
# #             if button['category'] == category
# #         ]),
# #         random.choice([
# #             button['label']
# #             for button in all_buttons
# #             if button['category'] == category
# #         ]),

# #         sep='\t'
# #     )