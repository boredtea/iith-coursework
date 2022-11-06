# Beats++: Rules and Examples

# Keywords

## List of keywords

- break, continue
- elif, else, if
- constant, static
- class
- func
- start
- for, while
- import, from
- null
- int
- return (at the end of a function)
- returns (in the function declaration)
- None

### Keywords specific to Beats++

- pitch: primitive
- freq: primitive
- duration: primitive
- Note: derived
- Measure: derived
- Sheet: derived

## Naming Conventions

- All identifiers are case sensitive
- Identifiers can be used to refer to primitive and derived data types, functions, or constants
- All identifiers must begin with a letter and only include letters, underscores and numbers
- Identifiers have to start:
  - with an uppercase letter for derived data types (Note, Measure, Sheet)
  - with a lowercase letter for primitive data types (pitch, int, duration)
  - with an underscore character for functions
- An identifier declared within an outer scope cannot be redeclared within an inner scope

# Examples

| Syntax                                                       | Validity |                                                                            Explanation |
| ------------------------------------------------------------ | :------: | -------------------------------------------------------------------------------------: |
| `pitch 3sample! = 5;`                                        |  Wrong   |  identifier can't start with a number <br> identifier can't include special characters |
| `pitch sample3 = 5;`                                         |  Right   |                                                                                      - |
| `Note Sample_note = (420, 69);` <br> `io.play[sample_Note];` |  Wrong   | note won’t play as case sensitivity implies ‘Sample_Note’ is a non-existent identifier |
| `Note Sample_note = (420, 69);` <br> `io.play[Sample_Note];` |  Right   |                                                                                      - |
| `int pitch = 256;`                                           |  Wrong   |                                          pitch is a keyword so cannot be an identifier |
| `int pitch_1= 256;`                                          |  Right   |                                                                                      - |
| `Measure sample_Measure1 = new Measure[6];`                  |  Wrong   |                                 derived data type has to start with an uppercase lette |
| `Measure Sample_Measure1 = new Measure[6];`                  |  Right   |                                                                                      - |
| `func _construct_fib[int length] returns[Measure]`           |  Right   |                                                                                      - |
| `func construct_fib(int length) return(Measure)`             |  Wrong   |      name of the function, return instead of returns, round brackets instead of square |
# Relational and Logical Operators

## Relational Operators

| Operator function                   |  Symbol       |
| ----------------------------------- | :-----------: |
| greater than                        |     >         |
| lesser than                         |     <         |
| greater than or equal to            |    >=         |
| lesser than or equal to             |    <=         |
| equal to                            |    =:=        |
| not-equal to                        |    =/=        |
| comparing over different data types | .\<operator\> |

## Logical Operators

| Operator          | Symbol |
| ----------------- | :----: |
| NOT               |   !    |
| AND               |   &    |
| OR                |   \|   |
| short circuit AND |   &&   |
| short circuit OR  |  \|\|  |

**NOTE:** Anything that’s not zero or not null evaluates to true. Default value of true: 1.

## Rules and Examples

Refer to this block of code for all the following examples:

```
freq a_4 = 440.00;
freq a_5 = 880.00;
int frequencies = 440;
Note Note1 = (9, 2); <-- Relative declaration of note frequency, corresponds to frequency of A4 = 440 Hz-->
Note Note2 = (880.0, 1); <-- Absolute declaration of note frequency in hertz -->
Measure Measure1 = new Measure[4];
Measure1.add[Note1, 0];
Measure1.add[Note2, 2];
```

1. The first six symbols, when used as they are can only make comparisons between two entities of the same datatype (e.g. between two pitches or durations).

| Syntax                | Validity |                                                 Explanation |
| --------------------- | :------: | ----------------------------------------------------------: |
| `a_4 <= a_5`          |  Right   |                                           evaluates to true |
| `Note2._freq =/= a_5` |  Right   |                                          evaluates to false |
| `a_4 =:= frequencies` |  Wrong   | results in an error because they are of different datatypes |

2. The . operator is added as a predecessor to the other relational operators when one wants to compare just the values of the operands regardless of the type.

| Syntax                   | Validity |                                                                                                Explanation |
| ------------------------ | :------: | ---------------------------------------------------------------------------------------------------------: |
| `a_4 .=:= frequencies`   |  Right   |                                                            evaluates to true despite being different types |
| `a_5 .< frequencies`     |  Right   |                                                           evaluates to false despite being different types |
| `a_4 .(=:=) frequencies` |  Wrong   |                                                  incorrect usage of the operator, no brackets are required |
| `a_4 .<= a_5`            |  Right   | will **NOT** result in an error because they are already the same type, the . operator makes no difference |

3. Precendence of the operators:

| Operator  | Associativity |
| --------- | :-----------: |
| < <= >= > | left to right |
| =:= =/=   | left to right |
| &&        | left to right |
| \|\|      | left to right |
| &         | left to right |
| \|        | left to right |

