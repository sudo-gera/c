for q in 'qwertyuiopasdfghjklzxcvbnm':
    w=r'''                            {
                                "conditions": [
                                    {
                                        "type": "variable_unless",
                                        "name": "multitouch_extension_finger_count_total",
                                        "value": 0
                                    },
                                    {
                                        "input_sources": [
                                            {
                                                "language": "ru"
                                            }
                                        ],
                                        "type": "input_source_if"
                                    }
                                ],
                                "from": {
                                    "key_code": "'''+q+r'''",
                                    "modifiers": {
                                        "optional": [
                                            "any"
                                        ]
                                    }
                                },
                                "to": [
                                    {
                                        "shell_command":"/opt/homebrew/opt/python@3.10/bin/python3 -c \"__import__('pynput.keyboard').keyboard.Controller().press('''+"'"+q+"'"+r''')\""
                                    }
                                ],
                                "type": "basic"
                            },'''
    print(w)