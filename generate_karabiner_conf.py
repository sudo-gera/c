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
Modifiers = typing.Literal['caps_lock', 'left_control', 'left_shift', 'left_option', 'left_command', 'right_control', 'right_shift', 'right_option', 'right_command', 'fn']
Layouts = typing.Literal['en', 'ru']
ButtonTypes = typing.Literal['key_code', 'consumer_key_code', 'pointing_button', 'generic_desktop', 'apple_vendor_top_case_key_code']
PossibleFingerCountValues = typing.Literal[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
# PossibleFingerCountValues = typing.Literal[0, 1]
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

category_by_button_pair : dict[ButtonPair, Category] = {
    typing.cast(
        tuple[str, str],
        tuple([
            *button['data'][0].keys()
        ] + [
            *button['data'][0].values()
        ])
    ):button['category']
    for button in all_buttons if not button['not_from']
}

ButtonPair = typing.Annotated[
    tuple[str, str],
    list(category_by_button_pair)
]

assert sorted(typing.cast(typing.Any, ButtonPair).__metadata__[0]) == sorted(category_by_button_pair)

categories = {
    button['category']
    for button in all_buttons
}

def all_values_impl(x: typing.Any) -> typing.Any:
    if isinstance(x, str):
        x = eval(x)
    tx = x
    if tx is bool:
        # if random.random() < 0.1:
            # return (False, True)
        # return (False, )
        return (False, True)
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
    fn: bool
    layout: Layouts
    multitouch_extension_finger_count_total: PossibleFingerCountValues
    button_pair: ButtonPair

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

#######################################################################################################################################

def decide_what_to_do(event: event_t) -> event_t:
    new_event_args = copy.deepcopy(vars(event))
    def swap(a: str,s: str) -> None:
        nonlocal new_event_args
        new_event_args[a], new_event_args[s] = new_event_args[s], new_event_args[a]
    @call
    def process_modifiers() -> None:
        ...
        # swap('left_command', 'fn')
        # swap('left_option', 'fn')
        # swap('right_option', 'right_command')
    @call
    def process_self_modifiers() -> None:
        if category_by_button_pair[event.button_pair] != 'Modifier keys':
            return
        if event.button_pair[1] == 'left_command':
            new_event_args['button_pair'] = ('key_code', 'left_option')
        if event.button_pair[1] == 'keyboard_fn':
            new_event_args['button_pair'] = ('key_code', 'left_command')
        if event.button_pair[1] == 'left_option':
            new_event_args['button_pair'] = ('apple_vendor_top_case_key_code', 'keyboard_fn')
        if event.button_pair[1] == 'right_command':
            new_event_args['button_pair'] = ('key_code', 'right_option')
        if event.button_pair[1] == 'right_option':
            new_event_args['button_pair'] = ('key_code', 'right_command')
    @call
    def process_arrow_mods() -> None:
        if event.button_pair[1] != 'delete_or_backspace':
            if category_by_button_pair[event.button_pair] != 'Arrow keys':
                return
        swap('left_command', 'left_option')
        swap('right_command', 'right_option')
    @call
    def process_touchpad() -> None:
        if event.multitouch_extension_finger_count_total == 0:
            return
        button_pair = [*event.button_pair]
        if button_pair[1] == 'up_arrow':
            button_pair[1] = 'page_up'
        if button_pair[1] == 'down_arrow':
            button_pair[1] = 'page_down'
        if button_pair[1] == 'left_arrow':
            button_pair[1] = 'home'
        if button_pair[1] == 'right_arrow':
            button_pair[1] = 'end'
        if button_pair[1] == 'delete_or_backspace':
            button_pair[1] = 'delete_forward'
        new_event_args['button_pair'] = tuple(button_pair)
    @call
    def process_functions() -> None:
        if category_by_button_pair[event.button_pair] != 'Function keys':
            return
        if event.multitouch_extension_finger_count_total == 0:
            return
        new_event_args['fn'] = True
        if event.button_pair[1] in 'f1 f2 f11 f12'.split():
            new_event_args['right_option'] = True
            new_event_args['right_shift'] = True
    @call
    def process_space() -> None:
        if event.button_pair[1] != 'spacebar':
            return
        swap('fn', 'left_option')
    @call
    def process_punct() -> None:
        if event.layout != 'ru':
            return
        if event.button_pair[1] == '6' and (event.left_shift or event.right_shift):
            new_event_args['button_pair'] = ('key_code', 'slash')
            new_event_args['left_shift'] = False
            new_event_args['right_shift'] = False
        if event.button_pair[1] == '7' and (event.left_shift or event.right_shift):
            new_event_args['button_pair'] = ('key_code', 'slash')
            new_event_args['left_shift'] = event.left_shift
            new_event_args['right_shift'] = event.right_shift
        if event.button_pair[1] == 'slash':
            if event.left_shift or event.right_shift:
                new_event_args['button_pair'] = ('key_code', '6')
                new_event_args['left_shift'] = event.left_shift
                new_event_args['right_shift'] = event.right_shift
            else:
                new_event_args['button_pair'] = ('key_code', '7')
                new_event_args['right_shift'] = True
    event = event_t(**new_event_args)
    return event

#######################################################################################################################################

print('making decicions...')

manipulators : list[tuple[event_t, event_t]] = []
for from_event_params in tqdm(product_with_len(*[
        all_values(attr_type)
        for attr_type in event_t.__annotations__.values()
    ])):
    from_event = event_t(*from_event_params)
    to_event = decide_what_to_do(from_event)
    if from_event != to_event:
        manipulators.append((from_event, to_event))
    # manipulators.append((from_event, to_event))

@dataclasses.dataclass(frozen=True)
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

@dataclasses.dataclass(frozen=True)
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

print('checking data...')

assert len(dict(tqdm(manipulators))) == len(manipulators)

print('preparing for optimization...')

optimized_manipulators = {
    optimized_event_k(
        caps_lock=(False, (f.caps_lock, )),
        left_control=(False, (f.left_control, )),
        left_shift=(False, (f.left_shift, )),
        left_option=(False, (f.left_option, )),
        left_command=(False, (f.left_command, )),
        right_control=(False, (f.right_control, )),
        right_shift=(False, (f.right_shift, )),
        right_option=(False, (f.right_option, )),
        right_command=(False, (f.right_command, )),
        fn=(False, (f.fn, )),
        layout=(False, (f.layout, )),
        multitouch_extension_finger_count=(False, (f.multitouch_extension_finger_count_total, )),
        button_pair=f.button_pair,
    ):optimized_event_v(
        caps_lock=t.caps_lock,
        left_control=t.left_control,
        left_shift=t.left_shift,
        left_option=t.left_option,
        left_command=t.left_command,
        right_control=t.right_control,
        right_shift=t.right_shift,
        right_option=t.right_option,
        right_command=t.right_command,
        fn=t.fn,
        button_pair=t.button_pair,
    )
    for f, t in tqdm(manipulators)
}



# while 1:
#     dict_changed = False
#     for manipulator_from, manipulator_to in tqdm([*optimized_manipulators.items()]):
#         if manipulator_from not in optimized_manipulators:
#             continue
#         if len(manipulator_from.multitouch_extension_finger_count[1])>1:
#             continue
#         alternatives = [
#             optimized_event_k(**(vars(manipulator_from) | dict(multitouch_extension_finger_count=(False, (finger_count,)))))
#             for finger_count in sorted([*cast(Any, PossibleFingerCountValues).__args__])
#         ]
#         alternatives = [
#             alternative
#             for alternative in alternatives
#             if optimized_manipulators.get(alternative, None) == manipulator_to
#         ]
#         if len(alternatives) < 2:
#             continue
#         dict_changed = True
#         optimized_manipulators[
#             optimized_event_k(
#                 **(
#                     vars(manipulator_from) | dict(
#                         multitouch_extension_finger_count=(
#                             True,
#                             tuple(
#                                 sorted(
#                                     {*cast(Any, PossibleFingerCountValues).__args__}
#                                     -
#                                     {
#                                         *chain(
#                                             *[
#                                                 alternative.multitouch_extension_finger_count[1]
#                                                 for alternative in alternatives
#                                             ]
#                                         )
#                                     }
#                                 ),
#                             )
#                         ),
#                     )
#                 ),
#             )
#         ] = manipulator_to
#         for alternative in alternatives:
#             del optimized_manipulators[alternative]
#     if not dict_changed:
#         break

# while 1:
#     dict_changed = False
#     for manipulator_from, manipulator_to in tqdm([*optimized_manipulators.items()]):
#         if manipulator_from not in optimized_manipulators:
#             continue
#         if len(manipulator_from.layout[1])>1:
#             continue
#         alternatives = [
#             optimized_event_k(**(vars(manipulator_from) | dict(layout=(False, (layout,)))))
#             for layout in sorted([*cast(Any, Layouts).__args__])
#         ]
#         alternatives = [
#             alternative
#             for alternative in alternatives
#             if optimized_manipulators.get(alternative, None) == manipulator_to
#         ]
#         if len(alternatives) < 2:
#             continue

#         straight_alternatives = {
#             *chain(
#                 *[
#                     alternative.layout[1]
#                     for alternative in alternatives
#                 ]
#             )
#         }
#         reverse_alternatives = {*cast(Any, Layouts).__args__} - straight_alternatives

#         dict_changed = True
#         optimized_manipulators[
#             optimized_event_k(
#                 **(
#                     vars(manipulator_from) | dict(
#                         layout=(
#                             True,
#                             tuple(sorted(reverse_alternatives),),
#                         ) if len(reverse_alternatives) < len(straight_alternatives) else (
#                             False,
#                             tuple(sorted(straight_alternatives),),
#                         ),
#                     )
#                 ),
#             )
#         ] = manipulator_to
#         for alternative in alternatives:
#             del optimized_manipulators[alternative]
#     if not dict_changed:
#         break

# for modifier in sorted([*cast(Any, Layouts).__args__]):

def remove_duplicates(attr_name: str, possible_values: list[typing.Any]) -> None:
    for c in count():
        dict_changed = False
        print(f'preparing for optimizing {attr_name} parameter, iteration={c}')
        copied_keys = [*tqdm(optimized_manipulators.items())]
        print(f'optimizing {attr_name} parameter, iteration={c}')
        for manipulator_from, manipulator_to in tqdm(copied_keys):
            if manipulator_from not in optimized_manipulators:
                continue
            if len(getattr(manipulator_from, attr_name)[1])>1:
                continue
            alternatives = [
                optimized_event_k(**(vars(manipulator_from) | {attr_name: (False, (possible_value,))}))
                for possible_value in possible_values
            ]
            alternatives = [
                alternative
                for alternative in alternatives
                if optimized_manipulators.get(alternative, None) == (
                    manipulator_to
                    if attr_name not in dir(manipulator_to) else
                    optimized_event_v(
                        **(
                            vars(manipulator_to) | {
                                attr_name: getattr(alternative, attr_name)[1][0]
                            }
                        )
                    )
                )
            ]
            if len(alternatives) < 2:
                continue

            straight_alternatives = {
                *chain(
                    *[
                        getattr(alternative, attr_name)[1]
                        for alternative in alternatives
                    ]
                )
            }
            reverse_alternatives = set(possible_values) - straight_alternatives

            dict_changed = True
            optimized_manipulators[
                optimized_event_k(
                    **(
                        vars(manipulator_from) | {
                            attr_name: (
                                True,
                                tuple(sorted(reverse_alternatives)),
                            ) if len(reverse_alternatives) < len(straight_alternatives) else (
                                False,
                                tuple(sorted(straight_alternatives)),
                            ),
                        }
                    ),
                )
            ] = manipulator_to
            for alternative in alternatives:
                del optimized_manipulators[alternative]
        if not dict_changed:
            break

remove_duplicates('multitouch_extension_finger_count', sorted(cast(Any, PossibleFingerCountValues).__args__))
remove_duplicates('layout', sorted(cast(Any, Layouts).__args__))
for modifier in sorted([*cast(Any, Modifiers).__args__]):
    remove_duplicates(modifier, [False, True])



# while 1:
#     for manipulator_from, manipulator_to in optimized_manipulators.items():
#         if manipulator_from.multitouch_extension_finger_count_is_unless:
#             continue
#         alternatives = [
#             optimized_event_k(**(vars(manipulator_from) | dict(multitouch_extension_finger_count=finger_count)))
#             for finger_count in sorted([*cast(Any, PossibleFingerCountValues).__args__])
#         ]
#         result_count : dict[optimized_event_v, int] = {}
#         for alternative in alternatives:
#             result_count[optimized_manipulators[alternative]] = 0
#         for alternative in alternatives:
#             result_count[optimized_manipulators[alternative]] += 1
#         popular_alternative = max(alternatives, key=lambda alternative: result_count[optimized_manipulators[alternative]])





#         if optimized_manipulators.get(alternatives[-1], None) != manipulator_to:
#             continue
#         while alternatives and alternatives[0] not in optimized_manipulators:
#             alternatives[:1] = []
#         if not alternatives:
#             continue
#         if any([
#             alternative not in optimized_manipulators
#             for alternative in alternatives
#         ]):
#             continue
#         min_i = min([
#             min_i
#             for min_i in range(len(alternatives))
#             if all([
#                 optimized_manipulators[alternatives[i]] == manipulator_to
#                 for i in range(min_i, len(alternatives))
#             ])
#         ])
#         if min_i == len(alternatives)-1:
#             continue
#         optimized_manipulators[
#             optimized_event_k(
#                 **(
#                     vars(manipulator_from) | dict(
#                         multitouch_extension_finger_count=alternatives[min_i].multitouch_extension_finger_count,
#                         multitouch_extension_finger_count_is_unless=True,
#                     )
#                 ),
#             )
#         ] = manipulator_to
#         for alternative in alternatives[min_i:]:
#             del optimized_manipulators[alternative]
#         break
#     else:
#         break


# while 1:
#     for manipulator_from, manipulator_to in optimized_manipulators.items():
#         if manipulator_from.multitouch_extension_finger_count_is_unless:
#             continue
#         alternatives = [
#             optimized_event_k(**(vars(manipulator_from) | dict(multitouch_extension_finger_count=finger_count)))
#             for finger_count in sorted([*cast(Any, PossibleFingerCountValues).__args__])
#         ]
#         if optimized_manipulators.get(alternatives[-1], None) != manipulator_to:
#             continue
#         while alternatives and alternatives[0] not in optimized_manipulators:
#             alternatives[:1] = []
#         if not alternatives:
#             continue
#         if any([
#             alternative not in optimized_manipulators
#             for alternative in alternatives
#         ]):
#             continue
#         min_i = min([
#             min_i
#             for min_i in range(len(alternatives))
#             if all([
#                 optimized_manipulators[alternatives[i]] == manipulator_to
#                 for i in range(min_i, len(alternatives))
#             ])
#         ])
#         if min_i == len(alternatives)-1:
#             continue
#         optimized_manipulators[
#             optimized_event_k(
#                 **(
#                     vars(manipulator_from) | dict(
#                         multitouch_extension_finger_count=alternatives[min_i].multitouch_extension_finger_count,
#                         multitouch_extension_finger_count_is_unless=True,
#                     )
#                 ),
#             )
#         ] = manipulator_to
#         for alternative in alternatives[min_i:]:
#             del optimized_manipulators[alternative]
#         break
#     else:
#         break

print(f'converting to json format')

whole_file = dict(
    title='auto generated',
    rules=[
        dict(
            description='auto generated',
            manipulators=[
                {
                    'type': 'basic',
                    'from':{
                        manipulator_from.button_pair[0]: manipulator_from.button_pair[1],
                        'modifiers': {
                            'mandatory': [
                                modifier
                                for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
                                if
                                not getattr(manipulator_from, modifier)[0]
                                and getattr(manipulator_from, modifier)[1][0]
                            ],
                            'optional': [
                                modifier
                                for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
                                if getattr(manipulator_from, modifier)[0]
                            ],
                        },
                    },
                    'to': [
                        {
                            manipulator_to.button_pair[0]: manipulator_to.button_pair[1],
                            'modifiers': [
                                modifier
                                for modifier in cast(tuple[str,...], cast(Any, Modifiers).__args__)
                                if getattr(manipulator_to, modifier)
                            ],
                        }
                    ],
                    'conditions': [
                        *[
                            {
                                "name": "multitouch_extension_finger_count_total",
                                "type": "variable_unless" if manipulator_from.multitouch_extension_finger_count[0] else "variable_if",
                                "value": multitouch_extension_finger_count,
                            }
                            for multitouch_extension_finger_count in manipulator_from.multitouch_extension_finger_count[1]
                        ],
                        *(
                            [
                                {
                                    "input_sources": [
                                        { "language": '^' + layout + '$' }
                                        for layout in manipulator_from.layout[1]
                                    ],
                                    "type": "input_source_unless" if manipulator_from.layout[0] else "input_source_if"
                                }
                            ] if manipulator_from.layout[1] else []
                        )
                    ]
                }
                for manipulator_from, manipulator_to in tqdm(optimized_manipulators.items())
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