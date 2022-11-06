# An Introduction to Beats++

### Purpose/Features of Beats++:
 - Musical Notation has always been written by hand, and still is done so even in the age of computers.
 - Representing Musical Information in a way which is both intuitive to the user and the machine has never been done before.
 - Beats++ aims to represent music and Musical Notation in an efficient way, thus opening opportunities for developers and musicians to write better programs more efficiently than by using libraries written in existing languages.
 - The main purpose of Beats++ is for users to code musical pieces in an operation-friendly way, which can be modified and played back in ways convenient to the user.
 - One of the few languages which works with file formats like .midi, which are designed for music production, and provides file handling with said formats.
 - Since the language is written specifically for music operations, it removes unnecessary programs out of the equation, as opposed to using a library in an existing language.
 - The basic data types are pitch, duration and integer.
 - Derived Data Types like Measures, Chords, Arpeggios, and are created using the basic data types.
 - Includes methods inherent to music theory like Transpose, Arpeggiate and Chordify?, thus simplifying the process of composing.
 - Includes implicit operations like multiplication of the duration of a note, and incrementing and decrementing the pitch of a note.
 - Syntactic similarity to C to keep the learning curve in check for newcomers.
 - File extension .bpm


### Do’s and Dont’s:
 - Statically typed language.
 - Compiled not interpreted to allow for quick runtime execution. 
 - Light, clean syntax that is fast to write.
 - Efficiency favoured over conciseness as the language targets a specific use case.
 - Possible multithreaded support for simultaneous playback of multiple instruments.
 - No explicit scoping.
 - No global variables.
 - JavaScript module type imports.
 - Hard check for redundant (unused) variables and imports at compile time.
 - Strict prevention on any uninitialized variables at compilation.
 - Functions support return of multiple variables; both derived and primitive data types are passed and returned by value.

### Sample Programs
```
import io from ‘io’;

func start[None] returns [None] {
    pitch sample = 2;
    duration sample_duration = 4;
    
    <--Initializing the note-->
    Note sample_note1 = (sample,sample_duration);

    <--Another form of initialization-->
    Note sample_note2 = (-10,3); 
    
    <-- Simple operations on notes -->
    Sample_note2 ++;

<-- Playing the note through computer audio-->
    io.play[sample_note1];
    io.play[sample_note2];

    return [ ];
}
```

```
func start[None] returns [None] {
    Note note1 = (10, 2);
    Note note2 = (7, 3);
    Note note3 = (9,4);
    Note note4 = (12, 1);

    <-- A measure is a fixed duration, containing a group of notes , which can overlap with each other -->
    <-- Measure takes the total duration as an argument for initialization-->
    Measure measure1 = new Measure[6];  

    <-- Can add notes to a measure at different starting durations-->
    measure1.add[note1,0];
    measure1.add[note2,1];
    measure1.add[note3,2];
    measure1.add[note4,5];
           
    io.play[measure1];
    io.midi_out[measure1];
    return [];
}

```

# Beats++: A Tutorial

This tutorial is aimed to show the essential elements of Beats++, without going into too much detail so as to introduce the language. It also aims to demonstrate the musical operators and expressions included in the language.


## 1. Hello World

We begin with the classic hello world program, with a small twist, to showcase the Musical capabilities of Beats++

The best way to start experimenting with a programming language is to write programs in it. Conventional wisdom suggests we proceed by getting the phrase “Hello World” onto the screen as a first step. In Beats++, the program to achieve the same.

The following sample program prints the phrase “Hello World” to the console, and plays a sample note through the audio system.

```
import io from ‘io’;
func start[None] from returns [None] {
	io.log[“Hello World\n”];
	io.play[(10,2)];
}
```

To run this program an executable with the same name as the source file has to be generated via compilation. For compilation with the standard compiler the terminal command is as follows:

`b++ file-name.bpm`

This produces an executable file with the same name in the working directory i.e. “file-name.out”.
To run this file, use the command
`./file-name.out`
You should see the text _Hello World_ on the terminal, with the cursor moved to a new line.

In the above example, `start` is the name of a function that carries special meaning to the compiler. Note that this name does not start with an underscore (as mentioned in the naming rules), since it is NOT a user defined function. This function is the starting point of execution for the program. 

The first set of square brackets is to specify the argument list, i.e the input variables (and their corresponding datatypes) that the function expects, and the second set of square brackets is to specify the return types of any variables that the function `returns` (produces as output). Both of these sets of brackets contain the word `None` in the above example, signifying that the function takes no input arguments, and returns no values. 

The first line of the program,

`import io from ‘io’;`

tells the compiler to include the standard input/output library and all functions used by the program from it. This line is an almost omnipresent feature in most Beats++ source files.
For the hello world program, main (i.e., start) consists of only two statements.

The first,

`io.log[“Hello World\n”];`

A function is called by naming it, followed by a list of arguments enclosed by square brackets. The log function takes in either a string or variable of arithmetic data type and prints the value of the variable out to the terminal.

The second statement,

`io.play[(10,2)];`

is a glimpse into the musical functionality that is at the heart of Beats++.

It takes in a variable of datatype `Note`and plays the note through the audio system. Notes are discussed in detail in a subsequent section. 

## 2. For Loop

```
func start[None] returns[None] {
	pitch p = 0;
	int count = 0;
	Measure M = new Measure[3];
	for(; p <= 4; p++) {
		if(p != 1 && p != 2) {
			Note Note1 = (p, 1);
			M.add[Note1, count];
			count++;
        }
    }
}
```

The for statement is a loop that takes in an initial assignment expression for the loop variable, a termination condition and an update expression to be executed at the end of each operation. Note that all three of the above expressions are optional. If the termination condition evaluates to true at the end of an iteration the loop stops execution and transfers control to the next instruction.\
The above program constructs an arpeggio with base frequency corresponding to the relative zero pitch value. The above process can be achieved concisely using the `std.arpeggiate` library function.

An alternate, shorthanded version of the for loop is demonstrated by performing the musical function "chordify":

```
func start[None] returns[None] {
	Measure M = new Measure[3];
	for value in range[0,4]{
		if(value != 1 && value != 2){
			Note Note1 = (p,1);
			M.add[Note1, 0];
			if(value == 4)
				M.add[Note1, 0];
		}
	}
}
```
The keyword _value_ is reserved to access the iterator value within the body of the loop in this shorthand way of initialising the loop.