| Syntax                                | Validity |                                                                                                Explanation |
| ------------------------------------- | :------: | ---------------------------------------------------------------------------------------------------------: |
| `Note2._freq =:= a_5 .>= frequencies` |  Right   |                            evaluated as `Note2._freq =:= (a_5 .>= frequencies)`: finally evaluates to true |
| `Note2._freq >= a_5 && Note1._duration =/= Note2._duration || frequencies =:= a_5`|  Right   |                   doesn't throw an error due to short circuiting |
| `&& Note1.duration =:= Note2._duration`|  Wrong   |                                                     logical operators need two operands, this just has one |
| `Note2._freq >= a_5 & Note1._duration =/= Note2._duration | frequencies =:= a_5`  |  Wrong   | `frequencies =:= a_5` throws an error as there is no short-circuiting|


# Control Flow Statements

## Loops<hr>
Beats++ has supports two kinds of loops:
- For loops
- While loops
The syntax for these loops are similar to C-like languages so there isn’t much of a learning curve for new users of Beats++.

## For loops

**Example 1**<br>
_Correct:_
```
for(int i = 0; i < 10; i++)
{
    <--  Insert loop body here  -->
}
```
_Incorrect:_ commas used to separate loop statements instead of semicolons
```
for(int i = 0, i < 10, i++;)
{
    <--  Insert loop body here  -->
}
```
**Example 2**<br>
_Correct:_
```
int length;
for(length = 2; length < 10; length++)
{
    <--  Insert loop body here  -->
}
```
_Incorrect:_ the integer length has already been declared outside of the declaration for loop and hence cannot be declared twice in the same scope. Additionally, a semicolon cannot be put at the end of the for loop declaration.
```
int length = 2;
for(int length = 2; length < 10; length++);
{
    <--  Insert loop body here  -->
}
```
## While loops

**Example 3**<br>
_Correct:_
```
int length = 2;
while(length > 0)
{
    <--  Insert loop body here  -->
    length--;
}
```
_Incorrect:_ while loop declaration only takes a single conditional statement. 
```
while(int length = 2; length > 0; length--)
{
    <--  Insert loop body here  -->
}
```

## Conditional Statements<hr>
Beats++ only provides if, else and elif stateents as conditional statements.

**Example 4**<br>
_Correct:_
```
int a = 5;
if(a =:= 5)
{
	a = 2;
}
else 
{
	a = 3;
}
```
_Incorrect:_ stand alone else statement is incorrect
```
int a = 5;
else 
{
	a = 3;
}
```
**Example 5**<br>
_Correct:_
```
int a = 5;
if(a =:= 5)
{
	a = 2;
}
elif(a >= 5)
{
	a = 3;
}

```
_Incorrect:_ The elif keyword cannot be used without a condition
```
int a = 5;
if(a =:= 5)
{
	a = 2;
}
elif
{
	a = 3;
}
```

**Example 6**<br>
The break and continue statements have their usual functionality.<br>
_Correct:_
```
int length = 5;
while(length > 0)
{
    <--  Insert loop body here  -->
    if(length == 2)
        break;
    length--;
}
```
_Incorrect:_ The break statement can only be used to break out of loops, and not conditional statements.
```
int a = 5;
if(a =:= 5)
{
	a = 2;
}
else 
{
	a = 3;
    break;
}
```

# Musical Operators and Functions

1. Example of overloaded io and concatenation for measure, sheet and note. In a way, this example also demonstrates the **type casting** possible in Beats++.
```
import io from ‘io’

func start[None] returns [None] {
	Note Note1 = (20, 2);
	Note Note2 = (-10, 1);
	Note Note3 = (5, 2);
		
	Measure Measure1 = new Measure[4];
	Measure1.add[Note1, 0];
	Measure1.add[Note2, 2];

	Measure Measure2 = new Measure[3];
	Measure2.add[Note3, 1];
	
	Sheet Song;
    <-- Operator ‘+’ on two Measures concatenates them and returns a Sheet -->
    Song = Measure1 + Measure2;	


    <-- Operation ‘+’ is typecasted/overloaded for Sheet+Measure, concatenates and returns a Sheet -->
    Sheet Song1 = Song + Measure1;
    <-- Also valid -->
    Sheet Song2 = Song1 + Song;
    <-- io.play is overloaded to play all the datatypes through the hardware speakers -->
    io.play[Note1];
    io.play[Measure1];
    io.play[Song];
}
```

2. A measure is a datatype with fixed duration, containing a group of notes, whose durations can overlap with each other. **Superimposition** allows all the notes from two measures (of the same duration) to be added to a new measure, maintaining the same placement of each note. Here is a pictoral example to explain what superimposition looks like. <br>

