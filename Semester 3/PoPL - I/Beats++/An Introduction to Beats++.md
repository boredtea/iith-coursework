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