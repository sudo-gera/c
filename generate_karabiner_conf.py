from __future__ import annotations
import multiprocessing.pool
from operator import *
from itertools import *
from functools import *
from typing_extensions import *
from pprint import pprint
import pathlib
import json
import typing as typing_basic
import typing_extensions
import sys
import hashlib
import random
from dataclasses import dataclass, replace
from urllib.request import urlopen
import multiprocessing

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
        return cast(Callable[[get_tqdm_T], get_tqdm_T], tqdm)
    except Exception as e:
        print(f'failed to import tqdm. {type(e).__name__}:{e}', file=sys.stderr)
        return identity
tqdm = get_tqdm()

Layouts = Literal['en', 'ru']
PossibleFingerCountValues = Literal[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

home = pathlib.Path.home()
conf_file_path = home / '.config' / 'karabiner' / 'assets' / 'complex_modifications' / 'auto_generated_conf.json'
dir_with_this_file = pathlib.Path(__file__).resolve().parent
buttons_list_file_path = dir_with_this_file / 'simple_modifications.json'

label_t = NewType('label_t', str)
button_key_t = NewType('button_key_t', str)
button_value_t = NewType('button_value_t', str)
category_t = NewType('category_t', str)

@dataclass(frozen=True)
class Button:
    label: str
    not_from: bool
    not_to: bool
    unsafe_from: bool
    button_key: button_key_t
    button_value: button_value_t
    category: category_t

ButtonPair = NewType('ButtonPair', tuple[str, str])

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

class map_with_len:
    def __init__(self, f: Any, *args: Any) -> None:
        self.len = min([len(arg) for arg in args])
        self.generator = map(f, *args)
    def __iter__(self) -> map_with_len:
        return self
    def __next__(self) -> Any:
        return self.generator.__next__()
    def __len__(self) -> int:
        return self.len
    def __length_hint__(self) -> int:
        return self.len

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
    multitouch_extension_finger_count: PossibleFingerCountValues
    button_pair: ButtonPair

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

def optimize_input_event(event: event_t) -> optimized_event_k:
    v : Any = {k:(False, (v,)) for k,v in vars(event).items()}
    v['button_pair'] = v['button_pair'][1][0]
    return optimized_event_k(**v)

def optimize_output_event(event: event_t) -> optimized_event_v:
    v : Any = {k:v for k,v in vars(event).items()}
    del v['multitouch_extension_finger_count']
    del v['layout']
    return optimized_event_v(**v)

assert set(event_t.__annotations__.keys()) == set(optimized_event_k.__annotations__.keys())

def decide_what_to_do(input_event: event_t) -> tuple[event_t, ...]:
    output_events : tuple[event_t, ...] = (input_event,)

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                button_pair=ButtonPair(('key_code','left_command')),
            )
        ]
        if output_event.button_pair[1] == 'fn' else
        [
            replace(
                output_event,
                button_pair=ButtonPair(('apple_vendor_top_case_key_code','keyboard_fn')),
            ),
        ]
        if output_event.button_pair[1] == 'left_option' and input_event.left_command and input_event.left_control else
        [
            replace(
                output_event,
                button_pair=ButtonPair(('key_code','left_command')),
                left_control=True,
            ),
        ]
        if output_event.button_pair[1] == 'left_option' else
        [
            replace(
                output_event,
                button_pair=ButtonPair(('key_code','left_option')),
            ),
        ]
        if output_event.button_pair[1] == 'left_command' else
        [
            replace(
                output_event,
                button_pair=ButtonPair(('key_code','right_option')),
            ),
        ]
        if output_event.button_pair[1] == 'right_command' else
        [
            replace(
                output_event,
                button_pair=ButtonPair(('key_code','right_control')),
            ),
        ]
        if output_event.button_pair[1] == 'right_option' and input_event.left_command and input_event.left_control else
        [
            replace(
                output_event,
                button_pair=ButtonPair(('key_code','right_command')),
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
                button_pair = ButtonPair(('key_code', 'page_up')),
            ),
        ]
        if input_event.multitouch_extension_finger_count >= 1 and input_event.button_pair[1] == 'up_arrow' else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'page_down')),
            ),
        ]
        if input_event.multitouch_extension_finger_count >= 1 and input_event.button_pair[1] == 'down_arrow' else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'home')),
            ),
        ]
        if input_event.multitouch_extension_finger_count >= 1 and input_event.button_pair[1] == 'left_arrow' else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'end')),
            ),
        ]
        if input_event.multitouch_extension_finger_count >= 1 and input_event.button_pair[1] == 'right_arrow' else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'delete_forward')),
            ),
        ]
        if input_event.multitouch_extension_finger_count >= 1 and input_event.button_pair[1] == 'delete_or_backspace' else
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
        if input_event.multitouch_extension_finger_count >= 1 and buttons[tuple(input_event.button_pair)[1]].category == 'Function keys' and input_event.button_pair[1] in 'f1 f2 f11 f12'.split() else
        [
            replace(
                output_event,
                fn=True,
            ),
        ]
        if input_event.multitouch_extension_finger_count >= 1 and buttons[tuple(input_event.button_pair)[1]].category == 'Function keys' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'slash')),
                left_shift = False,
                right_shift = False,
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == '6' and (input_event.left_shift or input_event.right_shift) else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'slash')),
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == '7' and (input_event.left_shift or input_event.right_shift) else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', '6')),
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == 'slash' and (input_event.left_shift or input_event.right_shift) else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', '7')),
                left_shift = True,
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == 'slash' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'd')),
            ),
        ]
        if input_event.button_pair[1] == 's' and input_event.left_command and input_event.left_control and (
            not input_event.caps_lock and
            not input_event.fn and
            not input_event.left_shift and
            not input_event.left_option and
            not input_event.right_control and
            not input_event.right_command and
            not input_event.right_option and
            not input_event.right_shift
        ) else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 's')),
            ),
        ]
        if input_event.button_pair[1] == 'd' and input_event.left_command and input_event.left_control and (
            not input_event.caps_lock and
            not input_event.fn and
            not input_event.left_shift and
            not input_event.left_option and
            not input_event.right_control and
            not input_event.right_command and
            not input_event.right_option and
            not input_event.right_shift
        ) else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'backslash')),
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == 'non_us_backslash' else
        [
            replace(
                output_event,
                button_pair = ButtonPair(('key_code', 'non_us_backslash')),
            ),
        ]
        if input_event.layout == 'ru' and input_event.button_pair[1] == 'backslash' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    output_events = tuple(chain(*[
        [
            replace(
                output_event,
                left_command = input_event.left_control,
                left_control = input_event.left_command,
                right_command = input_event.right_control,
                right_control = input_event.right_command,
            ),
        ]
        if input_event.button_pair[1] == 'tab' else
        [
            output_event
        ]
        for output_event in output_events
    ]))

    return output_events