## 3. Sheet and Measure System
Sheets and Measures from the backbone of storage for musical notes in Beats++. Simply put, a Measure can be interpreted as a fixed length array of Notes whereas a Sheet can be thought of as a flexible length series of Measures, akin to a vector from C++.
The Note data type is the fundamental building block for the above derived data types. An example program demonstrating basic capabilities of the three is shown below.

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

The first three lines of `start` deal with the declaration of `Notes` to be fed into the measure. They make use of the relative-frequency constructor of `Note`, which takes in a `pitch` attribute corresponding to an absolute frequency through a mapping as the first argument and the duration for Note to play as the second argument. An alternative construction using absolute frequency in the form of a floating point number (datatype `freq`) may be used instead. 

The next block of code declares a `Measure` of fixed length and adds a couple of notes to it through the add function. The add function takes the note to be added as the first parameter, and a starting point to play as the second. No constituent note can exceed total measure time i.e. (start point + duration) for each note added must be within the range of the `Measure`.

Sheets combine Measures and other Sheets into a single, collective unit. The combination is done using the concatenation operator `+`. Each measure/sheet concatenated with a sheet is simply appended to the end of the underlying vector. The choice of structure of the `Measure` and `Sheet` datatypes is elaborated in the Appendix. 

As a footnote, the program demonstrates the overloaded versions of the `io.play` function that supports audio playback of each of the derived data types discussed in this section.

## 4. Musical Operators + Functions

```
import io from ‘io’;

func _piano_to_brass[Note Note_init] returns[Note]{
	<-- Accessing the frequency of the Note_init variable -->
	freq note_freq = Note_init._freq;
	duration note_duration = Note_init._duration;
	pitch shift = 5;
	<-- pitch(relative frequency) can be added to freq(absolute frequency)-->
	freq new_freq = note_freq + shift;
	Note Note_final = (new_freq,note_duration);
	return Note_final;
}

func main[None] returns [None] {
	Note Note1 = (0, 3);
	Note Note2 = _piano_to_brass[Note2];

	io.play[Note1];
	io.play[Note2];
}
```

A popular musical operation is the ‘transpose’ operation. This operation is usually performed on an entire musical composition, and involves the addition(or subtraction) of a constant pitch(relative frequency) from each note in the composition. The above example demonstrates this operation applied in a specific context(transposing a single note from piano to brass instrument). 

In the above example, the first part involves the function named `_piano_to_brass`. A function is an encapsulation of some programming logic, allowing this block of code to be re-used in a simple manner. The line `func _piano_to_brass[Note Note_init] returns [Note]` signifies to the compiler that the function is called ‘_piano_to_brass’, accepts a variable of datatype `Note` as input, and returns a variable of datatype `Note` as output.

 The first set of square brackets is to specify the argument list, i.e the input variables (and their corresponding datatypes) that the function expects, and the second set of square brackets is to specify the return types of any variables that the function ‘returns’ (produces as output). 
 
 The code between the curly brackets comprises the body of the function, i.e., the statements that execute as part of the function. The function demonstrates some of the musical operations that Beats++ provides. More of these operations are elaborated in the Appendix. 
 
 The line `<-- … -->` is a comment, used to explain the code, or add documentation. Comments are ignored by the compiler, and do not change the program execution. 
 
 The statement `return Note2` at the end of the function body denotes that the value of Note2 is the output that the function ‘returns’, the datatype of which must match the datatype mentioned in the return type list. 

In the `start` function, the Note variable Note1 is initialized. The next line involves a ‘function call’ to the ‘_piano_to_brass’ function. The variable Note1 is provided to input to the function, and the variable Note2 receives the output generated by the function. Note that the datatype of the input and output variables must match the ones defined in the function argument list and return type list. The final two lines are once again function calls to the function ‘play’, provided by the ‘io’ library.


## 5. File Handling (MIDI)

The MIDI (Musical Instrument Digital Interface) protocol is the universal standard in digital music to store musical notation. Beats++ has functionality to write from and write to a MIDI file. This means the users can export the notation written in Beats++ to other software, and also import notation from external software to make edits to. 

The following program shows how to import a MIDI file, make changes to the notation, and export it back to MIDI.

```
import io from ‘io’;

func start[None] from returns[None] 
{
	Note Note1 = (10, 2);
	Note Note2 = (7, 3);

	Sheet Song;

	Song = io.from_midi[“music.midi”];

	
	Song<0>.add[note1, 3];
	Song<1>.add[note2, 4];

	io.play
	io.to_midi[Song, "new_music.midi"]; 
	
	return[];
}

```

Here, we first define two notes which we want to add to the Song. After this, we declare a Sheet variable so that we can import a MIDI file to the program. 

MIDI Imports are done by using the `from_midi[]` method, a part of the io library. This method returns a Sheet variable, so we assign the return value to our “Song”.

After this, we access the measures contained inside the Sheet. These are accessed by `Song<i>` (starting with index 0), and thus we can use the “add” method to add the notes to the measures as desired (same as previous examples). This demonstrates how we can easily make changes to MIDI files in Beats++, which would otherwise require a different application to perform. 

After all changes have been made, we can export the Sheet to a new MIDI file using the method `to_midi`, which takes a Sheet to be written, and the MIDI file name to be written to as parameters.


# Beats++ Language Evolution

## Structure of the Measure and Sheet Datatypes

The structure of the Measure datatype was highly important, as it is the most basic component of a musical composition, and also needed to be structured in a way such that it would be easily compatible with the MIDI file format.

The initially planned structure for the Measure datatype was a dynamic array of 'Note' variables. However, we soon realized that this would prevent the possibility of multiple Notes playing simultaneously, which is a very important musical aspect. This lead to the final structure of the Measure datatype, which is a collection of notes, overlapping in time with each other, with a fixed total duration. This allows all the functionality required for musical operations and compositions.
```
Measure Measure1 = new Measure[4];
Measure1.add[NoteA, 0];
Measure1.add[NoteB, 0];
Measure1.add[NoteC, 3];
```
```
Measure1 (duration 4)⇒
---------------------------
|NoteA|NoteA|       |NoteC|
|NoteB|     |       |     |
---------------------------
```

The superposition operator was also a late addition to the Measure datatype, this allowed a lot of musical operations to be carried out with ease, and was a significant improvement.

