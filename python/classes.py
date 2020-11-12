class Rule:
    def __init__(self,op,p,tm):
        self.op=op
        self.p=p
        self.tm=tm
class Type_:
  def __init__(self,type_,terminal):
      self.type_=type_
      self.terminal=terminal

class shape:
  def __init__(self,shape):
      self.shape=shape

class group:
  def __init__(self,group):
      self.group=group

class theta:
  def __init__(self,curves):
      self.curves=curves

class D:
  def __init__(self,orientation):
      self.orientation=orientation

class gTangle():
    def __init__(self,type_,group,shape):
        self.type_=type_
        self.shape=shape
        self.group=group

        self.groupval=100
        # self.theta=theta
        # self.D=D
        # self.pqueue=sorted(self.group)
    def mingroup(self):
        ming=100000000
        mint=0
        mins=0
        for i in range(len(self.group)):
            if self.group[i]<ming and self.type_[i].terminal==0:
                ming = self.group[i]
                mint = self.type_[i]
                mins = self.shape[i]
        return mint,ming,mins
        #pqueue<Gtangle> Queue on the basis of g

