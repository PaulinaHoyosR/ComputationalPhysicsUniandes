import sys

def remove_not_letters(line):
    return ''.join([a for a in line if a.isalpha()])

#open and read the file
file = open(sys.argv[1],'r')
text = file.readlines()
file.close()

for line in text:
   nl = remove_not_letters(line)
   phrase = nl.upper()
   if(phrase[::-1]==phrase):
        print "true"
   else:
        print "false"