A Sheet was designed as a dynamic array of Measures, which ties in very well with the structure of MIDI files and musical compositions. Initially, we had set the restriction that all the Measures comprising a Sheet would have to be of the same duration. However, this does not accurately represent a musical composition, as in rare cases, this duration may vary throughout the composition. Hence, this restriction was later omitted.

## Changes/Updates to Built in Datatypes:

The major datatypes in Beats++ are pitch, Note, Measure, and Sheet. These are unique to Beats++, and are the fundamental building blocks in using Beats++ as a musical programming language to create sophisticated musical compositions or even music-related software.Throughout the course of the language design, multiple iterations of these datatypes were necessary, and an inclusion of an extra datatype 'freq' was also necessary.

**Changes to the Note datatype**

The 'Note' datatype was initially only able to be initialized using 'pitch', which was a relative frequency denoted using a bounded integer range of (-100,100), with the base value 0 corresponding to ~261Hz(The note C4 in western musical notation). However, a more fine grained control over the frequency of a note is often desired in musical software,  though most instruments do not work this way. This was the motivation behind the addition of a new datatype 'freq' which could hold positive floating-point numbers, corresponding to an absolute frequency value in Hertz.

The Note datatype was also suitably modified, so that it could be initialized using a 'pitch' or 'freq' type value. This value is internally modified to an absolute frequency and stored and this absolute frequency value is what is used for all functionality of the Note datatype.

## Rules for identifiers:

Initial versions of Beats++ included some fairly routine naming conventions with usual rules like no identifier can begin with a digit and no special characters in the variable name.

Through the course of our experiences with various well-established languages, we felt a need for the identifier to take on a bigger role than just referencing a memory location.

A format that could give context to the programmer about the nature of the variable it holds proved to be a useful tool to speed up the code writing process.

Hence, we established the following set of naming conventions:

-   Identifiers for all primitive data types to begin with a lowercase letter.

-   Identifiers for derived/user-defined data types begin with an uppercase letter.

-   Identifiers for custom user-defined functions to begin with an underscore character.

## Removing redundancy:

A couple of core principles that were prominent throughout the development process were to limit redundancy in the syntax while maintaining readability. Clearly, there were multiple decisions where these principles motivated conflicting decisions. An example of this is found in our decision to remove the compulsory return statement (return[None]) from functions that do not return any values themselves. What eventually ruled in favour of this step was the fact that an explicit return statement at the end of the function could be removed without problems in compilation as the end of the function body could always be indicated by the end of its scope.

## Inclusion of Aliases

An opposing example in the readability-redundancy paradox was the inclusion of alias support for our data types using the replace keyword. While there is a world where the language can function without this support, the global reach in the form of a musician user base around the world convinced us of the need for aliases. The primary purpose of aliases is to enable musicians to rename frequencies and other musical terminology into a language of their choosing so that any programmer can configure his programs to the convenient language of choosing.


# Beats++ Rules and Examples

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

# Beats++ Examples

## 1. Writing Sheet Music
```
import io from ‘io’

func start[None] returns [None] {
	Note C4 = (0, 1);
	Note C4_l = (0, 2);
	Note D4 = (2, 1);
	Note D4_l = (2, 2);
	Note E4 = (4, 1);
	Note F4 = (5, 1);
	Note G4 = (7, 1);
	Note G4_l = (7, 2);
	Note A4 = (9, 1);
	<-- Line 1 -->
	Measure Line1 = new Measure[8];
	Line1.add[C4, 0];
	Line1.add[C4, 1];
	Line1.add[G4, 2];
	Line1.add[G4, 3];
	Line1.add[A4, 4];
	Line1.add[A4, 5];
	Line1.add[G4_l, 6];

	<-- Line 2 -->
	Measure Line2 = new Measure[8];
	Line2.add[F4, 0];
	Line2.add[F4, 1];
	Line2.add[E4, 2];
	Line2.add[E4, 3];
	Line2.add[D4, 4];
	Line2.add[D4, 5];
	Line2.add[C4_l, 6];

	<-- Line 3 -->
	Measure Line3 = new Measure[8];
	Line3.add[G4, 0];
	Line3.add[G4, 1];
	Line3.add[F4, 2];
	Line3.add[F4, 3];
	Line3.add[E4, 4];
	Line3.add[E4, 5];
	Line3.add[D4_l, 6];

	
	Sheet TwinkleStar;
    <-- Operator ‘+’ on two Measures concatenates them and returns a Sheet -->
    TwinkleStar = Line1 + Line2 + 2 * Line3 + Line1 + Line2;	
}

```
## 2. Writing Sheet Music: Optimised
```
import io from ‘io’
func _generateMeasure[Note Note1, Note Note2, Note Note3, Note Note4] returns[Measure] {

Measure newMeasure = new Measure[4];
	newMeasure.add[Note1, 0];
	newMeasure.add[Note2, 1];
	newMeasure.add[Note2, 2];
	newMeasure.add[Note2, 3];

	return newMeasure;
}

func _generateSheet[Measure Measure1, Measure Measure2] returns[Sheet] {
	
	Sheet Song;
	for(int i = 1; i <= 8; i++)
	{
		if(i % 2 =:= 0)
		Song = Song + Measure1;
		else
		Song = Song + Measure2;
	}
	return Song;
}

func start[None] returns [None] {

	Note Silence = (0.0, 1);
	Note B3 = (246.94, 1);
	Note A3 = (220.00, 1);
	Note G3 = (196.00, 1);
	Note D4 = (293.66, 1);
		
	<-- Using then function we created to make adding notes to a measure easier-->
	Measure Line1 = new Measure[4];
	Line1 = _generateMeasure[B3, A3, G3, A3];
	Measure Line2 = new Measure[4];
	Line2 = _generateMeasure[B3, B3, B3, Silence];
	Measure Line3 = new Measure[4];
	Line3 = _generateMeasure[A3, A3, A3, Silence];
	Measure Line4 = new Measure[4];
	Line4 = _generateMeasure[B3, D4, D4, Silence];
	Measure Line5 = new Measure[4];
	Line5 = _generateMeasure[B3, B3, B3, B3];
	Measure Line6 = new Measure[4];
	Line6 = _generateMeasure[A3, A3, A3, A3];


	
	Sheet Verse = Line1 + Line2 + Line3 + Line4 + Line1 + Line5 + Line6 + G3;

    Sheet Chorus = Line1 + Line2 + Line3 + Line4 + Line1 + Line5 + Line6 + G3 + D4;

    Sheet MaryLittleLamb = _generateSheet(Verse, Chorus);
}

```
## 3. Audio Output: "Playing" the Fibonacci Series
```
import io from ‘io’;

func _fibonacci[int length] returns[Measure M]{

	Measure M = new Measure[length];
	pitch p = 110;

	for(int i = 0; i < length; i++){
		Note New_note = (p, 1);
		M.add(New_note,i);
		p = p * 2;
	}
	return M;
}

func start[None] returns [None] {

	Measure Fib = new Measure[10];
	Fib = _fibonacci[10];
	io.play[Fib];
}

```
## 4. Chordify/Arpeggiate 
```
import io from ‘io’;
import std from ‘std’;

func start[None] returns [None] {

	Note Note1 = (10,1);
	Note Note2 = (12,1);
	Note Note3 = (14,1);

<-- Second parameter of chordify is an integer which specifies the type of chord(Major, Minor, 7th etc.) -->
<-- Chordify returns chord with same duration as Note -->

	Measure Measure1 = std.chordify[Note1,1];
	Measure Measure2 = std.chordify[Note2,1];
	Measure Measure3 = std.chordify[Note3,1];
	
	<-- Each measure is now of duration 1 with a chord(multiple notes) at the first position -->

	Measure1.append_blank[2];
	Measure2.prepend_blank[1];
	Measure2.append_blank[1]
	Measure3.prepend_blank[2];

	<-- Now each measure is of duration 3, and Measure(i) has the chord at position i -->
	
	<-- A progression is a group of chords in order, which is vastly seen across musical compositions, and can now be reused -->

    Measure Progression = Measure1 ++ Measure2 ++ Measure3;
}


```

