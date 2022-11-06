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
