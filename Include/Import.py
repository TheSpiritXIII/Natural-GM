import os, shutil

def copy_with_extension(source, dest, extension):
    for subdir, dirs, files in os.walk(source):
        for file in files:
            if file[-len(extension):]== '.hpp':
                shutil.copyfile(subdir + file, dest + file)

def ensure_dir(directory):
    d = os.path.dirname(directory)
    if not os.path.exists(directory):
        os.makedirs(directory)

ensure_dir('NGM/API/')
copy_with_extension('../Source/API/', 'NGM/', '.hpp')
copy_with_extension('../Source/Content/', 'NGM/', '.hpp')
copy_with_extension('../Source/Manager/', 'NGM/', '.hpp')