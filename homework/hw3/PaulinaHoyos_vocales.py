#Get name of the input file.
import sys
filename = sys.argv[1]

#open and read the file
file = open(filename,'r')
text = file.readlines()
file.close()

#variables
n_a = 0
n_e = 0
n_i = 0
n_o = 0
n_u = 0

#count the vowels
for i in text:
    for j in i:
        if(j=='a' or  j=='A'):
            n_a=n_a+1
        elif(j=='e' or j=='E'):
            n_e = n_e + 1 
        elif(j=='i' or j=='I'):
            n_i = n_i + 1  
        elif(j=='o' or j=='O'):
            n_o = n_o + 1
        elif(j=='u' or j=='U'):
            n_u = n_u + 1   

#print in screen
print 'a ',n_a, "\n", 'e ', n_e, "\n", 'i ', n_i, "\n", 'o ', n_o, "\n", 'u '. n_u