def process_one_event(from_event: event_t) -> tuple[optimized_event_k, optimized_event_v] | tuple[None, None]:
    to_events = decide_what_to_do(from_event)
    assert len(to_events) == 1
    to_event = to_events[0]
    if to_event == from_event:
        return (None, None)
    return (optimize_input_event(from_event), optimize_output_event(to_event))

def get_buttons_list_bin_data() -> bytes:
    buttons_list_bin_data = b''
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

if __name__ == '__main__':
    with buttons_list_file_path.open('wb') as file:
        file.write(buttons_list_bin_data)

def get_buttons_list_json_data() -> list[Any]:
    assert buttons_list_bin_data is not None
    buttons_list_json_data = json.loads(buttons_list_bin_data)
    assert isinstance(buttons_list_json_data, list)
    return buttons_list_json_data
buttons_list_json_data = get_buttons_list_json_data()

def get_buttons() -> dict[str, Button]:
    buttons: dict[str, Button] = {}

    true_or_missing_keys : Final = {'not_from', 'not_to', 'unsafe_from'}
    must_present_keys : Final = {'label', 'data'}

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
                label=label_t(label),
                not_from=not_from,
                not_to=not_to,
                unsafe_from=unsafe_from,
                button_key=button_key_t(key),
                button_value=button_value_t(value),
                category=category_t(category),
            )

    return buttons
buttons = get_buttons()

modifiers = [
    'fn' if value == 'keyboard_fn' else value
    for value in [
        button.button_value
        for button in buttons.values()
        if button.category == 'Modifier keys'
    ]
]

AnnotatedButtonPair = Annotated[
    tuple[str, str],
    [
        (button.button_key, button.button_value)
        for button in buttons.values()
    ]
]

@dataclass(frozen=True)
class annotated_event_t:
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
    multitouch_extension_finger_count: PossibleFingerCountValues
    button_pair: AnnotatedButtonPair

if __name__ == '__main__':
    print('making decicions...')

    optimized_manipulators : dict[optimized_event_k, optimized_event_v] = {}

    for input_event_args in tqdm(
        product_with_len(
            *[
                all_values(attr_type)
                for attr_type in annotated_event_t.__annotations__.values()
            ]
        )
    ):
        input_event = event_t(*input_event_args)
        k, v = process_one_event(input_event)
        if k is not None and v is not None:
            optimized_manipulators[k] = v
            assert v.button_pair in all_values(AnnotatedButtonPair)

    def remove_duplicates(attr_name: str, possible_values: list[Any]) -> None:
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

    for attr_name, attr_type in event_t.__annotations__.items():
        if attr_name != 'button_pair':
            remove_duplicates(attr_name, [*all_values(attr_type)])


    # remove_duplicates('multitouch_extension_finger_count', [*all_values(PossibleFingerCountValues)])
    # remove_duplicates('layout', [*all_values(Layouts)])
    # for modifier in modifiers:
    #     remove_duplicates(modifier, [False, True])

    print(f'converting to json format')

    with open(__file__, 'rb') as this_file_file:
        this_file_data = this_file_file.read()
    
    this_file_hash = hashlib.sha256(this_file_data).digest().hex()

    whole_file = dict(
        title='auto generated',
        rules=[
            dict(
                description=this_file_hash,
                manipulators=[
                    {
                        'type': 'basic',
                        'from':{
                            manipulator_from.button_pair[0]: manipulator_from.button_pair[1],
                            'modifiers': {
                                'mandatory': [
                                    modifier
                                    for modifier in modifiers
                                    if
                                    not getattr(manipulator_from, modifier)[0]
                                    and getattr(manipulator_from, modifier)[1][0]
                                ],
                                'optional': [
                                    modifier
                                    for modifier in modifiers
                                    if getattr(manipulator_from, modifier)[0]
                                ],
                            },
                        },
                        'to': [
                            {
                                manipulator_to.button_pair[0]: manipulator_to.button_pair[1],
                                'modifiers': [
                                    modifier
                                    for modifier in modifiers
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
    with conf_file_path.open('w') as file_:
        json.dump(whole_file, file_, indent=4)

