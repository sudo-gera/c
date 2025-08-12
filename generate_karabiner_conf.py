from __future__ import annotations

import pathlib
import dataclasses
import typing

home = pathlib.Path.home()

conf_file_path = home / '.config' / 'karabiner' / 'assets' / 'complex_modifications' / 'auto_generated_conf.json'

# # @dataclasses.dataclass
# # class whole_file_t:
# #     title: str
# #     rules: list[rule_t]

# # @dataclasses.dataclass
# # class rule_t:
# #     description: str
# #     manipulators: list[manipulator_t]

# # @dataclasses.dataclass
# # class manipulator_t:
# #     # Type: typing.Literal['basic'] = 'basic'
# #     From: manipulator_from_t
# #     To: manipulator_to_t
# #     Conditions: manipulator_conditions_t

# # @dataclasses.dataclass
# # class manipulator_from_t:
# #     key_code: key_code_t
# #     modifiers: modifiers_t

# # @dataclasses.dataclass
# # class manipulator_to_t:
# #     key_code: key_code_t
# #     modifiers: modifiers_t

# # @dataclasses.dataclass
# # class manipulator_conditions_t:
# #     ...

# # @dataclasses.dataclass
# # class key_code_t:
# #     ...

# # @dataclasses.dataclass
# # class modifiers_t:
# #     ...

# #################################################################################################################

# @dataclasses.dataclass
# class physical_button_t:
#     name: str
#     is_mod: bool = False

# #     1|      2|      3|      4|      5|      6|      7|      8|      9|     10|     11|     12|     13|     14|
# #234567|1234567|1234567|1234567|1234567|1234567|1234567|1234567|1234567|1234567|1234567|1234567|1234567|1234567|

# all_buttons = '''

# ESC     F1      F2      F3      F4      F5      F6      F7      F8      F9      F10     F11     F12     POWER

# PAR     1       2       3       4       5       6       7       8       9       0       -       =       BSPACE

# TAB     Q       W       E       R       T       Y       U       I       O       P       [       ]       ENTER

# CAPS    A       S       D       F       G       H       J       K       L       ;       '       \\      

# LSHIFT  GRAVE   Z       X       C       V       B       N       M       ,       .       /       RSHIFT

# FN      LCTRL   LOPT    LCOM    SPACE   RCOM    ROPT    LEFT    UP      DOWN    RIGHT

# '''

# from itertools import *
# from operator import *
# from functools import *

# physical_button_table = [
#     [
#         physical_button_t(
#             name=''.join(
#                 map(
#                     itemgetter(1),
#                     g
#                 )
#             ).strip()
#         )
#         for k, g in groupby(
#             enumerate(line),
#             lambda ic: ic[0]//8,
#         )
#     ]
#     for line in filter(bool, all_buttons.splitlines())
# ]

# all_names = [
#     x.name
#     for x in chain(*physical_button_table)
# ]

# assert len(set(all_names)) == len(all_names)

# def physical_button_by_name(name: str) -> physical_button_t:
#     matching_buttons = [
#         x
#         for x in chain(*physical_button_table)
#         if x.name == name
#     ]
#     assert len(matching_buttons) == 1
#     return matching_buttons[0]

# physical_button_by_name('CAPS').is_mod = True
# physical_button_by_name('LCOM').is_mod = True
# physical_button_by_name('LCTRL').is_mod = True
# physical_button_by_name('LOPT').is_mod = True
# physical_button_by_name('LSHIFT').is_mod = True
# physical_button_by_name('RCOM').is_mod = True
# # physical_button_by_name('RCTRL').is_mod = True
# physical_button_by_name('ROPT').is_mod = True
# physical_button_by_name('RSHIFT').is_mod = True
# physical_button_by_name('FN').is_mod = True

import pathlib
from urllib.request import urlopen
import json
from operator import *
from itertools import *
from functools import *

dir_with_this_file = pathlib.Path(__file__).resolve().parent
all_possible_keys_file_path = dir_with_this_file / 'simple_modifications.json'

# try:
#     call
# except NameError:
#     call = lambda

# @call
# def all_keys():
#     try:
#         data = urlopen('https://raw.githubusercontent.com/pqrs-org/Karabiner-Elements/refs/heads/main/src/apps/SettingsWindow/Resources/simple_modifications.json').read()
#         json.loads(data)
#     except Exception:
#         with all_possible_keys_file_path.open('rb') as file:
#             data = file.read()

