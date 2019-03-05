#!/usr/bin/env python
# -*- coding: utf-8 -*- 

# REFERENCE: http://tuvalu.santafe.edu/~aaronc/powerlaws/

import sys
import os
from math import *
from random import *

# function x=randht(n, varargin)

# RANDHT generates n observations distributed as some continous heavy-
# tailed distribution. Options are power law, log-normal, stretched 
# exponential, power law with cutoff, and exponential. Can specify lower 
# cutoff, if desired.
# 
#    Example:
#       x = randht(10000,'powerlaw',alpha);
#       x = randht(10000,'xmin',xmin,'powerlaw',alpha);
#       x = randht(10000,'cutoff',alpha, lambda);
#       x = randht(10000,'exponential',lambda);
#       x = randht(10000,'lognormal',mu,sigma);
#       x = randht(10000,'stretched',lambda,beta);
#
#    See also PLFIT, PLVAR, PLPVA
#
#    Source: http://www.santafe.edu/~aaronc/powerlaws/


# Version 1.0.2 (2008 April)
# Copyright (C) 2007 Aaron Clauset (Santa Fe Institute)

# Ported to python by Joel Ornstein (2011 August)
# (joel_ornstein@hmc.edu)

# Distributed under GPL 2.0
# http://www.gnu.org/copyleft/gpl.html
# RANDHT comes with ABSOLUTELY NO WARRANTY
# 
# Notes:
# 
def randht(n,*varargin):
    Type   = '';
    xmin   = 1;
    alpha  = 2.5;
    beta   = 1;
    Lambda = 1;
    mu     = 1;
    sigma  = 1;


    # parse command-line parameters; trap for bad input
    i=0; 
    while i<len(varargin): 
        argok = 1; 
        if type(varargin[i])==str: 
            if varargin[i] == 'xmin':
                xmin = varargin[i+1]
                i = i + 1
            elif varargin[i] == 'powerlaw':
                Type = 'PL'
                alpha  = varargin[i+1]
                i = i + 1
            elif varargin[i] == 'cutoff':
                Type = 'PC';
                alpha  = varargin[i+1]
                Lambda = varargin[i+2]
                i = i + 2
            elif varargin[i] == 'exponential':
                Type = 'EX'
                Lambda = varargin[i+1]
                i = i + 1
            elif varargin[i] == 'lognormal':
                Type = 'LN';
                mu = varargin[i+1]
                sigma = varargin[i+2]
                i = i + 2
            elif varargin[i] == 'stretched':
                Type = 'ST'
                Lambda = varargin[i+1]
                beta = varargin[i+2]
                i = i + 2
            else: argok=0
        
      
        if not argok: 
            print '(RANDHT) Ignoring invalid argument #' ,i+1 
      
        i = i+1 

    if n<1:
        print '(RANDHT) Error: invalid ''n'' argument; using default.\n'
        n = 10000;

    if xmin < 1:
        print '(RANDHT) Error: invalid ''xmin'' argument; using default.\n'
        xmin = 1;




    x=[]
    if Type == 'EX':
        x=[]
        for i in range(n):
            x.append(xmin - (1./Lambda)*log(1-random()))
    elif Type == 'LN':
        y=[]
        for i in range(10*n):
            y.append(exp(mu+sigma*normalvariate(0,1)))

        while True:
            y= filter(lambda X:X>=xmin,y)
            q = len(y)-n;
            if q==0: break

            if q>0:
                r = range(len(y));
                shuffle(r)
                ytemp = []
                for j in range(len(y)):
                    if j not in r[0:q]:
                        ytemp.append(y[j])
                y=ytemp
                break
            if (q<0):
                for j in range(10*n):
                    y.append(exp(mu+sigma*normalvariate(0,1)))
            
        x = y
        
    elif Type =='ST':
        x=[]
        for i in range(n):
            x.append(pow(pow(xmin,beta) - (1./Lambda)*log(1.-random()),(1./beta)))
    elif Type == 'PC':
        
        x = []
        y=[]
        for i in range(10*n):
            y.append(xmin - (1./Lambda)*log(1.-random()))
        while True:
            ytemp=[]
            for i in range(10*n):
                if random()<pow(y[i]/float(xmin),-alpha):ytemp.append(y[i])
            y = ytemp
            x = x+y
            q = len(x)-n
            if q==0: break;

            if (q>0):
                r = range(len(x))
                shuffle(r)

                xtemp = []
                for j in range(len(x)):
                    if j not in r[0:q]:
                        xtemp.append(x[j])
                x=xtemp
                break;
            
            if (q<0):
                y=[]
                for j in range(10*n):
                    y.append(xmin - (1./Lambda)*log(1.-random()))


    else:
        x=[]
        for i in range(n):
            x.append(xmin*pow(1.-random(),-1./(alpha-1.)))

    return x
                              

# Below are main function to call randht
# print "脚本名：", sys.argv[0]
# for i in range(1, len(sys.argv)):
        # print "参数", i, sys.argv[i]
if __name__ == '__main__':
    #we want to generate a distribution following 20/80 rule
    x = randht(int(sys.argv[1]),'powerlaw', 0.8);
    for i in x:
        print i