```
Note NoteA = (10, 2);
Note NoteB = (-1, 1);
Note NoteC = (5, 1);
Note NoteD = (1, 3);

Measure Measure1 = new Measure[4];
Measure1.add[NoteA, 0];
Measure1.add[NoteB, 0];
Measure1.add[NoteC, 3];

Measure Measure2 = new Measure[4];
Measure2.add[NoteD, 1];

<-- Applying the superimposition operator on two Measures -->
Measure3 = Measure1 ++ Measure2;
```
**Measure1 (duration 4) ⇒**
```
---------------------------------
| NoteA | NoteA |       | NoteC |
| NoteB |       |      	|      	|
---------------------------------
```
**Measure2 (duration 4) ⇒**
```
----------------------------------
|       | NoteD | NoteD | NoteD |
|       |       |       |       |
----------------------------------
```
**Measure3 = Measure1 ++ Measure2 ⇒**
```
----------------------------------
| NoteA | NoteD | NoteD | NoteD |
| NoteB | NoteA |       | NoteC |
----------------------------------
```
**NOTE:** There is no upper bound on the number of measures that can be superimposed together

**Incorrect uses of the superimposition operator**
```
Measure Measure1 = new Measure[4];
Measure Measure2 = new Measure[5]; 
<-- Erroneous use of superimposition operator ‘++’, measures should be of same duration -->
Measure Measure3 = Measure1 ++ Measure2;
```
3. An arpeggio is a series of notes played up and down a musical scale. The std library contains similar functions inherent to musical notation. The following function uses the **arpeggiate** function.
```
import std from ‘std’;
func start[None] returns [None] {

    Note Note1 = (20,2);
	Measure Measure1 = new Measure[4];
    Measure Measure2 = new Measure[4];
	Measure Measure3 = new Measure[4];

	Measure1.add[Note1,0];          
	Measure2 = std.arpeggiate(Measure2, note1);
	
	<-- insert Measure2 in Measure1 where needed -->
    <-- in other words, superimpose -->
	Measure3 = Measure1 ++ Measure2;
}
```

4. A few examples of **note overflow** in a measure.

```
Measure Measure1 = new Measure[1];
Measure Measure2 = new Measure[2];
Note Note1 = (0, 2);

<-- Error, since duration of note exceeds duration of measure -->
Measure1.add[Note1, 0];

<-- Error, since duration of note will ‘overflow’ the duration of the measure -->
Measure2.add[Note1, 1];

<-- Both of the following are errors, since position does not exist in the measure -->
Measure1.add[Note1, 3];
Measure1.add[Note1, -1];
```

5. Beats++ has provisions to define a Note in two ways: using either the `pitch` or the `freq` keyword. <br>
- `pitch`: This assigns the Note a pitch that's relative to a base frequency (C4 by default ~ 262 Hz). Pitch takes on only integer values.
- `freq`: This assigns the Note an absolute frequncy in Hertz. Freq takes on decimal (double) values.
```
pitch pitch1 = -3;
freq freq1 = 223.2;
duration duration1 = 4;
<-- A Note can be initialized in two ways: using absolute frequency (freq) or relative to a base frequency (pitch) -->
Note Note1 = (pitch1, duration1);
Note Note2 = (freq1, duration1);

Note Note3 = (3, 4); <-- Relative -->
Note Note4 = (440.00, 4); <-- Absolute -->
```

6. MIDI files are a predominant format in music production, and we provide a structure called the 'Sheet' data type (as a dynamic array of ‘Measure’ objects of varying duration) to write to or read from a **MIDI file**.
```
import io from ‘io’;

func start[None] returns [None] {

    Sheet MySong;
    <-- Appending measures to the Sheet -->
    …
    …
    …
    io.to_midi[MySong];
}
```
7. In music, **transposition** refers to the process or operation of moving a collection of notes (pitches or pitch classes) up or down in pitch by a constant interval. <br>
This functionality is provided by the addition of a constant pitch to a Note.
```
<-- Initializing note with pitch (relative frequency) -->
Note Note1 = (10, 2);
pitch transposeAmt = 3;
<-- Note2 will now have pitch of 13. Equivalent to something like A ==> C in Western Musical Notation -->
Note Note2 = Note1 + pitch;
```
8. We offer provisions to access the frequency (in Hertz) and the duration (in seconds) of a Note after it has been initialised.
```
<-- Initializing notes in 2 ways, with pitch and frequency -->
Note Note1 = (-10, 2);
Note Note2 = (222.0, 3);<-- Implicit initialization with frequency -->

<-- dur1 will be equal to 2 -->
duration dur1 = Note1._duration;

<-- Note1 was initialized with pitch (relative frequency), which is implicitly converted to a frequency -->
<-- that is, _freq will return the absolute value of the note frequency in hertz regardless of how it was initialised -->

freq freq1 = Note1._freq;
freq freq2 = Note2._freq;
```