## 5. `pitch` (relative) vs `freq` (absolute)
```
import io from 'io';

func start[None] returns [None] {

    Note A4_absolute = (440.00, 1); <-- freq datatype -->

    Note A4_relative = (10, 1);  <-- pitch datatype -->

    <-- both these are the same notes and sound exactly the same -->

    io.play(A4_absolute);

    io.play(A4_relative);

    <-- implicitly, the absolute frequency is stored in hertz for every note regardless of how it was defined -->

    io.log[A4_relative._freq]; <-- output of 440.00 -->
}
```

## 6. File Handling

*Reads in a musical composition as a MIDI file, and transposes the entire composition by a fixed interval, and writes the new composition to another MIDI file*
```

import io from ‘io’;

func _transpose_piano_to_brass[Note Note_init] returns [Note] {
	<-- Accessing the frequency of the Note_init variable →

	freq note_freq = Note_init._freq;
	duration note_duration = Note_init._duration;

	pitch shift = 5;

	<-- pitch(relative frequency) can be added to freq(absolute frequency)-->
	freq new_freq = note_freq + shift;
	Note Note_final = (new_freq,note_duration);

	return Note_final;
}
	
func start[None] returns [None] {

	Sheet Sheet1 = io.from_midi[‘sample.midi’];

	<-- Function as a variable -->
	f[Note]->[Note] alter_note_fn = _transpose_piano_to_brass;

    int sheetLength = Sheet1.length;
    for(int i = 0; i < sheetLength; i++) {

        <-- Sheet1[i] is a Measure-->
        <-- applyToAllNotes takes a function, which is applied on every note in the Measure. This functionality is provided, since iterating through Notes of a Measure isn’t straightforward-->

        Sheet1[i].applyToAllNotes[alter_note_fn];
    }	

    io.to_midi[‘sample_modified.midi’,Sheet1];
}

```


## 7. Generating an "Aalap"

```
import io from ‘io’;

#alias Aalap Measure 
#alias Swar Note 
#alias Sa 240.00 
#alias Re 270.00 
#alias Ga 300.00 
#alias Pa 360.00 
#alias Dha 400.00 
#alias Sa_up 480.00 

func start[None] returns [None] {
	
	Swar Sa = (Sa, 1);
	Swar Re = (Re, 1);
	Swar Ga = (Ga, 1);
	Swar Pa = (Pa, 1);
	Swar Dha = (Dha, 1);
	Swar Sa_up = (Sa_up, 1);
	
Aalap Aaroha = new Aaroha[6];
Aaroh.add[Sa, 0];
	Aaroha.add[Re, 1];
	Aaroha.add[Ga, 2];
	Aaroha.add[Pa, 3];
	Aaroha.add[Dha, 4];
	Aaroha.add[Sa_up, 5];


	Aalap A1 = new Aalap[6];

	<-- using a random formula to generate an aalap →
	int r = 3675;

	for(int i = 0; i < 6; i++)
	{
		r = (((r * 7621) + 1)/3276) % 6;
		A1.add[Aaroha[r], i];
    }
	
	io.play[A1];
}


```
## 8. Midi to Sheet Music

The sheet datatype is structured to be easily interfaced with MIDI files. However, the chosen structure also allows for easy interpretation of the 'Sheet' datatype as 'Sheet Music'

```
import io from ‘io’;

func start[None] returns [None] {

	Sheet Sheet1 = io.from_midi[‘sample.midi’];
	io.to_sheet[‘sheet.pdf’,Sheet1];

}
```
## 9. Live Playback
```
import io from ‘io’;

func start[None] returns [None] {

	Note N1 = (100.0,1);
	Note N2 = (200.0,1);
	Note N3 = (300.0,1);
	Note N4 = (400.0,1);
	Note N5 = (500.0,1);
	Note N6 = (600.0,1);
	Note N7 = (700.0,1);
	String Key = "";

	while(1)
    {

	    <-- Take an input from the user -->
        Key = io.readKey[]; 
        if(Key =:= "a")
            io.play[N1];
        elif(Key =:= "s")
            io.play[N2];
        elif(Key =:= "d")
            io.play[N3];
        elif(Key =:= "f")
            io.play[N4];
        elif(Key =:= "g")
            io.play[N5];
        elif(Key =:= "h")
            io.play[N6];
        elif(Key =:= "j")
            io.play[N7];
        elif(Key =:= "q")
            break;
    }
}
```
# Beats++ Criticism
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

# Conclusions and Lessons Learnt


The experience of designing a language was one of a kind. However, every conclusion we arrived at boiled down to the fact that at every step of the design, we faced a tradeoff. Every decision that was made had both pros and cons.

Once again, no language is perfect. It is impossible for the designers to structure a language to suit everyone's needs and it is solely up to the designers to choose how their language is written, and which group of individuals the language is built for.

