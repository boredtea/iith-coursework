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
