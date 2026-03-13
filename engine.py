# TapiocaBuilder
# engine.py


import os
import shutil
import subprocess


variables = {}
targets = {}
current_target = None


def read_file(path):
    with open(path, "r",encoding="utf-8") as f:
        return f.read().strip()
    
def normalize_path(path):
    return os.path.normpath(path)    

def parse_file(file):

    global current_target

    with open(file, "r", encoding="utf-8") as f:
        for raw_line in f:
            line = raw_line.strip()
            if not line or line.startswith("#"):
                continue
            # variables
            if line.startswith("$") and "=" in line:
                name, value = line.split("=", 1)
                name = name.strip()
                value = value.strip()

                if value.startswith("read("):
                    path = value.split('"')[1]
                    variables[name] = read_file(path)
                else:
                    variables[name] = value
                continue
            # targets
            if line.startswith(":"):
                current_target = line[1:].strip()
                targets[current_target] = []
                continue
            # command inside target
            if current_target is not None:
                targets[current_target].append(line)

def replace_vars(text):
    for k,v in variables.items():
        text = text.replace(k,v)
    return text

def get_executable_ext():
    if os.name == "nt":  # if Windows
        return ".exe"
    return ""  # If Unix-like(macOS, Linux,FreeBSD)

def cmd_copy(line):
    inside = line.split('"')
    src = replace_vars(inside[1])
    dst = replace_vars(inside[3])
    src = os.path.normpath(src)
    dst = os.path.normpath(dst)
    dirpath = os.path.dirname(dst)
    if dirpath != "":
        os.makedirs(dirpath, exist_ok=True)
    print("[COPY]", src, "->", dst)
    shutil.copy2(src, dst)

def cmd_write(line):
    inside = line.split('"')
    content = replace_vars(inside[1])
    file = replace_vars(inside[3])
    file = os.path.normpath(file)
    dirpath = os.path.dirname(file)

    if dirpath != "":
        os.makedirs(dirpath, exist_ok=True)
    print("[WRITE]", file)
    with open(file, "w", encoding="utf-8") as f:
        f.write(content)


def cmd_run(line):
    cmd = line.split('"')[1]
    cmd = replace_vars(cmd)
    print("[RUN]", cmd)
    subprocess.run(cmd, shell=True)

def cmd_compile_cxx(line):

    inside = line.split('"')
    src = replace_vars(inside[1])
    dst = replace_vars(inside[3])
    src = normalize_path(src)
    dst = normalize_path(dst)

    compiler = variables.get("$CXX")
    ext = get_executable_ext()
    # Add extension automatically if don't have one.
    if os.path.splitext(dst)[1] == "":
        dst = dst + ext
    dirpath = os.path.dirname(dst)
    if dirpath:
        os.makedirs(dirpath, exist_ok=True)
    print("[CXX]", src, "->", dst)
    subprocess.run(f"{compiler} \"{src}\" -o \"{dst}\"", shell=True)

def cmd_compile_c(line):
    inside = line.split('"')
    src = replace_vars(inside[1])
    dst = replace_vars(inside[3])
    src = normalize_path(src)
    dst = normalize_path(dst)

    compiler = variables.get("$CC",)
    ext = get_executable_ext()

    if os.path.splitext(dst)[1] == "":
        dst = dst + ext
    dirpath = os.path.dirname(dst)
    if dirpath:
        os.makedirs(dirpath, exist_ok=True)
    print("[CC]", src, "->", dst)
    subprocess.run(f"{compiler} \"{src}\" -o \"{dst}\"", shell=True)

def cmd_echo(line):
    text = line.split('"')[1]
    print(text)
def cmd_mkdir(line):
    directory = line.split('"')[1]
    directory = normalize_path(directory)
    print("[MKDIR] " + directory)
    os.mkdir(directory)

def execute(target):

    if target not in targets:
        print("No valid TapiocaBuilder Project Found!", target)
        return

    cmds = targets[target]

    for line in cmds:

        line = replace_vars(line)
        if line.startswith("copy"):
            cmd_copy(line[5:])
        elif line.startswith("write"):
            cmd_write(line)
        elif line.startswith("run"):
            cmd_run(line)
        elif line.startswith("compile-cxx"):
            cmd_compile_cxx(line)
        elif line.startswith("compile-c"):
            cmd_compile_c(line)
        elif line.startswith("echo"):
            cmd_echo(line)
        elif line.startswith("mkdir"):
            cmd_mkdir(line)


def run_make_engine(file,cli_target):
    parse_file(file)
    execute(cli_target)