# def call(obj, /, *args, **kwargs):
#     """Same as obj(*args, **kwargs)."""
#     return obj(*args, **kwargs)

import dataclasses
import typing
import sys
import random
if sys.version_info < (3, 11):
    from collections.abc import Callable
    from operator import attrgetter as attrgetter, itemgetter as itemgetter, methodcaller as methodcaller
    from typing import TypeVar
    from typing import ParamSpec
    _R = TypeVar("_R")
    _P = ParamSpec("_P")
    def call(obj: Callable[_P, _R], /, *args: _P.args, **kwargs: _P.kwargs) -> _R:
        return obj(*args, **kwargs)

Category = typing.Literal['Letter keys', 'Generic desktop keys', 'Mouse keys', 'Arrow keys', 'Mouse buttons', 'Media controls', 'International keys', 'Generic GUI application control keys', 'Japanese', 'Others', 'Keys in pc keyboards', 'Controls and symbols', 'Software function', 'D-pad', 'Function keys', 'Modifier keys', 'Sticky modifier keys', 'Keypad keys', 'Application launch keys', 'Remote control buttons', 'Disable this key', 'Number keys']
Modifiers = typing.Literal['caps_lock', 'left_control', 'left_shift', 'left_option', 'left_command', 'right_control', 'right_shift', 'right_option', 'right_command', 'keyboard_fn']
Layout = typing.Literal['^en$', '^ru$']
ButtonTypes = typing.Literal['key_code', 'consumer_key_code', 'pointing_button', 'generic_desktop', 'apple_vendor_top_case_key_code']
# PossibleFingerCountValues = typing.Literal[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
PossibleFingerCountValues = typing.Literal[0, 1]
AllButtonsButtonDescriptionData = typing.TypedDict('AllButtonsButtonDescriptionData', {'key_code': str})
AllButtonsButtonDescription = typing.TypedDict('AllButtonsButtonDescription', {'label': str, 'category': Category, 'not_from': bool, 'unsafe_from': bool, 'not_to': bool, 'data': list[AllButtonsButtonDescriptionData]})

@call
def all_buttons() -> list[AllButtonsButtonDescription]:
    @call
    def data() -> tuple[typing.Any, bytes]:
        try:
            bin_data = urlopen('https://raw.githubusercontent.com/pqrs-org/Karabiner-Elements/refs/heads/main/src/apps/SettingsWindow/Resources/simple_modifications.json').read()
            return json.loads(bin_data), bin_data
        except Exception as e:
            print(f'failed to load keys. {type(e).__name__}:{e}')
            with all_possible_keys_file_path.open('rb') as file:
                bin_data = file.read()
                return json.loads(bin_data), bin_data
    j_data, bin_data = data

    with all_possible_keys_file_path.open('wb') as file:
        file.write(bin_data)

    all_buttons : list[AllButtonsButtonDescription] = []
    category = j_data[0]
    assert 'category' in category
    for button in j_data:
        if 'category' in button:
            category = button
        else:
            all_buttons.append(category | button)

    true_or_missing_keys : typing.Final = ('not_from', 'not_to', 'unsafe_from')

    for true_or_missing_key in true_or_missing_keys:
        assert all([
            isinstance(button.get(true_or_missing_key, True), bool)
            and
            button.get(true_or_missing_key, True) == True
            for button in all_buttons
        ])

        for button in all_buttons:
            button[true_or_missing_key] = button.get(true_or_missing_key, False)

    for button in all_buttons:
        assert set(button.keys()) == set(AllButtonsButtonDescription.__annotations__.keys())

    assert all([
        isinstance(button['data'], list)
        and (
            button['not_from']
            or
            len(button['data']) == 1
            and
            isinstance(button['data'][0], dict)
            and
            frozenset(button['data'][0].keys()) in {
                frozenset([button_type])
                for button_type in typing.cast(typing.Any, ButtonTypes).__args__
            }
            and
            len(button['data'][0].values()) == 1
            and
            isinstance([*button['data'][0].values()][0], str)
        )
        for button in all_buttons
    ])

    return all_buttons

ButtonCode = typing.Annotated[
    str,
    list(
        set(
            [
                [
                    *button['data'][0].values()
                ][0]
                for button in all_buttons if not button['not_from']
            ]
        )
    )
]