A challenging part about having to design a language from scratch was that whatever "new" idea we came up with, wasn't original. Almost everything we could think of had already been done by someone at some point. Moreover, we've already been exposed to and closely working with multiple programming languages by now, and trying to create something new posed a bit of a problem because we were already so used to the other existing languages. Thus, our process started with listing features of existing languages which we liked, and pairing them with functionality that no other language provided.

Another huge challenge was the choice of structure of the non-primitive datatypes.

The structure of these datatypes had to be carefully designed, keeping in mind:

-   The implementation of the structure had to be possible, given the currently available tools available

-   It had to be well planned, so as to provide all of the functionality that was needed. For example, the 'Sheet' and 'Measure' datatypes were designed keeping in mind easy compatibility with MIDI files, as this is the predominant file format for all things music.

We discovered that one of the most difficult parts of language design was actually restricting it to a particular domain, while still retaining enough functionality and convenience to be an actual language, rather than a library. But we realised that having a very specific use case would always beg the question: "Why not use a library?". Musical languages are not the only victim. Libraries for scientific programming are widely available in languages like C++ and Python, but there still exist programming languages which are preferred by many over the libraries.

When a language is structured around a specific function, it evolves accordingly. More than the use of the language itself, this fact influences the design stage more. With every iterative update, we saw the language evolve organically. Here, redundancy was automatically avoided because of our focus on a specific part alone.


# Beats++ Appendix

# Lexical Conventions

## Comments

The characters <-- mark the start of a comment and it terminates with the characters -->
Beats++ only supports comments in a multi line fashion. Comments cannot be nested. The occurrence of comments within a string or character literals is restricted.
## Tokens

There are six classes of tokens encompassing identifiers, keywords, constants, string literals, operators, and other separators. Comments as described below are ignored by the compiler. Whitespace in the form of extra spaces, tabs, newlines etc. are also ignored except when they act as separators for tokens. Some white space is required to separate otherwise adjacent identifiers, keywords, and constants.

## Identifiers

An identifier is a combination of letters, digits and underscores. Identifiers are case sensitive and can be of any length. Identifiers must begin underscore or letter. There are certain rules established for identifiers based on the type of variable they are representing:

- Identifiers for primitive data types like pitch and duration begin with a lowercase letter.

- Identifiers for derived data types like Note, Measure etc. should begin with an uppercase letter.

- Identifiers for functional identifiers(Names of user-defined functions) must start with an underscore.

## Keywords

The following identifiers are reserved for the use as keywords, and may not be used otherwise:

- int
- class
- break
- if
- else
- elif
- alias
- return
- returns
- const
- float
- continue
- for
- new
- while
- func
- null
- import
- none
- auto
- from
- value
- in
- pitch
- duration
- Note
- Measure
- Sheet

## Constants

### Integer constants

Integer constants consist of a sequence of digits without any quotes encompassing them. The standard length for the integer data type is 32 bits. For indication of unsigned integer, as is required for our aliased data type pitch, a suffix of u or U after the digits shall suffice.

### Floating constants

A floating constant consists of an integer part, a fraction part and an optional type suffix, u or U. The integer and fraction parts both consist of a sequence of digits. Either the integer part, or the fraction part (not both) may be missing; The decimal point must be present. The type is determined by the suffix; U or u makes it unsigned float, a change necessary for the aliased-double data type freq(short for frequency).

# Meaning of identifiers

An identifier is a user defined name, which may refer to a function, class, or variable. These identifiers cannot be keywords, which are reserved by the compiler, and carry special meaning.

A variable is specified with a datatype and a storage class
The Naming conventions to be followed are :

- All identifiers are case sensitive
- All identifiers must begin with a letter (or underscore in case of user defined functions) and only include letters, underscores and numbers
- Identifiers have to start:
  - with an uppercase letter for derived data types (Note, Measure, Sheet)
  - with a lowercase letter for primitive data types (pitch, int, duration)
  - with an underscore character for functions
  - Add off examples from the examples wala submission for incorrect and correct variable names

## Storage Class

    The storage class determines the lifetime of the storage of the variable. By default, a variable has a storage class of 'local', which means the related storage will be discarded at the end of the scope in which it was declared(generally, the current function). By using the keyword 'heap' while declaring a variable, it will be stored on the heap(rather than the stack), and the variable will retain its memory and value until the variable is explicitly deleted using the 'delete' keyword.\
    Example:

```
func _example[None] returns [None] {
<-- This variable will be stored on the stack, destroyed when function exits -->
int a = 10;

<-- This variable will be stored on the heap, persists across function calls, and can be passed around. Destroyed only when the 'delete' keyword is used -->
heap int b = 2; 
}
```

## Basic Types

The primitive datatypes are int, pitch, freq, and duration.

- **_int_**: Variables declared as type 'int' can store integer values between (), corresponding to x bytes of storage
- **_pitch_**: Variables declared as type 'pitch' can store integer values between (-100, 100). This dataype corresponds to relative frequencies in musical notation, with the base frequency(pitch of 0) corresponding to the note 'C4' in western musical notation. This relative frequency is automatically converted to an absolute frequency value internally.
- **_freq_**: Variables declared as type 'freq' (frequency) can store positive floating point (decimal) numbers. This datatype is used to set the frequency(in Hz) for various operations and other datatypes.
- **_duration_**: Variables declared as type 'duration' can store positive integer values in the range(), bytes x. This is analogous to the datatype 'unsigned int' in languages like C. This datatype is mainly used to specify the length in time that a musical element will correspond to.(Refer to examples?)

- The memory sizes corresponding to the basic datatypes are machine and implementation independent.

## Derived Types

The derived types are 'Note, 'Measure', and 'Sheet'.

- **_Note_**: A Note is simply a tuple of (pitch/frequency, duration). This is the fundamental unit in a musical language. A note can be declared using a pitch or a frequency, and this determines the 'sound'?, while the duration determines the length in time for which the note will produce sound.
- **_Measure_**: A Measure contains a collection of notes, which may overlap with each other, and is of a fixed 'duration', which is set while declaring the Measure. The below example shows the usage of the Measure datatype, and provides a visualization for the structure of the same.

```
Note NoteA = (10, 2);
Note NoteB = (-1, 1);
Note NoteC = (5, 1);

Measure Measure1 = new Measure[4];
Measure1.add[NoteA, 0];
Measure1.add[NoteB, 0];
Measure1.add[NoteC, 3];
```

