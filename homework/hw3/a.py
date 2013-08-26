#!/usr/bin/env python
# -*- coding: utf-8 -*- 
 
import sys
import string
 
def v_sum(a,b):
    if (a == []):
        return []
    return [a[0]+b[0]]+v_sum(a[1:],b[1:])
 
 
def isa(c):
    return c == u'a' or c == u'A' or c == u'á' or c == u'Á'
 
def ise(c):
    return c == u'e' or c == u'E' or c == u'é' or c == u'É'
 
def isi(c):
    return c == u'i' or c == u'I' or c == u'í' or c == u'Í'
 
def iso(c):
    return c == u'o' or c == u'O' or c == u'ó' or c == u'Ó'
 
def isu(c):
    return c == u'u' or c == u'U' or c == u'ú' or c == u'Ú'
 
def process(s):
    if (s == ''):
        return [0,0,0,0,0]
    c = s[0]
    s_r = process(s[1:])
    return v_sum([int(isa(c)),int(ise(c)),int(isi(c)),int(iso(c)),int(isu(c))],s_r)
        
 
s = string.join(open(sys.argv[1]).readlines()).decode('utf-8')
arr = process(s)
print "a: %d \ne: %d\ni: %d\no: %d\nu: %d\n"%(arr[0],arr[1],arr[2],arr[3],arr[4])
