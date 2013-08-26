import os

filenames = os.listdir('./')

for filename in filenames:
    file = open(filename, 'r')
    file_lines = file.readlines()
    print filename, len(file_lines)
    
