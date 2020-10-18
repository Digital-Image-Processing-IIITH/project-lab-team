# Proposal

## `Project Number`
### 16

## `Project Title`
### gTangle: a Grammar for the Procedural Generation of Tangle Patterns

## `GitHub Link`
### [https://github.com/Digital-Image-Processing-IIITH/project-lab-team](https://github.com/Digital-Image-Processing-IIITH/project-lab-team)

## `Team`
| Name   |      Roll Number      | 
|----------|:-------------:|
| Aryamaan Jain |  2019121002 | 
| Jyoti Sunkara |    2018101044 |  
| Ammar Ahmed | 2018101058 |  
| Aman Goel | 2018101005 |  

## `Main Goals`

To create an application that allows the users to generate tangles from a grammar and a set of geometric, grouping and decorative operators in an interactive and seamless manner. 

### Goals Within The Implementation

1. `Grammar`

In the implementation shapes are arbitrary two dimensional polygons with holes, where their boundaries are represented as highly-tessellated closed curves.
The core idea is that all the grammar operators work on groups of shapes, both in input and output. We aim to use code to represent tangle grammars which explicitly express the grouping information of every shape, in a way that this information is directly accessible and modifiable by specific operators.

2. `Operators`

We aim to code the compact set of operators that are efficient, closed under any set of arbitrary shapes, and that are able to encode a wide amount of variations in the generated tangles as proposed in the paper. There are several operators that work on the grammar and they are broadly divided into three types:

-  Grouping operators: Grouping between the drawn shapes, rearranging them in a meaningful manner, that can also be independent from the step at which such shapes were created.
    
    - Ungroup operator : Takes all shapes in S and assigns a new group id to each one.
    -  Regroup operator: Rearranges the shapes of a selected group into multiple newly created groups

-  Geometric operators: Subdivide shape groups by splitting, outlining and placing objects in them.
    - Regular Split
    - Geometric Outline
    - Streamline Split
    - Shape Placement

-  Decorative operators: Modify the final appearance of a shape, without further subdivisions.
    - Filling: Sets the background color of a shape
    - Stippling: Stipples the shape with geometrical details like dots, dashes, curves

3. `Shape Perturbation`

Simulating the organic feel of our generated tangles by applying a perturbation for all subdivided shapes.

4. `Web Application`

Here we seek to implemented the tangle grammar in a interactive system that is able to generate tangles automatically, starting from any initial set of shapes. This tool can be used both for the solely automatic generation of a tangle, following the expansion process described in the paper and for the editing of an already generated tangle, to better adapt the final result to the user’s likings.



### Three Interation Modes
- History Navigation

Allows user to move through the expansion history of a tangle by selecting a shape.

- Re-expansion

Allows the re-execution of a specific expansion step. 

- Parameters Modification

When an expansion step is selected, using history navigation, the user can interactively modify the parameters of the operator executed at that step.



### Features
- Dropdown list for grammar selection
- Preview of the tangle style achievable by the selected grammar
- Button used for starting the generation of a tangle
- Slider showing the current expansion step, that can also be used to visualize previous steps in the generation history
- Slider shows the step in which the selected shape was generated
- Buttons used to switch between the selection mode and the drawing mode, used to provide new curves for the re-execution of a rule
- Button used for the re-expansion
- Data relative to the rule that created the selected shape
- Sliders used for parameters modification

 


## `Problem Definition`

### What is the problem?
Tangles are a form of structured two dimensional art characterized by repeating, recursive patterns. The aim is to present an application to procedurally generate realistic tangle drawings controlled by users in an interactive and intuitive way. 

The tangles are formally modelled with group grammars that explicitly handle the grouping of shapes necessary to represent tangle repetitions. A small set of expressive geometric, grouping and decorative operators are used to show that they can respectively express complex tangles patterns and sub-pattern distributions, with relatively simple grammars.  We aim to validate the results of the paper which shows how group grammars can produce a wide variety of patterns in a few seconds which on the flip side would take artists hours of tedious and time consuming work. 

### How things will be done?
// TODO

## `Results`
### What will be done?
// TODO

### Final outcome

An interactive system that is able to generate tangles automatically, starting from any initial set of shapes. This tool can be used both for the solely automatic generation of a tangle, following the expansion process described in the paper and for the editing of an already generated tangle, to better adapt the final result to the user’s likings.


## `Milestones And Timeline`

| Milestone   |      Date     | 
|----------|:-------------:|
| Coding the grammar |  20 October 2020 | 
| Grouping Operators |  22 October 2020 | 
| Geometric Operators |  24 October 2020 | 
| Decorative Operators |  26 October 2020 | 
| Shape Perturbation |  29 October 2020 | 
| Mid Project Evaluation |  31 October 2020 | 
| History Navigation mode |  3 November 2020 | 
| Re-expansion mode |  6 November 2020 | 
| Parameters Modification mode |  9 November 2020 | 
| Web application features |  12 November 2020 | 
| Final Project Evaluation |  19 November 2020 | 

## `Obtaining Dataset`

A dataset of grammars to generate the tangles is required for the implementation of the proposed algorithm.

A set of images showing the preview of the tangle style achievable by the selected grammar is required for display on the interface of the web application.

### Obtaining the datasets?

// TODO