```
 Measure1 (duration 4) =>
---------------------------
|NoteA|NoteA|       |NoteC|
|NoteB|     |       |     |
---------------------------
```

- **_Sheet_**: A Sheet is a dynamic array of Measures, placed one after the other. A Sheet can be interpreted musically as an entire musical composition, which can be exported in a number of different ways. MIDI files are a predominant format in music production, the structure provided by the 'Sheet' data type (as a dynamic array of ‘Measure’ objects of varying duration) enables a proper interface to read and write from MIDI files.

- **_String_**: The String data type is implemented as self-extending integer array at the lowest level(akin to a vector in cpp). Each index in the array holds the ASCII code for the corresponding character. At the time of printing or logging to console, these codes are parsed back to their original characters. All arithmetic operators are valid on individual indices, provided the result remains a valid ASCII code.

## Functions as a Datatype

In Beats++, a function can be assigned to a variable, and this variable will now possess the same behavior as a variable of any other regular datatype. It can be passed and returned from functions. However, the function type variable cannot be used with the io library functions.

The syntax for defining a variable that contains a function is as follows:

- _f[Parameter type list]->[Return type list] variable_name = name_of_function;_

```
func _example[Note] returns[Measure]  {

<-- Function body -->

}

f[Note]->[Measure] function_variable = _example;
```

# Conversions

It is necessary, under some circumstances, for a variable of one data type to be converted to another datatype, during particular operations. This section covers these conversions

## Duration - int conversion

Since the datatype 'duration' is simply an unsigned integer, it is possible to convert a variable of type 'duration' to type 'int'. The value is unchanged and can now be represented in the new type.

## Measure - Song conversion

While using the concatenation operator '+', a Measure is automatically converted to a Sheet (dynamic array of Measures) of length 1, to enable concatenation (refer to the section on expressions for more details on the concatenation operator)

- Measure + Measure -> Sheet

- Sheet + Measure -> Sheet

```
Sheet Sheet1 = Measure1 + Measure2;

Sheet Sheet2 = Sheet1 + Measure1;

<-- This is incorrect usage -->

Measure Measurfe3 = Measure1 + Measure 2;
```

## Pitch - Frequency Conversion

The datatypes `pitch` and `freq` are closely related, as pitch simply corresponds to a relative frequency, relative to a base frequency of 261.63Hz (Note C4 in Western Musical Notation). Hence, variables of type 'pitch' can be converted to type of 'frequency', by converting the relative frequency value to an absolute frequency. This conversion is what allows the 'Note' datatype to be initialized using pitch or frequency.

For convenience, the typecasting for pitch to frequency will be implicit. Frequency cannot be typecast into pitch, since all frequencies do not correspond to a relative pitch.

Refrence: 
<a href="https://pages.mtu.edu/~suits/notefreqs.html"> Basic Music Notes and Frequencies </a>

Examples:

```
pitch sample_pitch = 0;

freq sample_freq = sample_pitch;<-- sample_freq gets value of 261.63Hz(The base frequency on the assumed relative scale -->

pitch sample_pitch2 = -3;

freq sample_freq2 = sample_pitch2;
<-- sample_freq2 gets value of 220.00Hz -->
```

```
<-- The pitch-frequency conversion allows a Note to be initialized using either one of the two datatypes -->

duration sample_duration = 2;

pitch pitch1 = 0;

freq freq1 = 261.63;


<-- All the below Notes are identical -->

Note Note1 = (pitch1, sample_duration);

Note Note2 = (freq1, sample_duration);

Note Note3 = (0, 2);

Note Note4 = (261.63, 2);
```

# Expressions

An expression is any valid unit of code that resolves to a value. An expression may
consist of one or more 'operands', and zero or more 'operators' to produce a value.

All the 'operators' are defined below in the remainder of this section. Each operator
can support a particular set of types for the operands, and some operators are 'overload
to support different operations. Depending on the types of the operands, each operator
decides the type of operation to apply.

The precedence of evaluation of the various operators is defined in section x.
Beats++ supports the following types of operators:

- Arithmetic
- Logical
- Musical

The 'operands' may be any valid variable, constant, or another sub-expression, as long a
the types of the variable, constant, or the sub-expression (after evaluation) are
supported by the operator in use.

## Relational Operators

- \<    Lesser than

- \>    Greater than

- \<=  Lesser than or equal to

- \>=  Greater than or equal to

Expressions using these operators all evaluate to either 0 (if the expression is false) or 1 (if the expression is true). The result's datatype is int by default. These operators require two operands, are grouped in a left-to-right fashion and multiple operators can't be used one after the other (i.e., `a > b > c` is not allowed). The relational operators can only be used only to compare two operands of the same data type. But the . operator helps bypass this particular restriction (as explained later).

## Equality Operators

- =:=  Equal to

- =/=  Not equal to

These operators are the same as the relational operators in all ways except for the fact that they have lower precedence than their relational counterparts (i.e., `a > b =/= c <= d` is parsed as  `(a > b) =:= (c <= d)`).

## The Dot (.) Operator

The . operator is used as a predecessor to the other relational and equality operators when one wants to compare just the values of the operands regardless of their datatype. This operator facilitates comparing just numerical values by overlooking the data type. For example, `400 .<= 880.00` would result in 1 (true).

## Logical Operators

### AND Operator

This operator groups left-to-right and evaluates to true only when both operands are true, and is false in all other cases.

Beats++ has two kinds of logical AND operators:

- **&**\
  This operator doesn't short circuit the expression and evaluates both sides or operands.\
  i.e., `(a > b) & (c++ < d)` will always increment `c` regardless of whether `a > b` evaluates to true or not. Note that this is not the same as the bitwise 'and' as defined in C like languages.

- **&&**\
  This is the short-circuit operator and evaluates the right-hand side only if the left-hand side evaluates to true first, otherwise, it directly sets the result to false.\
  i.e., `(a > b) && (c++ < d)` will only increment `c` if `a > b` evaluates to true, else the result will directly be set to false

### OR Operator

This operator groups left-to-right and evaluates to false only when both operands are false, and is true in all other cases.

Be**a**ts++ has two kinds of logical OR operators:

- |\
  This operator doesn't short circuit the expression and evaluates both sides or operands.\
  **i.e.**, `(a > b) | (c++ < d)` will always increment `c` regardless of whether `a > b` evaluates to false or not. Note that this is not the same as the bitwise 'or' as defined in C like languages.

