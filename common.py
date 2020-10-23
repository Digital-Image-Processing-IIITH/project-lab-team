import enum

PARAM_SIZE = 20
TAG_SIZE = 16

ACTIVE_GRAMMAR = 2

IS_DEBUG = 0

resolution = 2
matrix_resolution = 100
matrix_num = int(matrix_resolution * matrix_resolution)

class Shapes(enum.Enum):
    basic_shape = 0 
    tangle_shape = 1
    annotated_shape = 2
    animated_shape = 3
    time_shape = 4

class History(enum.Enum):
    linear_history = 0
    tree_history = 1
    animation_history = 2

class Grammars(enum.Enum):
    tangle_grammar = 0
    learning_grammar = 1
    animation_grammar = 2

class Transforms(enum.Enum):
    op_default = 0
    op_init = 1
    op_time_init = 2
    op_split = 3
    op_place = 4
    op_time_slice = 5
    op_affine = 6
    op_affine_rot = 7
    op_affine_tran = 8
    op_affine_scale = 9
    op_affine_rot_tran = 10
    op_affine_rot_scale = 11
    op_affine_scale_tran = 12
    op_move_towards = 13
    op_explode = 14
    op_attribute = 15

class Animation(enum.Enum):
    anim_eulerian = 0
    anim_perturb = 1
    anim_wave = 2
    anim_single = 3
    anim_group = 4
    anim_morph = 5
    anim_attribute = 6
    anim_noop = 7

class Sets(enum.Enum):
    union_op = 0
    difference_op = 1
    intersection_op = 2
    xor_op = 3
    sum_op = 4
    place_in_op = 5

