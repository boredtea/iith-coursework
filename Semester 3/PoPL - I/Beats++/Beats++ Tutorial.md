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



