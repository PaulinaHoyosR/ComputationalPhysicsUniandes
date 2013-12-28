#!/usr/bin/python
#encoding: UTF-8
import sys, codecs

#open and read the file
file = codecs.open(sys.argv[1], "r", "utf8")
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
        if(j==u'a' or  j==u'A' or j==u'á' or j==u'Á'):
            n_a=n_a+1
        elif(j==u'e' or j==u'E' or j==u'é' or j==u'É'):
            n_e = n_e + 1 
        elif(j==u'i' or j==u'I' or j==u'í' or j==u'Í'):
            n_i = n_i + 1  
        elif(j==u'o' or j==u'O' or j==u'ó' or j==u'Ó'):
            n_o = n_o + 1
        elif(j==u'u' or j==u'U' or j==u'ú' or j==u'Ú'):
            n_u = n_u + 1   

#print in screen
print 'a ',n_a, "\n", 'e ', n_e, "\n", 'i ', n_i, "\n", 'o ', n_o, "\n", 'u ', n_u
