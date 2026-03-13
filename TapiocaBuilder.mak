# TapiocaBuilder Makefile


:build
run "pyinstaller main.py --onefile --icon program_icon.ico -n TapiocaBuilder"

:clean
run "rd /s /q build"
run "rd /s /q dist"
run "del TapiocaBuilder.spec"