# Criticism of Beats++:
No language is perfect. Beats++ is no exception to the rule. Since it is built with a very specific use case in mind, a few compromises are made, some of which are listed below:



## Sparse data type support
Music oriented data types such as Note, Measure and Sheet are central to the working of programs. Rudimentary arithmetic data types play a supporting role in condition evaluation and iteration statements. Hence, there are only two arithmetic data types of fixed bit size- int and double. This is a flexibility constraint for the programmer and also a compromise on efficiency in cases where a smaller bit-width data type would be sufficient.


## Confused Declaration in few cases: 

### Declaration of a Note:
        Note Note1 = (Note1_pitch, Note1_duration);
        
### Declaration of a Measure: 
        Measure Measure1 = new Measure[Measure1_Duration];

Both Note and Measure are derived data types in the language, but the declaration of one of them(Measure) is done using the keyword ‘new’ but this is not the case with the other one (Note).



## Purely procedural
- Classes are omitted from Beats++ as there is very limited use for the same within the confines of the language. However, in the occasional program where a need to combine functions with a group of variables is felt, there will have to be a degree of redundancy admitted by way of writing the variable groups and functions separately.
- In addition access control of functions to operate on specific variables will be difficult to achieve (here we are talking about variables with the same datatype, that would be indistinguishable to a function from an access standpoint).



## Lack of shorthand operations 
The language does provide a nice way to represent music but it can get tedious in a few cases. 
<br>For Example:
- If we want to declare an already existing note(meaning with the same pitch) but with a different duration, the whole note has to be declared again. There is no shorthand operation to copy the previous note and modify it.
- While adding notes to the measure, each note has to be added individually, using the add operation,  and there is no direct shorthand concatenation method.



## Lack of redeclaration support:
A decision made largely for increased readability, identifiers aren’t allowed a re-binding to a new variable on progression of program control to an inner scope. A minor hitch, but an inconvenience for programmers who are used to an allowance for the same.



## Lack of explicit data types for ‘chords’ and ‘arpeggios’
'chords' and ‘arpeggios’ are very crucial parts to musical compositions. 
A decision was taken to provide usage of these ‘chords’ and ‘arpeggios’ through Measures, but this comes with its own inconveniences, namely slightly terse and unwieldy usage.
