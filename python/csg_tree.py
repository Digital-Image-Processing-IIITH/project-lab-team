class NodeContent():
	def __init__(self, shapes = []):
		self.shapes = [shapes]


class Node():
	def __init__(self, shapes = []):
		self.parent = None
		self.content = NodeContent(shapes)
		self.node_tag = -1


class OpNode(Node):
	def __init__(self):
		self.child_left = None
		self.child_right = None
		self.op_type = None


class LeafNode(Node):
	def __init__(self):
		self.copies = None


class Tree():
	def __init__(self, nodes=[], leaves=[]):
		self.node_id = 0
		self.root = None
		self.nodes = nodes
		self.leaves = leaves


def AddShape(tree, shape);
	node = LeafNode()
	node.node_tag = get_node_id(tree)
	noceC = NodeContent(shape)
	node.content = nodeC
	AddNode(tree, node)
	return node


def CopyNode(tree, a):
	copy = LeafNode()
	copy.content = NodeContent(a.content.shapes)
	a.copies.append(copy)
	return copy	

def Sum(tree, a, b, update):
	pass

def Union(Tree* tree, Node* a, Node* b, bool update):
	pass

def Difference(tree, a, b, update):
	pass

def Intersection(tree, a, b, update):
	pass

def XOR(tree, a, b, update):
	pass

def PlaceInShape(tree, a, b, update):
	pass
    
def UpdateLeafNode(tree, a, anim, delta, update):
	pass

def UpdateLeafNode(tree, a, anim, current_time, incr, total_dur, update):
	pass

def UpdateLeafNode(tree, a, anim, frame, update):
	pass

def UpdateContent(tree, a):
	pass

def UpdateTree(tree):
	pass

def PropagateContent(tree, a):
	pass
    
def UpdateOpNode(tree, a):
	pass
    
def AddNode(tree, node):
	pass

def AddNode(tree, node):
	pass
    
def FindNode(tree, shape):
	pass
    
def BuildResult(tree, shapes, a, b):
	pass
    
def get_node_id(tree):
	pass