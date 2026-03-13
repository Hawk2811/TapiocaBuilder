# TapiocaBuilder
# main.py

import os
import sys
import engine
import argparse

PROGRAM_VERSION = "1.0"


def checkProjectLegacy():
    if os.name == "nt":
        if os.path.isfile(".\\BuildScript.cmd") == False:
            print("No TapiocaBuilder Project Found!")
            sys.exit(1)
        else:
            pass
    else:
        if os.path.isfile("./BuildScript.sh") == False:
            print("No TapiocaBuilder Project Found!")
            sys.exit(1)
        else:
            pass


def build(args):
    if os.path.isfile("./TapiocaBuilder.mak"):
        engine.run_make_engine("TapiocaBuilder.mak","build")
    else:
        checkProjectLegacy()
        if os.name == "nt":
            os.system(".\\BuildScript.cmd")
            print("Completed Script Execution!")
        else:
            os.system("./BuildScript.sh")
            print("Completed Script Execution!")

def clean(args):
    if os.path.isfile("./TapiocaBuilder.mak"):
        engine.run_make_engine("TapiocaBuilder.mak","clean")
    else:
        checkProjectLegacy()
        if os.name == "nt":
            os.system(".\\CleanScript.cmd")
            print("Completed Script Execution!")
        else:
            os.system("./CleanScript.sh")
            print("Completed Script Execution!")

commands = {
    "build": build,
    "clean": clean,
}



def create_parser():
    parser = argparse.ArgumentParser(prog="tapiocabuilder",description="Simple Build System")
    parser.add_argument("--version",action="version",version="TapiocaBuilder Version " + PROGRAM_VERSION)
    subparsers = parser.add_subparsers(dest="command")
    command_build = subparsers.add_parser("build",help="Build Project")
    command_build.set_defaults(func="build")
    command_clean = subparsers.add_parser("clean", help="Clean Project")
    command_clean.set_defaults(func="clean")
    args = parser.parse_args()
    if args.command in commands:
        commands[args.command](args)
    else:
        print("Invalid command try --help")
def main():
    create_parser()


if __name__ == "__main__":
    main()

