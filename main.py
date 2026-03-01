import os
import sys
import argparse


PROGRAM_VERSION = "1.0.0"


def build(args):
    if os.name == "nt":
        os.system(".\\BuildScript.cmd")
    else:
        os.system("./BuildScript.sh")

def clean(args):
    if os.name == "nt":
        os.system(".\\CleanScript.cmd")
    else:
        os.system("./CleanScript.sh")

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