categories = {
    button['category']
    for button in all_buttons
}

def all_values_impl(x: typing.Any) -> typing.Any:
    if isinstance(x, str):
        x = eval(x)
    tx = x
    if tx is bool:
        return (False, True)
        return (False, )
    if isinstance(tx, type(typing.Literal[None])):
        return x.__args__
    if isinstance(tx, type(typing.Annotated[type, None])):
        return x.__metadata__[0]
    print(repr(x))
    assert False
def all_values(x: typing.Any) -> tuple[typing.Any]:

    return tuple([*all_values_impl(x)])

@dataclasses.dataclass(frozen=True)
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
    keyboard_fn: bool
    layout: Layout
    multitouch_extension_finger_count_total: PossibleFingerCountValues
    button_type: ButtonTypes
    button_code: ButtonCode

class product_with_len:
    def __init__(self, *args_: typing.Any) -> None:
        args = [list(arg) for arg in args_]
        self.len = reduce(mul, [len(arg) for arg in args], 1)
        self.generator = product(*args)
    def __iter__(self) -> product_with_len:
        return self
    def __next__(self) -> tuple[typing.Any, ...]:
        return self.generator.__next__()
    def __len__(self) -> int:
        return self.len
    def __length_hint__(self) -> int:
        return self.len


all_events_generator = product_with_len(*[
    all_values(eval(attr_type))
    for attr_type in event_t.__annotations__.values()
])

T = typing.TypeVar('T')

def identity(arg: T) -> T:
    return arg

tqdm : typing.Callable[[typing.Any], typing.Any] = identity
try:
    from tqdm import tqdm
except Exception as e:
    print(f'failed to import tqdm. {type(e).__name__}:{e}')

import copy
from typing import *

def decide_what_to_do(event: event_t) -> event_t:
    if event.button_code == 'q':
        o = event
        event = event_t(**(vars(event)|dict(button_code='w')))
        assert event != o
    return event

manipulators : list[tuple[event_t, event_t]] = []
for from_event_params in tqdm(product_with_len(*[
        all_values(attr_type)
        for attr_type in event_t.__annotations__.values()
    ])):
    from_event = event_t(*from_event_params)
    to_event = decide_what_to_do(from_event)
    if from_event != to_event:
        manipulators.append((from_event, to_event))

whole_file = dict(
    title='auto generated',
    rules=[
        dict(
            description='auto generated',
            manipulators=[
                {
                    'from':{
                        manipulator[0].button_type: manipulator[0].button_code,
                        'modifiers': {
                            'mandatory': [
                                modifier
                                for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
                                if getattr(manipulator[0], modifier)
                            ]
                        },
                    },
                    'to': [
                        {
                            manipulator[1].button_type: manipulator[1].button_code,
                            'modifiers': {
                                'mandatory': [
                                    modifier
                                    for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
                                    if getattr(manipulator[1], modifier)
                                ]
                            },
                        }
                    ],
                    'conditions': [
                        {
                            "name": "multitouch_extension_finger_count_total",
                            "type": "variable_if",
                            "value": manipulator[0].multitouch_extension_finger_count_total
                        },
                        {
                            "input_sources": [{ "language": manipulator[0].layout }],
                            "type": "input_source_if"
                        }
                    ]
                }
                for manipulator in tqdm(manipulators)
            ],
        )
    ]
)

print(f'saving to {conf_file_path!r}')
with conf_file_path.open('w') as file:
    json.dump(whole_file, file, indent=4)

# print(
# [
# [*button['data'][0].values()][0]
# for button in all_buttons
#     if button['category'] == 'Modifier keys'
# ]
# )

# print(categories)

# for button in all_buttons:
#     if not button['not_from']:
#         print(f"{button['category']:40s} {button['label']}")
    # if button['category'] == 'Modifier keys':
    #     print(button)
        # print(f"{button['category']:40s} {button['label']}")

# for category in categories:
#     print(
#         category,
#         random.choice([
#             button['label']
#             for button in all_buttons
#             if button['category'] == category
#         ]),
#         random.choice([
#             button['label']
#             for button in all_buttons
#             if button['category'] == category
#         ]),
#         random.choice([
#             button['label']
#             for button in all_buttons
#             if button['category'] == category
#         ]),
#         sep='\t'
#     )