- ||\
  This is the short-circuit operator and evaluates the right-hand side only if the left-hand side evaluates to false first, otherwise, it directly sets the result to true.\
  i.e., `(a > b) || (c++ < d)` will only increment `c` if `a > b` evaluates to false, else the result will directly be set to true

### NOT Operator

This operator negates the truth value of the expression that follows it. The `!` symbol is used for the NOT operator.

### Precedence of the operators

| Operator  | Associativity |
| --------- | :-----------: |
| < <= >= > | left to right |
| =:= =/=   | left to right |
| &&        | left to right |
| \|\|      | left to right |
| &         | left to right |
| \|        | left to right |

## Assignment Operators and Expressions

There are multiple assignment expressions, all of which are grouped from left to right. The following are the expressions supported:

`= *= /= -= %= += ++=`

All the above operators require compatible datatypes on both sides of the expression. The ++ operator is the superimposition operator which can only be used with the Measures data type.
An expression of the form _E1 op= E2_ is equivalent to _E1 = E1 op E2_.

For example:\
`a += c` is equivalent to `a = a + c`.\
`a` is reassigned the value of `a(old) + c`.

## Musical Expressions

### Concatenation

- In Beats++, two measures can be concatenated to form a resulting Sheet containing the information of the first two.

- The operator and usage for concatenation is as follows:

```
import io from ‘io’

fu start[None] returns [None] {
  Note Note1 = (20,2);
    Note Note2 = (-10,1);
  Note Note3 = (5,2);
    Measure Measure1 = new Measure[4];
    Measure1.add[Note1,0];
  Measure1.add[Note2,2];

    Measure Measure2 = new Measure[3];
  Measure2.add[Note3,1];

  Sheet Song;
    <-- Operator ‘+’ on two Measures concatenates them and returns a Sheet -->
    Song = Measure1 + Measure2;


  <-- Operation ‘+’ is typecasted/overloaded for Sheet+Measure, concatenates and returns a Sheet-->
  Sheet Song1 = Song + Measure1;
    <-- Also valid -->
    Sheet Song2 = Song1 + Song;
}
```

### Superimposition

- In Beats++, two measures of the same length can be superimposed, where notes of one measure are inserted as is into another measure.

- The syntax for superimposition is as follows:

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

- The result of the above snippet can be visualized as:

```
Measure1 (duration 4)⇒
---------------------------
|NoteA|NoteA|       |NoteC|
|NoteB|     |       |     |
---------------------------


Measure2 (duration 4)⇒
--------------------------
|      |NoteD|NoteD|NoteD|
|      |     |     |     |
--------------------------

Measure3 (duration 4)⇒
-------------------------
|NoteA|NoteD|NoteD|NoteD|
|NoteB|NoteA|     |NoteC|
-------------------------

```

### Addition of Pitches and Frequencies

- As mentioned before, relative pitches can be converted to frequencies, but not the other way around.

- Furthermore, the '+' operator is overloaded to support addition of pitches and frequencies.

- **Case 1:** \
  _frequency3 = frequency-expression1 + frequency-expression2_

  Here, the '+' operator is overloaded to add the two frequencies to result in a total sum (similar to floating point addition)

- **Case 2:** \
  _pitch-expression3 = pitch-expression1 + pitch-expression2_

  Here, the '+' operator adds two relative pitches and gives a resulting pitch.

- **Case 3:** \
  _frequency-expression3 = pitch-expression1 + frequency-expression2_

  Here, the '+' operator typecasts pitch into frequency, and adds the two frequencies to get the resulting frequency.

- **Case 4:** \
  Any other combination of operator usage will not work due to the restrictions on typecasting.

  - This operation is also implicitly carried out when a variable of type `freq` or `pitch` is added to a variable of datatype `Note`.

## Function calls

A function call consists of the identifier for the function followed by square brackets, within which a comma-separated list of assignment expressions (possibly empty), which constitute the arguments to the function. If no declaration for the identifier exists within the scope of the call, it is searched for within the standard library as well as any imports made into the program. Example call:

_list-of-variables-to-store-return = function-identifier[list-of-arguments];_

**Note:** In case the function doesn't have a return value, the assignment component of the above statement shall be omitted.

The list of return variables shall be separated by commas and be in the order that is compatible with the return type of the function.

In preparing for the call to a function, a copy is made of each argument of primitive type. All argument-passing for the primitive data types is strictly by value. However, arguments of any derived data type are passed by reference to the original variable. This implies that changes made by the function to primitive arguments are independent of the original variables, whereas those made on derived data types are reflected in the original variables.

# Declarations

## Function Declarators

Functions declaration consist of three major components:

- Identifier name

- List of parameters

- List of return values

Each function declaration is preceded by the func keyword. This is followed by the identifier for the function.

Immediately after the identifier comes the list-of-arguments the function takes in. Each argument is separated from others by a comma and the list is wrapped in square brackets. The returns keyword is used to separate the argument list from the list of return values. Return values take the same form as the list for arguments i.e. comma separated and wrapped in square brackets. An empty set of square brackets is used to indicate no arguments or no return values. Following the return values are a pair of curly braces that encompass the function body. Each function must mark its end by the keyword return which is followed by the return value list, if any. Identifiers used for arguments in the function declaration are simply placeholders and are not bound to any actual variable within the scope and are thus free to use

- A function declaration of a function 'X' has the format:
  _func X[parameter list] returns [return type list] { <-- Function Body --> }_

- The parameter list has the format: datatype1 variable1, datatype2 variable2, ...

- Beats++ supports multiple return values from a single function. Hence, the need for a return type list is needed. The format for the same is : return_datatype1, return_datatype2, ...

- The datatypes of the variables returned via return statement at the end of the function body should match the datatypes mentioned in the return type list.

- If the function takes no parameters, or has no return values, then the keyword 'None' should be specified in the corresponding list during declaration.

## Variables

### String Declarations

Strings are declared via the _String_ keyword followed by identifier name. _String_ comes under the derived datatype umbrella and as per the naming conventions, the identifier for it has to begin with an uppercase character.\
There are two ways to initialize a _String_:

