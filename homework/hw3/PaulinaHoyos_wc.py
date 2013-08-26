import os
filenames = os.listdir(os.getcwd())

for filename in filenames:
    file = open(filename, 'r')
    file_lines = file.readlines()
    print filename, len(file_lines)
    file.close()
