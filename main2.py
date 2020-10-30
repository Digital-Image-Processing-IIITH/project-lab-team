import numpy

# from operators import *
from classes import *
import random

tanglelist=[]

# from svgpathtools import svg2paths

# paths, attributes = svg2paths('./svg/quads.svg')


groupval=100

def ungroup(tangle,shape,rule):
    # group=tangle.mingroup()
    t,g,s=0,0,0
    for i in range(len(tangle.shape)):
        if(tangle.shape==shape):
            t=tangle.type_
    tangle.groupval+=1
    return t,tangle.groupval,shape

    

def regroup(shape,rule):
    pass
    # tigi = calcregtigi(shape,rule)
    

def regsplit(shape,rule):
    pass

def outline(shape,rule):
    pass

def streamsplit(shape,rule):
    pass

def place(shape,rule):
    pass


operations={
    'ungroup':ungroup,
    'regroup':regroup,
    'regsplit': regsplit,
     'outline':outline,
     'streamsplit':streamsplit,
     'place':place
     }



rules=[]
rules.append(Rule('ungroup',[],'0'))
# rules.append(Rule('regsplit',['line',90,1],'0'))
# rules.append(Rule('regroup',[3],'0'))
# rules.append(Rule('outline',[25],'0'))
# rules.append(Rule('streamsplit',[0,30],'0'))
# rules.append(Rule('place',[20,25],'0'))


type_=[Type_('0',0),Type_('0',0)]
group=[0,0]
shape=[0,1]


T=gTangle(type_,group,shape)
 

print(T.shape,T.group)
def expand(tangle):
    type_,group,shapes=tangle.mingroup()
    rtype=[]
    for rule in rules:
        if rule.tm==type_.type_:
            rtype.append(rule)
    rchoice=random.choice(rtype)
    Sn=[]
    Tn=[]
    Gn=[]
    for shape in tangle.shape: 
        a,b,c =ungroup(tangle,shape,rchoice)
        if b>100:
            a=Type_(str(a),1)
        else:
            a=Type_(str(a),0)
        Tn.append(a)
        Gn.append(b)
        Sn.append(c)
        
    # tangle.shape= tangle.shape -  shapes + Sn
    newtype_=[]
    newgroup=[]
    newshape=[]
    for i in range(len(tangle.shape)):

        if(tangle.shape[i] not in Sn):
            newtype_.append(tangle.type_[i])
            newgroup.append(tangle.group[i])
            newshape.append(tangle.shape[i])
    # print("sn is ",len(Sn))