- Wrap text to be stored as string in single or double quotes. To include quotes in the string, use escape sequences " `'` ", " `"` "

- Use the `toString[]` function of _String_ class to pass an _int_ for conversion to corresponding single char from ASCII code.

### Example

```
<-- Initialize string with text enclosed hello world -->
String identifier-name = "Hello world";
```

```
<-- identifier-name gets assigned "a" in this case-->
String identifier_name = String.toString[65];
```

## Statements, External Declarations

### Compound Statements

The compound statements in Beats++ works exactly as it does in most other C-like languages.

Multiple statements when wrapped with curly braces {} are called a block and acts like a single statement. All function bodies are compound statements, as are loop and conditional statement bodies when there are more than one statements to be executed in its body.

### Selection Statements

Beats++ provides if, else and elif statements as conditional statements.

```
if (expression) {
<--statements-->
}
```

This is an if statement without a corresponding else statement. The statements inside it will only be executed if the expression evaluates to true, or is a non-zero or non-null value.

```
if (expression) {
<--statements-->
}
else {
<--statements-->
}
```

This is an if statement coupled with an else statement. The statements inside the if will only be executed if the expression evaluates to true, or is a non-zero or non-null value. If the expression evaluates to false, the statements inside the else will be executed.

```
if (expression) {
<--statements-->
}
elif (expression) {
<--statements-->
}
else {
<--statements-->
}
```

This is an if-elif-else ladder. There is no bound on the number of elif's allowed between the starting if and the ending else. It is also not compulsory to have an else statement in the end.

### Iterative statements

The syntax for the following loops are the same as C-like languages so there isn't much of a learning curve for new users of Beats++.

### **While Loops**

```
while (expression) {
<--statements-->
}
```

In the while loop, the statements in the body of the loop are executed repeatedly as long as the expression evaluates to true (or has a value other than 0 or null). The evaluation of the expression happens before every iteration or execution of the inner statements.

### **For Loops**

```
for (expression1; expression2; expression3) {
<--statements-->
}
```

Expression 1 specifies the initialisation for the loop and is evaluated only once, right before the first iteration of the loop.

Expression 2 is evaluated before each iteration and is analogous to the single expression in the while loop. Thus, the for loop is terminated if expression 2 evaluates to false.

Expression 3 is evaluated after each iteration, and acts like an update or re-initialisation statement for the loop.

None of the three expressions is compulsory and any of them may be dropped while using a for loop.\
Thus,

```
for ( ; ; ) {
<--statements-->
}
```

is also a perfectly valid loop.

An alternative shorthand way of initiating a for loops is possible via the `std.range[]` library function. The _range_ function isoverloaded to allow for an optional explicit step size. The lightweight version takes in two integer parameters: a begin and end value (both inclusive).
Default step size in 1. The alternative version takes in a third integer parameter to explicitly state the step size.
The keyword value is reserved and used to access value of the iterator at each iteration within the loop. It acts as a temporary integer under the hood.

```
for value in std.range(0,6){
  <-- loop body here -->
}
```

### Jump Statements

Beats++ provides two jump statements which can only be used inside loops: break and continue, and one jump statement which can only be used inside functions: return.

### **break**

This keyword is used to break out of a loop regardless of whether the loop's expression evaluates to false and passes the control to the block enclosing the loop.

### **continue**

This keyword is used to force the next iteration of a loop and skips all the statements following it for that particular iteration.

### **return**

This keyword is used by functions to return its caller. Beats++ allows functions to return multiple values (elaborated upon in the functions section). Having no return statement is equivalent to having a return statement not followed by any expression. The return keyword is classified as a jump statement because a function can only have one return statement and any statement or blocks following the return statement will be skipped.

# Scope Linkage

## Scoping 

The same identifier cannot be used for different purposes in the same scope, even if the usage could be different in the scope.

The lexical scope of a class or function identifier in an external declaration begins at the immediate end of its declaration and persists to the end of the translation unit in which it appears.

The scope of a parameter of a function definition begins at the start of the function and remains till the end of the function (but not outside the function, it ends at the end of the function declarator).

The scope of an identifier declared at the start of a function begins at the immediate end of its declaration, and remains till the end of the function (but not outside the function, it ends at the end of the function declarator).

If an identifier is explicitly declared at the head of a block, including the block constituting a function, any re-declaration of the identifier outside the block is suspended until the end of the block.

Blocks are identified by a pair of curly braces and may be nested within other blocks.

Overloading of the same identifer is prohibited even within an inner scope of original block in which the identifier was declared.

## Linkage

Within a translation unit, all declarations of the same object or function identifier with internal linkage refer to the same thing, and the object or function is unique to that translation unit that is destroyed on moving out of its scope. All declarations for the same object or function identifier with external linkage i.e imports refer to the same thing, and the object or function is shared by the entire program. For this purpose imports are made at the start of a program, outside of `start[]`. Imports are made in two ways: from pre-existing libraries or user-created packages (these are just files without a `start[]` and are meant to store custom classes and data type templates created by the user. For import from a standard library, the statement is as follows

`import library-name;`

For imports of specific functions/classes from a library:

_import function-name, class-name from library-name;_

Note that either of function-name and class-name can be omitted from the above statement. Also, multiple imports from the same library/package can be separated via the comma separator.

For imports from user-created packages, the library-name should be replaced by an absolute or relative path to the package from the working file's directory.

# Compiled vs Interpreted

Beats++ is built around the objective of providing musicians an easy pathway to produce sheet music and customise the "sheet" with great speed. Keeping the above in mind, one of the most important things to keep into account is low runtime. This is based on the motivation to make the execution of programs as fast and efficient as possible. Combined with the relatively lightweight syntax and lack of pointers, Beats++ proves to be a relatively easy language to debug. Combining the previous two conditions, Beats++ is made to be a compiled language, with executables produced on compilation characterised by the ".bpm" extension.

# Aliases

Aliases are user-defined names for pre-defined entities. Aliases always have to be defined right after the import statements and before writing any other lines of code. Alias assigns a name to any entity in the code, be it a numerical value or renaming a datatype to something new for the entire scope of the program.

Musicians are spread high and low over the world, and understandbly, musical terms are not universal. This functionality has been included for making Beats++ convinient to use for any musician in any language, so they can rename frequency values and other musical terms to something they are familiar with.

Example:
```
#alias Vibhag Measure <-- Renaming Measure to Vibhag -->
#alias Swar Note <-- Renaming Note to Swar -->
#alias Sa 480.00 <-- Assigning a double value of 480.00 to Sa -->

Swar Swar1 = (Sa, 2);
Vibhag V1 = new Vibhag[4];
V1.add[Swar1, 0];
```

